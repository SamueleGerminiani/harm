
#pragma once

#include "BDTLimits.hh"
#include "limitsBaseListener.h"

#include <cmath>
#include <stack>
#include <string>

namespace hparser {
using namespace antlr4;

class BDTLimitsParserHandler : public limitsBaseListener {

public:
  explicit BDTLimitsParserHandler();

  ~BDTLimitsParserHandler() override = default;

  harm::BDTLimits getLimits() ;
  std::unordered_set<std::string> getSetOptions();
  void addErrorMessage(const std::string &msg);

private:
  bool _abort;
  std::vector<std::string> _errorMessages;

  std::string printErrorMessage();
  virtual void enterFile(limitsParser::FileContext *ctx) override;
  void exitFile(limitsParser::FileContext *ctx) override;

  virtual void enterParameter(limitsParser::ParameterContext *ctx) override;

  virtual void enterAtom(limitsParser::AtomContext *ctx) override;

  virtual void enterDep(limitsParser::DepContext *ctx) override;

  virtual void enterWidth(limitsParser::WidthContext *ctx) override;

  virtual void enterAll(limitsParser::AllContext *ctx) override;

  virtual void enterOffset(limitsParser::OffsetContext *ctx) override;

  virtual void enterNegated(limitsParser::NegatedContext *ctx) override;

  virtual void enterEffort(limitsParser::EffortContext *ctx) override;

  virtual void enterStrategy(limitsParser::StrategyContext *ctx) override;

  virtual void enterEveryRule(antlr4::ParserRuleContext *ctx) override;
  virtual void visitTerminal(antlr4::tree::TerminalNode *node) override;

  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;

  harm::BDTLimits _limits;
  std::unordered_set<std::string> _setOptions;
};
} // namespace hparser
