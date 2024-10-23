#include <limits>
#include <ostream>
#include <stdexcept>
#include <unordered_set>
#include <utility>

#include "Float.hh"
#include "Int.hh"
#include "Limits.hh"
#include "PointerUtils.hh"
#include "PropositionParserHandler.hh"
#include "Token.h"
#include "Trace.hh"
#include "exp.hh"
#include "expUtils/implicitConversion.hh"
#include "formula/atom/Constant.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/BitSelector.hh"
#include "formula/expression/GenericExpression.hh"
#include "misc.hh"
#include "tree/ErrorNode.h"
#include "tree/ParseTree.h"
#include "tree/TerminalNode.h"

namespace hparser {
using namespace expression;

PropositionParserHandler::PropositionParserHandler(
    const harm::TracePtr &trace)
    : _proposition(), _numericExpressions(), _trace(trace) {}

void PropositionParserHandler::clear() {
  while (!_proposition.empty()) {
    _proposition.pop();
  }

  while (!_numericExpressions.empty()) {
    _numericExpressions.pop();
  }
}

void PropositionParserHandler::enterStartBoolean(
    propositionParser::StartBooleanContext *ctx) {
  clear();
}
void PropositionParserHandler::enterStartInt(
    propositionParser::StartIntContext *ctx) {
  clear();
}

void PropositionParserHandler::enterStartFloat(
    propositionParser::StartFloatContext *ctx) {
  clear();
}

std::string getVariableName(const std::string &input,
                            const std::string &type) {
  size_t startDelimiterPos = input.find("«");
  size_t endDelimiterPos = input.rfind("»");
  size_t typePos = input.rfind("," + type);

  if (startDelimiterPos == std::string::npos ||
      endDelimiterPos == std::string::npos ||
      typePos == std::string::npos) {
    messageError("Invalid string format in parseVariable(" + type +
                 "): " + input);
  }

  return input.substr(startDelimiterPos + 2,
                      typePos - (startDelimiterPos + 2));
}

void PropositionParserHandler::exitInt_constant(
    propositionParser::Int_constantContext *ctx) {
  std::string conStr = std::string(ctx->getText());
  if (ctx->GCC_BINARY() != nullptr) {
    messageErrorIf(conStr.size() - 2 > 64,
                   "Constant '" + conStr.substr(0, conStr.size()) +
                       "' exceeds the maximum length of 64 bits" +
                       printErrorMessage());
    UInt value = safeStoull(conStr.substr(2, conStr.size() - 2), 2);
    IntConstantPtr c = generatePtr<IntConstant>(
        value, ExpType::UInt, conStr.size() - 2, _trace->getLength());
    _numericExpressions.push(c);
    return;
  } else if (ctx->HEX() != nullptr) {
    messageErrorIf((conStr.size() - 2) * 4 > 64,
                   "Constant '" + conStr.substr(0, conStr.size()) +
                       "' exceeds the maximum length of 64 bits" +
                       printErrorMessage());
    UInt value = safeStoull(conStr.substr(2, conStr.size() - 2), 16);
    IntConstantPtr c = generatePtr<IntConstant>(
        value, ExpType::UInt, (conStr.size() - 2) * 4,
        _trace->getLength());
    _numericExpressions.push(c);
    return;
  } else if (ctx->SINTEGER() != nullptr ||
             ctx->UINTEGER() != nullptr) {

    if (ctx->CONST_SUFFIX() == nullptr) {
      // Store the int as 2s complement int
      UInt value = safeStoll(conStr);
      IntConstantPtr c = generatePtr<IntConstant>(
          value, ExpType::SInt, 64, _trace->getLength());
      _numericExpressions.push(c);
    } else {
      if (ctx->CONST_SUFFIX()->getText() == "ll") {
        // Store the int as 2s complement int
        UInt value = safeStoll(conStr);
        IntConstantPtr c = generatePtr<IntConstant>(
            value, ExpType::SInt, 64, _trace->getLength());
        _numericExpressions.push(c);

      } else if (ctx->CONST_SUFFIX()->getText() == "ull") {
        // Store the int as classic unsigned binary
        UInt value = safeStoull(conStr);

        IntConstantPtr c = generatePtr<IntConstant>(
            value, ExpType::UInt, 64, _trace->getLength());
        _numericExpressions.push(c);

      } else {
        messageError("Unsupported suffix '" +
                     ctx->CONST_SUFFIX()->getText() + "'" +
                     printErrorMessage());
      }
    }
    return;
  } else if (ctx->VERILOG_BINARY()) {
    //get the size of the logic constant: in the prefix of the binary or form the length of the binary
    size_t size = ctx->UINTEGER()
                      ? safeStoull(ctx->UINTEGER()->getText())
                      : ctx->VERILOG_BINARY()->getText().size() - 2;

    std::string binary_str =
        ctx->VERILOG_BINARY()->getText().substr(2);

    UInt value = safeStoull(binary_str, 2);
    IntConstantPtr c = generatePtr<IntConstant>(
        value, ExpType::UInt, binary_str.size(), _trace->getLength());
    _numericExpressions.push(c);
    return;
  } else {
    messageError("Invalid logic constant");
  }
  messageError("Unknown int constant!" + printErrorMessage());
}

void PropositionParserHandler::exitBooleanAtom(
    propositionParser::BooleanAtomContext *ctx) {

  std::string exp = std::string(ctx->getText());
  if (ctx->BOOLEAN_VARIABLE() != nullptr) {
    auto name = getVariableName(exp, "bool");
    _proposition.push(_trace->getBooleanVariable(name));

  } else if (ctx->BOOLEAN_CONSTANT() != nullptr) {
    if (exp == "@false") {
      BooleanConstantPtr c = generatePtr<BooleanConstant>(
          false, ExpType::Bool, 1, _trace->getLength());
      _proposition.push(c);
      return;
    } else if (exp == "@true") {
      BooleanConstantPtr c = generatePtr<BooleanConstant>(
          true, ExpType::Bool, 1, _trace->getLength());
      _proposition.push(c);
      return;
    } else {
      messageError("Uknown boolean constant!" + printErrorMessage());
    }

  } else {
    messageError("Unknown boolean atom!" + printErrorMessage());
  }
}
void PropositionParserHandler::exitIntAtom(
    propositionParser::IntAtomContext *ctx) {
  std::string exp = std::string(ctx->getText());
  if (ctx->INT_VARIABLE() != nullptr) {
    auto name = getVariableName(exp, "int");
    _numericExpressions.push(_trace->getIntVariable(name));
  } else if (ctx->int_constant() != nullptr) {
    //already handled in exitIntConstant
  } else {
    messageError("Unknown int atom!" + printErrorMessage());
  }
}

void PropositionParserHandler::exitFloatAtom(
    propositionParser::FloatAtomContext *ctx) {

  std::string exp = std::string(ctx->getText());

  if (ctx->FLOAT_VARIABLE() != nullptr) {
    auto name = getVariableName(exp, "float");
    _numericExpressions.push(_trace->getFloatVariable(name));

  } else if (ctx->FLOAT_CONSTANT() != nullptr) {
    Float value = safeStod(exp);
    FloatConstantPtr c = generatePtr<FloatConstant>(
        value, ExpType::Float, 64, _trace->getLength());
    _numericExpressions.push(c);

  } else {
    messageError("Unknown float atom!" + printErrorMessage());
  }
}

#define Int
#define Float
#define Logic

#define handleNumericRelExp(expSuffix, op1, op2, stackTarget)        \
  if (isInt(op1.getType().first)) {                                  \
    stackTarget.push(makeGenericExpression<Int##expSuffix>(          \
        op1._intExp, op2._intExp));                                  \
  } else if (isFloat(op1.getType().first)) {                         \
    stackTarget.push(makeGenericExpression<Float##expSuffix>(        \
        op1._floatExp, op2._floatExp));                              \
  } else {                                                           \
    messageError("Unknown type of expression\n" +                    \
                 printErrorMessage());                               \
  }

#define handleBitWiseExp(expSuffix, op1, op2, stackTarget,           \
                         conversionResult)                           \
  if (isInt(op1.getType().first)) {                                  \
    auto res = makeGenericExpression<Int##expSuffix>(op1._intExp,    \
                                                     op2._intExp);   \
    res->setType(conversionResult.first, conversionResult.second);   \
    stackTarget.push(res);                                           \
  } else {                                                           \
    messageError("Unknown type of expression\n" +                    \
                 printErrorMessage());                               \
  }

#define handleNumericArithmeticExp(expSuffix, op1, op2, stackTarget, \
                                   conversionResult)                 \
  if (isInt(op1.getType().first)) {                                  \
    auto res = makeGenericExpression<Int##expSuffix>(op1._intExp,    \
                                                     op2._intExp);   \
    res->setType(conversionResult.first, conversionResult.second);   \
    stackTarget.push(res);                                           \
  } else if (isFloat(op1.getType().first)) {                         \
    auto res = makeGenericExpression<Float##expSuffix>(              \
        op1._floatExp, op2._floatExp);                               \
    res->setType(conversionResult.first, conversionResult.second);   \
    stackTarget.push(res);                                           \
  } else {                                                           \
    messageError("Unknown type of expression\n" +                    \
                 printErrorMessage());                               \
  }

void PropositionParserHandler::exitBoolean(
    propositionParser::BooleanContext *ctx) {

  //ignore parenthesis
  if (ctx->LROUND() && ctx->RROUND()) {
    return;
  }

  if (ctx->boolean().size() == 1) {
    if (ctx->NOT()) {
      PropositionPtr p = _proposition.top();
      _proposition.pop();
      _proposition.push(makeGenericExpression<PropositionNot>(p));
      return;
    }
    messageError("Unknown unary boolean operator!" +
                 printErrorMessage());
  } else if (ctx->boolean().size() == 2) {
    antlr4::Token *boolop = ctx->booleanop;
    if (boolop != nullptr) {
      // std::cout<<__func__<<"boolop"<<std::endl;
      PropositionPtr p2 = _proposition.top();
      _proposition.pop();
      PropositionPtr p1 = _proposition.top();
      _proposition.pop();
      if (boolop->getText() == "&&") {
        //operator is associative
        if (std::dynamic_pointer_cast<PropositionAnd>(p1) !=
            nullptr) {
          PropositionAndPtr p1and =
              std::dynamic_pointer_cast<PropositionAnd>(p1);
          p1and->addItem(p2);
          _proposition.push(p1and);
        } else {
          _proposition.push(
              makeGenericExpression<PropositionAnd>(p1, p2));
        }
        return;
      } else if (boolop->getText() == "||") {
        //operator is associative
        if (std::dynamic_pointer_cast<PropositionOr>(p1) != nullptr) {
          PropositionOrPtr p1or =
              std::dynamic_pointer_cast<PropositionOr>(p1);
          p1or->addItem(p2);
          _proposition.push(p1or);
        } else {
          _proposition.push(
              makeGenericExpression<PropositionOr>(p1, p2));
        }
        return;
      }
      messageError("Unknown boolean operator in expression!" +
                   printErrorMessage());
    }
    if (ctx->EQ() != nullptr) {
      PropositionPtr p2 = _proposition.top();
      _proposition.pop();
      PropositionPtr p1 = _proposition.top();
      _proposition.pop();
      _proposition.push(makeGenericExpression<PropositionEq>(p1, p2));
      return;
    }
    if (ctx->NEQ() != nullptr) {
      PropositionPtr p2 = _proposition.top();
      _proposition.pop();
      PropositionPtr p1 = _proposition.top();
      _proposition.pop();
      _proposition.push(
          makeGenericExpression<PropositionNeq>(p1, p2));
      return;
    }
    messageError("Unknown binary boolean operator!" +
                 printErrorMessage());
  }

  if (ctx->numeric().size() == 1) {
    //implitic conversion to bool
    if (_numericExpressions.isTopFloat()) {
      _proposition.push(
          generatePtr<FloatToBool>(_numericExpressions.topFloat()));
    } else if (_numericExpressions.isTopInt()) {
      _proposition.push(
          generatePtr<IntToBool>(_numericExpressions.topInt()));
    } else {
      messageError("Unknown type to convert to bool!" +
                   printErrorMessage());
    }
    _numericExpressions.pop();
    return;

  } else if (ctx->numeric().size() == 2) {

    PropositionParserHandler::NumericPack exp2 =
        _numericExpressions.top();
    _numericExpressions.pop();

    PropositionParserHandler::NumericPack exp1 =
        _numericExpressions.top();
    _numericExpressions.pop();

    auto conversionResult =
        applyCStandardConversion(exp1.getType(), exp2.getType());

    convert(exp1, exp2, conversionResult);

    propositionParser::RelopContext *relop = ctx->relop();

    if (relop != nullptr) {

      if (relop->LT() != nullptr) {
        handleNumericRelExp(Less, exp1, exp2, _proposition) return;
      }

      if (relop->LE() != nullptr) {
        handleNumericRelExp(LessEq, exp1, exp2, _proposition) return;
        return;
      }
      if (relop->GT() != nullptr) {
        handleNumericRelExp(Greater, exp1, exp2, _proposition) return;
        return;
      }
      if (relop->GE() != nullptr) {
        handleNumericRelExp(GreaterEq, exp1, exp2,
                            _proposition) return;
        return;
      }
      messageError("Unknown relational operator!" +
                   printErrorMessage());
    }

    if (ctx->EQ() != nullptr) {
      handleNumericRelExp(Eq, exp1, exp2, _proposition) return;
      return;
    }
    if (ctx->NEQ() != nullptr) {
      handleNumericRelExp(Neq, exp1, exp2, _proposition) return;
      return;
    }
    messageError("Unknown binary bool operator between numerics!" +
                 printErrorMessage());
  }
}

void PropositionParserHandler::exitNumeric(
    propositionParser::NumericContext *ctx) {

  if (ctx->floatAtom() || ctx->intAtom()) {
    //handled elsewhere
    return;
  }

  //ignore parenthesis
  if (ctx->LROUND() && ctx->RROUND()) {
    return;
  }

  if (ctx->numeric().size() == 1 &&
      _numericExpressions.isTopFloat()) {
    messageError("Unknown unary float operator!" +
                 printErrorMessage());
  }

  if (ctx->numeric().size() == 1) {

    if (ctx->NEG() != nullptr) {
      if (_numericExpressions.isTopInt()) {
        IntNotPtr le_r = makeGenericExpression<IntNot>(
            _numericExpressions.topInt());
        le_r->setType(_numericExpressions.topInt()->getType().first,
                      _numericExpressions.topInt()->getType().second);
        _numericExpressions.pop();
        _numericExpressions.push(le_r);
        return;
      }
      messageError("Error in int/logic neg operator!" +
                   printErrorMessage());
    }

    if (ctx->range() != nullptr) {
      size_t left;
      size_t right;
      auto type = _numericExpressions.top().getType();
      messageErrorIf(!ctx->range()->SINTEGER().empty(),
                     "Negative index in bit range!" +
                         printErrorMessage());
      messageErrorIf(ctx->range()->UINTEGER().empty(),
                     "Invalid range!" + printErrorMessage());

      left = safeStoull(ctx->range()->UINTEGER()[0]->getText());
      if (ctx->range()->UINTEGER().size() > 1) {
        right = safeStoull(ctx->range()->UINTEGER()[1]->getText());
      } else {
        right = left;
      }

      size_t lower_bound = left < right ? left : right;
      size_t upper_bound = left > right ? left : right;
      messageErrorIf(upper_bound >= type.second,
                     "Range is wider than the size of the variable!" +
                         printErrorMessage());

      if (_numericExpressions.isTopInt()) {
        IntExpressionPtr le_r = nullptr;
        le_r = generatePtr<IntBitSelector>(
            _numericExpressions.topInt(), lower_bound, upper_bound);
        _numericExpressions.pop();
        _numericExpressions.push(le_r);
        return;
      }
      messageError("Error in int/logic range!" + printErrorMessage());
    }

    messageError(
        "Unknown unary int/logic operator in int/logic expression!" +
        printErrorMessage());
  }

  if (ctx->numeric().size() == 2) {
    antlr4::Token *logop = ctx->logop;

    if (logop != nullptr) {
      messageErrorIf(_numericExpressions.isTopFloat(),
                     "Cannot use log operator in float expression!" +
                         printErrorMessage());
      PropositionParserHandler::NumericPack np2 =
          _numericExpressions.top();
      _numericExpressions.pop();

      messageErrorIf(_numericExpressions.isTopFloat(),
                     "Cannot use log operator in float expression!" +
                         printErrorMessage());

      PropositionParserHandler::NumericPack np1 =
          _numericExpressions.top();
      _numericExpressions.pop();

      auto conversionResult =
          applyCStandardConversion(np1.getType(), np2.getType());

      //apply implicit conversion
      convert(np1, np2, conversionResult);

      if (logop->getText() == "&") {
        handleBitWiseExp(BAnd, np1, np2, _numericExpressions,
                         conversionResult);
        return;
      }
      if (logop->getText() == "|") {
        handleBitWiseExp(BOr, np1, np2, _numericExpressions,
                         conversionResult);
        return;
      }
      if (logop->getText() == "^") {
        handleBitWiseExp(BXor, np1, np2, _numericExpressions,
                         conversionResult);
        return;
      }
      if (logop->getText() == "<<") {
        auto conversionResult =
            applyCStandardConversion(np1.getType(), np1.getType());
        handleBitWiseExp(LShift, np1, np2, _numericExpressions,
                         conversionResult);
        return;
      }
      if (logop->getText() == ">>") {
        auto conversionResult =
            applyCStandardConversion(np1.getType(), np1.getType());
        handleBitWiseExp(RShift, np1, np2, _numericExpressions,
                         conversionResult);
        return;
      }

      messageError("Unknown binary int/logic operator in int/logic "
                   "expression!" +
                   printErrorMessage());
    }

    antlr4::Token *artop = ctx->artop;

    if (artop != nullptr) {
      PropositionParserHandler::NumericPack np2 =
          _numericExpressions.top();
      _numericExpressions.pop();
      PropositionParserHandler::NumericPack np1 =
          _numericExpressions.top();
      _numericExpressions.pop();

      auto conversionResult =
          applyCStandardConversion(np1.getType(), np2.getType());

      //apply implicit conversion
      convert(np1, np2, conversionResult);

      if (artop->getText() == "*") {
        handleNumericArithmeticExp(Mul, np1, np2, _numericExpressions,
                                   conversionResult);
        return;
      }

      if (artop->getText() == "/") {
        handleNumericArithmeticExp(Div, np1, np2, _numericExpressions,
                                   conversionResult);
        return;
      }
      if (artop->getText() == "-") {

        handleNumericArithmeticExp(Sub, np1, np2, _numericExpressions,
                                   conversionResult);
        return;
      }
      if (artop->getText() == "+") {
        handleNumericArithmeticExp(Sum, np1, np2, _numericExpressions,
                                   conversionResult);
        return;
      }

      messageError("Unknown arithmetic operator in numeric "
                   "expression!" +
                   printErrorMessage());
    } //artop != nullptr
  }   //numericExp == 2
}

PropositionPtr PropositionParserHandler::getProposition() {
  messageErrorIf(_proposition.empty(),
                 "No proposition to return" + printErrorMessage());
  messageErrorIf(!_numericExpressions.empty(),
                 "Stray numeric expressions in stack" +
                     printErrorMessage());

  PropositionPtr ret = _proposition.top();
  _proposition.pop();

  return ret;
}

IntExpressionPtr PropositionParserHandler::getIntExpression() {
  messageErrorIf(!_proposition.empty(),
                 "Stray propositions in stack" + printErrorMessage());
  messageErrorIf(_numericExpressions.empty(),
                 "No numeric to return" + printErrorMessage());

  IntExpressionPtr ret = nullptr;

  if (_numericExpressions.isTopInt()) {
    ret = _numericExpressions.topInt();
  } else {
    ret = generatePtr<FloatToInt>(_numericExpressions.topFloat());
  }
  _numericExpressions.pop();

  messageErrorIf(!_numericExpressions.empty(),
                 "Stray numeric expression in stack" +
                     printErrorMessage());
  return ret;
}

FloatExpressionPtr PropositionParserHandler::getFloatExpression() {
  messageErrorIf(!_proposition.empty(),
                 "Stray propositions in stack" + printErrorMessage());
  messageErrorIf(_numericExpressions.empty(),
                 "Numeric stack is empty" + printErrorMessage());

  FloatExpressionPtr ret = nullptr;
  if (_numericExpressions.isTopFloat()) {
    ret = _numericExpressions.topFloat();
  } else {
    ret = generatePtr<IntToFloat>(_numericExpressions.topInt());
  }
  _numericExpressions.pop();

  messageErrorIf(!_numericExpressions.empty(),
                 "Stray numeric expression in stack" +
                     printErrorMessage());

  return ret;
}

std::string PropositionParserHandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void PropositionParserHandler::visitErrorNode(
    __attribute__((unused)) antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}
void PropositionParserHandler::addErrorMessage(
    const std::string &msg) {
  _errorMessages.push_back(msg);
}

void PropositionParserHandler::convert(
    NumericPack &exp1, NumericPack &exp2,
    std::pair<expression::ExpType, size_t> conversionResult) {
  if (isInt(conversionResult.first)) {
    if (!isInt(exp1.getType().first)) {
      exp1.convert(NumericType::NumericInt);
    }
    if (!isInt(exp2.getType().first)) {
      exp2.convert(NumericType::NumericInt);
    }
  }
  if (isFloat(conversionResult.first)) {
    if (!isFloat(exp1.getType().first)) {
      exp1.convert(NumericType::NumericFloat);
    }
    if (!isFloat(exp2.getType().first)) {
      exp2.convert(NumericType::NumericFloat);
    }
  }
}

//-----------------------------NumericPack--------------------------------------

PropositionParserHandler::NumericPack::NumericPack()
    : _intExp(nullptr), _floatExp(nullptr) {}

PropositionParserHandler::NumericPack::NumericPack(
    const expression::IntExpressionPtr &intExp)
    : _intExp(intExp), _floatExp(nullptr) {}

PropositionParserHandler::NumericPack::NumericPack(
    const expression::FloatExpressionPtr &floatExp)
    : _intExp(nullptr), _floatExp(floatExp) {}

std::pair<expression::ExpType, size_t>
PropositionParserHandler::NumericPack::getType() {
  if (_intExp != nullptr) {
    return _intExp->getType();
  } else if (_floatExp != nullptr) {
    return _floatExp->getType();
  }

  messageError("NumericPack is empty");
  return std::make_pair(expression::ExpType::Unknown, 0);
}

void PropositionParserHandler::NumericPack::convert(
    NumericType toType) {

  if (_intExp) {
    switch (toType) {
    case NumericType::NumericInt:
      break;
    case NumericType::NumericFloat:
      _floatExp = generatePtr<expression::IntToFloat>(_intExp);
      break;
    default:
      messageError("Unknown NumericType");
    }
    _intExp = nullptr;
    return;
  } else if (_floatExp) {
    switch (toType) {
    case NumericType::NumericInt:
      _intExp = generatePtr<expression::FloatToInt>(_floatExp);
      break;
    case NumericType::NumericFloat:
      break;
    default:
      messageError("Unknown NumericType");
    }

    _floatExp = nullptr;
    return;
  }
  messageError("NumericPack is empty");
}

//-------------NumericStack-------------------

void PropositionParserHandler::NumericStack::push(
    expression::IntExpressionPtr exp) {
  _expressions.emplace(exp);
}
void PropositionParserHandler::NumericStack::push(
    expression::FloatExpressionPtr exp) {
  _expressions.emplace(exp);
}

void PropositionParserHandler::NumericStack::pop() {
  _expressions.pop();
}

expression::FloatExpressionPtr
PropositionParserHandler::NumericStack::topFloat() {
  messageErrorIf(_expressions.top()._floatExp == nullptr,
                 "Top of stack is not a float expression");
  return _expressions.top()._floatExp;
}
expression::IntExpressionPtr
PropositionParserHandler::NumericStack::topInt() {
  messageErrorIf(_expressions.top()._intExp == nullptr,
                 "Top of stack is not a int expression");
  return _expressions.top()._intExp;
}
PropositionParserHandler::NumericPack
PropositionParserHandler::NumericStack::top() {
  messageErrorIf(_expressions.empty(),
                 "Calling top() on empty Stack");
  return _expressions.top();
}
bool PropositionParserHandler::NumericStack::empty() {
  return _expressions.empty();
}
bool PropositionParserHandler::NumericStack::isTopFloat() {
  return _expressions.top()._floatExp != nullptr;
}
bool PropositionParserHandler::NumericStack::isTopInt() {
  return _expressions.top()._intExp != nullptr;
}
size_t PropositionParserHandler::NumericStack::size() {
  return _expressions.size();
}

std::string PropositionParserHandler::NumericStack::printStack() {
  std::stack<NumericPack> expressions;
  std::string str = "\n";
  while (!empty()) {
    if (isTopFloat()) {
      str += float2String(topFloat());
    } else {
      str += int2String(topInt());
    }
    str += "\n";
    expressions.push(_expressions.top());
    pop();
  }
  while (!expressions.empty()) {
    _expressions.push(expressions.top());
    expressions.pop();
  }
  return str;
}

bool PropositionParserHandler::isEmpty(const NumericPack &p) {
  return p._floatExp == nullptr && p._intExp == nullptr;
}
} // namespace hparser
