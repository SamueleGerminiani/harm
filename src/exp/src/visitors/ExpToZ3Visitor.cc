
#include "visitors/ExpToZ3Visitor.hh"
#include "expUtils/cConversion.hh"

namespace expression {
static float float_precision = 0.01;
static float float_limit = std::pow(2, 20);
static double double_precision = 0.01;
static double double_limit = std::pow(2, 30);

#define EXTEND_LOGIC(O, OE1, OE2, E1, E2)                                      \
  uint8_t TO_EXTEND[2];                                                        \
  TO_EXTEND[0] = std::abs(OE1->getType().second - O.getType().second);         \
  TO_EXTEND[1] = std::abs(OE2->getType().second - O.getType().second);         \
  if (TO_EXTEND[0] > 0) {                                                      \
    /*If the operand is going from unsigned to signed, add a zero to           \
    avoid errors with z3::sext*/                                               \
    if (OE1->getType().first == VarType::ULogic) {                             \
      E1 = z3::zext(E1, 1);                                                    \
      TO_EXTEND[0] = TO_EXTEND[0] - 1;                                         \
    }                                                                          \
    E1 = z3::sext(E1, TO_EXTEND[0]);                                           \
  }                                                                            \
  if (TO_EXTEND[1] > 0) {                                                      \
    if (OE2->getType().first == VarType::ULogic) {                             \
      E2 = z3::zext(E2, 1);                                                    \
      TO_EXTEND[1] = TO_EXTEND[1] - 1;                                         \
    }                                                                          \
    E2 = z3::sext(E2, TO_EXTEND[1]);                                           \
  }

#define EXTEND_LOGIC_APPLY_CSTANDARD(O, OE1, OE2, E1, E2)                      \
  auto conversionResult = applyCStandardConversion(                            \
      std::make_pair(OE1->getType().first, OE1->getType().second),             \
      std::make_pair(OE2->getType().first, OE2->getType().second));            \
  uint8_t TO_EXTEND[2];                                                        \
  TO_EXTEND[0] = std::abs(OE1->getType().second - conversionResult.second);    \
  TO_EXTEND[1] = std::abs(OE2->getType().second - conversionResult.second);    \
  if (TO_EXTEND[0] > 0) {                                                      \
    /*If the operand is going from unsigned to signed, add a zero to           \
    avoid errors with z3::sext*/                                               \
    if (OE1->getType().first == VarType::ULogic) {                             \
      E1 = z3::zext(E1, 1);                                                    \
      TO_EXTEND[0] = TO_EXTEND[0] - 1;                                         \
    }                                                                          \
    E1 = z3::sext(E1, TO_EXTEND[0]);                                           \
  }                                                                            \
  if (TO_EXTEND[1] > 0) {                                                      \
    if (OE2->getType().first == VarType::ULogic) {                             \
      E2 = z3::zext(E2, 1);                                                    \
      TO_EXTEND[1] = TO_EXTEND[1] - 1;                                         \
    }                                                                          \
    E2 = z3::sext(E2, TO_EXTEND[1]);                                           \
  }

#define EXTEND_FLOAT(O, OE1, OE2, E1, E2)                                      \
  bool TO_EXTEND[2];                                                           \
  TO_EXTEND[0] = (O.getType().second - OE1->getType().second) != 0;            \
  TO_EXTEND[1] = (O.getType().second - OE2->getType().second) != 0;            \
  z3::expr rm(_c, _c.fpa_rounding_mode());                                     \
  z3::sort srt = _c.fpa_sort(11, 53);                                          \
  if (TO_EXTEND[0]) {                                                          \
    E1 = z3::expr(_c, Z3_mk_fpa_to_fp_float(_c, rm, E1, srt));                 \
  }                                                                            \
  if (TO_EXTEND[1]) {                                                          \
    E2 = z3::expr(_c, Z3_mk_fpa_to_fp_float(_c, rm, E2, srt));                 \
  }

#define EXTEND_FLOAT_APPLY_CSTANDARD(O, OE1, OE2, E1, E2)                      \
  auto conversionResult = applyCStandardConversion(                            \
      std::make_pair(OE1->getType().first, OE1->getType().second),             \
      std::make_pair(OE2->getType().first, OE2->getType().second));            \
                                                                               \
  bool TO_EXTEND[2];                                                           \
  TO_EXTEND[0] = (conversionResult.second - OE1->getType().second) != 0;       \
  TO_EXTEND[1] = (conversionResult.second - OE2->getType().second) != 0;       \
                                                                               \
  z3::expr rm(_c, _c.fpa_rounding_mode());                                     \
  z3::sort srt = _c.fpa_sort(11, 53);                                          \
  if (TO_EXTEND[0]) {                                                          \
    E1 = z3::expr(_c, Z3_mk_fpa_to_fp_float(_c, rm, E1, srt));                 \
  }                                                                            \
  if (TO_EXTEND[1]) {                                                          \
    E2 = z3::expr(_c, Z3_mk_fpa_to_fp_float(_c, rm, E2, srt));                 \
  }

ExpToZ3Visitor::~ExpToZ3Visitor() {}

ExpToZ3Visitor::ExpToZ3Visitor()
    : ExpVisitor(), _z3Expressions(), _overflowCond(_c), _varToTypeSize() {

  _overflowCond = _c.bool_val(true);
}

z3::expr ExpToZ3Visitor::get() {
  assert(_z3Expressions.size() == 1);
  //    std::cout<<_overflowCond<<"\n";
  return _z3Expressions.top() && _overflowCond;
}

size_t ExpToZ3Visitor::getNumberVariables() { return _varToTypeSize.size(); }
void ExpToZ3Visitor::clear() {
  for (size_t i = 0; i < _z3Expressions.size(); i++) {
    _z3Expressions.pop();
  }

  _overflowCond = _c.bool_val(true);
  _varToTypeSize.clear();
}

// proposition
void ExpToZ3Visitor::visit(expression::BooleanVariable &o) {
  assert(_varToTypeSize.count(o.getName()) == 0 ||
         (_varToTypeSize.at(o.getName()) ==
          std::make_pair(o.getType().first, o.getType().second)));
  _varToTypeSize[o.getName()] = o.getType();

  _z3Expressions.push(_c.bool_const(o.getName().c_str()));
}

void ExpToZ3Visitor::visit(expression::BooleanConstant &o) {
  if (o.evaluate(0)) {
    z3::expr trueConstant = _c.bool_val(true);
    _z3Expressions.push(trueConstant);
  } else {
    z3::expr falseConstant = _c.bool_val(false);
    _z3Expressions.push(falseConstant);
  }
}

void ExpToZ3Visitor::visit(expression::PropositionAnd &o) {
  z3::expr_vector expVector(_c);

  //  assert(o.getItems().size() > 1);

  for (const auto &e : o.getItems()) {
    e->acceptVisitor(*this);
    expVector.push_back(_z3Expressions.top());
    _z3Expressions.pop();
  }
  _z3Expressions.push(z3::mk_and(expVector));
}

void ExpToZ3Visitor::visit(expression::PropositionOr &o) {
  z3::expr_vector expVector(_c);

  assert(o.getItems().size() > 1);

  for (const auto &e : o.getItems()) {
    e->acceptVisitor(*this);
    expVector.push_back(_z3Expressions.top());
    _z3Expressions.pop();
  }
  _z3Expressions.push(z3::mk_or(expVector));
}
void ExpToZ3Visitor::visit(expression::PropositionXor &o) {
  assert(o.getItems().size() == 2);
  o.getItems()[0]->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();
  o.getItems()[1]->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  _z3Expressions.push(e1 ^ e2);
}

void ExpToZ3Visitor::visit(expression::PropositionEq &o) {
  assert(o.getItems().size() == 2);
  o.getItems()[0]->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();
  o.getItems()[1]->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  _z3Expressions.push(e1 == e2);
}

void ExpToZ3Visitor::visit(expression::PropositionNeq &o) {
  assert(o.getItems().size() == 2);
  o.getItems()[0]->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();
  o.getItems()[1]->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  _z3Expressions.push(e1 != e2);
}

void ExpToZ3Visitor::visit(expression::PropositionNot &o) {
  assert(o.getItems().size() == 1);
  o.getItems()[0]->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();
  _z3Expressions.push(!e1);
}

void ExpToZ3Visitor::visit(expression::LogicNot &o) {
  assert(o.getItems().size() == 1);
  o.getItems()[0]->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();
  _z3Expressions.push(~e1);
}

// numeric
void ExpToZ3Visitor::visit(expression::NumericVariable &o) {
  assert(_varToTypeSize.count(o.getName()) == 0 ||
         (_varToTypeSize.at(o.getName()) ==
          std::make_pair(o.getType().first, o.getType().second)));

  _varToTypeSize[o.getName()] = o.getType();

  if (o.getType().second == 32) {
    z3::expr var = _c.fpa_const(o.getName().c_str(), 8, 24);
    _z3Expressions.push(var);
    _overflowCond = _overflowCond &&
                    var != _c.fpa_val(-std::numeric_limits<float>::infinity());
    _overflowCond = _overflowCond &&
                    var != _c.fpa_val(std::numeric_limits<float>::infinity());
    _overflowCond =
        _overflowCond &&
        (z3::abs(var) > _c.fpa_val(float_precision) || var == _c.fpa_val(.0f));
    _overflowCond = _overflowCond && (z3::abs(var) < _c.fpa_val(float_limit));
  } else if (o.getType().second == 64) {
    z3::expr var = _c.fpa_const(o.getName().c_str(), 11, 53);
    _z3Expressions.push(var);
    _overflowCond = _overflowCond && var != _c.fpa_val(std::nan(""));
    _overflowCond = _overflowCond &&
                    var != _c.fpa_val(std::numeric_limits<double>::infinity());
    _overflowCond = _overflowCond &&
                    var != _c.fpa_val(-std::numeric_limits<double>::infinity());
    _overflowCond =
        _overflowCond &&
        (z3::abs(var) > _c.fpa_val(double_precision) || var == _c.fpa_val(.0));
    _overflowCond = _overflowCond && (z3::abs(var) < _c.fpa_val(double_limit));
  } else {
    messageError("Wrong floating-point size: expected 32 or 64!");
  }
}

void ExpToZ3Visitor::visit(expression::NumericConstant &o) {
  if (o.getType().second == 32) {
    _z3Expressions.push(_c.fpa_val((float)o.evaluate(0)));
  } else if (o.getType().second == 64) {
    _z3Expressions.push(_c.fpa_val((double)o.evaluate(0)));
  } else {
    messageError("Wrong floating-point size: expected 32 or 64!");
  }
}

void ExpToZ3Visitor::visit(expression::NumericSum &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT(o, oe1, oe2, e1, e2);

  z3::expr finalExpr = e1 + e2;

  _z3Expressions.push(finalExpr);
}

void ExpToZ3Visitor::visit(expression::NumericSub &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT(o, oe1, oe2, e1, e2);
  z3::expr finalExpr = e1 - e2;

  _z3Expressions.push(finalExpr);
}

void ExpToZ3Visitor::visit(expression::NumericMul &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT(o, oe1, oe2, e1, e2);

  z3::expr finalExpr = e1 * e2;

  _z3Expressions.push(finalExpr);
}
void ExpToZ3Visitor::visit(expression::NumericDiv &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  if (oe2->getType().second == 32) {
    _overflowCond = _overflowCond && (e2 != _c.fpa_val((float)0));
  } else {
    _overflowCond = _overflowCond && (e2 != _c.fpa_val((double)0));
  }

  EXTEND_FLOAT(o, oe1, oe2, e1, e2);

  z3::expr finalExpr = e1 / e2;

  _z3Expressions.push(finalExpr);
}
void ExpToZ3Visitor::visit(expression::NumericEq &o) {
  assert(o.getItems().size() == 2);
  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT_APPLY_CSTANDARD(o, oe1, oe2, e1, e2);

  _z3Expressions.push(e1 == e2);
}
void ExpToZ3Visitor::visit(expression::NumericNeq &o) {
  assert(o.getItems().size() == 2);
  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT_APPLY_CSTANDARD(o, oe1, oe2, e1, e2);

  _z3Expressions.push(e1 != e2);
}

void ExpToZ3Visitor::visit(expression::NumericGreater &o) {
  assert(o.getItems().size() == 2);
  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT_APPLY_CSTANDARD(o, oe1, oe2, e1, e2);

  _z3Expressions.push(e1 > e2);
}

void ExpToZ3Visitor::visit(expression::NumericGreaterEq &o) {
  assert(o.getItems().size() == 2);
  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT_APPLY_CSTANDARD(o, oe1, oe2, e1, e2);

  _z3Expressions.push(e1 >= e2);
}

void ExpToZ3Visitor::visit(expression::NumericLess &o) {
  assert(o.getItems().size() == 2);
  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT_APPLY_CSTANDARD(o, oe1, oe2, e1, e2);

  _z3Expressions.push(e1 < e2);
}

void ExpToZ3Visitor::visit(expression::NumericLessEq &o) {
  assert(o.getItems().size() == 2);
  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_FLOAT_APPLY_CSTANDARD(o, oe1, oe2, e1, e2);

  _z3Expressions.push(e1 <= e2);
}

void ExpToZ3Visitor::visit(expression::NumericToBool &o) {
  o.getItem().acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();
  _z3Expressions.push(e1 > 0);
}

// logic
void ExpToZ3Visitor::visit(expression::LogicVariable &o) {
  assert(_varToTypeSize.count(o.getName()) == 0 ||
         (_varToTypeSize.at(o.getName()) ==
          std::make_pair(o.getType().first, o.getType().second)));

  _varToTypeSize[o.getName()] =
      std::make_pair(o.getType().first, o.getType().second);

  _z3Expressions.push(_c.bv_const(o.getName().c_str(), o.getType().second));
}

void ExpToZ3Visitor::visit(expression::LogicConstant &o) {
  _z3Expressions.push(_c.bv_val(o.evaluate(0), o.getType().second));
}
void ExpToZ3Visitor::visit(expression::LogicSum &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = e1 + e2;

  // Add over/underflow conditions
  if (o.getType().first == VarType::SLogic) {
    _overflowCond = _overflowCond && z3::bvadd_no_overflow(e1, e2, true);
    _overflowCond = _overflowCond && z3::bvadd_no_underflow(e1, e2);
  } else {
    _overflowCond = _overflowCond && z3::bvadd_no_overflow(e1, e2, false);
    _overflowCond = _overflowCond && z3::bvadd_no_underflow(e1, e2);
  }

  _z3Expressions.push(finalExpr);
}

void ExpToZ3Visitor::visit(expression::LogicSub &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = e1 - e2;

  // Add over/underflow conditions
  if (o.getType().first == VarType::SLogic) {
    _overflowCond = _overflowCond && z3::bvsub_no_overflow(e1, e2);
    _overflowCond = _overflowCond && z3::bvsub_no_underflow(e1, e2, true);
  } else {
    _overflowCond = _overflowCond && z3::bvsub_no_overflow(e1, e2);
    _overflowCond = _overflowCond && z3::bvsub_no_underflow(e1, e2, false);
  }

  _z3Expressions.push(finalExpr);
}

void ExpToZ3Visitor::visit(expression::LogicMul &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = e1 * e2;

  if (o.getType().first == VarType::SLogic) {
    // Add over/underflow conditions
    _overflowCond = _overflowCond && z3::bvmul_no_overflow(e1, e2, true);
    _overflowCond = _overflowCond && z3::bvmul_no_underflow(e1, e2);
  } else {
    // Add over/underflow conditions
    _overflowCond = _overflowCond && z3::bvmul_no_overflow(e1, e2, false);
    _overflowCond = _overflowCond && z3::bvmul_no_underflow(e1, e2);
  }

  _z3Expressions.push(finalExpr);
}

void ExpToZ3Visitor::visit(expression::LogicDiv &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  // add the condition before extending the size
  _overflowCond = _overflowCond && (e2 != _c.bv_val(0, oe2->getType().second));

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = e1 / e2;

  // Add over/underflow conditions
  if (o.getType().first == VarType::SLogic) {
    _overflowCond = _overflowCond && z3::bvsdiv_no_overflow(e1, e2);
  }

  _z3Expressions.push(finalExpr);
}
void ExpToZ3Visitor::visit(expression::LogicEq &o) {
  assert(o.getItems().size() == 2);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC_APPLY_CSTANDARD(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = (e1 == e2);

  _z3Expressions.push(finalExpr);
}

void ExpToZ3Visitor::visit(expression::LogicNeq &o) {
  assert(o.getItems().size() == 2);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC_APPLY_CSTANDARD(o, oe1, oe2, e1, e2)

  _z3Expressions.push(e1 != e2);
}

void ExpToZ3Visitor::visit(expression::LogicGreater &o) {
  assert(o.getItems().size() == 2);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC_APPLY_CSTANDARD(o, oe1, oe2, e1, e2)

  if (conversionResult.first == VarType::SLogic) {
    _z3Expressions.push(e1 > e2);
  } else {
    _z3Expressions.push(z3::ugt(e1, e2));
  }
}

void ExpToZ3Visitor::visit(expression::LogicGreaterEq &o) {
  assert(o.getItems().size() == 2);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_LOGIC_APPLY_CSTANDARD(o, oe1, oe2, e1, e2)

  if (conversionResult.first == VarType::SLogic) {
    _z3Expressions.push(e1 >= e2);
  } else {
    _z3Expressions.push(z3::uge(e1, e2));
  }
}

void ExpToZ3Visitor::visit(expression::LogicLess &o) {
  assert(o.getItems().size() == 2);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_LOGIC_APPLY_CSTANDARD(o, oe1, oe2, e1, e2)

  if (conversionResult.first == VarType::SLogic) {
    _z3Expressions.push(e1 < e2);
  } else {
    _z3Expressions.push(z3::ult(e1, e2));
  }
}

void ExpToZ3Visitor::visit(expression::LogicLessEq &o) {
  assert(o.getItems().size() == 2);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  EXTEND_LOGIC_APPLY_CSTANDARD(o, oe1, oe2, e1, e2)

  if (conversionResult.first == VarType::SLogic) {
    _z3Expressions.push(e1 <= e2);
  } else {
    _z3Expressions.push(z3::ule(e1, e2));
  }
}

void ExpToZ3Visitor::visit(expression::LogicToBool &o) {
  o.getItem().acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();
  _z3Expressions.push(e1 > 0);
}

void ExpToZ3Visitor::visit(expression::LogicBAnd &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = e1 & e2;

  _z3Expressions.push(finalExpr);
}
void ExpToZ3Visitor::visit(expression::LogicLShift &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = z3::shl(e1, e2);

  _z3Expressions.push(finalExpr);
}
void ExpToZ3Visitor::visit(expression::LogicRShift &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = z3::ashr(e1, e2);

  _z3Expressions.push(finalExpr);
}
void ExpToZ3Visitor::visit(expression::LogicBOr &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = e1 | e2;

  _z3Expressions.push(finalExpr);
}

void ExpToZ3Visitor::visit(expression::LogicBXor &o) {
  assert(o.getItems().size() > 1);

  auto &oe1 = o.getItems()[0];
  auto &oe2 = o.getItems()[1];

  oe1->acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();

  oe2->acceptVisitor(*this);
  z3::expr e2 = _z3Expressions.top();
  _z3Expressions.pop();

  /*Extend the size of the operands to make all operands of the same size (if
   * needed)*/
  EXTEND_LOGIC(o, oe1, oe2, e1, e2)

  z3::expr finalExpr = e1 ^ e2;

  _z3Expressions.push(finalExpr);
}

void ExpToZ3Visitor::visit(expression::LogicToNumeric &o) {
  auto &oe = o.getItem();
  oe.acceptVisitor(*this);
  z3::expr e1 = _z3Expressions.top();
  _z3Expressions.pop();
  Z3_ast floatExpr;
  z3::expr rm(_c, _c.fpa_rounding_mode());
  z3::sort srt = _c.fpa_sort(8, 24);
  if (oe.getType().first == VarType::SLogic) {
    floatExpr = Z3_mk_fpa_to_fp_signed(_c, rm, e1, srt);
  } else {
    floatExpr = Z3_mk_fpa_to_fp_unsigned(_c, rm, e1, srt);
  }
  _z3Expressions.push(z3::expr(_c, floatExpr));
}

} // namespace expression
