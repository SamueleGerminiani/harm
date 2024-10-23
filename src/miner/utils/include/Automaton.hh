
#pragma once
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace harm {
class EdgeProposition;

class Automaton {

public:
  //----Internal classes Node-Edge to make custom automata
  /*! \class Edge
      \brief edge of the custom automaton
  */
  struct Edge;

  /*! \class Node
      \brief  state of the custom automaton
  */
  struct Node {
    enum class Type {
      Accepting,
      Rejecting,
      Pending,
    };

    Node(size_t id, Type type);
    ~Node();
    size_t _id;
    Type _type;
    std::vector<Edge *> _outEdges;
    std::vector<Edge *> _inEdges;
  };
  struct Edge {
    Edge(EdgeProposition *prop, Node *toNode);
    Edge(EdgeProposition *prop, Node *toNode, Node *fromNode);
    ~Edge();
    EdgeProposition *_prop = nullptr;
    Node *_toNode = nullptr;
    Node *_fromNode = nullptr;
    std::string _id = "";
  };
  //-----------------------------------------------
  ~Automaton() {
    // delete all nodes of the automatas
    for (auto &i_node : _idToNode) {
      delete i_node.second;
    }
  }

  std::unordered_map<size_t, Node *> _idToNode;
  ///start node of the automaton
  Node *_root;
  Node *_accepting = nullptr;
  Node *_rejecting = nullptr;
};

std::string printAutomaton(const Automaton *aut);
} // namespace harm
