#include "visitors/ExpToZ3Visitor.hh"

#include <algorithm>

#include "Logic.hh"
#include "expUtils/ExpType.hh"
#include "expUtils/implicitConversion.hh"
#include "formula/expression/Ternary.hh"
#include "message.hh"
#include "visitors/PrinterVisitor.hh"

namespace expression {

namespace {
enum { EQ, NEQ, GT, GE, LT, LE };
enum { AND, OR, XOR };
enum { SUM, SUB, MUL };
} // namespace

ExpToZ3Visitor::ExpToZ3Visitor(z3::context &ctx, unsigned U)
    : _ctx(ctx), _U(U) {}

z3::expr ExpToZ3Visitor::encode(const PropositionPtr &p) {
  p->acceptVisitor(*this);
  return popBool();
}

std::map<std::string, std::string>
ExpToZ3Visitor::variableValues(const z3::model &m) {
  std::map<std::string, std::string> values;
  auto bitsOf = [&](const z3::expr &e) {
    // bit i of the model value, as 0/1
    z3::expr val = m.eval(e, true);
    std::string bin;
    for (int i = (int)_U - 1; i >= 0; i--) {
      z3::expr b = m.eval(val.extract(i, i), true);
      bin += b.get_numeral_uint() ? '1' : '0';
    }
    return bin; // MSB first, _U bits
  };
  for (const auto &[key, t] : _logicAtoms) {
    if (key.rfind("v:", 0) != 0) {
      continue;
    }
    std::string v = bitsOf(t.v), x = bitsOf(t.x), z = bitsOf(t.z);
    std::string four;
    for (unsigned i = _U - t.w; i < _U; i++) {
      four += x[i] == '1' ? 'x' : z[i] == '1' ? 'z' : v[i];
    }
    values[key.substr(2)] = four;
  }
  for (const auto &[key, b] : _boolAtoms) {
    if (key.rfind("v:", 0) == 0) {
      values[key.substr(2)] = m.eval(b, true).is_true() ? "1" : "0";
    }
  }
  for (const auto &[key, i] : _intAtoms) {
    if (key.rfind("v:", 0) == 0) {
      values[key.substr(2)] = m.eval(i, true).get_decimal_string(0);
    }
  }
  return values;
}

// ---------------------------------------------------------------- helpers
void ExpToZ3Visitor::see(unsigned width) {
  _maxWidth = std::max(_maxWidth, width);
}

z3::expr ExpToZ3Visitor::mask(unsigned width) {
  if (width == 0) {
    return zero();
  }
  if (width >= _U) {
    return ~zero();
  }
  return z3::lshr(~zero(), bv(_U - width));
}

z3::expr ExpToZ3Visitor::ext(const z3::expr &v, unsigned R, bool sgn) {
  if (!sgn) {
    return v & mask(R);
  }
  if (R >= _U) {
    return v;
  }
  return z3::ashr(z3::shl(v, bv(_U - R)), bv(_U - R));
}

z3::expr ExpToZ3Visitor::anyXZ(const LTerm &t) {
  return (t.x | t.z) != zero();
}

z3::expr ExpToZ3Visitor::popBool() {
  messageErrorIf(_bools.empty(), "Z3 encoding: empty boolean stack");
  z3::expr e = _bools.back();
  _bools.pop_back();
  return e;
}
z3::expr ExpToZ3Visitor::popInt() {
  messageErrorIf(_ints.empty(), "Z3 encoding: empty int stack");
  z3::expr e = _ints.back();
  _ints.pop_back();
  return e;
}
z3::expr ExpToZ3Visitor::popFloat() {
  messageErrorIf(_floats.empty(), "Z3 encoding: empty float stack");
  z3::expr e = _floats.back();
  _floats.pop_back();
  return e;
}
ExpToZ3Visitor::LTerm ExpToZ3Visitor::popLogic() {
  messageErrorIf(_logics.empty(), "Z3 encoding: empty logic stack");
  LTerm t = _logics.back();
  _logics.pop_back();
  return t;
}

template <typename Node> std::string ExpToZ3Visitor::text(Node &o) {
  PrinterVisitor pv(Language::SpotLTL, false, PrintMode::ShowAll);
  o.acceptVisitor(pv);
  return pv.get();
}

void ExpToZ3Visitor::opaqueBool(const std::string &key) {
  _usedOpaque = true;
  auto it = _boolAtoms.find("o:" + key);
  if (it == _boolAtoms.end()) {
    it = _boolAtoms
             .emplace("o:" + key, _ctx.bool_const(("ob" + std::to_string(
                                                             _boolAtoms.size()))
                                                      .c_str()))
             .first;
  }
  _bools.push_back(it->second);
}
void ExpToZ3Visitor::opaqueInt(const std::string &key) {
  _usedOpaque = true;
  auto it = _intAtoms.find("o:" + key);
  if (it == _intAtoms.end()) {
    it = _intAtoms
             .emplace("o:" + key,
                      _ctx.bv_const(
                          ("oi" + std::to_string(_intAtoms.size())).c_str(), 64))
             .first;
  }
  _ints.push_back(it->second);
}
void ExpToZ3Visitor::opaqueFloat(const std::string &key) {
  _usedOpaque = true;
  auto it = _floatAtoms.find("o:" + key);
  if (it == _floatAtoms.end()) {
    it = _floatAtoms
             .emplace("o:" + key,
                      _ctx.constant(
                          ("of" + std::to_string(_floatAtoms.size())).c_str(),
                          _ctx.fpa_sort(11, 53)))
             .first;
  }
  _floats.push_back(it->second);
}
void ExpToZ3Visitor::opaqueLogic(const std::string &key, unsigned w,
                                 bool sgn) {
  _usedOpaque = true;
  see(w);
  auto it = _logicAtoms.find("o:" + key);
  if (it == _logicAtoms.end()) {
    std::string n = "ol" + std::to_string(_logicAtoms.size());
    // unconstrained raw value and masks: covers every value HARM can produce, a collapsed
    // (1-bit x) arithmetic result included
    LTerm t{_ctx.bv_const((n + "v").c_str(), _U),
            _ctx.bv_const((n + "x").c_str(), _U),
            _ctx.bv_const((n + "z").c_str(), _U), w, sgn, true};
    it = _logicAtoms.emplace("o:" + key, t).first;
  }
  _logics.push_back(it->second);
}

ExpToZ3Visitor::LTerm ExpToZ3Visitor::extendTo(const LTerm &t,
                                               unsigned width, bool sgn) {
  z3::expr m = mask(t.w);
  z3::expr x = t.x & m;
  z3::expr z = t.z & m;
  z3::expr i = t.v & m & ~(x | z);
  if (sgn && t.w > 0 && width > t.w) {
    z3::expr high = mask(width) & ~m;
    z3::expr msb = z3::shl(bv(1), bv(t.w - 1));
    z3::expr xMsb = (x & msb) != zero();
    z3::expr zMsb = (z & msb) != zero();
    z3::expr iMsb = (i & msb) != zero();
    z3::expr nx = z3::ite(xMsb, x | high, x);
    z3::expr nz = z3::ite(!xMsb && zMsb, z | high, z);
    z3::expr ni = z3::ite(!xMsb && !zMsb && iMsb, i | high, i);
    x = nx;
    z = nz;
    i = ni;
  }
  return LTerm{i, x, z, width, t.sgn, false};
}

ExpToZ3Visitor::LTerm ExpToZ3Visitor::operandAt(const LTerm &t, unsigned R,
                                                bool resSgn) {
  // the bits of the operand's own width; sign extension by shift left, arithmetic shift right
  // (a cheap bit-vector operation, no ite): applied to the value, x and z masks alike, it
  // repeats an x or z sign bit as x or z, and a known 1 as 1 (value bits are 0 under x/z)
  z3::expr m = mask(t.w);
  z3::expr x = t.x & m, z = t.z & m;
  z3::expr v = t.v & m & ~(x | z);
  if (resSgn && t.sgn && R > t.w && t.w > 0 && t.w < _U) {
    auto sx = [&](const z3::expr &e) {
      return z3::ashr(z3::shl(e, bv(_U - t.w)), bv(_U - t.w));
    };
    v = sx(v);
    x = sx(x);
    z = sx(z);
  }
  z3::expr r = mask(R);
  return LTerm{v & r, x & r, z & r, R, resSgn, false};
}

z3::expr ExpToZ3Visitor::intNorm(const z3::expr &v,
                                 const std::pair<ExpType, size_t> &t) {
  unsigned w = (unsigned)std::min<size_t>(t.second, 64);
  if (w >= 64) {
    return v;
  }
  z3::expr low = v.extract(w - 1, 0);
  return isSigned(t.first) ? z3::sext(low, 64 - w) : z3::zext(low, 64 - w);
}

z3::expr ExpToZ3Visitor::intAs(const z3::expr &v,
                               const std::pair<ExpType, size_t> &own,
                               const std::pair<ExpType, size_t> &res) {
  unsigned w = (unsigned)std::min<size_t>(own.second, 64);
  if (w >= 64) {
    return v;
  }
  z3::expr low = v.extract(w - 1, 0);
  return isSigned(res.first) && isSigned(own.first) ? z3::sext(low, 64 - w)
                                                     : z3::zext(low, 64 - w);
}

void ExpToZ3Visitor::logicCompare(const std::pair<ExpType, size_t> &a,
                                  const std::pair<ExpType, size_t> &b,
                                  int op) {
  LTerm r = popLogic();
  LTerm l = popLogic();
  auto res = applyCStandardConversion(a, b);
  unsigned R = res.second;
  bool sgn = isSigned(res.first);
  see(R);
  l = operandAt(l, R, sgn);
  r = operandAt(r, R, sgn);
  z3::expr x = ext(l.v, R, sgn), y = ext(r.v, R, sgn);
  z3::expr c = _ctx.bool_val(true);
  switch (op) {
  case EQ:
    c = x == y;
    break;
  case NEQ:
    c = x != y;
    break;
  case GT:
    c = sgn ? x > y : z3::ugt(x, y);
    break;
  case GE:
    c = sgn ? x >= y : z3::uge(x, y);
    break;
  case LT:
    c = sgn ? x < y : z3::ult(x, y);
    break;
  case LE:
    c = sgn ? x <= y : z3::ule(x, y);
    break;
  }
  // HARM: a comparison with an x or z bit in an operand is false (D-011)
  _bools.push_back(!anyXZ(l) && !anyXZ(r) && c);
}

void ExpToZ3Visitor::logicBitwise(const std::pair<ExpType, size_t> &type,
                                  int op) {
  LTerm r = popLogic();
  LTerm l = popLogic();
  unsigned R = type.second;
  bool sgn = isSigned(type.first);
  see(R);
  l = operandAt(l, R, sgn);
  r = operandAt(r, R, sgn);
  z3::expr op1 = l.v, op2 = r.v;
  z3::expr lxz = l.x | l.z, rxz = r.x | r.z;
  z3::expr v = zero(), x = zero();
  if (op == AND) {
    z3::expr toZero = (lxz & ~(op2 | rxz)) | (rxz & ~(op1 | lxz));
    v = op1 & op2 & ~toZero;
    x = (lxz | rxz) & ~toZero;
  } else if (op == OR) {
    z3::expr toOne = (lxz & op2) | (rxz & op1);
    v = op1 | op2 | toOne;
    x = (lxz | rxz) & ~toOne;
  } else {
    v = (op1 ^ op2) & ~(lxz | rxz);
    x = lxz | rxz;
  }
  _logics.push_back(LTerm{v, x, zero(), R, sgn, false});
}

void ExpToZ3Visitor::logicArith(const std::pair<ExpType, size_t> &type,
                                int op) {
  LTerm r = popLogic();
  LTerm l = popLogic();
  unsigned R = type.second;
  bool sgn = isSigned(type.first);
  see(R);
  l = operandAt(l, R, sgn);
  r = operandAt(r, R, sgn);
  z3::expr op1 = l.v, op2 = r.v;
  z3::expr val = (op == SUM ? op1 + op2 : op == SUB ? op1 - op2 : op1 * op2) & mask(R);
  // D-035: an x or z operand bit makes the whole result x (IEEE 1800-2017 11.4.2)
  z3::expr unknown = anyXZ(l) || anyXZ(r);
  _logics.push_back(LTerm{z3::ite(unknown, zero(), val),
                          z3::ite(unknown, mask(R), zero()), zero(), R, sgn,
                          false});
}

void ExpToZ3Visitor::intCompare(const std::pair<ExpType, size_t> &a,
                                const std::pair<ExpType, size_t> &b,
                                int op) {
  auto common = applyCStandardConversion(a, b);
  z3::expr y = intAs(popInt(), b, common);
  z3::expr x = intAs(popInt(), a, common);
  bool sgn = common.first == ExpType::SInt;
  z3::expr c = _ctx.bool_val(true);
  switch (op) {
  case EQ:
    c = x == y;
    break;
  case NEQ:
    c = x != y;
    break;
  case GT:
    c = sgn ? x > y : z3::ugt(x, y);
    break;
  case GE:
    c = sgn ? x >= y : z3::uge(x, y);
    break;
  case LT:
    c = sgn ? x < y : z3::ult(x, y);
    break;
  case LE:
    c = sgn ? x <= y : z3::ule(x, y);
    break;
  }
  _bools.push_back(c);
}

// ---------------------------------------------------------------- proposition
void ExpToZ3Visitor::visit(BooleanConstant &o) {
  _bools.push_back(_ctx.bool_val(o.evaluate(0)));
}
void ExpToZ3Visitor::visit(BooleanVariable &o) {
  auto it = _boolAtoms.find("v:" + o.getName());
  if (it == _boolAtoms.end()) {
    it = _boolAtoms
             .emplace("v:" + o.getName(),
                      _ctx.bool_const(("b_" + o.getName()).c_str()))
             .first;
  }
  _bools.push_back(it->second);
}
void ExpToZ3Visitor::visit(PropositionAnd &o) {
  z3::expr e = _ctx.bool_val(true);
  for (auto &i : o.getItems()) {
    i->acceptVisitor(*this);
    e = e && popBool();
  }
  _bools.push_back(e);
}
void ExpToZ3Visitor::visit(PropositionOr &o) {
  z3::expr e = _ctx.bool_val(false);
  for (auto &i : o.getItems()) {
    i->acceptVisitor(*this);
    e = e || popBool();
  }
  _bools.push_back(e);
}
void ExpToZ3Visitor::visit(PropositionXor &o) {
  z3::expr e = _ctx.bool_val(false);
  for (auto &i : o.getItems()) {
    i->acceptVisitor(*this);
    e = e != popBool();
  }
  _bools.push_back(e);
}
void ExpToZ3Visitor::visit(PropositionEq &o) {
  o.getItems()[0]->acceptVisitor(*this);
  o.getItems()[1]->acceptVisitor(*this);
  z3::expr b = popBool(), a = popBool();
  _bools.push_back(a == b);
}
void ExpToZ3Visitor::visit(PropositionNeq &o) {
  o.getItems()[0]->acceptVisitor(*this);
  o.getItems()[1]->acceptVisitor(*this);
  z3::expr b = popBool(), a = popBool();
  _bools.push_back(a != b);
}
void ExpToZ3Visitor::visit(PropositionNot &o) {
  o.getItems()[0]->acceptVisitor(*this);
  _bools.push_back(!popBool());
}
void ExpToZ3Visitor::visit(PropositionTernary &o) {
  o.getCondition()->acceptVisitor(*this);
  o.getWhenTrue()->acceptVisitor(*this);
  o.getWhenFalse()->acceptVisitor(*this);
  z3::expr f = popBool(), t = popBool(), c = popBool();
  _bools.push_back(z3::ite(c, t, f));
}

// temporal functions: opaque atoms (the same text gives the same atom)
#define OPAQUE_BOOL(NODE)                                            \
  void ExpToZ3Visitor::visit(NODE &o) { opaqueBool(text(o)); }
#define OPAQUE_INT(NODE)                                             \
  void ExpToZ3Visitor::visit(NODE &o) { opaqueInt(text(o)); }
#define OPAQUE_FLOAT(NODE)                                           \
  void ExpToZ3Visitor::visit(NODE &o) { opaqueFloat(text(o)); }
#define OPAQUE_LOGIC(NODE)                                           \
  void ExpToZ3Visitor::visit(NODE &o) {                              \
    opaqueLogic(text(o), o.getType().second,                         \
                isSigned(o.getType().first));                        \
  }
OPAQUE_BOOL(PropositionStable)
OPAQUE_BOOL(PropositionRose)
OPAQUE_BOOL(PropositionFell)
OPAQUE_BOOL(PropositionPast)

// ---------------------------------------------------------------- float (IEEE double)
void ExpToZ3Visitor::visit(FloatConstant &o) {
  _floats.push_back(_ctx.fpa_val((double)o.evaluate(0)));
}
void ExpToZ3Visitor::visit(FloatVariable &o) {
  auto it = _floatAtoms.find("v:" + o.getName());
  if (it == _floatAtoms.end()) {
    it = _floatAtoms
             .emplace("v:" + o.getName(),
                      _ctx.constant(("f_" + o.getName()).c_str(),
                                    _ctx.fpa_sort(11, 53)))
             .first;
  }
  _floats.push_back(it->second);
}
#define FLOAT_ARITH(NODE, FUN)                                       \
  void ExpToZ3Visitor::visit(NODE &o) {                              \
    o.getItems()[0]->acceptVisitor(*this);                           \
    o.getItems()[1]->acceptVisitor(*this);                           \
    z3::expr b = popFloat(), a = popFloat();                         \
    z3::expr rm = _ctx.fpa_rounding_mode();                          \
    _floats.push_back(z3::expr(_ctx, FUN(_ctx, rm, a, b)));          \
  }
FLOAT_ARITH(FloatSum, Z3_mk_fpa_add)
FLOAT_ARITH(FloatSub, Z3_mk_fpa_sub)
FLOAT_ARITH(FloatMul, Z3_mk_fpa_mul)
FLOAT_ARITH(FloatDiv, Z3_mk_fpa_div)
#define FLOAT_CMP(NODE, FUN, NEG)                                    \
  void ExpToZ3Visitor::visit(NODE &o) {                              \
    o.getItems()[0]->acceptVisitor(*this);                           \
    o.getItems()[1]->acceptVisitor(*this);                           \
    z3::expr b = popFloat(), a = popFloat();                         \
    z3::expr c(_ctx, FUN(_ctx, a, b));                               \
    _bools.push_back(NEG ? !c : c);                                  \
  }
FLOAT_CMP(FloatEq, Z3_mk_fpa_eq, false)
FLOAT_CMP(FloatNeq, Z3_mk_fpa_eq, true)
FLOAT_CMP(FloatGreater, Z3_mk_fpa_gt, false)
FLOAT_CMP(FloatGreaterEq, Z3_mk_fpa_geq, false)
FLOAT_CMP(FloatLess, Z3_mk_fpa_lt, false)
FLOAT_CMP(FloatLessEq, Z3_mk_fpa_leq, false)
void ExpToZ3Visitor::visit(FloatToBool &o) {
  // HARM: value != 0 (NaN is true, -0 is false)
  o.getItem()->acceptVisitor(*this);
  z3::expr f = popFloat();
  _bools.push_back(!z3::expr(_ctx, Z3_mk_fpa_eq(_ctx, f, _ctx.fpa_val(0.0))));
}
OPAQUE_INT(FloatToInt)
OPAQUE_LOGIC(FloatToLogic)
void ExpToZ3Visitor::visit(FloatSetMembership &o) {
  z3::expr e = _ctx.bool_val(false);
  for (auto &c : o.getConditions()) {
    c->acceptVisitor(*this);
    e = e || popBool();
  }
  _bools.push_back(e);
}
OPAQUE_BOOL(FloatStable)
OPAQUE_FLOAT(FloatPast)
void ExpToZ3Visitor::visit(FloatTernary &o) {
  o.getCondition()->acceptVisitor(*this);
  o.getWhenTrue()->acceptVisitor(*this);
  o.getWhenFalse()->acceptVisitor(*this);
  z3::expr f = popFloat(), t = popFloat(), c = popBool();
  _floats.push_back(z3::ite(c, t, f));
}

// ---------------------------------------------------------------- int (exact for 64-bit types)
// D-035: an integer of any width up to 64 is a 64-bit term holding its value, extended by its own
// sign (intNorm); operations extend their operands as SystemVerilog does (intAs)
void ExpToZ3Visitor::visit(IntConstant &o) {
  _ints.push_back(intNorm(_ctx.bv_val((uint64_t)o.evaluate(0), 64), o.getType()));
}
void ExpToZ3Visitor::visit(IntVariable &o) {
  auto it = _intAtoms.find("v:" + o.getName());
  if (it == _intAtoms.end()) {
    it = _intAtoms
             .emplace("v:" + o.getName(),
                      _ctx.bv_const(("i_" + o.getName()).c_str(), 64))
             .first;
  }
  _ints.push_back(intNorm(it->second, o.getType()));
}
#define INT_BINARY(NODE, OP)                                         \
  void ExpToZ3Visitor::visit(NODE &o) {                              \
    auto t = o.getType();                                            \
    o.getItems()[0]->acceptVisitor(*this);                           \
    o.getItems()[1]->acceptVisitor(*this);                           \
    z3::expr b = intAs(popInt(), o.getItems()[1]->getType(), t);     \
    z3::expr a = intAs(popInt(), o.getItems()[0]->getType(), t);     \
    _ints.push_back(intNorm(a OP b, t));                             \
  }
INT_BINARY(IntSum, +)
INT_BINARY(IntSub, -)
INT_BINARY(IntMul, *)
INT_BINARY(IntBAnd, &)
INT_BINARY(IntBOr, |)
INT_BINARY(IntBXor, ^)
void ExpToZ3Visitor::visit(IntNeg &o) {
  auto t = o.getType();
  o.getItems()[0]->acceptVisitor(*this);
  _ints.push_back(intNorm(-intAs(popInt(), o.getItems()[0]->getType(), t), t));
}
OPAQUE_LOGIC(LogicNeg)
OPAQUE_FLOAT(FloatNeg)
void ExpToZ3Visitor::visit(IntNot &o) {
  auto t = o.getType();
  o.getItems()[0]->acceptVisitor(*this);
  _ints.push_back(intNorm(~intAs(popInt(), o.getItems()[0]->getType(), t), t));
}
OPAQUE_INT(IntDiv) // by zero, Z3 gives all ones or ±1; HARM gives 0 (D-035)
#define INT_CMP(NODE, OP)                                            \
  void ExpToZ3Visitor::visit(NODE &o) {                              \
    o.getItems()[0]->acceptVisitor(*this);                           \
    o.getItems()[1]->acceptVisitor(*this);                           \
    intCompare(o.getItems()[0]->getType(), o.getItems()[1]->getType(), \
               OP);                                                  \
  }
INT_CMP(IntEq, EQ)
INT_CMP(IntNeq, NEQ)
INT_CMP(IntGreater, GT)
INT_CMP(IntGreaterEq, GE)
INT_CMP(IntLess, LT)
INT_CMP(IntLessEq, LE)
OPAQUE_INT(IntBitSelector)
void ExpToZ3Visitor::visit(IntToBool &o) {
  o.getItem()->acceptVisitor(*this);
  _bools.push_back(popInt() != _ctx.bv_val(0, 64));
}
OPAQUE_FLOAT(IntToFloat)
void ExpToZ3Visitor::visit(IntToLogic &o) {
  // D-035: the integer extended from its own width to the cast's, sign-extended when both are
  // signed (TypeCast.cc)
  see(64);
  see(o.getType().second);
  o.getItem()->acceptVisitor(*this);
  bool sx = isSigned(o.getType().first) && isSigned(o.getItem()->getType().first);
  z3::expr i = intAs(popInt(), o.getItem()->getType(), o.getType());
  z3::expr v = _U > 64 ? (sx ? z3::sext(i, _U - 64) : z3::zext(i, _U - 64))
                       : i.extract(_U - 1, 0);
  v = v & mask(o.getType().second);
  _logics.push_back(LTerm{v, zero(), zero(), (unsigned)o.getType().second,
                          isSigned(o.getType().first), false});
}
void ExpToZ3Visitor::visit(BoolToLogic &o) {
  // D-032: the bool as a 1-bit unsigned value, never x or z
  see(1);
  o.getItem()->acceptVisitor(*this);
  z3::expr c = popBool();
  _logics.push_back(LTerm{z3::ite(c, _ctx.bv_val(1, _U), zero()), zero(), zero(),
                          1, false, false});
}
OPAQUE_INT(IntLShift)
OPAQUE_INT(IntRShift)
OPAQUE_INT(IntARShift)
OPAQUE_LOGIC(LogicARShift)
void ExpToZ3Visitor::visit(IntSetMembership &o) {
  z3::expr e = _ctx.bool_val(false);
  for (auto &c : o.getConditions()) {
    c->acceptVisitor(*this);
    e = e || popBool();
  }
  _bools.push_back(e);
}
OPAQUE_BOOL(IntStable)
OPAQUE_BOOL(IntRose)
OPAQUE_BOOL(IntFell)
OPAQUE_INT(IntPast)
void ExpToZ3Visitor::visit(IntTernary &o) {
  auto ty = o.getType();
  o.getCondition()->acceptVisitor(*this);
  o.getWhenTrue()->acceptVisitor(*this);
  o.getWhenFalse()->acceptVisitor(*this);
  z3::expr f = intAs(popInt(), o.getWhenFalse()->getType(), ty);
  z3::expr t = intAs(popInt(), o.getWhenTrue()->getType(), ty);
  z3::expr c = popBool();
  _ints.push_back(intNorm(z3::ite(c, t, f), ty));
}

// ---------------------------------------------------------------- logic (4-valued)
void ExpToZ3Visitor::visit(LogicConstant &o) {
  Logic l = o.evaluate(0);
  see(l._size);
  ULogic m = (ULogic(1) << _U) - 1; // _U <= 511
  auto val = [&](const ULogic &u) {
    return _ctx.bv_val((u & m).str().c_str(), _U);
  };
  _logics.push_back(LTerm{val(l._int), val(l._x), val(l._z),
                          (unsigned)o.getType().second,
                          isSigned(o.getType().first), false});
}
void ExpToZ3Visitor::visit(LogicVariable &o) {
  unsigned w = o.getType().second;
  see(w);
  auto it = _logicAtoms.find("v:" + o.getName());
  if (it == _logicAtoms.end()) {
    std::string n = "l_" + o.getName();
    LTerm t{_ctx.bv_const((n + "_v").c_str(), _U),
            _ctx.bv_const((n + "_x").c_str(), _U),
            _ctx.bv_const((n + "_z").c_str(), _U), w,
            isSigned(o.getType().first), false};
    // as Logic stores trace values: no bits above the width, a bit is 0/1, x or z
    z3::expr above = ~mask(w);
    _assumptions.push_back((t.v & above) == zero());
    _assumptions.push_back((t.x & above) == zero());
    _assumptions.push_back((t.z & above) == zero());
    _assumptions.push_back((t.x & t.z) == zero());
    _assumptions.push_back((t.v & (t.x | t.z)) == zero());
    it = _logicAtoms.emplace("v:" + o.getName(), t).first;
  }
  _logics.push_back(it->second);
}
#define LOGIC_ARITH(NODE, OP)                                        \
  void ExpToZ3Visitor::visit(NODE &o) {                              \
    o.getItems()[0]->acceptVisitor(*this);                           \
    o.getItems()[1]->acceptVisitor(*this);                           \
    logicArith(o.getType(), OP);                                     \
  }
LOGIC_ARITH(LogicSum, SUM)
LOGIC_ARITH(LogicSub, SUB)
LOGIC_ARITH(LogicMul, MUL)
OPAQUE_LOGIC(LogicDiv) // by zero, Z3 gives all ones or ±1; HARM gives x (D-035)
#define LOGIC_BITWISE(NODE, OP)                                      \
  void ExpToZ3Visitor::visit(NODE &o) {                              \
    o.getItems()[0]->acceptVisitor(*this);                           \
    o.getItems()[1]->acceptVisitor(*this);                           \
    logicBitwise(o.getType(), OP);                                   \
  }
LOGIC_BITWISE(LogicBAnd, AND)
LOGIC_BITWISE(LogicBOr, OR)
LOGIC_BITWISE(LogicBXor, XOR)
void ExpToZ3Visitor::visit(LogicNot &o) {
  o.getItems()[0]->acceptVisitor(*this);
  LTerm t = popLogic();
  unsigned R = o.getType().second;
  bool sgn = isSigned(o.getType().first);
  see(R);
  // D-035: ~ of the operand extended to width R; an x or z bit stays x, with value bit 0
  t = operandAt(t, R, sgn);
  z3::expr xz = t.x | t.z;
  _logics.push_back(LTerm{~t.v & mask(R) & ~xz, xz, zero(), R, sgn, false});
}
#define LOGIC_CMP(NODE, OP)                                          \
  void ExpToZ3Visitor::visit(NODE &o) {                              \
    o.getItems()[0]->acceptVisitor(*this);                           \
    o.getItems()[1]->acceptVisitor(*this);                           \
    logicCompare(o.getItems()[0]->getType(),                         \
                 o.getItems()[1]->getType(), OP);                    \
  }
LOGIC_CMP(LogicEq, EQ)
LOGIC_CMP(LogicNeq, NEQ)
LOGIC_CMP(LogicGreater, GT)
LOGIC_CMP(LogicGreaterEq, GE)
LOGIC_CMP(LogicLess, LT)
LOGIC_CMP(LogicLessEq, LE)
void ExpToZ3Visitor::visit(LogicBitSelector &o) {
  o.getItem()->acceptVisitor(*this);
  LTerm t = popLogic();
  unsigned lo = o.getLowerBound(), len = o.getUpperBound() - lo + 1;
  // HARM: the raw bits [lower, upper] of the value and of the masks
  auto sel = [&](const z3::expr &e) { return z3::lshr(e, bv(lo)) & mask(len); };
  _logics.push_back(LTerm{sel(t.v), sel(t.x), sel(t.z), len,
                          isSigned(o.getType().first), false});
}
void ExpToZ3Visitor::visit(LogicToBool &o) {
  o.getItem()->acceptVisitor(*this);
  LTerm t = popLogic();
  // HARM: the value bits (x/z ignored, as stored) within the width are not all 0. A collapsed
  // arithmetic result has value 0, so its run-time width does not matter here.
  _bools.push_back((t.v & mask(t.w)) != zero());
}
OPAQUE_FLOAT(LogicToFloat)
OPAQUE_INT(LogicToInt)
OPAQUE_LOGIC(LogicLShift) // out-of-range shift amounts abort HARM
OPAQUE_LOGIC(LogicRShift)
void ExpToZ3Visitor::visit(LogicSetMembership &o) {
  z3::expr e = _ctx.bool_val(false);
  for (auto &c : o.getConditions()) {
    c->acceptVisitor(*this);
    e = e || popBool();
  }
  _bools.push_back(e);
}
OPAQUE_BOOL(LogicStable)
OPAQUE_BOOL(LogicRose)
OPAQUE_BOOL(LogicFell)
OPAQUE_LOGIC(LogicPast)

void ExpToZ3Visitor::visit(LogicCaseEq &o) {
  o.getItems()[0]->acceptVisitor(*this);
  o.getItems()[1]->acceptVisitor(*this);
  LTerm r = popLogic(), l = popLogic();
  if (l.mayCollapse || r.mayCollapse) {
    // === uses the run-time width of its operands
    opaqueBool(text(o));
    return;
  }
  unsigned W = std::max(l.w, r.w);
  bool sgn = l.sgn && r.sgn;
  LTerm a = extendTo(l, W, sgn), b = extendTo(r, W, sgn);
  _bools.push_back(a.v == b.v && a.x == b.x && a.z == b.z);
}
void ExpToZ3Visitor::visit(LogicCaseNeq &o) {
  o.getItems()[0]->acceptVisitor(*this);
  o.getItems()[1]->acceptVisitor(*this);
  LTerm r = popLogic(), l = popLogic();
  if (l.mayCollapse || r.mayCollapse) {
    opaqueBool(text(o));
    return;
  }
  unsigned W = std::max(l.w, r.w);
  bool sgn = l.sgn && r.sgn;
  LTerm a = extendTo(l, W, sgn), b = extendTo(r, W, sgn);
  _bools.push_back(!(a.v == b.v && a.x == b.x && a.z == b.z));
}
void ExpToZ3Visitor::visit(LogicConcat &o) {
  std::vector<LTerm> items;
  for (auto &i : o.getItems()) {
    i->acceptVisitor(*this);
    items.push_back(popLogic());
  }
  bool collapse = std::any_of(items.begin(), items.end(),
                              [](const LTerm &t) { return t.mayCollapse; });
  if (collapse) {
    // the positions of the items depend on their run-time widths
    opaqueLogic(text(o), o.getType().second, false);
    return;
  }
  see(o.getType().second);
  z3::expr v = zero(), x = zero(), z = zero();
  for (auto &t : items) {
    LTerm e = extendTo(t, t.w, false);
    v = z3::shl(v, bv(t.w)) | e.v;
    x = z3::shl(x, bv(t.w)) | e.x;
    z = z3::shl(z, bv(t.w)) | e.z;
  }
  _logics.push_back(
      LTerm{v, x, z, (unsigned)o.getType().second, false, false});
}
void ExpToZ3Visitor::visit(LogicTernary &o) {
  o.getCondition()->acceptVisitor(*this);
  o.getWhenTrue()->acceptVisitor(*this);
  o.getWhenFalse()->acceptVisitor(*this);
  LTerm f = popLogic(), t = popLogic();
  z3::expr c = popBool();
  unsigned R = o.getType().second;
  bool sgn = isSigned(o.getType().first);
  see(R);
  if (t.mayCollapse || f.mayCollapse) {
    opaqueLogic(text(o), R, sgn);
    return;
  }
  // HARM: a branch narrower or wider than the result is resized (Ternary<Logic>)
  auto resized = [&](const LTerm &b) {
    if (b.w == R) {
      return b;
    }
    if (R < b.w) {
      return LTerm{b.v & mask(R), b.x & mask(R), b.z & mask(R), R, sgn, false};
    }
    return extendTo(b, R, sgn);
  };
  LTerm a = resized(t), b = resized(f);
  _logics.push_back(LTerm{z3::ite(c, a.v, b.v), z3::ite(c, a.x, b.x),
                          z3::ite(c, a.z, b.z), R, sgn, false});
}

// ---------------------------------------------------------------- strings: opaque comparisons
OPAQUE_BOOL(StringEq)
OPAQUE_BOOL(StringNeq)
OPAQUE_BOOL(StringGreater)
OPAQUE_BOOL(StringGreaterEq)
OPAQUE_BOOL(StringLess)
OPAQUE_BOOL(StringLessEq)
#define UNREACHABLE(NODE)                                            \
  void ExpToZ3Visitor::visit(NODE &) {                               \
    messageError("Z3 encoding: unexpected node " #NODE);             \
  }
// string values only appear under (opaque) string comparisons
UNREACHABLE(StringVariable)
UNREACHABLE(StringConstant)
UNREACHABLE(StringConcat)
UNREACHABLE(Substring)
// temporal nodes are not propositions
UNREACHABLE(BooleanLayerPermutationPlaceholder)
UNREACHABLE(BooleanLayerNot)
UNREACHABLE(BooleanLayerDTPlaceholder)
UNREACHABLE(BooleanLayerInst)
UNREACHABLE(BooleanLayerFunction)
UNREACHABLE(PropertyAlways)
UNREACHABLE(PropertyNext)
UNREACHABLE(PropertyEventually)
UNREACHABLE(PropertyUntil)
UNREACHABLE(PropertyRelease)
UNREACHABLE(PropertyAnd)
UNREACHABLE(PropertyOr)
UNREACHABLE(PropertyNot)
UNREACHABLE(PropertyImplication)
UNREACHABLE(SereConcat)
UNREACHABLE(SereAnd)
UNREACHABLE(SereOr)
UNREACHABLE(SereIntersect)
UNREACHABLE(SereFirstMatch)
UNREACHABLE(SereDelay)
UNREACHABLE(SereConsecutiveRep)
UNREACHABLE(SerePlus)
UNREACHABLE(SereGoto)
UNREACHABLE(SereNonConsecutiveRep)

} // namespace expression
