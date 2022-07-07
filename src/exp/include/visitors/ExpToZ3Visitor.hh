
#pragma once

#include "z3++.h"
#include "z3.h"

#include "visitors/ExpVisitor.hh"

#include <algorithm>
#include <cmath>
#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace expression {

class ExpToZ3Visitor : public ExpVisitor {
public:
  /// @brief Constructor.
  ExpToZ3Visitor();

  /// @brief Destructor.
  virtual ~ExpToZ3Visitor() override;

  z3::expr get();
  size_t getNumberVariables();
  z3::context *getContext();

  void clear();
  void clear_keep_context();

  // proposition
  void visit(BooleanConstant &o) override;
  void visit(BooleanVariable &o) override;
  void visit(PropositionAnd &o) override;
  void visit(PropositionOr &o) override;
  void visit(PropositionXor &o) override;
  void visit(PropositionEq &o) override;
  void visit(PropositionNeq &o) override;
  void visit(PropositionNot &o) override;

  // numeric
  void visit(NumericConstant &o) override;
  void visit(NumericVariable &o) override;
  void visit(NumericSum &o) override;
  void visit(NumericSub &o) override;
  void visit(NumericMul &o) override;
  void visit(NumericDiv &o) override;
  void visit(NumericEq &o) override;
  void visit(NumericNeq &o) override;
  void visit(NumericGreater &o) override;
  void visit(NumericGreaterEq &o) override;
  void visit(NumericLess &o) override;
  void visit(NumericLessEq &o) override;
  void visit(NumericToBool &o) override;

  // logic
  void visit(LogicConstant &o) override;
  void visit(LogicVariable &o) override;
  void visit(LogicSum &o) override;
  void visit(LogicSub &o) override;
  void visit(LogicMul &o) override;
  void visit(LogicDiv &o) override;
  void visit(LogicBAnd &o) override;
  void visit(LogicBOr &o) override;
  void visit(LogicBXor &o) override;
  void visit(LogicNot &o) override;
  void visit(LogicEq &o) override;
  void visit(LogicNeq &o) override;
  void visit(LogicGreater &o) override;
  void visit(LogicGreaterEq &o) override;
  void visit(LogicLess &o) override;
  void visit(LogicLessEq &o) override;
  void visit(LogicToNumeric &o) override;
  void visit(LogicToBool &o) override;
  void visit(LogicLShift &o) override;
  void visit(LogicRShift &o) override;

protected:
  enum ope : int {
    PropositionNot = 0,
    PropositionAnd,
    PropositionOr,
    PropositionXor,
    PropositionEq,
    PropositionNeq,

    NumericSum,
    NumericSub,
    NumericMul,
    NumericDiv,
    NumericEq,
    NumericNeq,
    NumericGreater,
    NumericGreaterEq,
    NumericLess,
    NumericLessEq,

    LogicSum,
    LogicSub,
    LogicMul,
    LogicDiv,
    LogicBAnd,
    LogicBOr,
    LogicBXor,
    LogicNot,
    LogicEq,
    LogicNeq,
    LogicGreater,
    LogicGreaterEq,
    LogicLess,
    LogicLessEq,
  };

  std::stack<z3::expr> _z3Expressions;
  z3::context _c;
  z3::expr _overflowCond;

public:
  std::unordered_map<std::string, std::pair<VarType, size_t>> _varToTypeSize;
};

} // namespace oden
