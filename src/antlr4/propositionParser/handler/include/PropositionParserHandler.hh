
#pragma once
#include <unordered_map>

#include <stack>
#include <stddef.h>
#include <string>
#include <utility>
#include <vector>

#include "expUtils/ExpType.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/expression/TypeCast.hh"
#include "message.hh"
#include "propositionBaseListener.h"
#include "propositionParser.h"

namespace antlr4 {
namespace tree {
class ErrorNode;
} // namespace tree
} // namespace antlr4
namespace harm {
class Trace;
} // namespace harm

namespace hparser {

class PropositionParserHandler : public propositionBaseListener {

public:
  //------NumericPack---------------------------
  enum class NumericType {
    NumericInt,
    NumericLogic,
    NumericFloat,
    NumericUnknown
  };

  /// \brief NumericPack is a wrapper for a generic numeric expression.
  struct NumericPack {
    NumericPack();
    NumericPack(const expression::LogicExpressionPtr &logExp);
    NumericPack(const expression::IntExpressionPtr &intExp);
    NumericPack(const expression::FloatExpressionPtr &floatExp);

    expression::IntExpressionPtr _intExp;
    expression::LogicExpressionPtr _logExp;
    expression::FloatExpressionPtr _floatExp;

    std::pair<expression::ExpType, size_t> getType();

    /// \brief Convert the expression to the given type.
    void convert(NumericType toType);
  };

  /// \brief Apply implicit conversion to the given types.
  void
  convert(NumericPack &exp1, NumericPack &exp2,
          std::pair<expression::ExpType, size_t> conversionResult);

  //------NumericStack---------------------------
  class NumericStack {

  public:
    NumericStack() = default;
    ~NumericStack() = default;

    // Push the given expression to the stack.
    void push(expression::IntExpressionPtr exp);
    void push(expression::LogicExpressionPtr exp);
    void push(expression::FloatExpressionPtr exp);

    void pop();

    expression::FloatExpressionPtr topFloat();
    expression::IntExpressionPtr topInt();
    expression::LogicExpressionPtr topLogic();

    bool isTopFloat();
    bool isTopInt();
    bool isTopLogic();

    NumericPack top();

    bool empty();
    size_t size();

    std::string printStack();

  private:
    std::stack<NumericPack> _expressions;
  };

  bool isEmpty(const NumericPack &p);

  // ----------PropositionParserHandler----------------
public:
  explicit PropositionParserHandler(const harm::TracePtr &trace);

  ~PropositionParserHandler() override = default;

  expression::PropositionPtr getProposition();
  expression::IntExpressionPtr getIntExpression();
  expression::LogicExpressionPtr getLogicExpression();
  expression::StringExpressionPtr getStringExpression();
  expression::FloatExpressionPtr getFloatExpression();
  void addErrorMessage(const std::string &msg);

private:
  std::string printErrorMessage();

  void exitBoolean(propositionParser::BooleanContext *ctx) override;
  virtual void
  exitNumeric(propositionParser::NumericContext *ctx) override;
  virtual void
  exitString(propositionParser::StringContext *ctx) override;

  void exitBooleanAtom(
      propositionParser::BooleanAtomContext *ctx) override;
  virtual void
  exitIntAtom(propositionParser::IntAtomContext *ctx) override;
  virtual void
  exitLogicAtom(propositionParser::LogicAtomContext *ctx) override;
  void exitLogic_constant(
      propositionParser::Logic_constantContext *ctx) override;
  void exitConcatenation(
      propositionParser::ConcatenationContext *ctx) override;
  void exitNumericTernary(
      propositionParser::NumericTernaryContext *ctx) override;
  void exitBooleanTernary(
      propositionParser::BooleanTernaryContext *ctx) override;

  /// fill literals ('0 '1 'x 'z) waiting for the width of the other operand
  std::unordered_map<expression::LogicExpression *, char> _fillLiterals;
  bool isFill(NumericPack &p);
  /// if one of the operands is a fill literal, replace it with a constant as wide as the other
  void resolveFill(NumericPack &a, NumericPack &b);
  /// error if a fill literal never got a width
  void checkNoUnresolvedFill();
  /// D-034: a number as a Boolean (true where it has a known 1 bit); a Boolean that was made a
  /// number (BoolToLogic) is given back as it was, so that trees keep their pre-D-034 shape
  expression::PropositionPtr toBool(NumericPack np);
  /// D-034: a Boolean as a 1-bit number
  NumericPack toNumber(const expression::PropositionPtr &p);
  /// D-035: SystemVerilog's context-determined operands (IEEE 1800-2017 11.6.1, 11.8.2): the
  /// width and signedness of a context (a comparison, a condition, a ?: or an inside) are given to
  /// its context-determined operands, recursively (+ - * / & | ^ ~ unary -, the left operand of a
  /// shift, the branches of ?:); not to self-determined ones (shift amounts, selects,
  /// concatenation items, function arguments, the operands of a nested comparison)
  void toContext(NumericPack &np, std::pair<expression::ExpType, size_t> context);
  /// D-034: the comparison op (< <= > >= == != === !==) of two numbers, as a proposition
  expression::PropositionPtr compare(NumericPack e1, NumericPack e2,
                                     const std::string &op);
  virtual void
  exitStringAtom(propositionParser::StringAtomContext *ctx) override;
  void exitInt_constant(
      propositionParser::Int_constantContext *ctx) override;
  virtual void
  exitFloatAtom(propositionParser::FloatAtomContext *ctx) override;
  virtual void enterNonTemporalFunction(
      propositionParser::NonTemporalFunctionContext *ctx) override;
  /// D-034: the sizes of the two stacks when a function starts: its result goes to the stack
  /// of its argument's kind ($past of a number is a number), whatever the grammar position
  std::unordered_map<propositionParser::NonTemporalFunctionContext *,
                     std::pair<size_t, size_t>>
      _functionStart;
  virtual void exitNonTemporalFunction(
      propositionParser::NonTemporalFunctionContext *ctx) override;
  virtual void
  exitSm_range(propositionParser::Sm_rangeContext *ctx) override;

  virtual void exitSm_constant(
      propositionParser::Sm_constantContext *ctx) override;
  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;

  virtual void enterStartBoolean(
      propositionParser::StartBooleanContext *ctx) override;

  virtual void
  enterStartInt(propositionParser::StartIntContext *ctx) override;

  virtual void
  enterStartFloat(propositionParser::StartFloatContext *ctx) override;
  virtual void enterStartString(
      propositionParser::StartStringContext *ctx) override;
  virtual void
  enterStartLogic(propositionParser::StartLogicContext *ctx) override;

  void clear();

  std::stack<expression::PropositionPtr> _proposition;
  NumericStack _numericExpressions;
  std::stack<expression::StringExpressionPtr> _string;

  //SetMembership stacks----------------------
  std::stack<std::pair<NumericPack, NumericPack>> _sm_ranges;
  std::stack<NumericPack> _sm_constants;
  //-----------------------------------------

  harm::TracePtr _trace;

  std::vector<std::string> _errorMessages;
};
} // namespace hparser
