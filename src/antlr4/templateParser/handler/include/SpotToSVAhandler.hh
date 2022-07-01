#pragma once

#include "Template.hh"
#include "Trace.hh"
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

class SpotToSVAhandler : public spotBaseListener {

public:
  explicit SpotToSVAhandler(harm::Trace *trace);

  ~SpotToSVAhandler() override = default;
  void addErrorMessage(const std::string &msg);
  Hstring &getConvertedFormula();
  bool _useCache = 1;

private:
  bool _abort;

  std::stack<Hstring> _subFormulas;
  harm::Trace *_trace;
  Hstring _convertedFormula;
  std::unordered_map<std::string, expression::Proposition **> _phToProp;
  std::unordered_map<std::string, std::string> _propStrToInst;
  size_t dtCount = 0;
  size_t instCount = 0;
  std::vector<std::string> _errorMessages;
  std::string printErrorMessage();

  void enterFile(spotParser::FileContext *ctx) override;
  void exitFile(spotParser::FileContext *ctx) override;
  virtual void exitFormula(spotParser::FormulaContext *ctx) override;

  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;
  virtual void exitTformula(spotParser::TformulaContext *ctx) override;
  virtual void exitSere(spotParser::SereContext *ctx) override;
};

} // namespace hparser
