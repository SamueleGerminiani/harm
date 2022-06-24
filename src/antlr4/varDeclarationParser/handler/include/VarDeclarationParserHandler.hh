
#pragma once

#include "exp.hh"
#include "varDeclarationBaseListener.h"

#include <cmath>
#include <stack>
#include <string>

using namespace antlr4;

namespace hparser {

using Name = std::string;
using Type = std::pair<std::string, size_t>;
using VarDeclaration = std::pair<Name, Type>;
class VarDeclarationParserHandler : public varDeclarationBaseListener {
public:
  explicit VarDeclarationParserHandler();

  ~VarDeclarationParserHandler() override = default;

  virtual void enterVarDec(varDeclarationParser::VarDecContext *ctx) override;

  void addErrorMessage(const std::string &msg);
  VarDeclaration &getVarDeclaration() { return _varDecl; }

private:
  std::string printErrorMessage();
  std::vector<std::string> _errorMessages;
  bool _abort;

  VarDeclaration _varDecl;
  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;
  void exitFile(varDeclarationParser::FileContext *ctx) override;
};

} // namespace hparser
