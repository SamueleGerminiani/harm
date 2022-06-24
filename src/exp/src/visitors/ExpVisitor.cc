#include "visitors/ExpVisitor.hh"

//------------------------------------------------------------------------------
#define LEAF_NODE(LEAF)                                                        \
    void ExpVisitor::visit(LEAF &) {}

#define EXPRESSION_NODE_1(NODE)                                                \
    void ExpVisitor::visit(NODE &o) {                                         \
        auto &propositions = o.getItems();                                     \
        for (auto *prop : propositions)                                        \
            prop->acceptVisitor(*this);                                        \
    }

#define EXPRESSION_NODE_2(NODE)                                                \
    void ExpVisitor::visit(NODE &o) { o.getItem().acceptVisitor(*this); }

#define EXPRESSION_NODE_3(NODE)                                                \
    void ExpVisitor::visit(NODE &o) {                                         \
        o.getItem1().acceptVisitor(*this);                                     \
        o.getItem2().acceptVisitor(*this);                                     \
    }
//------------------------------------------------------------------------------

namespace expression {

// proposition
LEAF_NODE(BooleanConstant)
LEAF_NODE(BooleanVariable)
EXPRESSION_NODE_1(PropositionAnd)
EXPRESSION_NODE_1(PropositionOr)
EXPRESSION_NODE_1(PropositionXor)
EXPRESSION_NODE_1(PropositionEq)
EXPRESSION_NODE_1(PropositionNeq)
EXPRESSION_NODE_1(PropositionNot)
EXPRESSION_NODE_2(PropositionPast)
EXPRESSION_NODE_2(LogicToBool)

// numeric
LEAF_NODE(NumericConstant)
LEAF_NODE(NumericVariable)
EXPRESSION_NODE_1(NumericSum)
EXPRESSION_NODE_1(NumericSub)
EXPRESSION_NODE_1(NumericMul)
EXPRESSION_NODE_1(NumericDiv)
EXPRESSION_NODE_1(NumericEq)
EXPRESSION_NODE_1(NumericNeq)
EXPRESSION_NODE_1(NumericGreater)
EXPRESSION_NODE_1(NumericGreaterEq)
EXPRESSION_NODE_1(NumericLess)
EXPRESSION_NODE_1(NumericLessEq)
EXPRESSION_NODE_2(NumericPast)
EXPRESSION_NODE_2(NumericToBool)

// logic
LEAF_NODE(LogicConstant)
LEAF_NODE(LogicVariable)
EXPRESSION_NODE_1(LogicSum)
EXPRESSION_NODE_1(LogicSub)
EXPRESSION_NODE_1(LogicMul)
EXPRESSION_NODE_1(LogicDiv)
EXPRESSION_NODE_1(LogicBAnd)
EXPRESSION_NODE_1(LogicBOr)
EXPRESSION_NODE_1(LogicBXor)
EXPRESSION_NODE_1(LogicEq)
EXPRESSION_NODE_1(LogicNeq)
EXPRESSION_NODE_1(LogicGreater)
EXPRESSION_NODE_1(LogicGreaterEq)
EXPRESSION_NODE_1(LogicLess)
EXPRESSION_NODE_1(LogicLessEq)
EXPRESSION_NODE_1(LogicNot)
EXPRESSION_NODE_1(LogicLShift)
EXPRESSION_NODE_1(LogicRShift)
EXPRESSION_NODE_2(LogicPast)
EXPRESSION_NODE_2(LogicBitSelector)
EXPRESSION_NODE_2(LogicToNumeric)

} 
