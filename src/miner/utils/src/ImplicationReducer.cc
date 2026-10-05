#include "ImplicationReducer.hh"

#include <algorithm>
#include <cstdint>
#include <deque>
#include <functional>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <unordered_map>

#include <spot/tl/formula.hh>
#include <spot/tl/parse.hh>
#include <spot/twa/twagraph.hh>
#include <spot/twa/bdddict.hh>
#include <spot/twa/formula2bdd.hh>
#include <spot/twaalgos/isdet.hh>
#include <spot/twaalgos/postproc.hh>
#include <spot/twaalgos/translate.hh>
#include <spot/tl/ltlf.hh>

#include "Assertion.hh"
#include "CoiInfo.hh"
#include "PropositionCanonicalizer.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Constant.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/temporal/temporal.hh"
#include "globals.hh"
#include "message.hh"

namespace harm {
using namespace expression;

std::string toString(Implication i) {
  switch (i) {
  case Implication::Equivalent:
    return "EQUIVALENT";
  case Implication::AImpliesB:
    return "A_IMPLIES_B";
  case Implication::BImpliesA:
    return "B_IMPLIES_A";
  case Implication::None:
    return "NONE";
  case Implication::Skipped:
    return "SKIPPED";
  }
  return "?";
}

namespace {

// ---------------------------------------------------------------- atoms (maximal non-boolean)
/// the items of a boolean connective, or nullptr if 'p' is an atom
const std::vector<PropositionPtr> *connectiveItems(const PropositionPtr &p,
                                                   std::string &op) {
  if (auto x = std::dynamic_pointer_cast<PropositionAnd>(p)) {
    op = "&";
    return &x->getItems();
  }
  if (auto x = std::dynamic_pointer_cast<PropositionOr>(p)) {
    op = "|";
    return &x->getItems();
  }
  if (auto x = std::dynamic_pointer_cast<PropositionXor>(p)) {
    op = "^";
    return &x->getItems();
  }
  if (auto x = std::dynamic_pointer_cast<PropositionEq>(p)) {
    op = "<->";
    return &x->getItems();
  }
  if (auto x = std::dynamic_pointer_cast<PropositionNeq>(p)) {
    op = "^";
    return &x->getItems();
  }
  if (auto x = std::dynamic_pointer_cast<PropositionNot>(p)) {
    op = "!";
    return &x->getItems();
  }
  return nullptr;
}

void collectAtoms(const PropositionPtr &p, std::vector<PropositionPtr> &atoms) {
  std::string op;
  if (auto items = connectiveItems(p, op)) {
    for (const auto &i : *items) {
      collectAtoms(i, atoms);
    }
  } else if (std::dynamic_pointer_cast<BooleanConstant>(p) == nullptr) {
    atoms.push_back(p);
  }
}

/// the boolean skeleton of 'p' in Spot syntax, atoms replaced by their class tokens
std::string skeleton(
    const PropositionPtr &p,
    const std::unordered_map<const Proposition *, std::string> &tokens) {
  if (auto c = std::dynamic_pointer_cast<BooleanConstant>(p)) {
    return c->evaluate(0) ? "true" : "false";
  }
  std::string op;
  if (auto items = connectiveItems(p, op)) {
    if (op == "!") {
      return "!(" + skeleton((*items)[0], tokens) + ")";
    }
    std::string s;
    for (const auto &i : *items) {
      s += (s.empty() ? "(" : " " + op + " ") + skeleton(i, tokens);
    }
    return s + ")";
  }
  return tokens.at(p.get());
}

std::vector<PropositionPtr> leafPropositions(const TemporalExpressionPtr &te) {
  std::vector<PropositionPtr> leaves;
  traverse(te, [&](const TemporalExpressionPtr &current) {
    if (auto inst = std::dynamic_pointer_cast<BooleanLayerInst>(current)) {
      leaves.push_back(inst->getProposition());
    }
    return false;
  });
  return leaves;
}

// ---------------------------------------------------------------- HARM's finite-trace semantics
// D-004 as amended. Spot's infinite-word implication is not enough: HARM evaluates a mined
// assertion on a finite trace, and an instance still pending at the end counts as holding. The
// evaluator (AutomataBasedEvaluator) runs a deterministic Spot automaton of the consequent whose
// atoms are the boolean leaves, not the atoms inside them, so a violation that is certain at the
// atom level can be seen only some cycles later (e.g. 'X (b && !b)'). Hence the second check:
// an exact model of HARM's evaluation, explored over every finite trace.

/// the shared BDD dictionary and translators of one reduction
struct Context {
  spot::bdd_dict_ptr dict = spot::make_bdd_dict();
  spot::translator trans{dict};
  spot::translator det{dict};
  int owner = 0; // the address owns the variables registered here
  Context() { det.set_pref(spot::postprocessor::Deterministic); }
  ~Context() { dict->unregister_all_my_variables(&owner); }
};

/// how HARM evaluates G(antecedent |-> consequent) with a fixed-length boolean antecedent
struct HarmModel {
  std::vector<bdd> ant;   // the antecedent, one boolean step per cycle (atom level)
  bool overlap = true;    // the consequent starts on the last antecedent cycle
  unsigned init = 0;      // the consequent automaton (as in AutomataBasedEvaluator)
  std::vector<int> term;  // 0 pending, 1 accepting sink, 2 rejecting sink
  std::vector<std::vector<std::pair<bdd, unsigned>>> edges; // atom-level conditions
  // --trace-end sva (D-016): the consequent in LTLf, as in AutomataBasedEvaluator's
  // TraceEndModel; a pending instance fails at the end if its state here may not end the trace.
  // With --trace-end harm: one state, which may always end the trace
  unsigned init2 = 0;
  std::vector<std::vector<std::pair<bdd, unsigned>>> edges2{{{bddtrue, 0}}};
  std::vector<bool> endOK2{true};
};

/// the antecedent as one boolean step per cycle, starting at 'start'; false if not a fixed
/// sequence of boolean steps; returns the last cycle in 'end'
bool antecedentSteps(const TemporalExpressionPtr &te, int start,
                     const std::function<bdd(const PropositionPtr &)> &leafBdd,
                     std::vector<bdd> &steps, int &end) {
  if (start > 62) {
    return false;
  }
  if (auto inst = std::dynamic_pointer_cast<BooleanLayerInst>(te)) {
    if ((int)steps.size() <= start) {
      steps.resize(start + 1, bddtrue);
    }
    steps[start] &= leafBdd(inst->getProposition());
    end = start;
    return true;
  }
  if (auto c = std::dynamic_pointer_cast<SereConcat>(te)) {
    int e;
    return antecedentSteps(c->getItems()[0], start, leafBdd, steps, e) &&
           antecedentSteps(c->getItems()[1], e + (c->isOverlapping() ? 0 : 1),
                           leafBdd, steps, end);
  }
  bool intersect = std::dynamic_pointer_cast<SereIntersect>(te) != nullptr;
  if (intersect || std::dynamic_pointer_cast<SereAnd>(te) != nullptr) {
    // both operands start together; '&&' needs them to end together, '&' ends with the later
    end = start;
    for (size_t i = 0; i < te->getItems().size(); i++) {
      int e;
      if (!antecedentSteps(te->getItems()[i], start, leafBdd, steps, e) ||
          (intersect && i > 0 && e != end)) {
        return false;
      }
      end = std::max(end, e);
    }
    return true;
  }
  if (auto d = std::dynamic_pointer_cast<SereDelay>(te)) {
    auto w = d->getWindow();
    if (w.first != w.second) {
      return false;
    }
    auto &items = d->getItems();
    int from = start;
    if (items.size() == 2 &&
        !antecedentSteps(items[0], start, leafBdd, steps, from)) {
      return false;
    }
    if (items.size() == 1 && w.first > 0) {
      // '##n b' with nothing before: the first cycles are free
      if ((int)steps.size() <= start) {
        steps.resize(start + 1, bddtrue);
      }
    }
    return antecedentSteps(items.back(), from + (int)w.first, leafBdd, steps,
                           end);
  }
  return false;
}

/// HARM's model of 'te', or nullopt if 'te' is not G(antecedent |-> consequent) with a fixed
/// boolean antecedent (such assertions are never reduced)
std::optional<HarmModel> harmModel(
    const TemporalExpressionPtr &te,
    const std::unordered_map<const Proposition *, std::string> &tokens,
    Context &ctx) {
  auto always = std::dynamic_pointer_cast<PropertyAlways>(te);
  if (always == nullptr) {
    return std::nullopt;
  }
  auto imp =
      std::dynamic_pointer_cast<PropertyImplication>(always->getItems()[0]);
  if (imp == nullptr) {
    return std::nullopt;
  }
  bool ok = true;
  auto leafBdd = [&](const PropositionPtr &leaf) -> bdd {
    spot::parsed_formula pf = spot::parse_infix_boolean(skeleton(leaf, tokens));
    if (!pf.errors.empty()) {
      ok = false;
      return bddtrue;
    }
    return spot::formula_to_bdd(pf.f, ctx.dict, &ctx.owner);
  };
  HarmModel m;
  int end = 0;
  if (!antecedentSteps(imp->getItems()[0], 0, leafBdd, m.ant, end) || !ok) {
    return std::nullopt;
  }
  m.ant.resize(end + 1, bddtrue);
  m.overlap = imp->isOverlapping();

  // the consequent over its leaves, as HARM sees it
  TemporalExpressionPtr con = imp->getItems()[1];
  std::unordered_map<const Proposition *, std::string> subst;
  std::map<std::string, bdd> leafOf; // leaf atom -> its atom-level condition
  for (const auto &leaf : leafPropositions(con)) {
    std::string sk = skeleton(leaf, tokens);
    subst[leaf.get()] = "\"L:" + sk + "\"";
    leafOf.emplace("L:" + sk, leafBdd(leaf));
  }
  spot::parsed_formula pf =
      spot::parse_infix_psl(temp2StringSubst(con, Language::SpotLTL, subst));
  if (!pf.errors.empty() || !ok) {
    return std::nullopt;
  }
  auto aut = ctx.det.run(pf.f);
  spot::postprocessor post;
  post.set_pref(spot::postprocessor::Complete);
  aut = post.run(aut);
  if (!spot::is_deterministic(aut) || !spot::is_complete(aut)) {
    return std::nullopt;
  }
  bddPair *pair = bdd_newpair();
  for (const auto &[name, cond] : leafOf) {
    int v = ctx.dict->has_registered_proposition(spot::formula::ap(name),
                                                  aut);
    if (v >= 0) {
      bdd_setbddpair(pair, v, cond);
    }
  }
  unsigned n = aut->num_states();
  m.init = aut->get_init_state_number();
  m.term.assign(n, 0);
  m.edges.resize(n);
  for (unsigned s = 0; s < n; s++) {
    size_t outs = 0;
    bool selfLoop = false;
    for (auto &e : aut->out(s)) {
      outs++;
      selfLoop = e.dst == s;
      m.edges[s].emplace_back(bdd_veccompose(e.cond, pair), e.dst);
    }
    if (outs == 1 && selfLoop) {
      m.term[s] = aut->state_is_accepting(s) ? 1 : 2;
    }
  }
  if (clc::traceEnd == "sva") {
    // as AutomataBasedEvaluator::buildTraceEndModel, where a formula it cannot model keeps
    // HARM's semantics: here such an assertion is never reduced
    if (!pf.f.is_ltl_formula()) {
      bdd_freepair(pair);
      return std::nullopt;
    }
    const std::string alive = "harm_trace_alive";
    auto aut2 = post.run(ctx.det.run(spot::from_ltlf(pf.f, alive.c_str())));
    if (!spot::is_deterministic(aut2)) {
      bdd_freepair(pair);
      return std::nullopt;
    }
    for (const auto &[name, cond] : leafOf) {
      int v = ctx.dict->has_registered_proposition(spot::formula::ap(name),
                                                    aut2);
      if (v >= 0) {
        bdd_setbddpair(pair, v, cond);
      }
    }
    int av = ctx.dict->has_registered_proposition(spot::formula::ap(alive), aut2);
    auto dead = ctx.trans.run(
        spot::formula::G(spot::formula::Not(spot::formula::ap(alive))));
    unsigned n2 = aut2->num_states();
    m.init2 = aut2->get_init_state_number();
    m.edges2.assign(n2, {});
    m.endOK2.assign(n2, true);
    for (unsigned s = 0; s < n2; s++) {
      auto from = spot::make_twa_graph(aut2, spot::twa::prop_set::all());
      from->set_init_state(s);
      m.endOK2[s] = from->intersects(dead);
      for (auto &e : aut2->out(s)) {
        bdd cond = av < 0 ? e.cond : bdd_restrict(e.cond, bdd_ithvar(av));
        if (cond != bddfalse) {
          m.edges2[s].emplace_back(bdd_veccompose(cond, pair), e.dst);
        }
      }
    }
  }
  bdd_freepair(pair);
  return m;
}

/// a pending consequent instance: its state in HARM's automaton and in the LTLf automaton
using ConState = std::pair<unsigned, unsigned>;

/// the next state of a pending consequent instance; 'outcome' 2: failed, 1: held, 0: pending
ConState stepCon(const HarmModel &m, ConState c, const bdd &letter, int &outcome) {
  auto holds = [&](const bdd &b) { return (b & letter) != bddfalse; };
  outcome = 0;
  for (const auto &[cond, dst] : m.edges[c.first]) {
    if (holds(cond)) {
      outcome = m.term[dst];
      c.first = dst;
      break;
    }
  }
  for (const auto &[cond, dst] : m.edges2[c.second]) {
    if (holds(cond)) {
      c.second = dst;
      break;
    }
  }
  return c;
}

/// the pending instances of one assertion after a prefix of the trace
struct Pending {
  uint64_t ant = 0;          // bit k: an antecedent instance has matched k cycles
  bool startNext = false;    // a consequent starts on the next cycle (|=>)
  std::vector<ConState> con; // the pending consequent instances
  bool failed = false;       // an instance failed inside the trace

  std::string key() const {
    std::string k = std::to_string(ant) + (startNext ? "+" : "-");
    for (auto c : con) {
      k += "," + std::to_string(c.first) + "." + std::to_string(c.second);
    }
    return k;
  }
  /// fails if the trace ends now (--trace-end sva: a strong obligation is pending)
  bool failsAtEnd(const HarmModel &m) const {
    return failed || std::any_of(con.begin(), con.end(), [&](const ConState &c) {
             return !m.endOK2[c.second];
           });
  }
};

/// one cycle of HARM's evaluation on a letter (a class of atom valuations)
Pending step(const HarmModel &m, const Pending &p, const bdd &letter) {
  auto holds = [&](const bdd &b) { return (b & letter) != bddfalse; };
  Pending q;
  q.failed = p.failed;
  std::set<ConState> active(p.con.begin(), p.con.end());
  if (p.startNext) {
    active.insert({m.init, m.init2});
  }
  uint64_t positions = p.ant | 1; // an instance starts on every cycle
  size_t last = m.ant.size() - 1;
  for (size_t k = 0; k <= last; k++) {
    if ((positions >> k & 1) && holds(m.ant[k])) {
      if (k < last) {
        q.ant |= (uint64_t)1 << (k + 1);
      } else if (m.overlap) {
        active.insert({m.init, m.init2});
      } else {
        q.startNext = true;
      }
    }
  }
  std::set<ConState> next;
  for (auto c : active) {
    int outcome;
    ConState d = stepCon(m, c, letter, outcome);
    if (outcome == 2) {
      q.failed = true;
    } else if (outcome == 0) {
      next.insert(d);
    }
  }
  q.con.assign(next.begin(), next.end());
  return q;
}

/// one instance of y, chosen to be the one that fails
struct Instance {
  int ant = -1;           // the next antecedent step to match; -1 if not started or past it
  bool conActive = false; // the consequent is pending in state 'con'
  ConState con{0, 0};
  bool started = false;
  bool startNext = false; // the consequent starts on the next cycle (|=>)
  bool failed = false;    // failed inside the trace (absorbing)

  std::string key() const {
    return std::to_string(ant) + "/" +
           (conActive ? std::to_string(con.first) + "." + std::to_string(con.second)
                      : std::string("-")) +
           (started ? "s" : "w") + (startNext ? "+" : "-") + (failed ? "F" : "");
  }
  bool failsAtEnd(const HarmModel &m) const {
    return failed || (conActive && !m.endOK2[con.second]);
  }
};

/// one cycle of y's chosen instance; nullopt if it can no longer fail. 'start' starts it now
std::optional<Instance> stepInstance(const HarmModel &m, Instance i,
                                     const bdd &letter, bool start) {
  auto holds = [&](const bdd &b) { return (b & letter) != bddfalse; };
  if (i.failed) {
    return i;
  }
  if (!i.started) {
    if (!start) {
      return i;
    }
    i.started = true;
    i.ant = 0;
  }
  if (i.startNext) {
    i.startNext = false;
    i.conActive = true;
    i.con = {m.init, m.init2};
  } else if (i.ant >= 0) {
    if (!holds(m.ant[i.ant])) {
      return std::nullopt; // the antecedent does not match: this instance holds
    }
    if (i.ant + 1 < (int)m.ant.size()) {
      i.ant++;
      return i;
    }
    i.ant = -1;
    if (!m.overlap) {
      i.startNext = true;
      return i;
    }
    i.conActive = true;
    i.con = {m.init, m.init2};
  }
  if (i.conActive) {
    int outcome;
    i.con = stepCon(m, i.con, letter, outcome);
    if (outcome == 2) {
      i.failed = true;
      i.conActive = false;
    } else if (outcome == 1) {
      return std::nullopt; // the consequent holds
    }
  }
  return i;
}

/// no finite trace makes x hold while y fails, in HARM's evaluation. A search over all finite
/// traces, tracking every pending instance of x and one chosen instance of y; it gives up
/// (answers false: never sound to drop) beyond 'maxStates' explored states
bool harmImplies(const HarmModel &x, const HarmModel &y,
                 size_t maxStates = 20000) {
  // letters: the classes of atom valuations that no condition of x or y separates
  std::vector<bdd> letters{bddtrue};
  auto refine = [&](const bdd &b) {
    std::vector<bdd> out;
    for (const auto &l : letters) {
      for (const bdd &part : {l & b, l & !b}) {
        if (part != bddfalse) {
          out.push_back(part);
        }
      }
    }
    letters.swap(out);
  };
  for (const HarmModel *m : {&x, &y}) {
    for (const auto &b : m->ant) {
      refine(b);
    }
    for (const auto *edges : {&m->edges, &m->edges2}) {
      for (const auto &es : *edges) {
        for (const auto &e : es) {
          refine(e.first);
        }
      }
    }
  }
  std::set<std::string> seen;
  std::deque<std::pair<Pending, Instance>> todo{{Pending(), Instance()}};
  seen.insert(todo.front().first.key() + "|" + todo.front().second.key());
  while (!todo.empty()) {
    auto [px, iy] = todo.front();
    todo.pop_front();
    for (const auto &l : letters) {
      Pending qx = step(x, px, l);
      if (qx.failed) {
        continue; // x fails from here on: no counterexample on this path
      }
      for (bool start : {false, true}) {
        if (start && iy.started) {
          break;
        }
        auto qy = stepInstance(y, iy, l, start);
        if (!qy) {
          continue;
        }
        if (qy->failsAtEnd(y) && !qx.failsAtEnd(x)) {
          return false; // the trace can end here: x holds, y fails
        }
        if (seen.insert(qx.key() + "|" + qy->key()).second) {
          if (seen.size() > maxStates) {
            return false; // too large to decide: keep both
          }
          todo.emplace_back(qx, *qy);
        }
      }
    }
  }
  return true;
}

// ---------------------------------------------------------------- abstraction and automata
struct Abstracted {
  bool ok = false;     // parsed by Spot and modelled as HARM evaluates it
  bool safety = false; // syntactic safety (D-004)
  spot::formula f;     // infinite-word semantics
  HarmModel harm;      // HARM's finite-trace semantics
  std::set<std::string> atoms;
  spot::twa_graph_ptr aut, negAut; // translated lazily
};

/// the canonical classes of all atoms of these formulas (Z3, H2)
std::unordered_map<const Proposition *, std::string>
atomTokens(const std::vector<TemporalExpressionPtr> &formulas,
           unsigned z3TimeoutMs) {
  std::vector<PropositionPtr> atoms;
  for (const auto &te : formulas) {
    for (const auto &leaf : leafPropositions(te)) {
      collectAtoms(leaf, atoms);
    }
  }
  PropositionCanonicalizer canon(z3TimeoutMs, "p", "");
  canon.build(atoms);
  return canon.tokens();
}

Abstracted abstractFormula(
    const TemporalExpressionPtr &te,
    const std::unordered_map<const Proposition *, std::string> &tokens,
    Context &ctx) {
  Abstracted a;
  std::unordered_map<const Proposition *, std::string> subst;
  for (const auto &leaf : leafPropositions(te)) {
    subst[leaf.get()] = skeleton(leaf, tokens);
    std::vector<PropositionPtr> atoms;
    collectAtoms(leaf, atoms);
    for (const auto &at : atoms) {
      a.atoms.insert(tokens.at(at.get()));
    }
  }
  std::string text = temp2StringSubst(te, Language::SpotLTL, subst);
  spot::parsed_formula pf = spot::parse_infix_psl(text);
  if (!pf.errors.empty()) {
    return a; // not understood by Spot: never reduced
  }
  a.f = pf.f;
  a.safety = pf.f.is_syntactic_safety();
  if (!a.safety) {
    return a; // D-004: never reduced, and not worth modelling
  }
  // an automaton of G(a -> X^k b) needs 2^k states: deeper assertions are never reduced
  for (const auto &l : leafOffsets(te)) {
    if (l.offset && *l.offset > maxImplicationDepth) {
      return a;
    }
  }
  auto m = harmModel(te, tokens, ctx);
  if (!m) {
    return a; // not modelled as HARM evaluates it: never reduced
  }
  a.harm = std::move(*m);
  a.ok = true;
  return a;
}

void translate(Abstracted &a, Context &ctx) {
  if (a.aut == nullptr) {
    a.aut = ctx.trans.run(a.f);
    a.negAut = ctx.trans.run(spot::formula::Not(a.f));
  }
}

/// x implies y both on infinite words (SVA, formal tools) and on finite traces as HARM
/// evaluates them (D-004 as amended)
bool implies(Abstracted &x, Abstracted &y, Context &ctx) {
  translate(x, ctx);
  translate(y, ctx);
  return !x.aut->intersects(y.negAut) && harmImplies(x.harm, y.harm);
}

Implication relation(Abstracted &a, Abstracted &b, Context &ctx) {
  if (!a.ok || !b.ok || !a.safety || !b.safety) {
    return Implication::Skipped;
  }
  bool ab = implies(a, b, ctx), ba = implies(b, a, ctx);
  return ab && ba ? Implication::Equivalent
         : ab     ? Implication::AImpliesB
         : ba     ? Implication::BImpliesA
                  : Implication::None;
}

} // namespace

Implication implicationBetween(const TemporalExpressionPtr &a,
                               const TemporalExpressionPtr &b,
                               unsigned z3TimeoutMs) {
  auto tokens = atomTokens({a, b}, z3TimeoutMs);
  Context ctx;
  Abstracted x = abstractFormula(a, tokens, ctx),
             y = abstractFormula(b, tokens, ctx);
  return relation(x, y, ctx);
}

std::vector<AssertionPtr>
reduceByImplication(const std::vector<AssertionPtr> &in,
                    const std::string &keep,
                    std::vector<ImplicationRecord> *records,
                    unsigned z3TimeoutMs, size_t *pairsChecked) {
  const size_t n = in.size();
  std::vector<TemporalExpressionPtr> formulas;
  for (const auto &a : in) {
    formulas.push_back(a->_formula);
  }
  auto tokens = atomTokens(formulas, z3TimeoutMs);
  Context ctx;
  std::vector<Abstracted> abs;
  std::vector<std::string> text;
  for (const auto &a : in) {
    abs.push_back(abstractFormula(a->_formula, tokens, ctx));
    text.push_back(a->toString());
  }

  // pairs that share an atom (sound, incomplete: F4)
  std::map<std::string, std::vector<size_t>> byAtom;
  for (size_t i = 0; i < n; i++) {
    if (abs[i].ok && abs[i].safety) {
      for (const auto &at : abs[i].atoms) {
        byAtom[at].push_back(i);
      }
    }
  }
  std::set<std::pair<size_t, size_t>> candidates;
  for (const auto &[at, idx] : byAtom) {
    for (size_t x = 0; x < idx.size(); x++) {
      for (size_t y = x + 1; y < idx.size(); y++) {
        candidates.emplace(idx[x], idx[y]);
      }
    }
  }
  if (pairsChecked != nullptr) {
    *pairsChecked = candidates.size();
  }
  std::vector<std::vector<bool>> imp(n, std::vector<bool>(n, false));
  for (const auto &[i, j] : candidates) {
    Implication r = relation(abs[i], abs[j], ctx);
    imp[i][j] = r == Implication::AImpliesB || r == Implication::Equivalent;
    imp[j][i] = r == Implication::BImpliesA || r == Implication::Equivalent;
  }

  // equivalence classes: keep the smallest text of each
  std::vector<size_t> rep(n);
  std::iota(rep.begin(), rep.end(), 0);
  std::function<size_t(size_t)> find = [&](size_t x) {
    return rep[x] == x ? x : rep[x] = find(rep[x]);
  };
  for (size_t i = 0; i < n; i++) {
    for (size_t j = i + 1; j < n; j++) {
      if (imp[i][j] && imp[j][i]) {
        size_t a = find(i), b = find(j);
        if (a != b) {
          if (text[b] < text[a]) {
            std::swap(a, b);
          }
          rep[b] = a;
        }
      }
    }
  }
  std::vector<bool> dropped(n, false);
  std::vector<std::string> why(n);
  for (size_t i = 0; i < n; i++) {
    if (find(i) != i) {
      dropped[i] = true;
      why[i] = "equivalent";
    }
  }
  auto strict = [&](size_t a, size_t b) { return imp[a][b] && !imp[b][a]; };

  if (keep == "ranked") {
    // best-ranked first: keep an assertion unless it is related to one already kept
    std::vector<size_t> order;
    for (size_t i = 0; i < n; i++) {
      if (!dropped[i]) {
        order.push_back(i);
      }
    }
    std::stable_sort(order.begin(), order.end(), [&](size_t a, size_t b) {
      return in[a]->_finalScore > in[b]->_finalScore;
    });
    std::vector<size_t> kept;
    for (size_t i : order) {
      for (size_t k : kept) {
        if (strict(k, i) || strict(i, k)) {
          dropped[i] = true;
          why[i] = strict(k, i) ? "implied" : "implies";
          break;
        }
      }
      if (!dropped[i]) {
        kept.push_back(i);
      }
    }
  } else {
    bool stronger = keep != "weaker";
    for (size_t i = 0; i < n; i++) {
      if (dropped[i]) {
        continue;
      }
      for (size_t j = 0; j < n; j++) {
        if (j != i && find(j) == j &&
            (stronger ? strict(j, i) : strict(i, j))) {
          dropped[i] = true;
          why[i] = stronger ? "implied" : "implies";
          break;
        }
      }
    }
  }

  std::vector<AssertionPtr> out;
  for (size_t i = 0; i < n; i++) {
    if (!dropped[i]) {
      out.push_back(in[i]);
    }
  }
  if (records != nullptr) {
    for (size_t i = 0; i < n; i++) {
      if (!dropped[i]) {
        continue;
      }
      ImplicationRecord r{in[i], {}, why[i]};
      for (size_t k = 0; k < n; k++) {
        if (dropped[k]) {
          continue;
        }
        bool related = why[i] == "equivalent" ? find(i) == k
                       : why[i] == "implied"  ? imp[k][i]
                                              : imp[i][k];
        if (related) {
          r.kept.push_back(in[k]);
        }
      }
      records->push_back(r);
    }
  }
  return out;
}

} // namespace harm
