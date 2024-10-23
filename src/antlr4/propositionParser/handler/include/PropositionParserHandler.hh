
#pragma once

#include <stack>
#include <stddef.h>
#include <string>
#include <utility>
#include <vector>

#include "expUtils/ExpType.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
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
  enum class NumericType { NumericInt, NumericFloat, NumericUnknown };

  /// \brief NumericPack is a wrapper for a generic numeric expression.
  struct NumericPack {
    NumericPack();
    NumericPack(const expression::IntExpressionPtr &intExp);
    NumericPack(const expression::FloatExpressionPtr &floatExp);

    expression::IntExpressionPtr _intExp;
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
    void push(expression::FloatExpressionPtr exp);

    void pop();

    expression::FloatExpressionPtr topFloat();
    expression::IntExpressionPtr topInt();

    bool isTopFloat();
    bool isTopInt();

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
  expression::FloatExpressionPtr getFloatExpression();
  void addErrorMessage(const std::string &msg);

private:
  std::string printErrorMessage();

  void exitBoolean(propositionParser::BooleanContext *ctx) override;
  virtual void
  exitNumeric(propositionParser::NumericContext *ctx) override;

  void exitBooleanAtom(
      propositionParser::BooleanAtomContext *ctx) override;
  virtual void
  exitIntAtom(propositionParser::IntAtomContext *ctx) override;
  void exitInt_constant(
      propositionParser::Int_constantContext *ctx) override;
  virtual void
  exitFloatAtom(propositionParser::FloatAtomContext *ctx) override;
  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;

  virtual void enterStartBoolean(
      propositionParser::StartBooleanContext *ctx) override;

  virtual void
  enterStartInt(propositionParser::StartIntContext *ctx) override;

  virtual void
  enterStartFloat(propositionParser::StartFloatContext *ctx) override;

  void clear();

  std::stack<expression::PropositionPtr> _proposition;
  NumericStack _numericExpressions;

  //SetMembership stacks----------------------
  std::stack<std::pair<NumericPack, NumericPack>> _sm_ranges;
  std::stack<NumericPack> _sm_constants;
  //-----------------------------------------

  harm::TracePtr _trace;

  std::vector<std::string> _errorMessages;
};
} // namespace hparser
