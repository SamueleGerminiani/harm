#include "BDTLimitsParserHandler.hh"
#include "message.hh"
#include <string>

#define CHECK_ABORT                                                            \
  if (_abort)                                                                  \
    return;

namespace hparser {

BDTLimitsParserHandler::BDTLimitsParserHandler() : _abort(false) {}

void BDTLimitsParserHandler::exitFile(__attribute__((unused))
                                        limitsParser::FileContext *ctx) {
  _errorMessages.clear();
}
void BDTLimitsParserHandler::enterFile(limitsParser::FileContext *ctx) {}

void BDTLimitsParserHandler::enterParameter(
    limitsParser::ParameterContext *ctx) {}

void BDTLimitsParserHandler::enterAtom(limitsParser::AtomContext *ctx) {}

void BDTLimitsParserHandler::enterDep(limitsParser::DepContext *ctx) {
  _limits._maxDepth = std::stoull(ctx->NUMERIC()->getText());
  _setOptions.insert("D");
}

void BDTLimitsParserHandler::enterWidth(limitsParser::WidthContext *ctx) {
  _limits._maxWidth = std::stoull(ctx->NUMERIC()->getText());
  _setOptions.insert("W");
}

void BDTLimitsParserHandler::enterAll(limitsParser::AllContext *ctx) {
  _limits._maxAll = std::stoull(ctx->NUMERIC()->getText());
  _setOptions.insert("A");
}

void BDTLimitsParserHandler::enterOffset(limitsParser::OffsetContext *ctx) {
  _limits._saveOffset = ctx->NOT() == nullptr;
  _setOptions.insert("O");
}

void BDTLimitsParserHandler::enterNegated(limitsParser::NegatedContext *ctx) {
  _limits._useNegatedProps = ctx->NOT() == nullptr;
  _setOptions.insert("N");
}

void BDTLimitsParserHandler::enterEffort(limitsParser::EffortContext *ctx) {
  _limits._bdtRange = std::stod(ctx->NUMERIC()->getText());
  _setOptions.insert("E");
}

void BDTLimitsParserHandler::enterStrategy(limitsParser::StrategyContext *ctx) {
  _limits._isRandomConstructed = ctx->RAN() != nullptr;
  _setOptions.insert("Strategy");
}

void BDTLimitsParserHandler::enterEveryRule(antlr4::ParserRuleContext *ctx) {}
void BDTLimitsParserHandler::visitTerminal(antlr4::tree::TerminalNode *node) {}

harm::BDTLimits BDTLimitsParserHandler::getLimits() { return _limits; }
std::unordered_set<std::string> BDTLimitsParserHandler::getSetOptions() {
  return _setOptions;
}
std::string BDTLimitsParserHandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void BDTLimitsParserHandler::visitErrorNode(__attribute__((unused))
                                            antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}
void BDTLimitsParserHandler::addErrorMessage(const std::string &msg) {
  _errorMessages.push_back(msg);
}
} // namespace hparser
