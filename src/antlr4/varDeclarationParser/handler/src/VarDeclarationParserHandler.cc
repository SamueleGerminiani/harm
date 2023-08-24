#include "VarDeclarationParserHandler.hh"

#define CHECK_ABORT                                                            \
  if (_abort)                                                                  \
    return;

namespace hparser {
VarDeclarationParserHandler::VarDeclarationParserHandler() {}

void VarDeclarationParserHandler::exitFile(
    __attribute__((unused)) varDeclarationParser::FileContext *ctx) {
  _errorMessages.clear();
}

void VarDeclarationParserHandler::enterVarDec(
    varDeclarationParser::VarDecContext *ctx) {

  auto type = std::make_pair(
      ctx->VARTYPE()->getText(),
      (ctx->LOGIC_CONSTANT().empty()
           ? 0
           : std::max(std::stoul(ctx->LOGIC_CONSTANT()[0]->getText()),
                      std::stoul(ctx->LOGIC_CONSTANT()[1]->getText()))));

  std::string name=ctx->Name()->getText();
  name = name.substr(2, name.size() - 4);


  _varDecl = std::make_pair(name, type);
}
std::string VarDeclarationParserHandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void VarDeclarationParserHandler::visitErrorNode(
    __attribute__((unused)) antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}
void VarDeclarationParserHandler::addErrorMessage(const std::string &msg) {
  _errorMessages.push_back(msg);
}
} // namespace hparser
