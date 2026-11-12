#include <string>
#include <utility>

#include "Logic.hh"
#include "expUtils/ExpType.hh"
#include "expUtils/expUtils.hh"
#include "expUtils/implicitConversion.hh"
#include "expUtils/ope.hh"
#include "formula/expression/GenericExpression.hh"
#include "message.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

//==== Call to Visitor's methods ===============================================
#define VISITOR_CALL(Operator, ET, OT)                               \
  template <>                                                        \
  void GenericExpression<ope::ope::Operator, ET, OT>::acceptVisitor( \
      ExpVisitor &vis) {                                             \
    vis.visit(*this);                                                \
  }

// proposition
VISITOR_CALL(PropositionAnd, Proposition, Proposition)
VISITOR_CALL(PropositionOr, Proposition, Proposition)
VISITOR_CALL(PropositionXor, Proposition, Proposition)
VISITOR_CALL(PropositionEq, Proposition, Proposition)
VISITOR_CALL(PropositionNeq, Proposition, Proposition)
VISITOR_CALL(PropositionNot, Proposition, Proposition)

// float
VISITOR_CALL(FloatSum, FloatExpression, FloatExpression)
VISITOR_CALL(FloatSub, FloatExpression, FloatExpression)
VISITOR_CALL(FloatNeg, FloatExpression, FloatExpression)
VISITOR_CALL(FloatMul, FloatExpression, FloatExpression)
VISITOR_CALL(FloatDiv, FloatExpression, FloatExpression)
VISITOR_CALL(FloatEq, FloatExpression, Proposition)
VISITOR_CALL(FloatNeq, FloatExpression, Proposition)
VISITOR_CALL(FloatGreater, FloatExpression, Proposition)
VISITOR_CALL(FloatGreaterEq, FloatExpression, Proposition)
VISITOR_CALL(FloatLess, FloatExpression, Proposition)
VISITOR_CALL(FloatLessEq, FloatExpression, Proposition)

// int
VISITOR_CALL(IntSum, IntExpression, IntExpression)
VISITOR_CALL(IntSub, IntExpression, IntExpression)
VISITOR_CALL(IntNeg, IntExpression, IntExpression)
VISITOR_CALL(IntMul, IntExpression, IntExpression)
VISITOR_CALL(IntDiv, IntExpression, IntExpression)
VISITOR_CALL(IntBAnd, IntExpression, IntExpression)
VISITOR_CALL(IntBOr, IntExpression, IntExpression)
VISITOR_CALL(IntBXor, IntExpression, IntExpression)
VISITOR_CALL(IntEq, IntExpression, Proposition)
VISITOR_CALL(IntNeq, IntExpression, Proposition)
VISITOR_CALL(IntGreater, IntExpression, Proposition)
VISITOR_CALL(IntGreaterEq, IntExpression, Proposition)
VISITOR_CALL(IntLess, IntExpression, Proposition)
VISITOR_CALL(IntLessEq, IntExpression, Proposition)
VISITOR_CALL(IntNot, IntExpression, IntExpression)
VISITOR_CALL(IntLShift, IntExpression, IntExpression)
VISITOR_CALL(IntRShift, IntExpression, IntExpression)
VISITOR_CALL(IntARShift, IntExpression, IntExpression)

// logic
VISITOR_CALL(LogicSum, LogicExpression, LogicExpression)
VISITOR_CALL(LogicSub, LogicExpression, LogicExpression)
VISITOR_CALL(LogicNeg, LogicExpression, LogicExpression)
VISITOR_CALL(LogicMul, LogicExpression, LogicExpression)
VISITOR_CALL(LogicDiv, LogicExpression, LogicExpression)
VISITOR_CALL(LogicBAnd, LogicExpression, LogicExpression)
VISITOR_CALL(LogicBOr, LogicExpression, LogicExpression)
VISITOR_CALL(LogicBXor, LogicExpression, LogicExpression)
VISITOR_CALL(LogicEq, LogicExpression, Proposition)
VISITOR_CALL(LogicNeq, LogicExpression, Proposition)
VISITOR_CALL(LogicCaseEq, LogicExpression, Proposition)
VISITOR_CALL(LogicCaseNeq, LogicExpression, Proposition)
VISITOR_CALL(LogicConcat, LogicExpression, LogicExpression)
VISITOR_CALL(LogicGreater, LogicExpression, Proposition)
VISITOR_CALL(LogicGreaterEq, LogicExpression, Proposition)
VISITOR_CALL(LogicLess, LogicExpression, Proposition)
VISITOR_CALL(LogicLessEq, LogicExpression, Proposition)
VISITOR_CALL(LogicNot, LogicExpression, LogicExpression)
VISITOR_CALL(LogicLShift, LogicExpression, LogicExpression)
VISITOR_CALL(LogicRShift, LogicExpression, LogicExpression)
VISITOR_CALL(LogicARShift, LogicExpression, LogicExpression)

//string
VISITOR_CALL(StringConcat, StringExpression, StringExpression)
VISITOR_CALL(StringEq, StringExpression, Proposition)
VISITOR_CALL(StringNeq, StringExpression, Proposition)
VISITOR_CALL(StringGreater, StringExpression, Proposition)
VISITOR_CALL(StringGreaterEq, StringExpression, Proposition)
VISITOR_CALL(StringLess, StringExpression, Proposition)
VISITOR_CALL(StringLessEq, StringExpression, Proposition)
//------------------------------------------------------------------------------

//==== evaluate methods for propositions =======================================
template <>
void GenericExpression<ope::ope::PropositionAnd, Proposition,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    for (const auto &prop : _items)
      if (!prop->evaluate(time))
        return false;

    return true;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::PropositionOr, Proposition,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    for (const auto &prop : _items)
      if (prop->evaluate(time))
        return true;

    return false;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::PropositionXor, Proposition,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto ret = _items[0]->evaluate(time);
    for (size_t i = 1; i < _items.size(); ++i)
      ret = ret ^ _items[i]->evaluate(time);

    return ret;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::PropositionEq, Proposition,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) == _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::PropositionNeq, Proposition,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) != _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::PropositionNot, Proposition,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 1,
                   "size==" + std::to_string(_items.size()));

    return !_items[0]->evaluate(time);
  };
  disableCache();
}
//------------------------------------------------------------------------------

//==== evaluate methods for float ============================================
template <>
void GenericExpression<ope::ope::FloatSum, FloatExpression,
                       FloatExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) + _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatSub, FloatExpression,
                       FloatExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) - _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatMul, FloatExpression,
                       FloatExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) * _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatDiv, FloatExpression,
                       FloatExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    messageErrorIf(
        _items[1]->evaluate(time) == 0,
        "division by zero in " + float2String(_items[0]) + "/" +
            float2String(_items[1]) + " (" +
            std::to_string(_items[0]->evaluate(time)) + "/" +
            std::to_string(_items[1]->evaluate(time)) + ")");

    Float res = _items[0]->evaluate(time) / _items[1]->evaluate(time);
    return res;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatEq, FloatExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    return _items[0]->evaluate(time) == _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatNeq, FloatExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    return _items[0]->evaluate(time) != _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatGreater, FloatExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    return _items[0]->evaluate(time) > _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatGreaterEq, FloatExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    return _items[0]->evaluate(time) >= _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatLess, FloatExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    return _items[0]->evaluate(time) < _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::FloatLessEq, FloatExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    return _items[0]->evaluate(time) <= _items[1]->evaluate(time);
  };
  disableCache();
}
//------------------------------------------------------------------------------

#define RESIZES(value, type)                                         \
  value = (SInt)(value << (64 - type.second)) >> (64 - type.second);

#define RESIZEU(value, type)                                         \
  value = (UInt)(value << (64 - type.second)) >> (64 - type.second);

//==== evaluate methods for int ==============================================
namespace {
/// D-035: an integer operand as SystemVerilog extends it to the result (IEEE 1800-2017 11.8.2):
/// from its own width, sign-extended when the result is signed (both operands are then signed),
/// zero-extended otherwise
UInt extendInt(UInt raw, const std::pair<ExpType, size_t> &own, ExpType res) {
  const size_t w = std::min<size_t>(own.second, 64);
  if (w >= 64) {
    return raw;
  }
  if (isSigned(res) && isSigned(own.first)) {
    return (UInt)(((SInt)(raw << (64 - w))) >> (64 - w));
  }
  return raw & ((UInt(1) << w) - 1);
}
UInt maskTo(UInt v, size_t w) { return w >= 64 ? v : v & ((UInt(1) << w) - 1); }
/// the result's bits as the result type stores them (sign-extended when signed)
UInt store(UInt v, const std::pair<ExpType, size_t> &t) {
  if (isSigned(t.first)) {
    RESIZES(v, t)
  } else {
    RESIZEU(v, t)
  }
  return v;
}
} // namespace

#define INT_BINARY(NODE, EXPR)                                       \
  template <>                                                        \
  void GenericExpression<ope::ope::NODE, IntExpression,              \
                         IntExpression>::initEvaluate() {            \
    directEvaluate = [this](size_t time) {                           \
      messageErrorIf(_items.size() != 2,                             \
                     "size==" + std::to_string(_items.size()));      \
      auto t = this->getType();                                      \
      UInt a = extendInt(_items[0]->evaluate(time),                  \
                         _items[0]->getType(), t.first);             \
      UInt b = extendInt(_items[1]->evaluate(time),                  \
                         _items[1]->getType(), t.first);             \
      bool sgn = isSigned(t.first);                                  \
      (void)sgn;                                                     \
      return store(EXPR, t);                                         \
    };                                                               \
    disableCache();                                                  \
  }
// two's complement: + - * & | ^ are the same bits signed or unsigned
INT_BINARY(IntSum, a + b)
INT_BINARY(IntSub, a - b)
INT_BINARY(IntMul, a * b)
INT_BINARY(IntBAnd, a & b)
INT_BINARY(IntBOr, a | b)
INT_BINARY(IntBXor, a ^ b)
// D-035, Q3 (a): a division by zero gives 0 (a C integer has no x; SystemVerilog gives x)
INT_BINARY(IntDiv,
           b == 0 ? UInt(0)
                  : (sgn ? (UInt)((SInt)a == INT64_MIN && (SInt)b == -1
                                      ? (SInt)a
                                      : (SInt)a / (SInt)b)
                         : a / b))

#define INT_COMPARE(NODE, OP)                                        \
  template <>                                                        \
  void GenericExpression<ope::ope::NODE, IntExpression,              \
                         Proposition>::initEvaluate() {              \
    directEvaluate = [this](size_t time) {                           \
      messageErrorIf(_items.size() != 2,                             \
                     "size==" + std::to_string(_items.size()));      \
      auto t = applyCStandardConversion(_items[0]->getType(),        \
                                        _items[1]->getType());       \
      UInt a = extendInt(_items[0]->evaluate(time),                  \
                         _items[0]->getType(), t.first);             \
      UInt b = extendInt(_items[1]->evaluate(time),                  \
                         _items[1]->getType(), t.first);             \
      if (isSigned(t.first)) {                                       \
        return (SInt)a OP(SInt) b;                                   \
      }                                                              \
      return maskTo(a, t.second) OP maskTo(b, t.second);             \
    };                                                               \
    disableCache();                                                  \
  }
INT_COMPARE(IntEq, ==)
INT_COMPARE(IntNeq, !=)
INT_COMPARE(IntGreater, >)
INT_COMPARE(IntGreaterEq, >=)
INT_COMPARE(IntLess, <)
INT_COMPARE(IntLessEq, <=)

template <>
void GenericExpression<ope::ope::IntNot, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 1,
                   "size==" + std::to_string(_items.size()));
    auto t = this->getType() /* D-035: the context's type */;
    UInt a = extendInt(_items[0]->evaluate(time), _items[0]->getType(),
                       t.first);
    return store(~a, t);
  };
  disableCache();
}
// D-034: unary minus, at the operand's type (as ~ is)
template <>
void GenericExpression<ope::ope::IntNeg, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 1,
                   "size==" + std::to_string(_items.size()));
    auto t = this->getType() /* D-035: the context's type */;
    UInt a = extendInt(_items[0]->evaluate(time), _items[0]->getType(),
                       t.first);
    return store(UInt(0) - a, t);
  };
  disableCache();
}
template <>
void GenericExpression<ope::ope::FloatNeg, FloatExpression,
                       FloatExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 1,
                   "size==" + std::to_string(_items.size()));
    return -_items[0]->evaluate(time);
  };
  disableCache();
}

// D-035: shifts as SystemVerilog's (IEEE 1800-2017 11.4.10): the amount is unsigned and
// self-determined (from its own width); a shift by the result's width or more gives 0 (>>> of a
// negative signed value: -1); << and >> fill with 0, >>> with the sign bit of a signed result
#define INT_SHIFT(NODE, KIND)                                        \
  template <>                                                        \
  void GenericExpression<ope::ope::NODE, IntExpression,              \
                         IntExpression>::initEvaluate() {            \
    directEvaluate = [this](size_t time) {                           \
      messageErrorIf(_items.size() != 2,                             \
                     "size==" + std::to_string(_items.size()));      \
      auto t = this->getType();                                      \
      const size_t w = std::min<size_t>(t.second, 64);               \
      UInt a = maskTo(extendInt(_items[0]->evaluate(time),           \
                                _items[0]->getType(), t.first),      \
                      w);                                            \
      UInt n = extendInt(_items[1]->evaluate(time),                  \
                         _items[1]->getType(), ExpType::UInt);       \
      bool negative = isSigned(t.first) && w > 0 &&                  \
                      ((a >> (w - 1)) & 1);                          \
      UInt r;                                                        \
      if (KIND == 0) { /* << */                                      \
        r = n >= w ? 0 : a << n;                                     \
      } else if (KIND == 1 || !negative) { /* >>, or >>> of a      \
                                              non-negative value */  \
        r = n >= w ? 0 : a >> n;                                     \
      } else { /* >>> of a negative signed value */                  \
        r = n >= w ? ~UInt(0) : ~((~a & maskTo(~UInt(0), w)) >> n);  \
      }                                                              \
      return store(r, t);                                            \
    };                                                               \
    disableCache();                                                  \
  }
INT_SHIFT(IntLShift, 0)
INT_SHIFT(IntRShift, 1)
INT_SHIFT(IntARShift, 2)

//==== evaluate methods for logic ==============================================
template <>
void GenericExpression<ope::ope::LogicSum, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto sumType = this->getType();
    return sum(_items[0]->evaluate(time), _items[1]->evaluate(time),
               sumType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicSub, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto subType = this->getType();
    return sub(_items[0]->evaluate(time), _items[1]->evaluate(time),
               subType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicMul, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto mulType = this->getType();
    return mul(_items[0]->evaluate(time), _items[1]->evaluate(time),
               mulType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicDiv, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto divType = this->getType();
    return div(_items[0]->evaluate(time), _items[1]->evaluate(time),
               divType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicBAnd, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto bandType = this->getType();
    return band(_items[0]->evaluate(time), _items[1]->evaluate(time),
                bandType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicBOr, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto bOrType = this->getType();
    return bor(_items[0]->evaluate(time), _items[1]->evaluate(time),
               bOrType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicBXor, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto bXorType = this->getType();
    return bxor(_items[0]->evaluate(time), _items[1]->evaluate(time),
                bXorType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicLShift, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto blsType = this->getType();
    return bls(_items[0]->evaluate(time), _items[1]->evaluate(time),
               blsType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicRShift, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto brsType = this->getType();
    return brs(_items[0]->evaluate(time), _items[1]->evaluate(time),
               brsType);
  };
  disableCache();
}
template <>
void GenericExpression<ope::ope::LogicARShift, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto brsType = this->getType();
    return bars(_items[0]->evaluate(time), _items[1]->evaluate(time),
               brsType);
  };
  disableCache();
}
template <>
void GenericExpression<ope::ope::LogicEq, LogicExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());
    return eq(_items[0]->evaluate(time), _items[1]->evaluate(time),
              resType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicNeq, LogicExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());
    return neq(_items[0]->evaluate(time), _items[1]->evaluate(time),
               resType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicCaseEq, LogicExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    return caseEq(_items[0]->evaluate(time), _items[1]->evaluate(time));
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicCaseNeq, LogicExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    return !caseEq(_items[0]->evaluate(time), _items[1]->evaluate(time));
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicConcat, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    std::vector<Logic> values;
    values.reserve(_items.size());
    for (const auto &item : _items) {
      values.push_back(item->evaluate(time));
    }
    return concat(values);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicGreater, LogicExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());
    return gt(_items[0]->evaluate(time), _items[1]->evaluate(time),
              resType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicGreaterEq, LogicExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());
    return gte(_items[0]->evaluate(time), _items[1]->evaluate(time),
               resType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicLess, LogicExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());
    return lt(_items[0]->evaluate(time), _items[1]->evaluate(time),
              resType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicLessEq, LogicExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());
    return lte(_items[0]->evaluate(time), _items[1]->evaluate(time),
               resType);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::LogicNeg, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 1,
                   "size==" + std::to_string(_items.size()));
    auto resType = this->getType() /* D-035: the context's type */;
    // 0 - v at the operand's width (x/z as in subtraction)
    Logic v = _items[0]->evaluate(time);
    Logic zero(resType.second, isSigned(resType.first), 0, 0, 0);
    return sub(zero, v, resType);
  };
  disableCache();
}
template <>
void GenericExpression<ope::ope::LogicNot, LogicExpression,
                       LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 1,
                   "size==" + std::to_string(_items.size()));
    auto resType = this->getType() /* D-035: the context's type */;
    return bnot(_items[0]->evaluate(time), resType);
  };
  disableCache();
}
//------------------------------------------------------------------------------
//==== evaluate methods for string ==============================================
template <>
void GenericExpression<ope::ope::StringEq, StringExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) == _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::StringNeq, StringExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) != _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::StringGreater, StringExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) > _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::StringGreaterEq, StringExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) >= _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::StringLess, StringExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) < _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::StringLessEq, StringExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    return _items[0]->evaluate(time) <= _items[1]->evaluate(time);
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::StringConcat, StringExpression,
                       StringExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    String concat = "";
    for (size_t i = 0; i < _items.size(); i++) {
      concat = concat + _items[i]->evaluate(time);
    }

    return concat;
  };
  disableCache();
}
} // namespace expression
