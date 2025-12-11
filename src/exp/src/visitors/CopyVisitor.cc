#include <memory>
#include <utility>
#include <vector>

#include "../../miner/utils/include/DTLimits.hh"
#include "formula/atom/Constant.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/BitSelector.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/expression/SetMembership.hh"
#include "formula/expression/Substring.hh"
#include "formula/expression/TypeCast.hh"
#include "formula/function/Function.hh"
#include "formula/function/SVAfunction.hh"
#include "formula/temporal/Property.hh"
#include "formula/temporal/Sere.hh"
#include "misc.hh"
#include "visitors/CopyVisitor.hh"

//------------------------------------------------------------------------------
#define LEAF_NODE(LEAF, DEST)                                        \
  void CopyVisitor::visit(LEAF &o) { DEST = generatePtr<LEAF>(o); }

#define EXPRESSION(OPERATOR, OPERAND, RESULT)                        \
  void CopyVisitor::visit(OPERATOR &o) {                             \
    auto copy = makeGenericExpression<OPERATOR>(o.getMaxTime());     \
    auto type = o.getType();                                         \
    copy->setType(type.first, type.second);                          \
    auto &items = o.getItems();                                      \
    for (const auto &item : items) {                                 \
      item->acceptVisitor(*this);                                    \
      copy->addItem(OPERAND);                                        \
    }                                                                \
    RESULT = copy;                                                   \
  }

#define TEMPORAL_EXPRESSION(OPERATOR, OPERAND, RESULT)               \
  void CopyVisitor::visit(OPERATOR &o) {                             \
    auto copy = generatePtr<OPERATOR>();                             \
    auto &items = o.getItems();                                      \
    for (const auto &item : items) {                                 \
      item->acceptVisitor(*this);                                    \
      copy->addItem(OPERAND);                                        \
    }                                                                \
    RESULT = copy;                                                   \
  }

#define SERE_WINDOW_BASED(OPERATOR, OPERAND, RESULT)                 \
  void CopyVisitor::visit(OPERATOR &o) {                             \
    auto copy = generatePtr<OPERATOR>();                             \
    copy->setWindow(o.getWindow());                                  \
    auto &items = o.getItems();                                      \
    for (const auto &item : items) {                                 \
      item->acceptVisitor(*this);                                    \
      copy->addItem(OPERAND);                                        \
    }                                                                \
    RESULT = copy;                                                   \
  }

#define UNARY_FUNCTION(TYPE, RESULT)                                 \
  void CopyVisitor::visit(TYPE &o) { RESULT = o.clone(); }

#define TYPE_CAST(OPERATOR, OPERAND, RESULT)                         \
  void CopyVisitor::visit(OPERATOR &o) {                             \
    o.getItem()->acceptVisitor(*this);                               \
    RESULT = generatePtr<OPERATOR>(OPERAND);                         \
  }
//------------------------------------------------------------------------------

namespace expression {

CopyVisitor::CopyVisitor(bool removePlaceholders)
    : ExpVisitor(), _proposition(nullptr), _float(nullptr),
      _int(nullptr), _removePlaceholders(removePlaceholders) {
  // ntd
}

CopyVisitor::~CopyVisitor() {
  //the caller of the visitor is responsible for deleting the returned object
}

void CopyVisitor::reset() {
  _proposition = nullptr;
  _float = nullptr;
  _int = nullptr;
  _logic = nullptr;
  _string = nullptr;
  _temporal = nullptr;
}

PropositionPtr CopyVisitor::getProposition() {
  messageErrorIf(
      _proposition == nullptr,
      "CopyVisitor::getProposition() : no proposition found");
  PropositionPtr ret = _proposition;
  _proposition = nullptr;
  return ret;
}
IntExpressionPtr CopyVisitor::getInt() {
  messageErrorIf(_int == nullptr,
                 "CopyVisitor::getInt() : no int expression found");
  IntExpressionPtr ret = _int;
  reset();
  return ret;
}
FloatExpressionPtr CopyVisitor::getFloat() {
  messageErrorIf(
      _float == nullptr,
      "CopyVisitor::getFloat() : no float expression found");
  FloatExpressionPtr ret = _float;
  reset();
  return ret;
}
TemporalExpressionPtr CopyVisitor::getTemporal() {
  messageErrorIf(
      _temporal == nullptr,
      "CopyVisitor::getTemporal() : no temporal expression found");
  TemporalExpressionPtr ret = _temporal;
  reset();
  return ret;
}

LogicExpressionPtr CopyVisitor::getLogic() {
  messageErrorIf(
      _logic == nullptr,
      "CopyVisitor::getLogic() : no logic expression found");
  LogicExpressionPtr ret = _logic;
  reset();
  return ret;
}

StringExpressionPtr CopyVisitor::getString() {
  messageErrorIf(
      _string == nullptr,
      "CopyVisitor::getString() : no string expression found");
  StringExpressionPtr ret = _string;
  reset();
  return ret;
}

NumericExpressionPtr CopyVisitor::getNum() {
  if (_float != nullptr) {
    return generatePtr<NumericExpression>(getFloat());
  } else if (_int != nullptr) {
    return generatePtr<NumericExpression>(getInt());
  } else if (_logic != nullptr) {
    return generatePtr<NumericExpression>(getLogic());
  }
  messageError("CopyVisitor::getNum() : no numeric expression found");
  return nullptr;
}

// proposition
LEAF_NODE(BooleanConstant, _proposition)
LEAF_NODE(BooleanVariable, _proposition)
EXPRESSION(PropositionAnd, _proposition, _proposition)
EXPRESSION(PropositionOr, _proposition, _proposition)
EXPRESSION(PropositionXor, _proposition, _proposition)
EXPRESSION(PropositionEq, _proposition, _proposition)
EXPRESSION(PropositionNeq, _proposition, _proposition)
EXPRESSION(PropositionNot, _proposition, _proposition)
UNARY_FUNCTION(PropositionPast, _proposition)
UNARY_FUNCTION(PropositionStable, _proposition)
UNARY_FUNCTION(PropositionFell, _proposition)
UNARY_FUNCTION(PropositionRose, _proposition)

// float
LEAF_NODE(FloatConstant, _float)
LEAF_NODE(FloatVariable, _float)
EXPRESSION(FloatSum, _float, _float)
EXPRESSION(FloatSub, _float, _float)
EXPRESSION(FloatMul, _float, _float)
EXPRESSION(FloatDiv, _float, _float)
EXPRESSION(FloatEq, _float, _proposition)
EXPRESSION(FloatNeq, _float, _proposition)
EXPRESSION(FloatLess, _float, _proposition)
EXPRESSION(FloatLessEq, _float, _proposition)
EXPRESSION(FloatGreater, _float, _proposition)
EXPRESSION(FloatGreaterEq, _float, _proposition)
TYPE_CAST(FloatToBool, _float, _proposition)
TYPE_CAST(FloatToInt, _float, _int)
TYPE_CAST(FloatToLogic, _float, _logic)
UNARY_FUNCTION(FloatPast, _float)
UNARY_FUNCTION(FloatStable, _proposition)

void CopyVisitor::visit(FloatSetMembership &o) {
  o.getItem()->acceptVisitor(*this);
  _proposition = generatePtr<FloatSetMembership>(o);
}

// int
LEAF_NODE(IntConstant, _int)
LEAF_NODE(IntVariable, _int)
EXPRESSION(IntSum, _int, _int)
EXPRESSION(IntSub, _int, _int)
EXPRESSION(IntMul, _int, _int)
EXPRESSION(IntDiv, _int, _int)
EXPRESSION(IntBAnd, _int, _int)
EXPRESSION(IntBOr, _int, _int)
EXPRESSION(IntBXor, _int, _int)
EXPRESSION(IntNot, _int, _int)
EXPRESSION(IntEq, _int, _proposition)
EXPRESSION(IntNeq, _int, _proposition)
EXPRESSION(IntLess, _int, _proposition)
EXPRESSION(IntLessEq, _int, _proposition)
EXPRESSION(IntGreater, _int, _proposition)
EXPRESSION(IntGreaterEq, _int, _proposition)
EXPRESSION(IntRShift, _int, _int)
EXPRESSION(IntLShift, _int, _int)
TYPE_CAST(IntToBool, _int, _proposition)
TYPE_CAST(IntToFloat, _int, _float)
TYPE_CAST(IntToLogic, _int, _logic)
UNARY_FUNCTION(IntPast, _int)
UNARY_FUNCTION(IntStable, _proposition)
UNARY_FUNCTION(IntFell, _proposition)
UNARY_FUNCTION(IntRose, _proposition)

void CopyVisitor::visit(IntBitSelector &o) {
  o.getItem()->acceptVisitor(*this);
  _int = generatePtr<IntBitSelector>(_int, o.getUpperBound(),
                                     o.getLowerBound());
}

void CopyVisitor::visit(IntSetMembership &o) {
  o.getItem()->acceptVisitor(*this);
  _proposition = generatePtr<IntSetMembership>(o);
}

//logic
LEAF_NODE(LogicConstant, _logic)
LEAF_NODE(LogicVariable, _logic)
EXPRESSION(LogicSum, _logic, _logic)
EXPRESSION(LogicSub, _logic, _logic)
EXPRESSION(LogicMul, _logic, _logic)
EXPRESSION(LogicDiv, _logic, _logic)
EXPRESSION(LogicBAnd, _logic, _logic)
EXPRESSION(LogicBOr, _logic, _logic)
EXPRESSION(LogicBXor, _logic, _logic)
EXPRESSION(LogicNot, _logic, _logic)
EXPRESSION(LogicEq, _logic, _proposition)
EXPRESSION(LogicNeq, _logic, _proposition)
EXPRESSION(LogicLess, _logic, _proposition)
EXPRESSION(LogicLessEq, _logic, _proposition)
EXPRESSION(LogicGreater, _logic, _proposition)
EXPRESSION(LogicGreaterEq, _logic, _proposition)
EXPRESSION(LogicRShift, _logic, _logic)
EXPRESSION(LogicLShift, _logic, _logic)
TYPE_CAST(LogicToBool, _logic, _proposition)
TYPE_CAST(LogicToFloat, _logic, _float)
TYPE_CAST(LogicToInt, _logic, _int)
UNARY_FUNCTION(LogicPast, _logic)
UNARY_FUNCTION(LogicStable, _proposition)
UNARY_FUNCTION(LogicFell, _proposition)
UNARY_FUNCTION(LogicRose, _proposition)

void CopyVisitor::visit(LogicBitSelector &o) {
  o.getItem()->acceptVisitor(*this);
  _logic = generatePtr<LogicBitSelector>(_logic, o.getUpperBound(),
                                         o.getLowerBound());
}

void CopyVisitor::visit(LogicSetMembership &o) {
  o.getItem()->acceptVisitor(*this);
  _proposition = generatePtr<LogicSetMembership>(o);
}

// string
LEAF_NODE(StringConstant, _string)
LEAF_NODE(StringVariable, _string)
EXPRESSION(StringConcat, _string, _string)
EXPRESSION(StringEq, _string, _proposition)
EXPRESSION(StringNeq, _string, _proposition)
EXPRESSION(StringLess, _string, _proposition)
EXPRESSION(StringLessEq, _string, _proposition)
EXPRESSION(StringGreater, _string, _proposition)
EXPRESSION(StringGreaterEq, _string, _proposition)

void CopyVisitor::visit(Substring &o) {
  o.getItem()->acceptVisitor(*this);
  _string = generatePtr<Substring>(_string, o.getStartIndex(),
                                   o.getNChars());
}

//temporal
void CopyVisitor::visit(BooleanLayerNot &o) {
  o.getBL()->acceptVisitor(*this);
  _temporal = generatePtr<BooleanLayerNot>(_temporal);
}

void CopyVisitor::visit(BooleanLayerPermutationPlaceholder &o) {
  if (!_removePlaceholders) {
    messageErrorIf(_proposition != nullptr,
                   "CopyVisitor::visit(BooleanLayerPlaceholder) : "
                   "there should not be a proposition here");
    if (!_tokenToTempExp.count(o.getToken())) {
      //generate the placeholder
      _temporal = generatePtr<BooleanLayerPermutationPlaceholder>(
          generatePtrPtr<Proposition>((Proposition *)nullptr),
          o.getToken());
      _tokenToTempExp[o.getToken()] = _temporal;
    } else {
      //reuse the placeholder
      _temporal = std::dynamic_pointer_cast<
          BooleanLayerPermutationPlaceholder>(
          _tokenToTempExp.at(o.getToken()));
    }
  } else {
    //the _r is to specify that this inst was generated by removing a placeholder
    (*o.getPlaceholderPointer())->acceptVisitor(*this);
    _temporal = generatePtr<BooleanLayerInst>(_proposition,
                                              o.getToken() + "_r");
    _proposition = nullptr;
  }
}
void CopyVisitor::visit(BooleanLayerDTPlaceholder &o) {
  if (!_removePlaceholders) {
    messageErrorIf(_proposition != nullptr,
                   "CopyVisitor::visit(BooleanLayerDTPlaceholder) : "
                   "there should not be a proposition here");
    BooleanLayerDTPlaceholderPtr pp =
        generatePtr<BooleanLayerDTPlaceholder>(
            o.getType(),
            generatePtrPtr<Proposition>((Proposition *)nullptr),
            o.getToken(), o.getID());
    _temporal = pp;
  } else {
    (*o.getPlaceholderPointer())->acceptVisitor(*this);
    _temporal = generatePtr<BooleanLayerInst>(_proposition,
                                              o.getToken() + "_r");
    _proposition = nullptr;
  }
}

void CopyVisitor::visit(BooleanLayerInst &o) {
  messageErrorIf(o.getProposition() == nullptr,
                 "CopyVisitor::visit(BooleanLayerInst) : "
                 "no proposition found");
  if (!_tokenToTempExp.count(o.getToken())) {
    //generate the inst
    o.getProposition()->acceptVisitor(*this);
    _temporal =
        generatePtr<BooleanLayerInst>(_proposition, o.getToken());
    _tokenToTempExp[o.getToken()] = _temporal;
  } else {
    //reuse the inst
    _temporal = _tokenToTempExp.at(o.getToken());
  }
  _proposition = nullptr;
}

void CopyVisitor::visit(BooleanLayerFunction &o) {

  if (!_removePlaceholders) {
    messageErrorIf(_proposition != nullptr,
                   "CopyVisitor::visit(BooleanLayerFunction) : "
                   "there should not be a proposition here");
    _temporal = generatePtr<BooleanLayerFunction>(
        o.getFunction()->clone(), o.getToken());
  } else {
    //copy the function to the propositional layer
    (*o.getFunction()->getPlaceholderPointer())->acceptVisitor(*this);
    //FIXME: this is not optimal, we should not modify the original function, can we do better?
    o.getFunction()->setTemporal(0);
    o.getFunction()->setOperand(_proposition);
    FunctionPropositionPtr f = o.getFunction()->clone();
    o.getFunction()->setOperand(nullptr);
    o.getFunction()->setTemporal(1);

    _proposition = nullptr;
    _temporal = generatePtr<BooleanLayerInst>(f, o.getToken() + "_r");
  }
}

void CopyVisitor::visit(PropertyImplication &o) {
  auto copy = generatePtr<PropertyImplication>();
  copy->setOverlapping(o.isOverlapping());
  copy->setMMImplication(o.isMMImplication());
  auto &items = o.getItems();
  messageErrorIf(items.size() != 2,
                 "CopyVisitor::visit(PropertyImplication) : "
                 "PropertyImplication should have 2 items");
  for (const auto &item : items) {
    item->acceptVisitor(*this);
    copy->addItem(_temporal);
  }
  _temporal = copy;
}
void CopyVisitor::visit(PropertyNext &o) {
  auto copy = generatePtr<PropertyNext>();
  copy->setDelay(o.getDelay());
  auto &items = o.getItems();
  messageErrorIf(items.size() != 1,
                 "CopyVisitor::visit(PropertyNext) : "
                 "PropertyNext should have 1 item");
  items[0]->acceptVisitor(*this);
  copy->addItem(_temporal);
  _temporal = copy;
}
void CopyVisitor::visit(SereConcat &o) {
  auto copy = generatePtr<SereConcat>();
  copy->setOverlapping(o.isOverlapping());
  auto &items = o.getItems();
  messageErrorIf(items.size() != 2,
                 "CopyVisitor::visit(SereConcat) : "
                 "SereConcat should have 2 items");

  for (const auto &item : items) {
    item->acceptVisitor(*this);
    copy->addItem(_temporal);
  }
  _temporal = copy;
}

TEMPORAL_EXPRESSION(PropertyAlways, _temporal, _temporal);
TEMPORAL_EXPRESSION(PropertyEventually, _temporal, _temporal);
TEMPORAL_EXPRESSION(PropertyAnd, _temporal, _temporal);
TEMPORAL_EXPRESSION(PropertyOr, _temporal, _temporal);
TEMPORAL_EXPRESSION(PropertyNot, _temporal, _temporal);
TEMPORAL_EXPRESSION(PropertyRelease, _temporal, _temporal);
TEMPORAL_EXPRESSION(PropertyUntil, _temporal, _temporal);
TEMPORAL_EXPRESSION(SereAnd, _temporal, _temporal);
TEMPORAL_EXPRESSION(SereOr, _temporal, _temporal);
TEMPORAL_EXPRESSION(SereIntersect, _temporal, _temporal);
TEMPORAL_EXPRESSION(SereFirstMatch, _temporal, _temporal);
TEMPORAL_EXPRESSION(SerePlus, _temporal, _temporal);
SERE_WINDOW_BASED(SereDelay, _temporal, _temporal);
SERE_WINDOW_BASED(SereConsecutiveRep, _temporal, _temporal);
SERE_WINDOW_BASED(SereGoto, _temporal, _temporal);
SERE_WINDOW_BASED(SereNonConsecutiveRep, _temporal, _temporal);

} // namespace expression
