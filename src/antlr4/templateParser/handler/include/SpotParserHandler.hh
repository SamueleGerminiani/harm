#pragma once

#include "Hstring.hh"
#include "Trace.hh"
#include "classes/function/Function.hh"
#include "exp.hh"
#include "spotBaseListener.h"

#include <cmath>
#include <stack>
#include <string>
#include <unordered_map>

namespace harm {
class Template;
}
namespace hparser {

class SpotParserHandler : public spotBaseListener {

public:
  explicit SpotParserHandler(harm::Trace *trace);

  ~SpotParserHandler() override = default;

  Hstring &getTemplateFormula();
  void addErrorMessage(const std::string &msg);

  bool _useCache = 1;

private:
  bool _abort;

  std::stack<Hstring> _subFormulas;
  harm::Trace *_trace;
  Hstring _templateFormula;
  std::unordered_map<std::string, expression::Proposition **> _phToProp;
  std::unordered_map<std::string, expression::Proposition **> _instToProp;
  std::unordered_map<std::string, expression::Function<expression::Proposition,expression::Proposition> * > _funIDtoFun;
  std::unordered_map<std::string, std::string> _propStrToInst;
  std::unordered_map<std::string, std::string> _funStrToFunID;
  size_t dtCount = 0;
  size_t instCount = 0;
  size_t funCount = 0;
  std::vector<std::string> _errorMessages;
  std::string printErrorMessage();

  void enterFile(spotParser::FileContext *ctx) override;
  void exitFile(spotParser::FileContext *ctx) override;
  virtual void exitFormula(spotParser::FormulaContext *ctx) override;
  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;
  virtual void exitTformula(spotParser::TformulaContext *ctx) override;
  virtual void exitSere(spotParser::SereContext *ctx) override;
  std::string handleNewPP(const std::string &ph);
  std::string handleNewInst(const std::string &prop);
  std::string handleNewFunc(const std::string &funStr,const std::string &nonTemporalExp, bool containsPH);
};

} // namespace hparser
