#include "CoiInfo.hh"

#include <algorithm>
#include <fstream>
#include <set>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

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

bool CoiInfo::inCone(const std::vector<std::string> &,
                     const std::vector<std::string> &) const {
  messageError("CoiInfo::inCone: not implemented yet (H7)");
  return false;
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
    return walk(imp->getItems()[1], imp->isOverlapping() ? e : plus(e, 1),
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
    bool hasUnknown = false, leafInCone = true, leafFits = true;
    for (const auto &v : vars) {
      if (!coi.knows(v)) {
        hasUnknown = true; // in the cone and fitting, but counted (D-014)
        continue;
      }
      bool vInCone = false, vFits = false;
      for (const auto &q : consequent) {
        for (const auto &c : q.vars) {
          if (!coi.knows(c)) {
            // the cone of an unknown consequent signal is unknown: it cannot exclude v
            vInCone = vFits = true;
            continue;
          }
          const CoiInfo::Source *s = coi.source(c, v);
          if (s == nullptr) {
            continue;
          }
          vInCone = true;
          if (!l.offset || !q.offset) {
            vFits = true;
            continue;
          }
          int d = *q.offset - *l.offset;
          if (std::find(s->depths.begin(), s->depths.end(), d) !=
                  s->depths.end() ||
              (s->saturated && d > coi._maxDepth)) {
            vFits = true;
          }
        }
      }
      leafInCone &= vInCone;
      leafFits &= vFits;
    }
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
