#include <algorithm>
#include <cmath>
#include <ostream>
#include <stddef.h>
#include <utility>

// clang-format off
#include "minerUtils.hh"
// clang-format on
#include "VarDeclaration.hh"
#include "VarDeclarationParserHandler.hh"
#include "message.hh"
#include "misc.hh"
#include "tree/ErrorNode.h"
#include "tree/TerminalNode.h"

namespace hparser {
VarDeclarationParserHandler::VarDeclarationParserHandler() {}

void VarDeclarationParserHandler::exitFile(
    __attribute__((unused)) varDeclarationParser::FileContext *ctx) {
  _errorMessages.clear();
}

void VarDeclarationParserHandler::enterVarDec(
    varDeclarationParser::VarDecContext *ctx) {

  size_t left;
  size_t right;
  if (ctx->range() != nullptr) {
    messageErrorIf(!ctx->range()->SINTEGER().empty(),
                   "Negative index in bit range!" +
                       printErrorMessage());
    messageErrorIf(ctx->range()->UINTEGER().empty(),
                   "Invalid range!" + printErrorMessage());

    left = safeStoull(ctx->range()->UINTEGER()[0]->getText());
    if (ctx->range()->UINTEGER().size() > 1) {
      right = safeStoull(ctx->range()->UINTEGER()[1]->getText());
      messageErrorIf(left < right,
                     "Invalid range: ascending bit ordering in "
                     "declaration range is not supported!" +
                         printErrorMessage());
    } else {
      right = 0;
    }
  }

  std::pair<std::string, size_t> type =
      std::make_pair(ctx->VARTYPE()->getText(),
                     (!ctx->range() ? 1 : left - right + 1));

  std::string name = ctx->Name()->getText();
  //remove « and »
  name = name.substr(2, name.size() - 4);
  _varDecl = harm::toVarDeclaration(name, type.first, type.second);
  _varDecl.setBase(harm::getTypeBase(type.first));
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
void VarDeclarationParserHandler::addErrorMessage(
    const std::string &msg) {
  _errorMessages.push_back(msg);
}

harm::VarDeclaration &
VarDeclarationParserHandler::getVarDeclaration() {
  return _varDecl;
}
} // namespace hparser
