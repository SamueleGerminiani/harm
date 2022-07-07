#include "MetricParserHandler.hh"

#include <vector>

#define CHECK_ABORT                                                            \
  if (_abort)                                                                  \
    return;

namespace hparser {
using namespace expression;

MetricParserHandler::MetricParserHandler(harm::Trace *trace)
    : _abort(false), _logicExpressions(), _numericExpressions(), _trace(trace) {
}

void MetricParserHandler::exitFile(__attribute__((unused))
                                   metricParser::FileContext *ctx) {
  _errorMessages.clear();
}
void MetricParserHandler::enterFile(__attribute__((unused))
                                    metricParser::FileContext *ctx) {
  _abort = false;

  _metric = new harm::Metric();
}

void MetricParserHandler::enterLogicConstant(
    metricParser::LogicConstantContext *ctx) {
  std::string conStr = std::string(ctx->getText());

  if (ctx->VERILOG_BINARY() != nullptr) {
    messageErrorIf(conStr.size() - 2 > 64,
                   "Constant '" + conStr.substr(0, conStr.size()) +
                       "' exceeds the maximum length of 64 bits"+printErrorMessage());
    ULogic value = std::stoull(conStr.substr(2, conStr.size() - 2), nullptr, 2);
    auto *c = new LogicConstant(value, VarType::ULogic, conStr.size() - 2,
                                _trace->getLength());
    _logicExpressions.push(c);
    return;
  } else if (ctx->GCC_BINARY() != nullptr) {
    messageErrorIf(conStr.size() - 2 > 64,
                   "Constant '" + conStr.substr(0, conStr.size()) +
                       "' exceeds the maximum length of 64 bits"+printErrorMessage());
    ULogic value = std::stoull(conStr.substr(2, conStr.size() - 2), nullptr, 2);
    auto *c = new LogicConstant(value, VarType::ULogic, conStr.size() - 2,
                                _trace->getLength());
    _logicExpressions.push(c);
    return;
  } else if (ctx->HEX() != nullptr) {
    messageErrorIf((conStr.size() - 2) * 4 > 64,
                   "Constant '" + conStr.substr(0, conStr.size()) +
                       "' exceeds the maximum length of 64 bits"+printErrorMessage());
    ULogic value = std::stoull(conStr.substr(2, conStr.size() - 2), nullptr, 16);
    auto *c = new LogicConstant(value, VarType::ULogic, (conStr.size() - 2) * 4,
                                _trace->getLength());
    _logicExpressions.push(c);
    return;
  } else if (ctx->NUMERIC() != nullptr) {
    size_t res = conStr.find('.');
    if (res != std::string::npos) {
      messageWarning("Float literal truncated to integer"+printErrorMessage());
      conStr = conStr.substr(0, res);
    }

    if (std::stoll(conStr) < 0) {
      // Store the logic as 2s complement int
      ULogic value = std::stoll(conStr);
      std::cout << value << "\n";
      auto *c =
          new LogicConstant(value, VarType::SLogic,
                            (size_t)(value != 0 ? std::log2(value) + 2 : 1),
                            _trace->getLength());
      _logicExpressions.push(c);
    } else {
      // Store the logic as classic unsigned binary
      ULogic value = std::stoull(conStr);
      auto *c =
          new LogicConstant(value, VarType::ULogic,
                            (size_t)(value != 0 ? std::log2(value) + 1 : 1),
                            _trace->getLength());
      _logicExpressions.push(c);
    }
    return;
  }
  messageError("Unknown logic constant!"+printErrorMessage());
}
void MetricParserHandler::enterNumericConstant(
    metricParser::NumericConstantContext *ctx) {
  if (ctx->NUMERIC() != nullptr) {
    Numeric value = std::stod(ctx->getText());
    auto *c =
        new NumericConstant(value, VarType::Numeric, 64, _trace->getLength());
    _numericExpressions.push(c);
    return;
  }
}

void MetricParserHandler::enterLogicVariable(
    metricParser::LogicVariableContext *ctx) {
  metricParser::VariableContext *tNode = ctx->variable();
  std::string varName = std::string(tNode->getText());
  // //std::cout << __func__ << ": " << varName << std::endl;

  if (ctx->SIGN() != nullptr && ctx->NUMERIC() != nullptr) {
    LogicConstant *newVar =
        new LogicConstant(0, VarType::ULogic, 32, _trace->getLength());
    _metric->_nameToLogicVarInMetric[varName] = newVar;
    _metric->_vars.push_back(varName);
    _logicExpressions.push(newVar);
  } else {
    messageError("Sign or size not set in logic variable"+printErrorMessage());
  }
}
void MetricParserHandler::enterNumericVariable(
    metricParser::NumericVariableContext *ctx) {
  metricParser::VariableContext *tNode = ctx->variable();
  std::string varName = std::string(tNode->getText());
  // //std::cout << __func__ << ": " << varName << std::endl;

  if (ctx->NUMERIC() != nullptr) {
    size_t size = std::stoul(ctx->NUMERIC()->toString());
    NumericConstant *newVar =
        new NumericConstant(99, VarType::ULogic, size, _trace->getLength());
    _metric->_nameToNumericVarInMetric[varName] = newVar;
    _metric->_vars.push_back(varName);
    _numericExpressions.push(newVar);
  } else {
    messageError("Size not set in numeric variable"+printErrorMessage());
  }
}
void MetricParserHandler::exitLogic(metricParser::LogicContext *ctx) {
  // std::cout<<__func__<<std::endl;

  if (ctx->LPAREN() && ctx->RPAREN()) {
    return;
  }

  if (ctx->logic().size() == 1) {
    if (ctx->NEG() != nullptr) {
      LogicExpression *le_r = makeExpression<LogicNot>(_logicExpressions.top());
      _logicExpressions.pop();
      _logicExpressions.push(le_r);
      return;
    }

    messageError("Unknown unary logic operator in logic expression!"+printErrorMessage());

  } else if (ctx->logic().size() == 2) {
    antlr4::Token *logop = ctx->logop;

    if (logop != nullptr) {
      LogicExpression *le2 = _logicExpressions.top();
      _logicExpressions.pop();

      LogicExpression *le1 = _logicExpressions.top();
      _logicExpressions.pop();

      auto conversionResult =
          applyCStandardConversion(le1->getType(), le1->getType());

      if (logop->getText() == "&") {
        LogicExpression *le_r = makeExpression<LogicBAnd>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }
      if (logop->getText() == "|") {
        LogicExpression *le_r = makeExpression<LogicBOr>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }
      if (logop->getText() == "^") {
        LogicExpression *le_r = makeExpression<LogicBXor>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }
      if (logop->getText() == "<<") {
        LogicExpression *le_r = makeExpression<LogicLShift>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }
      if (logop->getText() == ">>") {
        LogicExpression *le_r = makeExpression<LogicRShift>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }

      messageError("Unknown binary logic operator in logic "
                   "expression!"+printErrorMessage());
    }
  }
}
void MetricParserHandler::exitNumeric(metricParser::NumericContext *ctx) {
  // std::cout<<__func__<<std::endl;

  if (ctx->LPAREN() && ctx->RPAREN()) {
    return;
  }

  if (_logicExpressions.size() == 1) {
    LogicExpression *le = _logicExpressions.top();
    _logicExpressions.pop();
    _numericExpressions.push(new LogicToNumeric(le));
    return;
  }

  if (ctx->numeric().size() == 1) {
    messageError("Unknown unary numeric operator in logic expression!"+printErrorMessage());
  } else if (ctx->numeric().size() == 2) {
    antlr4::Token *artop = ctx->artop;

    if (artop != nullptr) {
      NumericExpression *ne2 = _numericExpressions.top();
      _numericExpressions.pop();

      NumericExpression *ne1 = _numericExpressions.top();
      _numericExpressions.pop();

      auto conversionResult =
          applyCStandardConversion(ne1->getType(), ne2->getType());

      if (artop->getText() == "*") {
        NumericExpression *ne_r = makeExpression<NumericMul>(ne1, ne2);
        ne_r->setType(conversionResult.first, conversionResult.second);
        _numericExpressions.push(ne_r);
        return;
      }
      if (artop->getText() == "/") {
        NumericExpression *ne_r = makeExpression<NumericDiv>(ne1, ne2);
        ne_r->setType(conversionResult.first, conversionResult.second);
        _numericExpressions.push(ne_r);
        return;
      }
      if (artop->getText() == "-") {
        NumericExpression *ne_r = makeExpression<NumericSub>(ne1, ne2);
        ne_r->setType(conversionResult.first, conversionResult.second);
        _numericExpressions.push(ne_r);
        return;
      }
      if (artop->getText() == "+") {
        NumericExpression *ne_r = makeExpression<NumericSum>(ne1, ne2);
        ne_r->setType(conversionResult.first, conversionResult.second);
        _numericExpressions.push(ne_r);
        return;
      }
      messageError("Unknown binary arithmetic operator in numeric "
                   "expression!"+printErrorMessage());
    }
  }
}

harm::Metric *MetricParserHandler::getMetric() {
  messageErrorIf(_numericExpressions.size() != 1, ""+printErrorMessage());

  _metric->_exp = _numericExpressions.top();

  _numericExpressions.pop();

  return _metric;
}
std::string MetricParserHandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void MetricParserHandler::visitErrorNode(__attribute__((unused))
                                         antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}
void MetricParserHandler::addErrorMessage(const std::string &msg) {
  _errorMessages.push_back(msg);
}
} // namespace hparser
