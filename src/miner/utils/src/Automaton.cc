
#include "Automaton.hh"
#include "EdgeProposition.hh"
#include <deque>

namespace harm {

Automaton::Node::Node(size_t id, Type type)
    : _id(id), _type(type) { // not todo
}
Automaton::Node::~Node() {
  for (auto &edge : _outEdges) {
    delete edge;
  }
}
Automaton::Edge::Edge(EdgeProposition *prop, Node *toNode)
    : _prop(prop), _toNode(toNode) {
  // not todo
}
Automaton::Edge::Edge(EdgeProposition *prop, Node *toNode,
                      Node *fromNode)
    : _prop(prop), _toNode(toNode), _fromNode(fromNode) {
  _id = "(" + std::to_string(_fromNode->_id) + ", " +
        std::to_string(_toNode->_id) + ")";
  // not todo
}
Automaton::Edge::~Edge() { delete _prop; }

std::string printAutomaton(const Automaton *aut) {
  Automaton::Node *root = aut->_root;
  std::deque<Automaton::Node *> fringe;
  std::unordered_set<Automaton::Node *> visited;
  std::string ret = "digraph Automaton {\n";

  // visit the automata starting from the initial state(BFS)
  fringe.push_front(root);
  visited.insert(root);

  while (!fringe.empty()) {
    // add to fringe all states reachable from this state
    // out edges can be added to fringe only once
    // add new states to fringe
    auto currState = fringe.back();
    fringe.pop_back();
    std::string nodeStyle = "shape=circle";
    if (currState->_type == Automaton::Node::Type::Accepting) {
      nodeStyle = "shape=doublecircle";
    }
    ret += std::to_string(currState->_id) +
           " [label=" + std::to_string(currState->_id) + "," +
           nodeStyle + "]\n";

    for (auto edge : currState->_outEdges) {
      ret += std::to_string(currState->_id) + " -> " +
             std::to_string(edge->_toNode->_id) + " [label=\"" +
             edge->_prop->toString() + "\"]";
      if (visited.count(edge->_toNode) == 0) {
        // mark as visited
        visited.insert({edge->_toNode});
        fringe.push_back(edge->_toNode);
      } // visited.count
      ret += "\n";
    }
  }
  ret += "}\n";
  return ret;
}

} // namespace harm
