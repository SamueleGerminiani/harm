#include "PropositionParserHandler.hh"

#define CHECK_ABORT                                                            \
  if (_abort)                                                                  \
    return;

namespace hparser {
using namespace expression;

PropositionParserHandler::PropositionParserHandler(harm::Trace *trace)
    : _abort(false), _proposition(), _logicExpressions(), _numericExpressions(),
      _trace(trace) {}

void PropositionParserHandler::exitFile(__attribute__((unused))
                                        propositionParser::FileContext *ctx) {
  _errorMessages.clear();
}
void PropositionParserHandler::enterFile(__attribute__((unused))
                                         propositionParser::FileContext *ctx) {
  _abort = false;

  while (!_proposition.empty()) {
    delete _proposition.top();
    _proposition.pop();
  }

  while (!_numericExpressions.empty()) {
    delete _numericExpressions.top();
    _numericExpressions.pop();
  }

  while (!_logicExpressions.empty()) {
    delete _logicExpressions.top();
    _logicExpressions.pop();
  }
}

struct VariableParsedData {
  std::string variable;
  char sign;
  size_t numeric;
};

VariableParsedData parseBooleanVariable(const std::string &input) {
  size_t startDelimiterPos = input.find("«");
  size_t endDelimiterPos = input.rfind("»");
  size_t boolPos = input.find(",bool");

  if (startDelimiterPos == std::string::npos ||
      endDelimiterPos == std::string::npos || boolPos == std::string::npos) {
    messageError("Invalid string format in parseBooleanVariable: " + input);
  }

  return {
      input.substr(startDelimiterPos + 2, boolPos - (startDelimiterPos + 2)),
      'u', 0};
}

VariableParsedData parseNumericVariable(const std::string &input) {
  size_t startDelimiterPos = input.find("«");
  size_t endDelimiterPos = input.rfind("»");
  size_t numericPos = input.find("numeric(");
  size_t openParenthesisPos = input.find('('); 
  size_t firstComma = input.find(','); 
  size_t closingParenthesisPos =
      input.find(')', numericPos + 8); 

  if (startDelimiterPos == std::string::npos ||
      endDelimiterPos == std::string::npos || numericPos == std::string::npos || closingParenthesisPos == std::string::npos ) {
    messageError("Invalid string format in parseNumericVariable: " + input);
  }

  std::string numericStr =
      input.substr(openParenthesisPos + 1, closingParenthesisPos - (openParenthesisPos + 1));
  if (!numericStr.empty() &&
      !std::all_of(numericStr.begin(), numericStr.end(), ::isdigit)) {
    messageError("Invalid NUMERIC value '"+std::string({numericStr})+"' in parseNumericVariable: "+input);
  }

  return {input.substr(startDelimiterPos + 2,
                       firstComma - (startDelimiterPos + 2)),
          's', std::stoull(numericStr)};
}

VariableParsedData parseLogicVariable(const std::string &input) {
  size_t startDelimiterPos = input.find("«");
  size_t endDelimiterPos = input.rfind("»");
  size_t logicPos = input.find("logic(");
  size_t comma1Pos = input.find(',', startDelimiterPos); 
  size_t comma2Pos = input.find(',', comma1Pos+1);
  size_t closingParenthesisPos = input.find(')', comma2Pos + 1);
  //print all the positions
  std::cout << "startDelimiterPos: " << input[startDelimiterPos] << std::endl;
  std::cout << "endDelimiterPos: " << input[endDelimiterPos] << std::endl;
  std::cout << "comma1Pos: " << input[comma1Pos] << std::endl;
  std::cout << "logicPos: " << input[logicPos] << std::endl;
  std::cout << "comma2Pos: " << input[comma2Pos] << std::endl;
  std::cout << "closingParenthesisPos: " << input[closingParenthesisPos] << std::endl;


  if (startDelimiterPos == std::string::npos ||
      endDelimiterPos == std::string::npos || logicPos == std::string::npos ||
      comma2Pos == std::string::npos ) {
    messageError("Invalid string format in parseLogicVariable: " + input);
  }

  char parsedSign = input[comma2Pos - 1];

  if (parsedSign != 's' && parsedSign != 'u') {
    messageError("Invalid SIGN '"+std::string({parsedSign})+"' value in parseLogicVariable: "+input);
  }

  std::string numericStr =
      input.substr(comma2Pos+1, closingParenthesisPos - (comma2Pos + 1));
  if (numericStr.empty() ||
      !std::all_of(numericStr.begin(), numericStr.end(), ::isdigit)) {
    messageError("Invalid NUMERIC value '"+std::string({numericStr})+"' in parseLogicVariable: "+input);
  }

  size_t parsedNumeric = numericStr.empty() ? 0 : std::stoull(numericStr);

  return {input.substr(startDelimiterPos + 2,
                       comma1Pos - (startDelimiterPos + 2)),
          parsedSign, parsedNumeric};
}

//void PropositionParserHandler::enterLogicConstant(
//    propositionParser::LogicConstantContext *ctx) {
//  std::string conStr = std::string(ctx->getText());
//
//  if (ctx->VERILOG_BINARY() != nullptr) {
//    messageErrorIf(conStr.size() - 2 > 64,
//                   "Constant '" + conStr.substr(0, conStr.size()) +
//                       "' exceeds the maximum length of 64 bits" +
//                       printErrorMessage());
//    ULogic value = std::stoull(conStr.substr(2, conStr.size() - 2), nullptr, 2);
//    auto *c = new LogicConstant(value, VarType::ULogic, conStr.size() - 2,
//                                _trace->getLength());
//    _logicExpressions.push(c);
//    return;
//  } else if (ctx->GCC_BINARY() != nullptr) {
//    messageErrorIf(conStr.size() - 2 > 64,
//                   "Constant '" + conStr.substr(0, conStr.size()) +
//                       "' exceeds the maximum length of 64 bits" +
//                       printErrorMessage());
//    ULogic value = std::stoull(conStr.substr(2, conStr.size() - 2), nullptr, 2);
//    auto *c = new LogicConstant(value, VarType::ULogic, conStr.size() - 2,
//                                _trace->getLength());
//    _logicExpressions.push(c);
//    return;
//  } else if (ctx->HEX() != nullptr) {
//    messageErrorIf((conStr.size() - 2) * 4 > 64,
//                   "Constant '" + conStr.substr(0, conStr.size()) +
//                       "' exceeds the maximum length of 64 bits" +
//                       printErrorMessage());
//    ULogic value =
//        std::stoull(conStr.substr(2, conStr.size() - 2), nullptr, 16);
//    auto *c = new LogicConstant(value, VarType::ULogic, (conStr.size() - 2) * 4,
//                                _trace->getLength());
//    _logicExpressions.push(c);
//    return;
//  } else if (ctx->NUMERIC() != nullptr) {
//    size_t res = conStr.find('.');
//    if (res != std::string::npos) {
//      messageWarning("Float literal truncated to integer");
//      conStr = conStr.substr(0, res);
//    }
//
//    if (ctx->CONST_SUFFIX() == nullptr) {
//      // Store the logic as 2s complement int
//      ULogic value;
//      try {
//        value = std::stoll(conStr);
//      } catch (const std::out_of_range &e) {
//        messageError("Integer overflow when converting '" + conStr + "'" +
//                     printErrorMessage());
//      }
//      auto *c =
//          new LogicConstant(value, VarType::SLogic, 64, _trace->getLength());
//      _logicExpressions.push(c);
//    } else {
//      if (ctx->CONST_SUFFIX()->getText() == "ll") {
//        // Store the logic as 2s complement int
//        ULogic value;
//        try {
//          value = std::stoll(conStr);
//        } catch (const std::out_of_range &e) {
//          messageError("Integer overflow when converting '" + conStr + "'" +
//                       printErrorMessage());
//        }
//        auto *c =
//            new LogicConstant(value, VarType::SLogic, 64, _trace->getLength());
//        _logicExpressions.push(c);
//
//      } else if (ctx->CONST_SUFFIX()->getText() == "ull") {
//        // Store the logic as classic unsigned binary
//        ULogic value;
//        try {
//          value = std::stoull(conStr);
//        } catch (const std::out_of_range &e) {
//          messageError("Integer overflow when converting '" + conStr + "'" +
//                       printErrorMessage());
//        }
//        auto *c =
//            new LogicConstant(value, VarType::ULogic, 64, _trace->getLength());
//        _logicExpressions.push(c);
//
//      } else {
//        messageError("Unsupported suffix '" + ctx->CONST_SUFFIX()->getText() +
//                     "'" + printErrorMessage());
//      }
//    }
//    return;
//  }
//  messageError("Unknown logic constant!" + printErrorMessage());
//}
//void PropositionParserHandler::enterNumericConstant(
//    propositionParser::NumericConstantContext *ctx) {
//  if (ctx->NUMERIC() != nullptr) {
//    Numeric value = std::stod(ctx->getText());
//    auto *c =
//        new NumericConstant(value, VarType::Numeric, 64, _trace->getLength());
//    _numericExpressions.push(c);
//    return;
//  }
//}

void PropositionParserHandler::enterBooleanAtom(
    propositionParser::BooleanAtomContext *ctx) {

  std::string exp = std::string(ctx->getText());
  if (ctx->BOOLEAN_VARIABLE()) {
    auto data = parseBooleanVariable(exp);
    _proposition.push(_trace->getBooleanVariable(data.variable));

  } else if (ctx->BOOLEAN_CONSTANT()) {
    if (exp == "@false") {
      auto *c =
          new BooleanConstant(false, VarType::Bool, 1, _trace->getLength());
      _proposition.push(c);
      return;
    } else if (exp == "@true") {
      auto *c =
          new BooleanConstant(true, VarType::Bool, 1, _trace->getLength());
      _proposition.push(c);
      return;
    } else {
      messageError("Uknown boolean constant!" + printErrorMessage());
    }

  } else {
    messageError("Unknown boolean atom!" + printErrorMessage());
  }
}
void PropositionParserHandler::enterLogicAtom(
    propositionParser::LogicAtomContext *ctx) {
  std::string exp = std::string(ctx->getText());
  if (ctx->LOGIC_VARIABLE()) {
    auto data = parseLogicVariable(exp);
    std::cout << data.numeric << "\n";
    std::cout << data.sign << "\n";
    std::cout << data.variable << "\n";
    _logicExpressions.push(_trace->getLogicVariable(data.variable));

  } else if (ctx->LOGIC_CONSTANT()) {

  } else {
    messageError("Unknown logic atom!" + printErrorMessage());
  }
}
void PropositionParserHandler::enterNumericAtom(
    propositionParser::NumericAtomContext *ctx) {

  std::string exp = std::string(ctx->getText());

  if (ctx->NUMERIC_VARIABLE()) {
    auto data = parseNumericVariable(exp);
    std::cout << data.numeric << "\n";
    std::cout << data.sign << "\n";
    std::cout << data.variable << "\n";
    _numericExpressions.push(_trace->getNumericVariable(data.variable));

  } else if (ctx->NUMERIC_CONSTANT()) {

  } else {
    messageError("Unknown boolean atom!" + printErrorMessage());
  }
}
void PropositionParserHandler::exitBoolean(
    propositionParser::BooleanContext *ctx) {
  if (ctx->LPAREN() && ctx->RPAREN()) {
    // std::cout<<__func__<<"()"<<std::endl;
    return;
  }
  if (ctx->boolean().size() == 1) {
    if (ctx->NOT()) {
      // std::cout<<__func__<<"!"<<std::endl;
      Proposition *p = _proposition.top();
      _proposition.pop();
      _proposition.push(makeExpression<PropositionNot>(p));
      return;
    }
    messageError("Unknown unary boolean operator!" + printErrorMessage());
  } else if (ctx->boolean().size() == 2) {
    antlr4::Token *boolop = ctx->booleanop;
    if (boolop != nullptr) {
      // std::cout<<__func__<<"boolop"<<std::endl;
      Proposition *p2 = _proposition.top();
      _proposition.pop();
      Proposition *p1 = _proposition.top();
      _proposition.pop();
      if (boolop->getText() == "&&") {
        _proposition.push(makeExpression<PropositionAnd>(p1, p2));
        return;
      } else if (boolop->getText() == "||") {
        _proposition.push(makeExpression<PropositionOr>(p1, p2));
        return;
      }
      messageError("Unknown boolean operator in expression!" +
                   printErrorMessage());
    }
    if (ctx->EQ() != nullptr) {
      // std::cout<<__func__<<"="<<std::endl;
      Proposition *p2 = _proposition.top();
      _proposition.pop();
      Proposition *p1 = _proposition.top();
      _proposition.pop();
      _proposition.push(makeExpression<PropositionEq>(p1, p2));
      return;
    }
    if (ctx->NEQ() != nullptr) {
      // std::cout<<__func__<<"!="<<std::endl;
      Proposition *p2 = _proposition.top();
      _proposition.pop();
      Proposition *p1 = _proposition.top();
      _proposition.pop();
      _proposition.push(makeExpression<PropositionNeq>(p1, p2));
      return;
    }
    messageError("Unknown binary boolean operator!" + printErrorMessage());
  }

  if (_logicExpressions.size() == 1) {
    LogicExpression *le = _logicExpressions.top();
    _logicExpressions.pop();
    _proposition.push(new LogicToBool(le));
    return;
    messageError("Unknown unary logic operator in boolean expression!" +
                 printErrorMessage());
  } else if (ctx->logic().size() == 2) {
    propositionParser::RelopContext *relop = ctx->relop();
    if (relop != nullptr) {
      // std::cout<<__func__<<"relop"<<std::endl;
      LogicExpression *le2 = _logicExpressions.top();
      _logicExpressions.pop();

      LogicExpression *le1 = _logicExpressions.top();
      _logicExpressions.pop();

      if (relop->LT() != nullptr) {
        _proposition.push(makeExpression<LogicLess>(le1, le2));
        return;
      }
      if (relop->LE() != nullptr) {
        _proposition.push(makeExpression<LogicLessEq>(le1, le2));
        return;
      }
      if (relop->GT() != nullptr) {
        _proposition.push(makeExpression<LogicGreater>(le1, le2));
        return;
      }
      if (relop->GE() != nullptr) {
        _proposition.push(makeExpression<LogicGreaterEq>(le1, le2));
        return;
      }
      messageError("Unknown relational operator!" + printErrorMessage());
    }
    if (ctx->EQ() != nullptr) {
      // std::cout<<__func__<<"="<<std::endl;
      LogicExpression *le2 = _logicExpressions.top();
      _logicExpressions.pop();
      LogicExpression *le1 = _logicExpressions.top();
      _logicExpressions.pop();
      _proposition.push(makeExpression<LogicEq>(le1, le2));
      return;
    }
    if (ctx->NEQ() != nullptr) {
      // std::cout<<__func__<<"!="<<std::endl;
      LogicExpression *le2 = _logicExpressions.top();
      _logicExpressions.pop();
      LogicExpression *le1 = _logicExpressions.top();
      _logicExpressions.pop();
      _proposition.push(makeExpression<LogicNeq>(le1, le2));
      return;
    }
    messageError("Unknown binary logic operator!" + printErrorMessage());
  }

  if (_numericExpressions.size() == 1) {
    NumericExpression *ne = _numericExpressions.top();
    _numericExpressions.pop();
    _proposition.push(new NumericToBool(ne));
    return;
  } else if (ctx->numeric().size() == 2) {
    propositionParser::RelopContext *relop = ctx->relop();
    if (relop != nullptr) {
      // std::cout<<__func__<<"relop"<<std::endl;
      NumericExpression *ne2 = _numericExpressions.top();
      _numericExpressions.pop();

      NumericExpression *ne1 = _numericExpressions.top();
      _numericExpressions.pop();

      if (relop->LT() != nullptr) {
        _proposition.push(makeExpression<NumericLess>(ne1, ne2));
        return;
      }
      if (relop->LE() != nullptr) {
        _proposition.push(makeExpression<NumericLessEq>(ne1, ne2));
        return;
      }
      if (relop->GT() != nullptr) {
        _proposition.push(makeExpression<NumericGreater>(ne1, ne2));
        return;
      }
      if (relop->GE() != nullptr) {
        _proposition.push(makeExpression<NumericGreaterEq>(ne1, ne2));
        return;
      }
      messageError("Unknown relational operator!" + printErrorMessage());
    }
    if (ctx->EQ() != nullptr) {
      // std::cout<<__func__<<"="<<std::endl;
      NumericExpression *le2 = _numericExpressions.top();
      _numericExpressions.pop();
      NumericExpression *le1 = _numericExpressions.top();
      _numericExpressions.pop();
      _proposition.push(makeExpression<NumericEq>(le1, le2));
      return;
    }
    if (ctx->NEQ() != nullptr) {
      // std::cout<<__func__<<"!="<<std::endl;
      NumericExpression *le2 = _numericExpressions.top();
      _numericExpressions.pop();
      NumericExpression *le1 = _numericExpressions.top();
      _numericExpressions.pop();
      _proposition.push(makeExpression<NumericNeq>(le1, le2));
      return;
    }
    messageError("Unknown binary numeric operator!" + printErrorMessage());
  }
}
void PropositionParserHandler::exitLogic(propositionParser::LogicContext *ctx) {
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
    if (ctx->bitSelect() != nullptr) {
      size_t left;
      size_t right;
      LogicExpression *le_r = nullptr;
      if (ctx->bitSelect()->NUMERIC().size() > 1) {
        left = std::stoul(ctx->bitSelect()->NUMERIC()[0]->getText());
        right = std::stoul(ctx->bitSelect()->NUMERIC()[1]->getText());
        le_r = new LogicBitSelector(_logicExpressions.top(), left, right);
      } else {
        left = std::stoul(ctx->bitSelect()->NUMERIC()[0]->getText());
        right = left;
        le_r = new LogicBitSelector(_logicExpressions.top(), left, right);
      }
      _logicExpressions.pop();
      _logicExpressions.push(le_r);
      return;
    }

    messageError("Unknown unary logic operator in logic expression!" +
                 printErrorMessage());

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
                   "expression!" +
                   printErrorMessage());
    }

    antlr4::Token *artop = ctx->artop;

    if (artop != nullptr) {
      LogicExpression *le2 = _logicExpressions.top();
      _logicExpressions.pop();

      LogicExpression *le1 = _logicExpressions.top();
      _logicExpressions.pop();

      auto conversionResult =
          applyCStandardConversion(le1->getType(), le2->getType());

      if (artop->getText() == "*") {
        LogicExpression *le_r = makeExpression<LogicMul>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }
      if (artop->getText() == "/") {
        LogicExpression *le_r = makeExpression<LogicDiv>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }
      if (artop->getText() == "-") {
        LogicExpression *le_r = makeExpression<LogicSub>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }
      if (artop->getText() == "+") {
        LogicExpression *le_r = makeExpression<LogicSum>(le1, le2);
        le_r->setType(conversionResult.first, conversionResult.second);
        _logicExpressions.push(le_r);
        return;
      }
      messageError("Unknown binary arithmetic operator in logic "
                   "expression!" +
                   printErrorMessage());
    }
  }
}
void PropositionParserHandler::exitNumeric(
    propositionParser::NumericContext *ctx) {
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
    messageError("Unknown unary numeric operator in logic expression!" +
                 printErrorMessage());
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
                   "expression!" +
                   printErrorMessage());
    }
  }
}

Proposition *PropositionParserHandler::getProposition() {
  messageErrorIf(_proposition.size() != 1,
                 "No proposition to return" + printErrorMessage());

  Proposition *ret = _proposition.top();
  _proposition.pop();

  return ret;
}

std::string PropositionParserHandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void PropositionParserHandler::visitErrorNode(__attribute__((unused))
                                              antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}
void PropositionParserHandler::addErrorMessage(const std::string &msg) {
  _errorMessages.push_back(msg);
}

} // namespace hparser
