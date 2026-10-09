
#include <algorithm>
#include <cctype>
#include <unordered_map>
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

class PropFatalLexerErrorListener : public antlr4::BaseErrorListener {
public:
  PropFatalLexerErrorListener() = default;
  PropFatalLexerErrorListener(std::string being_parse)
      : being_parsed(being_parse) {}
  void syntaxError(antlr4::Recognizer *recognizer,
                   antlr4::Token *offendingSymbol, size_t line,
                   size_t charPositionInLine, const std::string &msg,
                   std::exception_ptr e) override {
    messageError(
        "Lexer Error while parsing proposition '" + being_parsed +
        "', char position: " + std::to_string(charPositionInLine) +
        ", reason: " + msg);
  }

private:
  std::string being_parsed = "";
};

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
  PropFatalLexerErrorListener fatal(formula);
  lexer.addErrorListener(&fatal);
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
  PropFatalLexerErrorListener fatal(formula);
  lexer.addErrorListener(&fatal);
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

expression::LogicExpressionPtr
parseLogicExpression(std::string formula,
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
  antlr4::tree::ParseTree *treeFragAnt = parser.startLogic();
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  /*
  DEBUG
  exit(0);
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  */
  return listener.getLogicExpression();
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
  PropFatalLexerErrorListener fatal(formula);
  lexer.addErrorListener(&fatal);
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

expression::StringExpressionPtr
parseStringExpression(std::string formula,
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
  antlr4::tree::ParseTree *treeFragAnt = parser.startString();
  /*
  DEBUG
  exit(0);
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  */

  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  return listener.getStringExpression();
}

expression::PropositionPtr
parsePropositionAlreadyTyped(std::string formula,
                             const harm::TracePtr &trace) {

  // parse typed propositions
  hparser::PropositionParserHandler listener(trace);
  listener.addErrorMessage("\t\t\tIn formula: " + formula);
  antlr4::ANTLRInputStream input(formula);
  propositionLexer lexer(&input);
  PropFatalLexerErrorListener fatal(formula);
  lexer.addErrorListener(&fatal);
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

expression::PropositionPtr
tryParseProposition(std::string formula, const harm::TracePtr &trace,
                    std::string &error) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    return parseProposition(formula, trace);
  } catch (const hlog::HarmError &e) {
    error = e.what();
    return nullptr;
  }
}

static std::vector<std::string> reservedKeywords = {
    "inside",      "true",   "false",      "substr",   "and",
    "or",          "not",    "eventually", "s_eventually", "nexttime", "next",
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

namespace {
bool isIdentifierChar(char c) {
  return std::isalnum((unsigned char)c) || c == '_';
}

/// Replace whole identifiers only. A token matches at position i if
///  - it starts a word: the character before i is not part of an identifier or literal
///    ([A-Za-z0-9_$']), or the word before i consists only of the LTL unary operators X, F, G
///    written without a space (e.g. 'Xcon', 'GFa', as in Spot syntax), or only of the digits of a
///    cycle delay ('##3v2', produced by edit rules), and
///  - the character after the match cannot continue an identifier ([A-Za-z0-9_]).
/// Among the tokens matching at i, the longest wins.
/// This keeps literals such as 3'b1x0, 0xa and 8'hb1 intact when variables x, a or b1 exist.
void replaceIdentifiers(
    const std::vector<std::pair<std::string, std::string>> &tokens,
    std::string &formula) {
  std::unordered_map<char, std::vector<const std::pair<std::string,
                                                       std::string> *>>
      byFirstChar;
  for (const auto &t : tokens) {
    if (!t.first.empty()) {
      byFirstChar[t.first[0]].push_back(&t);
    }
  }
  std::string out;
  size_t i = 0;
  while (i < formula.size()) {
    //start of the word containing position i
    size_t wordStart = i;
    while (wordStart > 0 && isIdentifierChar(formula[wordStart - 1])) {
      wordStart--;
    }
    char beforeWord = wordStart == 0 ? ' ' : formula[wordStart - 1];
    bool canStart = beforeWord != '$' && beforeWord != '\'';
    if (canStart && wordStart < i) {
      //the word so far must be LTL unary operators ('Xa') or a cycle delay ('##3a')
      bool ltlOps = true, delay = beforeWord == '#';
      for (size_t k = wordStart; k < i; k++) {
        ltlOps &= formula[k] == 'X' || formula[k] == 'F' || formula[k] == 'G';
        delay &= std::isdigit((unsigned char)formula[k]) != 0;
      }
      canStart = ltlOps || delay;
    }
    const std::pair<std::string, std::string> *best = nullptr;
    if (canStart && byFirstChar.count(formula[i])) {
      for (const auto *t : byFirstChar.at(formula[i])) {
        const std::string &name = t->first;
        if (formula.compare(i, name.size(), name) != 0) {
          continue;
        }
        size_t end = i + name.size();
        if (end < formula.size() && isIdentifierChar(formula[end]) &&
            isIdentifierChar(name.back())) {
          continue;
        }
        if (best == nullptr || name.size() > best->first.size()) {
          best = t;
        }
      }
    }
    if (best != nullptr) {
      out += best->second;
      i += best->first.size();
    } else {
      out += formula[i];
      i++;
    }
  }
  formula = out;
}

/// D-032: «x,bool» becomes «x,bit» (a 1-bit logic for the parser) where it is an operand of a
/// bitwise operator: the nearest non-blank character before it is ^ or ~, or a single & or |, or
/// the nearest one after it is ^, or a single & or |; and the character before it is not !. A
/// doubled && or ||, and |-> or |=>, do not count; in templates & and | are temporal operators.
void markBitwiseBoolOperands(std::string &formula, bool inTemplate) {
  const std::string tag = ",bool»";
  auto isBlank = [](char c) { return c == ' ' || c == '\t' || c == '\n'; };
  // the operator character at i is a single & or | (not && / ||, not |-> / |=>)
  auto singleAndOr = [&](size_t i) {
    char c = formula[i];
    if (inTemplate || (c != '&' && c != '|')) {
      return false;
    }
    bool before = i > 0 && formula[i - 1] == c;
    bool after = i + 1 < formula.size() &&
                 (formula[i + 1] == c || formula[i + 1] == '-' || formula[i + 1] == '=');
    return !before && !after;
  };
  size_t pos = 0;
  while ((pos = formula.find(tag, pos)) != std::string::npos) {
    size_t start = formula.rfind("«", pos);
    size_t end = pos + tag.size();
    size_t b = start;
    while (b > 0 && isBlank(formula[b - 1])) {
      b--;
    }
    size_t a = end;
    while (a < formula.size() && isBlank(formula[a])) {
      a++;
    }
    bool opBefore = b > 0 && (formula[b - 1] == '^' || formula[b - 1] == '~' ||
                              singleAndOr(b - 1));
    bool opAfter = a < formula.size() && (formula[a] == '^' || singleAndOr(a));
    // after !, the variable stays a bool: '!a ^ b' would read as '!(a ^ b)', since HARM's ! binds
    // looser than ^ (unlike SystemVerilog); it is an error instead
    bool notBefore = b > 0 && formula[b - 1] == '!';
    if (start != std::string::npos && !notBefore && (opBefore || opAfter)) {
      formula.replace(pos, tag.size(), ",bit»");
    }
    pos = end;
  }
}
} // namespace

void addTypeToExp(std::string &formula,
                  std::vector<harm::VarDeclaration> varDeclarations,
                  bool inTemplate) {

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
    case ExpType::ULogic:
      nameType = startVar + varDec.getName() + ",logic" + endVar;
      break;
    case ExpType::SLogic:
      nameType = startVar + varDec.getName() + ",logic" + endVar;
      break;
    case ExpType::Float:
      nameType = startVar + varDec.getName() + ",float" + endVar;
      break;
    case ExpType::String:
      nameType = startVar + varDec.getName() + ",string" + endVar;
      break;
    default:
      messageError("Variable is of \'Uknown type\'");
      break;
    }

    varSubstitutions.push_back(
        std::make_pair(varDec.getName(), nameType));
    //hierarchical names can also be written with '.' (SystemVerilog style) instead of '::'
    if (varDec.getName().find("::") != std::string::npos) {
      std::string dotted = varDec.getName();
      replace("::", ".", dotted);
      varSubstitutions.push_back(std::make_pair(dotted, nameType));
    }

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
  //replace all the variables in the formula (whole identifiers only)
  replaceIdentifiers(varSubstitutions, formula);
  markBitwiseBoolOperands(formula, inTemplate);
  //        debug
  //       std::cout << "After: " << formula << "\n";
}

} // namespace hparser
