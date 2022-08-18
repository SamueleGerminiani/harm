#include "minerUtils.hh"
#include "Hierarchical.hh"
#include "KDE.hh"
#include "Kmeans.hh"
#include "Template.hh"
#include "globals.hh"

namespace harm {

std::ostream &operator<<(std::ostream &os, ClsOp op) {
  switch (op) {
  case ClsOp::Range:
    os << "r";
    break;
  case ClsOp::E:
    os << "e";
    break;
  case ClsOp::GE:
    os << "ge";
    break;
  case ClsOp::LE:
    os << "le";
    break;
  }
  return os;
}

std::pair<VarType, size_t> variableTypeFromString(const std::string &type,
                                                  size_t size) {
  if (type == "bool") {
    return std::make_pair(VarType::Bool, 1);
  } else if (type == "char") {
    return std::make_pair(VarType::SLogic, 8);
  } else if (type == "short") {
    return std::make_pair(VarType::SLogic, 16);
  } else if (type == "int") {
    return std::make_pair(VarType::SLogic, 32);
  } else if (type == "long int") {
    return std::make_pair(VarType::SLogic, 64);
  } else if (type == "unsigned char") {
    return std::make_pair(VarType::ULogic, 8);
  } else if (type == "unsigned short") {
    return std::make_pair(VarType::ULogic, 16);
  } else if (type == "unsigned int") {
    return std::make_pair(VarType::ULogic, 32);
  } else if (type == "unsigned long int") {
    return std::make_pair(VarType::ULogic, 64);
  } else if (type == "float") {
    return std::make_pair(VarType::Numeric, 32);
  } else if (type == "double") {
    return std::make_pair(VarType::Numeric, 64);
  } else if (type == "integer") {
    return std::make_pair(VarType::SLogic, 32);

  } else if (type == "byte") {
    return std::make_pair(VarType::SLogic, 8);
  } else if (type == "shortint") {
    return std::make_pair(VarType::SLogic, 16);
  } else if (type == "longint") {
    return std::make_pair(VarType::SLogic, 64);
  } else if (type == "byte unsigned") {
    return std::make_pair(VarType::ULogic, 8);
  } else if (type == "shortint unsigned") {
    return std::make_pair(VarType::ULogic, 16);
  } else if (type == "longint unsigned") {
    return std::make_pair(VarType::ULogic, 64);
  } else if (type == "time") {
    return std::make_pair(VarType::ULogic, 64);
  } else if (type == "shortreal") {
    return std::make_pair(VarType::Numeric, 32);
  } else if (type == "real") {
    return std::make_pair(VarType::Numeric, 64);
  } else if (type == "reg") {
    return std::make_pair(VarType::ULogic, size);
  } else if (type == "wire") {
    return std::make_pair(VarType::ULogic, size);
  } else if (type == "logic") {
    return std::make_pair(VarType::ULogic, size);
  } else if (type == "bit") {
    return std::make_pair(VarType::ULogic, size);
  }

  messageError("Unknown type: " + type);

  return std::make_pair(VarType::Bool, 1);
}

template <typename T>
std::vector<Proposition *> inline makeLogicRange(
    std::vector<std::pair<T, T>> &clusters, std::pair<VarType, T> type,
    CachedAllNumeric *cn) {

  std::vector<Proposition *> ret;
  for (auto &c : clusters) {
    if (c.first != c.second) {
      if (cn->_clsOps.count(ClsOp::Range)) {
        LogicExpression *ll = new LogicConstant(c.first, type.first,
                                                type.second, cn->getMaxTime());
        LogicExpression *rl = new LogicConstant(c.second, type.first,
                                                type.second, cn->getMaxTime());
        LogicExpression *l1 = copy(*cn->get()._le);
        LogicExpression *l2 = copy(*cn->get()._le);
        ret.push_back(makeExpression<PropositionAnd>(
            makeExpression<LogicGreaterEq>(l1, ll),
            makeExpression<LogicLessEq>(l2, rl)));
      }
      if (cn->_clsOps.count(ClsOp::GE)) {
        LogicExpression *l1 = copy(*cn->get()._le);
        LogicExpression *ll = new LogicConstant(c.first, type.first,
                                                type.second, cn->getMaxTime());
        ret.push_back(makeExpression<LogicGreaterEq>(l1, ll));
      }
      if (cn->_clsOps.count(ClsOp::LE)) {
        LogicExpression *l2 = copy(*cn->get()._le);
        LogicExpression *rl = new LogicConstant(c.second, type.first,
                                                type.second, cn->getMaxTime());
        ret.push_back(makeExpression<LogicLessEq>(l2, rl));
      }
    } else {
      if (cn->_clsOps.count(ClsOp::E)) {
        LogicExpression *lc = new LogicConstant(c.first, type.first,
                                                type.second, cn->getMaxTime());
        LogicExpression *le = copy(*cn->get()._le);
        ret.push_back(makeExpression<LogicEq>(le, lc));
      }
    }
  }
  return ret;
}

template <typename T>
std::vector<Proposition *> inline makeNumericRange(
    std::vector<std::pair<T, T>> &clusters, std::pair<VarType, T> type,
    CachedAllNumeric *cn) {

  std::vector<Proposition *> ret;
  for (auto &c : clusters) {
    if (c.first != c.second) {
      if (cn->_clsOps.count(ClsOp::Range)) {
        NumericExpression *ll = new NumericConstant(
            c.first, type.first, type.second, cn->getMaxTime());
        NumericExpression *rl = new NumericConstant(
            c.second, type.first, type.second, cn->getMaxTime());
        NumericExpression *l1 = copy(*cn->get()._ne);
        NumericExpression *l2 = copy(*cn->get()._ne);
        ret.push_back(makeExpression<PropositionAnd>(
            makeExpression<NumericGreaterEq>(l1, ll),
            makeExpression<NumericLessEq>(l2, rl)));
      }
      if (cn->_clsOps.count(ClsOp::GE)) {
        NumericExpression *l1 = copy(*cn->get()._ne);
        NumericExpression *ll = new NumericConstant(
            c.first, type.first, type.second, cn->getMaxTime());
        ret.push_back(makeExpression<NumericGreaterEq>(l1, ll));
      }
      if (cn->_clsOps.count(ClsOp::LE)) {
        NumericExpression *l2 = copy(*cn->get()._ne);
        NumericExpression *rl = new NumericConstant(
            c.second, type.first, type.second, cn->getMaxTime());
        ret.push_back(makeExpression<NumericLessEq>(l2, rl));
      }
    } else {
      if (cn->_clsOps.count(ClsOp::E)) {
        NumericExpression *lc = new NumericConstant(
            c.first, type.first, type.second, cn->getMaxTime());
        NumericExpression *le = copy(*cn->get()._ne);
        ret.push_back(makeExpression<NumericEq>(le, lc));
      }
    }
  }
  return ret;
}

template <typename T>
std::vector<std::pair<T, T>> clsElbow(std::vector<T> &elements,
                                      double clsEffort) {
  std::vector<std::pair<T, T>> clusters;
  if (clc::clsAlg == "kmeans") {
    clusters = kmeansElbow<T>(elements, 20, clsEffort);
  } else if (clc::clsAlg == "kde") {
    clusters = kdeElbow<T>(elements, 20, clsEffort);
  } else if (clc::clsAlg == "hc") {
    clusters = hcElbow<T>(elements, 20, clsEffort);
  }
  return clusters;
}

std::vector<Proposition *> genPropsThroughClustering(std::vector<size_t> &ivs,
                                                     CachedAllNumeric *cn,
                                                     size_t max_length) {

  std::vector<Proposition *> ret;
  std::pair<VarType, size_t> type = cn->getType();

  if (cn->getType().first == VarType::Numeric) {
    if (cn->getType().second == 32) {
      std::vector<float> elements;
      for (auto &iv : ivs) {
        elements.push_back(cn->evaluate(iv)._f);
      }
      auto clusters = clsElbow<float>(elements, cn->_clsEffort);
      return makeNumericRange<float>(clusters, type, cn);
    } else {
      std::vector<double> elements;
      for (auto &iv : ivs) {
        elements.push_back(cn->evaluate(iv)._d);
      }
      auto clusters = clsElbow<double>(elements, cn->_clsEffort);
      return makeNumericRange<double>(clusters, type, cn);
    }
  } else if (cn->getType().first == VarType::SLogic) {
    std::vector<SLogic> elements;
    for (auto &iv : ivs) {
      elements.push_back(cn->evaluate(iv)._s);
    }
    auto clusters = clsElbow<SLogic>(elements, cn->_clsEffort);
    return makeLogicRange<SLogic>(clusters, type, cn);
  } else if (cn->getType().first == VarType::ULogic) {
    std::vector<SLogic> elements;
    for (auto &iv : ivs) {
      elements.push_back(cn->evaluate(iv)._u);
    }
    std::vector<std::pair<SLogic, SLogic>> clusters =
        clsElbow<SLogic>(elements, cn->_clsEffort);
    return makeLogicRange<SLogic>(clusters, type, cn);
  } else {
    messageError("Unknown type in CachedAllNumeric");
  }

  //  debug
  //  for (auto &p : ret) {
  //    std::cout << prop2String(*p)<< "\n";
  //  }
  return ret;
}

std::shared_ptr<spot::twa_graph>
generateDeterministicSpotAutomaton(spot::formula &formula) {
  spot::translator trans;
  trans.set_pref(spot::postprocessor::Deterministic);
  auto aut = trans.run(formula);

  spot::postprocessor post;
  post.set_pref(spot::postprocessor::Complete);
  aut = post.run(aut);

  messageErrorIf(!spot::is_deterministic(aut),
                 "Automaton is not deterministic!");
  messageErrorIf(!spot::is_complete(aut), "Automaton is not complete!");
  return aut;
}

Automaton *
buildAutomaton(spot::twa_graph_ptr &automata,
               std::unordered_map<std::string, Proposition **> &tokenToProp) {
  size_t stateCount = 0;
  std::unordered_map<size_t, size_t> hashToId;
  auto initState = automata->get_init_state();
  Automaton *retA = new Automaton();

  // dictionary to extract edge propositions
  auto bddDict = automata->get_dict();
  // keep track of visited states
  std::unordered_map<size_t, const spot::state *> visited;
  // queue
  std::deque<const spot::state *> fringe;

  // visit the automata starting from the initial state(BFS)
  fringe.push_front(initState);
  // mark the first state as visited
  visited.insert({initState->hash(), initState});

  while (!fringe.empty()) {
    const spot::state *currState = fringe.back();
    fringe.pop_back();

    if (hashToId.count(currState->hash()) == 0) {
      //create a link to retrieve the Node ( only if it doesn't already exist)
      hashToId[currState->hash()] = stateCount++;
      retA->_idToNode[hashToId.at(currState->hash())] =
          new Automaton::Node(hashToId.at(currState->hash()), -1);
    }

    // identify if the current state is a terminal state
    auto it = automata->succ_iter(currState);
    if (it->first() && (it->dst()->hash() == currState->hash()) &&
        !it->next()) {
      if (automata->state_is_accepting(currState)) {
        // acceptance state:  the evaluation returns true
        retA->_idToNode.at(hashToId.at(currState->hash()))->_type = 1;
        retA->_accepting = retA->_idToNode.at(hashToId.at(currState->hash()));
      } else {
        // rejecting state:  the evaluation returns false
        retA->_idToNode.at(hashToId.at(currState->hash()))->_type = 0;
        retA->_rejecting = retA->_idToNode.at(hashToId.at(currState->hash()));
      }
    }
    delete it;

    // for each out edge
    for (auto s : automata->succ(currState)) {
      if (visited.count(s->dst()->hash()) == 0) {
        // mark as visited
        visited.insert({s->dst()->hash(), s->dst()});
        // put on the queue
        fringe.push_back(s->dst());
      }

      // retrieve the spotLTL representation of an edge
      spot::formula edge =
          spot::parse_formula(spot::bdd_format_formula(bddDict, s->cond()));

      if (hashToId.count(s->dst()->hash()) == 0) {
        //Again: create a link to retrieve the Node ( only if it doesn't exist already)
        hashToId[s->dst()->hash()] = stateCount++;
        retA->_idToNode[hashToId.at(s->dst()->hash())] =
            new Automaton::Node(hashToId.at(s->dst()->hash()), -1);
      }
      // add the custom edge to the custom node
      EdgeProposition *newEdgeProp = edgeToProposition(edge, tokenToProp);
      Automaton::Edge *newEdge = new Automaton::Edge(
          newEdgeProp, retA->_idToNode.at(hashToId.at(s->dst()->hash())),
          retA->_idToNode.at(hashToId.at(currState->hash())));

      retA->_idToNode.at(hashToId.at(currState->hash()))
          ->_outEdges.push_back(newEdge);
      retA->_idToNode.at(hashToId.at(s->dst()->hash()))
          ->_inEdges.push_back(newEdge);
    }
  }

  // set the initial state of the automaton
  retA->_root = retA->_idToNode.at(0);

  return retA;
}

EdgeProposition *edgeToProposition(
    const spot::formula &f,
    std::unordered_map<std::string, Proposition **> &tokenToProp) {
  //visit the expression depending on the type of operator

  // And
  if (f.is(spot::op::And)) {
    std::vector<EdgeProposition *> operands;
    for (size_t i = 0; i < f.size(); i++) {
      operands.push_back(edgeToProposition(f[i], tokenToProp));
    }

    return new EdgeAnd(operands);
  }

  // Or
  if (f.is(spot::op::Or)) {
    std::vector<EdgeProposition *> operands;
    for (size_t i = 0; i < f.size(); i++) {
      operands.push_back(edgeToProposition(f[i], tokenToProp));
    }

    return new EdgeOr(operands);
  }

  // Not
  if (f.is(spot::op::Not)) {
    return new EdgeNot(edgeToProposition(f[0], tokenToProp));
  }

  // Atomic proposition
  if (f.is(spot::op::ap)) {
    return new EdgePlaceholder(tokenToProp.at(f.ap_name()), f.ap_name());
  }

  // Constants

  if (f.is_tt()) {
    return new EdgeTrue();
  }

  if (f.is_ff()) {
    return new EdgeFalse();
  }

  messageError("Error in spot edge formula");
  return nullptr;
}
} // namespace harm
