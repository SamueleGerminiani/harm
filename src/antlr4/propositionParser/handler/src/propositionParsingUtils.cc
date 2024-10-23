
#include <algorithm>
#include <iterator>
#include <utility>

// clang-format off
#include "PropositionParserHandler.hh"
// clang-format on
#include "ANTLRInputStream.h"
#include "CommonTokenStream.h"
#include "Float.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "message.hh"
#include "misc.hh"
#include "propositionLexer.h"
#include "propositionParser.h"
#include "propositionParsingUtils.hh"
#include "tree/ParseTreeWalker.h"

namespace antlr4 {
namespace tree {
class ParseTree;
} // namespace tree
} // namespace antlr4

namespace hparser {
using namespace expression;
expression::PropositionPtr
parseProposition(std::string formula, const harm::TracePtr &trace) {

  auto decls = trace->getDeclarations();
  addTypeToExp(formula, decls);

  // parse typed propositions
  hparser::PropositionParserHandler listener(trace);
  listener.addErrorMessage("\t\t\tIn formula: " + formula);
  antlr4::ANTLRInputStream input(formula);
  propositionLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  propositionParser parser(&tokens);
  //print tokens
  /*
    std::map<size_t, std::string> indexToToken;
    for (auto [token,index] : parser.getTokenTypeMap()) {
        indexToToken[index] = token;
    }
    for (auto &i : lexer.getAllTokens()) {
        std::cout << i->toString() <<" "<<indexToToken.at(i->getType())<<"\n";
    }
    */
  antlr4::tree::ParseTree *treeFragAnt = parser.startBoolean();
  /*
  DEBUG
  exit(0);
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  */
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  return listener.getProposition();
}

expression::IntExpressionPtr
parseIntExpression(std::string formula, const harm::TracePtr &trace) {

  auto decls = trace->getDeclarations();
  addTypeToExp(formula, decls);

  // parse typed propositions
  hparser::PropositionParserHandler listener(trace);
  listener.addErrorMessage("\t\t\tIn formula: " + formula);
  antlr4::ANTLRInputStream input(formula);
  propositionLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  propositionParser parser(&tokens);
  //print tokens
  /*
    std::map<size_t, std::string> indexToToken;
    for (auto [token,index] : parser.getTokenTypeMap()) {
        indexToToken[index] = token;
    }
    for (auto &i : lexer.getAllTokens()) {
        std::cout << i->toString() <<" "<<indexToToken.at(i->getType())<<"\n";
    }
    */
  antlr4::tree::ParseTree *treeFragAnt = parser.startInt();
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  /*
  DEBUG
  exit(0);
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  */
  return listener.getIntExpression();
}

expression::FloatExpressionPtr
parseFloatExpression(std::string formula,
                     const harm::TracePtr &trace) {

  auto decls = trace->getDeclarations();
  addTypeToExp(formula, decls);

  // parse typed propositions
  hparser::PropositionParserHandler listener(trace);
  listener.addErrorMessage("\t\t\tIn formula: " + formula);
  antlr4::ANTLRInputStream input(formula);
  propositionLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  propositionParser parser(&tokens);
  //print tokens
  /*
    std::map<size_t, std::string> indexToToken;
    for (auto [token,index] : parser.getTokenTypeMap()) {
        indexToToken[index] = token;
    }
    for (auto &i : lexer.getAllTokens()) {
        std::cout << i->toString() <<" "<<indexToToken.at(i->getType())<<"\n";
    }
    */
  antlr4::tree::ParseTree *treeFragAnt = parser.startFloat();
  /*
  DEBUG
  exit(0);
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  */

  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  return listener.getFloatExpression();
}

expression::PropositionPtr
parsePropositionAlreadyTyped(std::string formula,
                             const harm::TracePtr &trace) {

  // parse typed propositions
  hparser::PropositionParserHandler listener(trace);
  listener.addErrorMessage("\t\t\tIn formula: " + formula);
  antlr4::ANTLRInputStream input(formula);
  propositionLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  propositionParser parser(&tokens);
  antlr4::tree::ParseTree *treeFragAnt = parser.startBoolean();
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  /*
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  DEBUG
  exit(0);
  */
  return listener.getProposition();
}

static std::vector<std::string> reservedKeywords = {
    "inside",      "true",   "false",      "substr",   "and",
    "or",          "not",    "eventually", "nexttime", "next",
    "X",           "until",  "W",          "always",   "G",
    "first_match", ".substr"};
void checkReservedKeywords(const std::string &formula) {
  for (const auto &keyword : reservedKeywords) {
    if (formula == keyword) {
      messageError(
          "The keyword " + keyword +
          " is reserved (in variable declaration): " + formula);
    }
  }
}

void addTypeToExp(std::string &formula,
                  std::vector<harm::VarDeclaration> varDeclarations) {

  // match the longest variables first to solve (3)
  std::sort(begin(varDeclarations), end(varDeclarations),
            [](harm::VarDeclaration &e1, harm::VarDeclaration &e2) {
              return e1.getName().size() > e2.getName().size();
            });

  std::vector<std::pair<std::string, std::string>> varSubstitutions;
  const std::string startVar = "«";
  const std::string endVar = "»";

  // gather all the variables in the formula
  for (auto varDec : varDeclarations) {
    checkReservedKeywords(varDec.getName());
    std::string nameType = "";
    switch (varDec.getType()) {
    case ExpType::Bool:
      nameType = startVar + varDec.getName() + ",bool" + endVar;
      break;
    case ExpType::UInt:
      nameType = startVar + varDec.getName() + ",int" + endVar;
      break;
    case ExpType::SInt:
      nameType = startVar + varDec.getName() + ",int" + endVar;
      break;
    case ExpType::Float:
      nameType = startVar + varDec.getName() + ",float" + endVar;
      break;
    default:
      messageError("Variable is of \'Uknown type\'");
      break;
    }

    varSubstitutions.push_back(
        std::make_pair(varDec.getName(), nameType));

  } // end var

  auto strConstants = extractSubStringsInsideQuotes(formula);
  for (auto &c : strConstants) {
    varSubstitutions.emplace_back(c, c);
  }

  //do not allow the subtitution of these keywords
  varSubstitutions.emplace_back("true", "@true");
  varSubstitutions.emplace_back("false", "@false");
  //do not allow the subtitution of reserved keywords
  for (const std::string &rk : reservedKeywords) {
    //true and false keywords are already substituted with the @ symbol
    if (rk != "true" && rk != "false") {
      varSubstitutions.emplace_back(rk, rk);
    }
  }
  //replace all the variables in the formula
  replace(varSubstitutions, formula);
  //        debug
  //       std::cout << "After: " << formula << "\n";
}

} // namespace hparser
