#include "DTLimitsParserHandler.hh"
#include "message.hh"
#include <string>

#define CHECK_ABORT                                                            \
  if (_abort)                                                                  \
    return;

namespace hparser {

DTLimitsParserHandler::DTLimitsParserHandler() : _abort(false) {}

void DTLimitsParserHandler::exitFile(__attribute__((unused))
                                        limitsParser::FileContext *ctx) {
  _errorMessages.clear();
}
void DTLimitsParserHandler::enterFile(limitsParser::FileContext *ctx) {}

void DTLimitsParserHandler::enterParameter(
    limitsParser::ParameterContext *ctx) {}

void DTLimitsParserHandler::enterAtom(limitsParser::AtomContext *ctx) {}

void DTLimitsParserHandler::enterDep(limitsParser::DepContext *ctx) {
  _limits._maxDepth = std::stoull(ctx->NUMERIC()->getText());
  _setOptions.insert("D");
}

void DTLimitsParserHandler::enterWidth(limitsParser::WidthContext *ctx) {
  _limits._maxWidth = std::stoull(ctx->NUMERIC()->getText());
  _setOptions.insert("W");
}

void DTLimitsParserHandler::enterAll(limitsParser::AllContext *ctx) {
  _limits._maxAll = std::stoull(ctx->NUMERIC()->getText());
  _setOptions.insert("A");
}

void DTLimitsParserHandler::enterOffset(limitsParser::OffsetContext *ctx) {
  _limits._saveOffset = ctx->NOT() == nullptr;
  _setOptions.insert("O");
}

void DTLimitsParserHandler::enterNegated(limitsParser::NegatedContext *ctx) {
  _limits._useNegatedProps = ctx->NOT() == nullptr;
  _setOptions.insert("N");
}

void DTLimitsParserHandler::enterEffort(limitsParser::EffortContext *ctx) {
  _limits._dtRange = std::stod(ctx->NUMERIC()->getText());
  _setOptions.insert("E");
}

void DTLimitsParserHandler::enterStrategy(limitsParser::StrategyContext *ctx) {
  _limits._isRandomConstructed = ctx->RAN() != nullptr;
  _setOptions.insert("Strategy");
}

void DTLimitsParserHandler::enterEveryRule(antlr4::ParserRuleContext *ctx) {}
void DTLimitsParserHandler::visitTerminal(antlr4::tree::TerminalNode *node) {}

harm::DTLimits DTLimitsParserHandler::getLimits() { return _limits; }
std::unordered_set<std::string> DTLimitsParserHandler::getSetOptions() {
  return _setOptions;
}
std::string DTLimitsParserHandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void DTLimitsParserHandler::visitErrorNode(__attribute__((unused))
                                            antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}
void DTLimitsParserHandler::addErrorMessage(const std::string &msg) {
  _errorMessages.push_back(msg);
}
} // namespace hparser
