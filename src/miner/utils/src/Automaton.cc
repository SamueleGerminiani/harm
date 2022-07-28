
#include "Automaton.hh"
namespace harm {

Automaton::Node::Node(size_t id, int type) : _id(id), _type(type) { // not todo
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
Automaton::Edge::Edge(EdgeProposition *prop, Node *toNode, Node *fromNode)
    : _prop(prop), _toNode(toNode), _fromNode(fromNode) {
  _id = "(" + std::to_string(_fromNode->_id) + ", " +
        std::to_string(_toNode->_id) + ")";
  // not todo
}
Automaton::Edge::~Edge() { delete _prop; }


} // namespace harm
