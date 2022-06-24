#pragma once

#include "classes/atom/Constant.hh"
#include "classes/atom/Variable.hh"
#include "classes/expression/Expression.hh"
#include "classes/expression/BitSelector.hh"
#include "classes/expression/TypeCast.hh"
#include "classes/temporal/temporal.hh"

namespace expression {

/// @brief ExpVisitor defines the base visitor to visit
/// propositions and expressions
class ExpVisitor {

  public:
    /// Virtual Destructor
    virtual ~ExpVisitor() = default;

    // proposition
    virtual void visit(BooleanConstant &o);
    virtual void visit(BooleanVariable &o);
    virtual void visit(PropositionAnd &o);
    virtual void visit(PropositionOr &o);
    virtual void visit(PropositionXor &o);
    virtual void visit(PropositionEq &o);
    virtual void visit(PropositionNeq &o);
    virtual void visit(PropositionNot &o);
    virtual void visit(PropositionPast &o);

    // numeric
    virtual void visit(NumericConstant &o);
    virtual void visit(NumericVariable &o);
    virtual void visit(NumericSum &o);
    virtual void visit(NumericSub &o);
    virtual void visit(NumericMul &o);
    virtual void visit(NumericDiv &o);
    virtual void visit(NumericPast &o);
    virtual void visit(NumericEq &o);
    virtual void visit(NumericNeq &o);
    virtual void visit(NumericGreater &o);
    virtual void visit(NumericGreaterEq &o);
    virtual void visit(NumericLess &o);
    virtual void visit(NumericLessEq &o);
    virtual void visit(NumericToBool &o);

    // logic
    virtual void visit(LogicConstant &o);
    virtual void visit(LogicVariable &o);
    virtual void visit(LogicSum &o);
    virtual void visit(LogicSub &o);
    virtual void visit(LogicMul &o);
    virtual void visit(LogicDiv &o);
    virtual void visit(LogicBAnd &o);
    virtual void visit(LogicBOr &o);
    virtual void visit(LogicBXor &o);
    virtual void visit(LogicNot &o);
    virtual void visit(LogicPast &o);
    virtual void visit(LogicEq &o);
    virtual void visit(LogicNeq &o);
    virtual void visit(LogicGreater &o);
    virtual void visit(LogicGreaterEq &o);
    virtual void visit(LogicLess &o);
    virtual void visit(LogicLessEq &o);
    virtual void visit(LogicBitSelector &o);
    virtual void visit(LogicToNumeric &o);
    virtual void visit(LogicToBool &o);
    virtual void visit(LogicLShift &o);
   virtual void visit(LogicRShift &o);

  protected:
    /// @brief Constructor
    ExpVisitor() = default;
};

} 
