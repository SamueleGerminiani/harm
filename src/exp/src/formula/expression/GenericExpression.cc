#include <string>
#include <utility>

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
template <>
void GenericExpression<ope::ope::IntSum, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto sumType = this->getType();
    UInt sum = 0;

    if (sumType.first == ExpType::SInt) {
      sum = (SInt)_items[0]->evaluate(time) +
            (SInt)_items[1]->evaluate(time);
      RESIZES(sum, sumType)
    } else {
      sum = (UInt)_items[0]->evaluate(time) +
            (UInt)_items[1]->evaluate(time);
      RESIZEU(sum, sumType)
    }

    return sum;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntSub, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto subType = this->getType();
    UInt sub = 0;

    if (subType.first == ExpType::SInt) {
      sub = (SInt)_items[0]->evaluate(time) -
            (SInt)_items[1]->evaluate(time);
      RESIZES(sub, subType)
    } else {
      sub = (UInt)_items[0]->evaluate(time) -
            (UInt)_items[1]->evaluate(time);
      RESIZEU(sub, subType)
    }
    return sub;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntMul, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto mulType = this->getType();

    UInt mul = 1;

    if (mulType.first == ExpType::SInt) {
      mul = (SInt)_items[0]->evaluate(time) *
            (SInt)_items[1]->evaluate(time);
      RESIZES(mul, mulType)
    } else {
      mul = (UInt)_items[0]->evaluate(time) *
            (UInt)_items[1]->evaluate(time);
      RESIZEU(mul, mulType)
    }

    return mul;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntDiv, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto divType = this->getType();
    UInt div = 0;

    if (divType.first == ExpType::SInt) {
      div = (SInt)_items[0]->evaluate(time) /
            (SInt)_items[1]->evaluate(time);
      RESIZES(div, divType)
    } else {
      div = (UInt)_items[0]->evaluate(time) /
            (UInt)_items[1]->evaluate(time);
      RESIZEU(div, divType)
    }
    return div;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntBAnd, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto bAndType = this->getType();
    UInt bAnd = 0;

    if (bAndType.first == ExpType::SInt) {
      bAnd = (SInt)_items[0]->evaluate(time) &
             (SInt)_items[1]->evaluate(time);
      RESIZES(bAnd, bAndType)
    } else {
      bAnd = (UInt)_items[0]->evaluate(time) &
             (UInt)_items[1]->evaluate(time);
      RESIZEU(bAnd, bAndType)
    }
    return bAnd;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntBOr, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto bOrType = this->getType();
    UInt bOr = 0;

    if (bOrType.first == ExpType::SInt) {
      bOr = (SInt)_items[0]->evaluate(time) |
            (SInt)_items[1]->evaluate(time);
      RESIZES(bOr, bOrType)
    } else {
      bOr = (UInt)_items[0]->evaluate(time) |
            (UInt)_items[1]->evaluate(time);
      RESIZEU(bOr, bOrType)
    }
    return bOr;
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntBXor, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto bXorType = this->getType();
    UInt bXor = 0;

    if (bXorType.first == ExpType::SInt) {
      bXor = (SInt)_items[0]->evaluate(time) ^
             (SInt)_items[1]->evaluate(time);
      RESIZES(bXor, bXorType)
    } else {
      bXor = (UInt)_items[0]->evaluate(time) ^
             (UInt)_items[1]->evaluate(time);
      RESIZEU(bXor, bXorType)
    }
    return bXor;
  };
  disableCache();
}
template <>
void GenericExpression<ope::ope::IntEq, IntExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());

    if (resType.first == ExpType::SInt) {
      return (SInt)_items[0]->evaluate(time) ==
             (SInt)_items[1]->evaluate(time);
    } else {
      return (UInt)_items[0]->evaluate(time) ==
             (UInt)_items[1]->evaluate(time);
    }
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntNeq, IntExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());

    if (resType.first == ExpType::SInt) {
      return (SInt)_items[0]->evaluate(time) !=
             (SInt)_items[1]->evaluate(time);
    } else {
      return (UInt)_items[0]->evaluate(time) !=
             (UInt)_items[1]->evaluate(time);
    }
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntGreater, IntExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());

    if (resType.first == ExpType::SInt) {
      return (SInt)_items[0]->evaluate(time) >
             (SInt)_items[1]->evaluate(time);
    } else {
      return (UInt)_items[0]->evaluate(time) >
             (UInt)_items[1]->evaluate(time);
    }
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntGreaterEq, IntExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));
    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());

    if (resType.first == ExpType::SInt) {
      return (SInt)_items[0]->evaluate(time) >=
             (SInt)_items[1]->evaluate(time);
    } else {
      return (UInt)_items[0]->evaluate(time) >=
             (UInt)_items[1]->evaluate(time);
    }
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntLess, IntExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());

    if (resType.first == ExpType::SInt) {
      return (SInt)_items[0]->evaluate(time) <
             (SInt)_items[1]->evaluate(time);
    } else {
      return (UInt)_items[0]->evaluate(time) <
             (UInt)_items[1]->evaluate(time);
    }
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntLessEq, IntExpression,
                       Proposition>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[1]->getType());

    if (resType.first == ExpType::SInt) {
      return (SInt)_items[0]->evaluate(time) <=
             (SInt)_items[1]->evaluate(time);
    } else {
      return (UInt)_items[0]->evaluate(time) <=
             (UInt)_items[1]->evaluate(time);
    }
  };
  disableCache();
}

template <>
void GenericExpression<ope::ope::IntNot, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 1,
                   "size==" + std::to_string(_items.size()));
    auto resType = applyCStandardConversion(_items[0]->getType(),
                                            _items[0]->getType());

    if (resType.first == ExpType::SInt) {
      auto res = ~(SInt)_items[0]->evaluate(time);
      RESIZES(res, resType);
      return (UInt)res;
    } else {
      auto res = ~(UInt)_items[0]->evaluate(time);
      RESIZEU(res, resType);
      return res;
    }
  };
  disableCache();
}
template <>
void GenericExpression<ope::ope::IntLShift, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    if (this->getType().first == ExpType::SInt) {
      messageWarningIf(
          (SInt)_items[0]->evaluate(time) < 0,
          "left bit shift on negative values is undefined behavior, "
          "got:" +
              std::to_string((SInt)_items[0]->evaluate(time)) + "");
      messageErrorIf(
          (SInt)_items[1]->evaluate(time) < 0,
          "right side of left bit shift must be positive, got:" +
              std::to_string((SInt)_items[1]->evaluate(time)));
      messageErrorIf(
          (SInt)_items[1]->evaluate(time) >
              (SInt)_items[0]->getType().second,
          "right side of left bit shift is greater than left side "
          "size, got:" +
              std::to_string((SInt)_items[1]->evaluate(time)));
      auto res = (SInt)_items[0]->evaluate(time)
                 << (SInt)_items[1]->evaluate(time);
      RESIZES(res, this->getType())
      return (UInt)res;
    } else {
      messageWarningIf(
          (UInt)_items[0]->evaluate(time) < 0,
          "left bit shift on negative values is undefined behavior, "
          "got:" +
              std::to_string((UInt)_items[0]->evaluate(time)) + "");
      messageErrorIf(
          (UInt)_items[1]->evaluate(time) < 0,
          "right side of left bit shift must be positive, got:" +
              std::to_string((UInt)_items[1]->evaluate(time)));
      messageErrorIf(
          (UInt)_items[1]->evaluate(time) >
              (UInt)_items[0]->getType().second,
          "right side of left bit shift is greater than left side "
          "size, got:" +
              std::to_string((UInt)_items[1]->evaluate(time)));
      auto res = (UInt)_items[0]->evaluate(time)
                 << (UInt)_items[1]->evaluate(time);
      RESIZEU(res, this->getType())
      return res;
    }
  };
  disableCache();
}
template <>
void GenericExpression<ope::ope::IntRShift, IntExpression,
                       IntExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    messageErrorIf(_items.size() != 2,
                   "size==" + std::to_string(_items.size()));

    if (this->getType().first == ExpType::SInt) {
      messageErrorIf(
          (SInt)_items[1]->evaluate(time) < 0,
          "right side of right bit shift must be positive, got:" +
              std::to_string((SInt)_items[1]->evaluate(time)));
      messageErrorIf(
          (SInt)_items[1]->evaluate(time) >
              (SInt)_items[0]->getType().second,
          "right side of right bit shift is greater than left side "
          "size, got:" +
              std::to_string((SInt)_items[1]->evaluate(time)));
      auto res = (SInt)_items[0]->evaluate(time) >>
                 (SInt)_items[1]->evaluate(time);
      RESIZES(res, this->getType())
      return (UInt)res;
    } else {
      messageErrorIf(
          (UInt)_items[1]->evaluate(time) < 0,
          "right side of right bit shift must be positive, got:" +
              std::to_string((UInt)_items[1]->evaluate(time)));
      messageErrorIf(
          (UInt)_items[1]->evaluate(time) >
              (UInt)_items[0]->getType().second,
          "right side of right bit shift is greater than left side "
          "size, got:" +
              std::to_string((UInt)_items[1]->evaluate(time)));
      auto res = (UInt)_items[0]->evaluate(time) >>
                 (UInt)_items[1]->evaluate(time);
      RESIZEU(res, this->getType())
      return res;
    }
  };
  disableCache();
}

} // namespace expression
