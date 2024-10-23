
#pragma once

#include <string>
#include <vector>

#include "VarDeclaration.hh"
#include "support/Declarations.h"
#include "varDeclarationBaseListener.h"
#include "varDeclarationParser.h"

namespace antlr4 {
namespace tree {
class ErrorNode;
} // namespace tree
} // namespace antlr4

using namespace antlr4;

namespace hparser {

class VarDeclarationParserHandler
    : public varDeclarationBaseListener {
public:
  explicit VarDeclarationParserHandler();
  ~VarDeclarationParserHandler() override = default;

  void addErrorMessage(const std::string &msg);
  harm::VarDeclaration &getVarDeclaration();

private:
  std::string printErrorMessage();
  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;
  void exitFile(varDeclarationParser::FileContext *ctx) override;
  virtual void
  enterVarDec(varDeclarationParser::VarDecContext *ctx) override;

  std::vector<std::string> _errorMessages;
  harm::VarDeclaration _varDecl;
};

} // namespace hparser
