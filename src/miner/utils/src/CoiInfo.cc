#include "CoiInfo.hh"

#include <algorithm>
#include <fstream>
#include <set>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Context.hh"
#include "DTOperator.hh"
#include "Location.hh"
#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "expUtils/expUtils.hh"
#include "formula/temporal/temporal.hh"
#include "message.hh"

namespace harm {
using namespace expression;
namespace pt = boost::property_tree;

// ---------------------------------------------------------------- loading
std::shared_ptr<CoiInfo> CoiInfo::load(const std::string &file,
                                       const TracePtr &trace) {
  std::ifstream in(file);
  messageErrorIf(!in.good(), "Cannot open coi file '" + file + "'");
  pt::ptree root;
  try {
    pt::read_json(in, root);
  } catch (const pt::json_parser_error &e) {
    messageError("Cannot parse coi file '" + file + "': " + e.what());
  }

  auto coi = std::make_shared<CoiInfo>();
  coi->_file = file;
  std::string version = root.get<std::string>("version", "");
  messageErrorIf(version != "1", "unsupported coi.json version '" +
                                     version + "' in '" + file +
                                     "' (expected \"1\")");
  try {
    coi->_vcdScope = root.get<std::string>("meta.vcd_scope");
    coi->_vcdRecursion = root.get<size_t>("meta.vcd_recursion");
    coi->_clock = root.get<std::string>("meta.clock");
    coi->_maxDepth = root.get<int>("meta.max_depth");
  } catch (const pt::ptree_error &e) {
    messageError("Invalid meta in coi file '" + file + "': " + e.what());
  }

  std::set<std::string> names;
  for (const auto &[target, cone] : root.get_child("targets")) {
    names.insert(target);
    auto &sources = coi->_targets[target];
    for (const auto &[_, s] : cone.get_child("sources")) {
      std::string sig = s.get<std::string>("sig");
      names.insert(sig);
      Source src;
      for (const auto &[__, d] : s.get_child("depths")) {
        src.depths.push_back(d.get_value<int>());
      }
      src.saturated = s.get<bool>("saturated", false);
      messageErrorIf(
          !std::is_sorted(src.depths.begin(), src.depths.end()) ||
              std::adjacent_find(src.depths.begin(), src.depths.end()) !=
                  src.depths.end(),
          "coi file '" + file + "': depths of " + target + " <- " + sig +
              " are not sorted and unique");
      messageErrorIf(!src.depths.empty() &&
                         src.depths.back() > coi->_maxDepth,
                     "coi file '" + file + "': depth above max_depth in " +
                         target + " <- " + sig);
      sources[sig] = src;
    }
  }
  if (root.get_child_optional("unknown")) {
    for (const auto &[_, u] : root.get_child("unknown")) {
      coi->_unknown.insert(u.get_value<std::string>());
      names.insert(u.get_value<std::string>());
    }
  }

  // every name must be a variable of the trace (the names are those HARM sees, H4)
  std::set<std::string> vars;
  for (const auto &d : trace->getDeclarations()) {
    vars.insert(d.getName());
  }
  std::string missing;
  for (const auto &n : names) {
    if (!vars.count(n)) {
      missing += (missing.empty() ? "" : ", ") + n;
    }
  }
  messageErrorIf(!missing.empty(),
                 "coi file '" + file +
                     "' names signals that are not variables of the trace: " +
                     missing +
                     " (check --vcd-ss/--vcd-r against meta.vcd_scope '" +
                     coi->_vcdScope + "' and meta.vcd_recursion " +
                     std::to_string(coi->_vcdRecursion) + ")");
  return coi;
}

bool CoiInfo::knows(const std::string &signal) const {
  return _targets.count(signal) && !_unknown.count(signal);
}

bool CoiInfo::inCone(const std::vector<std::string> &propVars,
                     const std::vector<std::string> &consequentVars) const {
  for (const auto &v : propVars) {
    if (!knows(v)) {
      continue; // in the cone, but counted by computeCoiMetrics (D-014)
    }
    bool vInCone = false;
    for (const auto &c : consequentVars) {
      // the cone of an unknown consequent signal is unknown: it cannot exclude v
      if (!knows(c) || source(c, v) != nullptr) {
        vInCone = true;
        break;
      }
    }
    if (!vInCone) {
      return false;
    }
  }
  return true;
}

bool CoiInfo::fits(const std::vector<std::string> &propVars,
                   const std::vector<ConsequentLeaf> &consequent,
                   CoiDepth depth) const {
  if (depth == CoiDepth::Any) {
    std::vector<std::string> all;
    for (const auto &q : consequent) {
      all.insert(all.end(), q.vars.begin(), q.vars.end());
    }
    return inCone(propVars, all);
  }
  for (const auto &v : propVars) {
    if (!knows(v)) {
      continue; // unknown: never excluded (D-017)
    }
    bool vFits = false;
    for (const auto &q : consequent) {
      for (const auto &c : q.vars) {
        if (!knows(c)) {
          vFits = true; // the cone of an unknown consequent signal is unknown
          continue;
        }
        const Source *s = source(c, v);
        if (s == nullptr) {
          continue;
        }
        if (!q.distance) {
          vFits = true; // offset not fixed: cone membership (D-014)
          continue;
        }
        int d = *q.distance;
        if (depth == CoiDepth::Exact) {
          vFits |= std::find(s->depths.begin(), s->depths.end(), d) !=
                       s->depths.end() ||
                   (s->saturated && d > _maxDepth);
        } else {
          vFits |= d >= 0 && ((!s->depths.empty() && d <= s->depths.back()) ||
                              s->saturated);
        }
      }
    }
    if (!vFits) {
      return false;
    }
  }
  return true;
}

const CoiInfo::Source *CoiInfo::source(const std::string &target,
                                       const std::string &source) const {
  auto t = _targets.find(target);
  if (t == _targets.end()) {
    return nullptr;
  }
  auto s = t->second.find(source);
  return s == t->second.end() ? nullptr : &s->second;
}

// ---------------------------------------------------------------- leaf offsets
namespace {
using Offset = std::optional<int>;

Offset plus(Offset o, int d) { return o ? Offset(*o + d) : std::nullopt; }

/// records the leaves of 'te' starting at cycle 'start'; returns the cycle at which 'te' ends
Offset walk(const TemporalExpressionPtr &te, Offset start, bool inAntecedent,
            std::vector<LeafOffset> &leaves) {
  if (auto inst = std::dynamic_pointer_cast<BooleanLayerInst>(te)) {
    leaves.push_back({inst->getProposition(), inAntecedent, start});
    return start;
  }
  if (auto ph = std::dynamic_pointer_cast<BooleanLayerPlaceholder>(te)) {
    // a template formula: the proposition currently loaded in the placeholder (H8)
    auto &pp = ph->getPlaceholderPointer();
    if (pp != nullptr && *pp != nullptr) {
      leaves.push_back({*pp, inAntecedent, start});
    }
    return start;
  }
  if (auto c = std::dynamic_pointer_cast<SereConcat>(te)) {
    Offset e = walk(c->getItems()[0], start, inAntecedent, leaves);
    return walk(c->getItems()[1], c->isOverlapping() ? e : plus(e, 1),
                inAntecedent, leaves);
  }
  if (auto d = std::dynamic_pointer_cast<SereDelay>(te)) {
    auto w = d->getWindow();
    bool fixed = w.first == w.second;
    auto &items = d->getItems();
    Offset from = start;
    if (items.size() == 2) {
      from = walk(items[0], start, inAntecedent, leaves);
    }
    return walk(items.back(), fixed ? plus(from, w.first) : std::nullopt,
                inAntecedent, leaves);
  }
  if (auto imp = std::dynamic_pointer_cast<PropertyImplication>(te)) {
    Offset e = walk(imp->getItems()[0], 0, true, leaves);
    // |-> and |=> start the consequent at the end of the antecedent; -> and => start it with
    // the antecedent, whatever its length (H8 finding F6)
    Offset from = imp->isMMImplication() ? e : Offset(0);
    return walk(imp->getItems()[1], imp->isOverlapping() ? from : plus(from, 1),
                false, leaves);
  }
  if (auto n = std::dynamic_pointer_cast<PropertyNext>(te)) {
    return walk(n->getItems()[0], plus(start, (int)n->getDelay()),
                inAntecedent, leaves);
  }
  if (std::dynamic_pointer_cast<PropertyAlways>(te) != nullptr) {
    return walk(te->getItems()[0], 0, inAntecedent, leaves);
  }
  bool unbounded =
      std::dynamic_pointer_cast<PropertyEventually>(te) != nullptr ||
      std::dynamic_pointer_cast<PropertyUntil>(te) != nullptr ||
      std::dynamic_pointer_cast<PropertyRelease>(te) != nullptr ||
      std::dynamic_pointer_cast<SereConsecutiveRep>(te) != nullptr ||
      std::dynamic_pointer_cast<SereNonConsecutiveRep>(te) != nullptr ||
      std::dynamic_pointer_cast<SereGoto>(te) != nullptr ||
      std::dynamic_pointer_cast<SerePlus>(te) != nullptr;
  // and, or, not, first_match, ...: the items start together
  Offset childStart = unbounded ? std::nullopt : start;
  std::vector<Offset> ends;
  for (auto &item : te->getItems()) {
    ends.push_back(walk(item, childStart, inAntecedent, leaves));
  }
  if (unbounded || ends.empty()) {
    return unbounded ? std::nullopt : start;
  }
  bool same = std::all_of(ends.begin(), ends.end(),
                          [&](const Offset &e) { return e == ends[0]; });
  return same ? ends[0] : std::nullopt;
}

std::vector<std::string> variablesOf(const PropositionPtr &p) {
  std::vector<std::string> vars;
  for (const auto &[name, type] : getVars(p)) {
    vars.push_back(name);
  }
  std::sort(vars.begin(), vars.end());
  vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
  return vars;
}
} // namespace

std::vector<LeafOffset> leafOffsets(const TemporalExpressionPtr &formula) {
  std::vector<LeafOffset> leaves;
  walk(formula, 0, false, leaves);
  return leaves;
}

std::vector<std::vector<ConsequentLeaf>>
dtIndexConsequents(const TemplateImplicationPtr &t) {
  DTOperatorPtr dto = t->getDT();
  if (dto == nullptr) {
    return {};
  }
  // a marker at each index in turn: its offset, and the consequent leaves', in the instantiated
  // formula (the same offsets as coiDepthFit, D-014). copy() copies propositions, so the marker
  // is found by its name, which cannot be a signal name
  const std::string markerName = "$harm_dt_index_marker";
  std::vector<unsigned int> markerValues(t->getTraceLength() + 1, 0);
  PropositionPtr marker = generatePtr<BooleanVariable>(
      markerValues.data(), markerName, t->getTraceLength());
  std::vector<std::vector<ConsequentLeaf>> out;
  for (size_t i = 0; i < dto->getNumIndices(); i++) {
    dto->addItem(marker, (int)i);
    auto leaves = leafOffsets(copy(t->getTemplateFormula(), true));
    dto->removeItems();
    std::optional<int> at;
    bool found = false;
    for (const auto &l : leaves) {
      auto vars = variablesOf(l.prop);
      if (l.inAntecedent && vars.size() == 1 && vars[0] == markerName) {
        at = l.offset;
        found = true;
      }
    }
    messageErrorIf(!found, "COI depth filter: cannot locate decision-tree index " +
                               std::to_string(i) + " in " + t->getTemplateStr());
    std::vector<ConsequentLeaf> row;
    for (const auto &l : leaves) {
      if (!l.inAntecedent) {
        std::optional<int> d;
        if (at && l.offset) {
          d = *l.offset - *at;
        }
        row.push_back({variablesOf(l.prop), d});
      }
    }
    out.push_back(row);
  }
  return out;
}

std::vector<std::vector<std::optional<int>>>
dtIndexDistances(const TemplateImplicationPtr &t) {
  std::vector<std::vector<std::optional<int>>> out;
  for (const auto &row : dtIndexConsequents(t)) {
    out.emplace_back();
    for (const auto &q : row) {
      out.back().push_back(q.distance);
    }
  }
  return out;
}

// ---------------------------------------------------------------- out-of-cone report (H9)
namespace {
std::string jsonStr(const std::string &s) {
  std::string out = "\"";
  for (char c : s) {
    if (c == '"' || c == '\\') {
      out += '\\';
    }
    out += c == '\n' ? ' ' : c;
  }
  return out + "\"";
}

std::string jsonList(const std::vector<std::string> &v) {
  std::string out = "[";
  for (size_t i = 0; i < v.size(); i++) {
    out += (i ? ", " : "") + jsonStr(v[i]);
  }
  return out + "]";
}

template <typename Vars> std::vector<std::string> names(const Vars &vars) {
  std::vector<std::string> out;
  for (const auto &[name, type] : vars) {
    out.push_back(name);
  }
  std::sort(out.begin(), out.end());
  out.erase(std::unique(out.begin(), out.end()), out.end());
  return out;
}

std::vector<std::string> numericVariables(const NumericExpressionPtr &n) {
  switch (n->getType().first) {
  case ExpType::Float:
    return names(getVars(n->get<FloatExpression>()));
  case ExpType::SInt:
  case ExpType::UInt:
    return names(getVars(n->get<IntExpression>()));
  default:
    return names(getVars(n->get<LogicExpression>()));
  }
}

struct ReportItem {
  std::string text;
  std::string origin; // empty: none
  bool numeric;
  std::vector<std::string> vars;
};
} // namespace

void writeCoiReport(const std::vector<ContextPtr> &contexts,
                    const std::string &file) {
  std::string out = "{\"version\": \"1\", \"contexts\": [";
  for (size_t ci = 0; ci < contexts.size(); ci++) {
    const Context &ctx = *contexts[ci];
    out += std::string(ci ? "," : "") + "\n  {\"name\": " + jsonStr(ctx._name) + ", \"coi\": ";
    if (ctx._coi == nullptr) {
      messageInfo("COI report: context '" + ctx._name +
                  "' has no <coi>: it is listed without consequents");
      out += "null, \"consequents\": []}";
      continue;
    }
    const CoiInfo &coi = *ctx._coi;
    out += jsonStr(coi._file) + ", \"consequents\": [";
    auto originOf = [&](const std::string &text) {
      auto o = ctx._origin.find(text);
      return o == ctx._origin.end() ? std::string() : o->second;
    };
    // D-022: consequents are the propositions of the c and ac domains; antecedents are the
    // propositions and numerics of every other domain (a, ac, dt, local ids)
    std::map<std::string, ReportItem> cons, ants;
    for (const auto &[id, props] : ctx._domainIdToProps) {
      bool isCon = id == (int)Location::Con || id == (int)Location::AntCon;
      bool isAnt = id != (int)Location::Con;
      for (const auto &p : props) {
        std::string t = prop2String(p);
        ReportItem item{t, originOf(t), false, variablesOf(p)};
        if (isCon) {
          cons.emplace(t, item);
        }
        if (isAnt) {
          ants.emplace(t, item);
        }
      }
    }
    std::map<std::string, ReportItem> numerics; // printed apart: a numeric may print like a prop
    for (const auto &[id, nums] : ctx._domainIdToNumerics) {
      if (id == (int)Location::Con) {
        continue;
      }
      for (const auto &n : nums) {
        std::string t = num2String(n);
        numerics.emplace(t, ReportItem{t, originOf(t), true, numericVariables(n)});
      }
    }
    std::vector<const ReportItem *> antecedents;
    for (const auto &[t, a] : ants) {
      antecedents.push_back(&a);
    }
    for (const auto &[t, a] : numerics) {
      antecedents.push_back(&a);
    }

    auto origin = [](const ReportItem &i) {
      return i.origin.empty() ? std::string("null") : jsonStr(i.origin);
    };
    size_t k = 0;
    for (const auto &[ct, c] : cons) {
      bool coneUnknown = std::any_of(c.vars.begin(), c.vars.end(),
                                     [&](const std::string &v) { return !coi.knows(v); });
      std::string outOfCone, unknown;
      for (const ReportItem *a : antecedents) {
        if (!a->numeric && a->text == ct) {
          continue; // not paired with itself
        }
        std::vector<std::string> unk, outside;
        for (const auto &v : a->vars) {
          if (!coi.knows(v)) {
            unk.push_back(v);
          } else if (!coneUnknown && !coi.inCone({v}, c.vars)) {
            outside.push_back(v); // D-017, variable by variable
          }
        }
        std::string head = "{\"text\": " + jsonStr(a->text) + ", \"origin\": " + origin(*a) +
                           ", \"numeric\": " + (a->numeric ? "true" : "false") +
                           ", \"variables\": " + jsonList(a->vars);
        if (!outside.empty()) {
          outOfCone += std::string(outOfCone.empty() ? "" : ", ") + head +
                       ", \"outside\": " + jsonList(outside) + "}";
        } else if (coneUnknown || !unk.empty()) {
          unknown += std::string(unknown.empty() ? "" : ", ") + head +
                     ", \"unknownVariables\": " + jsonList(unk) + "}";
        }
      }
      out += std::string(k++ ? "," : "") + "\n    {\"text\": " + jsonStr(ct) +
             ", \"origin\": " + origin(c) + ", \"variables\": " + jsonList(c.vars) +
             ", \"coneUnknown\": " + (coneUnknown ? "true" : "false") +
             ",\n     \"outOfCone\": [" + outOfCone + "],\n     \"unknown\": [" + unknown + "]}";
    }
    out += "]}";
  }
  out += "\n]}\n";
  std::ofstream ofs(file);
  messageErrorIf(!ofs.good(), "Cannot write the COI report '" + file + "'");
  ofs << out;
}

// ---------------------------------------------------------------- metrics (D-014)
CoiMetrics computeCoiMetrics(const TemporalExpressionPtr &formula,
                             const CoiInfo &coi) {
  auto leaves = leafOffsets(formula);
  struct Con {
    std::vector<std::string> vars;
    std::optional<int> offset;
  };
  std::vector<Con> consequent;
  for (const auto &l : leaves) {
    if (!l.inAntecedent) {
      consequent.push_back({variablesOf(l.prop), l.offset});
    }
  }

  std::vector<std::string> consequentVars;
  for (const auto &q : consequent) {
    consequentVars.insert(consequentVars.end(), q.vars.begin(), q.vars.end());
  }
  CoiMetrics m;
  size_t counted = 0, inCone = 0, fitting = 0;
  for (const auto &l : leaves) {
    if (!l.inAntecedent) {
      continue;
    }
    auto vars = variablesOf(l.prop);
    if (vars.empty()) {
      continue; // e.g. the 'true' of 'a ##1 true'
    }
    counted++;
    // in the cone: the rule shared with filter mode (D-017)
    bool leafInCone = coi.inCone(vars, consequentVars);
    bool hasUnknown = false;
    for (const auto &v : vars) {
      hasUnknown |= !coi.knows(v); // in the cone and fitting, but counted (D-014)
    }
    std::vector<ConsequentLeaf> dist;
    for (const auto &q : consequent) {
      std::optional<int> d;
      if (l.offset && q.offset) {
        d = *q.offset - *l.offset;
      }
      dist.push_back({q.vars, d});
    }
    // fits(Exact) implies inCone; the rule is shared with the depth filter (D-020)
    bool leafFits = coi.fits(vars, dist, CoiDepth::Exact);
    m.unknown += hasUnknown;
    inCone += leafInCone;
    fitting += leafInCone && leafFits;
  }
  if (counted > 0) {
    m.frac = (double)inCone / counted;
    m.depthFit = (double)fitting / counted;
  }
  return m;
}

} // namespace harm
