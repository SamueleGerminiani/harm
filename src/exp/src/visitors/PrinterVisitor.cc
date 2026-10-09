#include <optional>
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../miner/utils/include/DTLimits.hh"
#include "Int.hh"
#include "Logic.hh"
#include "colors.hh"
#include "expUtils/ExpType.hh"

#include "expUtils/ope.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/BitSelector.hh"
#include "formula/expression/Ternary.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/expression/SetMembership.hh"
#include "formula/expression/Substring.hh"
#include "formula/expression/TypeCast.hh"
#include "formula/function/SVAfunction.hh"
#include "globals.hh"
#include "misc.hh"
#include "visitors/PrinterVisitor.hh"

namespace expression {
PrinterVisitor::PrinterVisitor(Language lang, bool colored,
                               PrintMode mode)
    : ExpVisitor(), _ss(), _lang(lang), _colored(colored),
      _printMode(mode), _ope_stack(), _temporal_ope_stack() {
  _ope_stack.push(ope::ope::NoOp);
  _temporal_ope_stack.push(ope::temporalOpe::TemporalNoOp);
}

void PrinterVisitor::clear() {
  _ss.clear();
  _ss.str(std::string());
}

std::string PrinterVisitor::get() {
  std::string ret = _ss.str();
  clear();
  return ret;
}
} // namespace expression

//Atom------------------------------------------------------------------------------
#define selCol(bw, col) (_colored ? col : bw)
//in SystemVerilog, hierarchical names use '.' (a::b is a package scope)
#define VARIABLE(LEAF)                                               \
  void PrinterVisitor::visit(LEAF &o) {                              \
    std::string name = o.getName();                                  \
    if (_lang == Language::SVA && !clc::legacySvaPrinting) {         \
      replace("::", ".", name);                                      \
    }                                                                \
    _ss << selCol(name, VAR(name));                                  \
  }

// D-035 (R4): an unsigned integer constant prints as a sized SystemVerilog literal, so that the
// text re-parses to an unsigned value of the same width (a decimal would re-parse signed)
#define INT_CONSTANT(LEAF)                                           \
  void PrinterVisitor::visit(LEAF &o) {                              \
    if (o.getType().first == ExpType::UInt) {                        \
      UInt val = (UInt)o.evaluate(0);                                \
      size_t w = std::min<size_t>(o.getType().second, 64);           \
      if (w < 64) {                                                  \
        val &= (UInt(1) << w) - 1;                                   \
      }                                                              \
      std::string bits;                                              \
      for (UInt v = val; v != 0; v >>= 1) {                          \
        bits.insert(bits.begin(), char('0' + (v & 1)));              \
      }                                                              \
      std::string t = std::to_string(w) + "'b" + (bits.empty() ? "0" : bits); \
      _ss << selCol(t, VAR(t));                                      \
    } else {                                                         \
      _ss << selCol(std::to_string((SInt)o.evaluate(0)),             \
                    VAR(std::to_string((SInt)o.evaluate(0))));       \
    }                                                                \
  }

// D-035 (R4): a real keeps a decimal point ('2.0', not '2', which would re-parse as an integer)
#define REAL_CONSTANT(LEAF)                                          \
  void PrinterVisitor::visit(LEAF &o) {                              \
    std::ostringstream os;                                           \
    os << std::setprecision(17) << o.evaluate(0);                    \
    std::string t = os.str();                                        \
    if (t.find_first_of(".eEni") == std::string::npos) {             \
      t += ".0";                                                     \
    }                                                                \
    _ss << t;                                                        \
  }

#define LOGIC_CONSTANT(LEAF)                                         \
  void PrinterVisitor::visit(LEAF &o) {                              \
    if (clc::printLogicAsInt) {                                      \
      if (o.getType().first == ExpType::ULogic) {                    \
        _ss << selCol(                                               \
            to_string(o.evaluate(0).getUnsignedValue()),             \
            VAR(to_string(o.evaluate(0).getUnsignedValue())));       \
      } else {                                                       \
        _ss << selCol(                                               \
            to_string(o.evaluate(0).getSignedValue()),               \
            VAR(to_string(o.evaluate(0).getSignedValue())));         \
      }                                                              \
    } else {                                                         \
      /* D-035 (R4): a leading x or z digit after stripped zeros keeps */ \
      /* one 0 (4'bx01 would mean 4'bxx01); a signed literal keeps 's' */  \
      std::string digits = o.evaluate(0).toString();                 \
      if (!digits.empty() &&                                         \
          std::string("xXzZ").find(digits[0]) != std::string::npos &&\
          digits.size() < o.getType().second) {                      \
        digits = "0" + digits;                                       \
      }                                                              \
      std::string t = std::to_string(o.getType().second) +           \
                      (isSigned(o.getType().first) ? "'sb" : "'b") + \
                      digits;                                        \
      _ss << selCol(t, VAR(t));                                      \
    }                                                                \
  }

//'true' and 'false' are not SystemVerilog
#define BOOLEAN_CONSTANT(LEAF)                                       \
  void PrinterVisitor::visit(LEAF &o) {                              \
    bool sv = _lang == Language::SVA && !clc::legacySvaPrinting;     \
    std::string t = sv ? "1'b1" : "true";                            \
    std::string f = sv ? "1'b0" : "false";                           \
    _ss << (o.evaluate(0) ? selCol(t, BOOL(t)) : selCol(f, BOOL(f))); \
  }

#define STRING_CONSTANT(LEAF)                                        \
  void PrinterVisitor::visit(LEAF &o) {                              \
    _ss << "\"" << selCol(o.evaluate(0), VAR(o.evaluate(0)))         \
        << "\"";                                                     \
  }

//PropositionalExpression------------------------------------------------------------------------------

#define EXP_OPE(NODE)                                                \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    auto parent_op = _ope_stack.top();                               \
    bool asRight = _rightOperand;                                    \
    _rightOperand = false;                                           \
    _ope_stack.push(ope::ope::NODE);                                 \
    auto &items = o.getItems();                                      \
    auto iterStop = items.end();                                     \
    auto iter = items.begin();                                       \
    messageErrorIf(                                                  \
        items.empty(),                                               \
        "Attempting to print an empty propositional expression");    \
                                                                     \
    bool putBrakets =                                                \
        items.size() > 1 &&                                          \
        (hasHigherPrecedence(parent_op, ope::ope::NODE) ||           \
         (asRight && needsBracketsAsRight(parent_op, ope::ope::NODE)));\
    if (putBrakets) {                                                \
      _ss << selCol("(", BOOL("("));                                 \
    }                                                                \
    if (items.size() > 1) {                                          \
      --iterStop;                                                    \
      for (; iter != iterStop; ++iter) {                             \
        _rightOperand = false;                                       \
        (*iter)->acceptVisitor(*this);                               \
        _ss << " "                                                   \
            << selCol(opeToString(ope::NODE),                        \
                      BOOL(opeToString(ope::NODE)))                  \
            << " ";                                                  \
      }                                                              \
    }                                                                \
    /* the last item is a right operand (D-034) */                   \
    _rightOperand = items.size() > 1;                                \
    (*iter)->acceptVisitor(*this);                                   \
    _rightOperand = false;                                           \
    if (putBrakets) {                                                \
      _ss << selCol(")", BOOL(")"));                                 \
    }                                                                \
    _ope_stack.pop();                                                \
  }

// D-034: x inside {...} has the precedence of a relational operator; the values print in the
// order written, without a trailing blank
#define SET_MEMBERSHIP(NODE)                                         \
  void PrinterVisitor::visit(NODE &o) {                              \
    auto parent_op = _ope_stack.top();                               \
    bool asRight = _rightOperand;                                    \
    _rightOperand = false;                                           \
    bool putBrakets =                                                \
        hasHigherPrecedence(parent_op, ope::ope::NODE) ||            \
        (asRight && needsBracketsAsRight(parent_op, ope::ope::NODE));\
    if (putBrakets) {                                                \
      _ss << selCol("(", BOOL("("));                                 \
    }                                                                \
    _ope_stack.push(ope::ope::NODE);                                 \
    o.getItem()->acceptVisitor(*this);                               \
    std::string kw = " " + ope::opeToString(ope::ope::NODE) + " ";   \
    _ss << selCol(kw, BOOL(kw));                                     \
    _ss << selCol(o.valuesToString(), VAR(o.valuesToString()));      \
    _ope_stack.pop();                                                \
    if (putBrakets) {                                                \
      _ss << selCol(")", BOOL(")"));                                 \
    }                                                                \
  }

#define TYPE_CAST(NODE)                                              \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    o.getItem()->acceptVisitor(*this);                               \
  }

// D-034: a select binds tighter than every operator: its operand is bracketed unless it is a
// primary (the Select pseudo-operator is tighter than every class)
#define EXP_OPE_BIT_SELECTION(NODE)                                  \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    _rightOperand = false;                                           \
    _ope_stack.push(ope::ope::Select);                               \
    printSelected(o);                                                \
    _ope_stack.pop();                                                \
  }                                                                  \
  void PrinterVisitor::printSelected(expression::NODE &o) {          \
    if (o.getSourceLeft() >= 0) {                                    \
      /* the SystemVerilog indices as written (D-028) */             \
      o.getItem()->acceptVisitor(*this);                             \
      _ss << selCol("[", BOOL("["));                                 \
      _ss << selCol(std::to_string(o.getSourceLeft()),               \
                    VAR(std::to_string(o.getSourceLeft())));         \
      if (o.getSourceRight() != o.getSourceLeft()) {                 \
        _ss << selCol(":", BOOL(":"));                               \
        _ss << selCol(std::to_string(o.getSourceRight()),            \
                      VAR(std::to_string(o.getSourceRight())));      \
      }                                                              \
      _ss << selCol("]", BOOL("]"));                                 \
    } else if (o.getLowerBound() == o.getUpperBound()) {             \
      o.getItem()->acceptVisitor(*this);                             \
      _ss << selCol("[", BOOL("["));                                 \
      _ss << selCol(std::to_string(o.getLowerBound()),               \
                    VAR(std::to_string(o.getLowerBound())));         \
      _ss << selCol("]", BOOL("]"));                                 \
    } else {                                                         \
      o.getItem()->acceptVisitor(*this);                             \
      _ss << selCol("[", BOOL("["));                                 \
      _ss << selCol(std::to_string(o.getUpperBound()),               \
                    VAR(std::to_string(o.getUpperBound())));         \
      _ss << selCol(":", BOOL(":"));                                 \
      _ss << selCol(std::to_string(o.getLowerBound()),               \
                    VAR(std::to_string(o.getLowerBound())));         \
      _ss << selCol("]", BOOL("]"));                                 \
    }                                                                \
  }

#define UNARY_FUNCTION(TYPE)                                         \
  void PrinterVisitor::visit(TYPE &o) {                              \
    if (_colored) {                                                  \
      _ss << o.toColoredString(_printMode == PrintMode::ShowAll);    \
    } else {                                                         \
      _ss << o.toString(_printMode == PrintMode::ShowAll);           \
    }                                                                \
  }

//------------------------------------------------------------------------------

namespace expression {

// proposition
VARIABLE(BooleanVariable)
BOOLEAN_CONSTANT(BooleanConstant)
EXP_OPE(PropositionOr)
EXP_OPE(PropositionAnd)
EXP_OPE(PropositionXor)
EXP_OPE(PropositionEq)
EXP_OPE(PropositionNeq)
UNARY_FUNCTION(PropositionPast)
UNARY_FUNCTION(PropositionStable)
UNARY_FUNCTION(PropositionRose)
UNARY_FUNCTION(PropositionFell)

// D-034: a prefix operator binds tighter than every binary operator, so a binary operand gets
// brackets (through _ope_stack); a unary minus over a negation or a negative constant gets them
// too, so that '--' (decrement in SystemVerilog) is never printed
template <typename N> void PrinterVisitor::printPrefix(N &o, ope::ope op) {
  _rightOperand = false;
  _ope_stack.push(op);
  _ss << selCol(opeToString(op), BOOL(opeToString(op)));
  auto child = o.getItems()[0];
  bool minus = op == ope::ope::IntNeg || op == ope::ope::LogicNeg ||
               op == ope::ope::FloatNeg;
  std::string childText;
  if (minus) {
    PrinterVisitor pv(_lang, false, _printMode);
    child->acceptVisitor(pv);
    childText = pv.get();
  }
  bool brackets = minus && !childText.empty() && childText[0] == '-';
  if (brackets) {
    _ss << selCol("(", BOOL("("));
  }
  child->acceptVisitor(*this);
  if (brackets) {
    _ss << selCol(")", BOOL(")"));
  }
  _ope_stack.pop();
}

void PrinterVisitor::visit(expression::PropositionNot &o) {
  printPrefix(o, ope::ope::PropositionNot);
}

void PrinterVisitor::visit(expression::IntNot &o) {
  printPrefix(o, ope::ope::IntNot);
}
void PrinterVisitor::visit(expression::IntNeg &o) {
  printPrefix(o, ope::ope::IntNeg);
}
void PrinterVisitor::visit(expression::LogicNeg &o) {
  printPrefix(o, ope::ope::LogicNeg);
}
void PrinterVisitor::visit(expression::FloatNeg &o) {
  printPrefix(o, ope::ope::FloatNeg);
}

// float
VARIABLE(FloatVariable)
REAL_CONSTANT(FloatConstant)
EXP_OPE(FloatSum)
EXP_OPE(FloatSub)
EXP_OPE(FloatMul)
EXP_OPE(FloatDiv)
EXP_OPE(FloatEq)
EXP_OPE(FloatNeq)
EXP_OPE(FloatGreater)
EXP_OPE(FloatGreaterEq)
EXP_OPE(FloatLess)
EXP_OPE(FloatLessEq)
TYPE_CAST(FloatToLogic)
TYPE_CAST(FloatToInt)
TYPE_CAST(FloatToBool)
UNARY_FUNCTION(FloatStable)
UNARY_FUNCTION(FloatPast)

SET_MEMBERSHIP(FloatSetMembership)

// int
VARIABLE(IntVariable)
INT_CONSTANT(IntConstant)
EXP_OPE(IntSum)
EXP_OPE(IntSub)
EXP_OPE(IntMul)
EXP_OPE(IntDiv)
EXP_OPE(IntBAnd)
EXP_OPE(IntBOr)
EXP_OPE(IntBXor)
EXP_OPE(IntEq)
EXP_OPE(IntNeq)
EXP_OPE(IntGreater)
EXP_OPE(IntGreaterEq)
EXP_OPE(IntLess)
EXP_OPE(IntLessEq)
EXP_OPE_BIT_SELECTION(IntBitSelector)
EXP_OPE(IntLShift)
EXP_OPE(IntRShift)
EXP_OPE(IntARShift)
EXP_OPE(LogicARShift)
TYPE_CAST(IntToFloat)
TYPE_CAST(IntToBool)
TYPE_CAST(IntToLogic)
TYPE_CAST(BoolToLogic) // D-032: printed as the bool operand itself
UNARY_FUNCTION(IntPast)
UNARY_FUNCTION(IntStable)
UNARY_FUNCTION(IntRose)
UNARY_FUNCTION(IntFell)

SET_MEMBERSHIP(IntSetMembership)

// logic
VARIABLE(LogicVariable)
LOGIC_CONSTANT(LogicConstant)
EXP_OPE(LogicSum)
EXP_OPE(LogicSub)
EXP_OPE(LogicMul)
EXP_OPE(LogicDiv)
EXP_OPE(LogicBAnd)
EXP_OPE(LogicBOr)
EXP_OPE(LogicBXor)
EXP_OPE(LogicEq)
EXP_OPE(LogicNeq)
EXP_OPE(LogicGreater)
EXP_OPE(LogicGreaterEq)
EXP_OPE(LogicLess)
EXP_OPE(LogicLessEq)
EXP_OPE_BIT_SELECTION(LogicBitSelector)
EXP_OPE(LogicCaseEq)
EXP_OPE(LogicCaseNeq)

void PrinterVisitor::visit(expression::LogicConcat &o) {
  _ope_stack.push(ope::ope::LogicConcat);
  //print each item on its own, to fold a replication {N{a}} back
  std::string prefix = _ss.str();
  std::vector<std::string> parts;
  for (const auto &item : o.getItems()) {
    _ss.str("");
    _ss.clear();
    item->acceptVisitor(*this);
    parts.push_back(_ss.str());
  }
  _ss.str("");
  _ss.clear();
  _ss << prefix;
  bool replication =
      parts.size() > 1 &&
      std::all_of(parts.begin(), parts.end(),
                  [&parts](const std::string &p) { return p == parts[0]; });
  _ss << selCol("{", BOOL("{"));
  if (replication) {
    _ss << selCol(std::to_string(parts.size()),
                  VAR(std::to_string(parts.size())))
        << selCol("{", BOOL("{")) << parts[0] << selCol("}", BOOL("}"));
  } else {
    for (size_t i = 0; i < parts.size(); i++) {
      _ss << (i ? selCol(", ", BOOL(", ")) : "") << parts[i];
    }
  }
  _ss << selCol("}", BOOL("}"));
  _ope_stack.pop();
}

//a ternary is always parenthesized, so that the output can be parsed again
#define TERNARY(NODE)                                                \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    _ope_stack.push(ope::ope::Ternary);                              \
    _ss << selCol("(", BOOL("("));                                   \
    o.getCondition()->acceptVisitor(*this);                          \
    _ss << selCol(" ? ", BOOL(" ? "));                               \
    o.getWhenTrue()->acceptVisitor(*this);                           \
    _ss << selCol(" : ", BOOL(" : "));                               \
    o.getWhenFalse()->acceptVisitor(*this);                          \
    _ss << selCol(")", BOOL(")"));                                   \
    _ope_stack.pop();                                                \
  }
TERNARY(PropositionTernary)
TERNARY(IntTernary)
TERNARY(LogicTernary)
TERNARY(FloatTernary)
EXP_OPE(LogicLShift)
EXP_OPE(LogicRShift)
TYPE_CAST(LogicToFloat)
TYPE_CAST(LogicToBool)
TYPE_CAST(LogicToInt)
UNARY_FUNCTION(LogicPast)
UNARY_FUNCTION(LogicStable)
UNARY_FUNCTION(LogicRose)
UNARY_FUNCTION(LogicFell)

void PrinterVisitor::visit(expression::LogicNot &o) {
  printPrefix(o, ope::ope::LogicNot);
}

SET_MEMBERSHIP(LogicSetMembership)

//string
STRING_CONSTANT(StringConstant)
VARIABLE(StringVariable)
EXP_OPE(StringConcat)
EXP_OPE(StringEq)
EXP_OPE(StringNeq)
EXP_OPE(StringGreater)
EXP_OPE(StringGreaterEq)
EXP_OPE(StringLess)
EXP_OPE(StringLessEq)

void PrinterVisitor::visit(expression::Substring &o) {
  _ope_stack.push(ope::ope::Substring);
  _ss << selCol(o.toString(), o.toColoredString());
  o.getItem()->acceptVisitor(*this);
  _ope_stack.pop();
}

//TemporalExpression------------------------------------------------------------------------------

bool PrinterVisitor::sereNeedsCurlyBrackets() {
  return (_temporal_ope_stack.top() ==
              ope::temporalOpe::TemporalNoOp ||
          isPropertyOpe(_temporal_ope_stack.top())) &&
         _lang != Language::SVA;
}

std::pair<std::string, std::string>
PrinterVisitor::getSereBrackets() {
  if (_lang != Language::SVA) {
    return std::make_pair("{", "}");
  } else {
    return std::make_pair("(", ")");
  }
}
static std::string chooseTemporalOpColor(const std::string &str,
                                         ope::temporalOpe op) {
  if (op == ope::temporalOpe::PropertyAlways) {
    return GLOB(str);
  } else {
    return TEMP(str);
  }
}
bool isBinaryRightAssociative(ope::temporalOpe op) {
  return op == ope::temporalOpe::PropertyUntil ||
         op == ope::temporalOpe::PropertyRelease;
}

#define PROPERTY(NODE)                                               \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    auto parent_op = _temporal_ope_stack.top();                      \
    _temporal_ope_stack.push(ope::temporalOpe::NODE);                \
    auto &items = o.getItems();                                      \
    messageErrorIf(                                                  \
        items.empty(),                                               \
        "Attempting to print an empty temporal expression");         \
    messageErrorIf(items.size() > 2,                                 \
                   "Attempting to print a temporal expression with " \
                   "more than 2 items");                             \
                                                                     \
    bool putBrakets =                                                \
        (items.size() > 1 &&                                         \
         (hasHigherPrecedence(parent_op, ope::temporalOpe::NODE) ||  \
          (_lang == Language::SVA &&                                 \
           svaNeedsBrackets(parent_op, ope::temporalOpe::NODE)))) || \
        ope::temporalOpe::NODE == ope::temporalOpe::PropertyAlways;  \
    /* SVA: a unary operator of low precedence is wrapped whole */   \
    bool wrapSelf = items.size() == 1 && _lang == Language::SVA &&   \
                    svaNeedsBrackets(parent_op, ope::temporalOpe::NODE); \
    if (wrapSelf) {                                                  \
      _ss << selCol("(", chooseTemporalOpColor(                      \
                             "(", ope::temporalOpe::NODE));          \
    }                                                                \
                                                                     \
    if (items.size() > 1) {                                          \
      bool leftRequiresBrackets = false;                             \
      if (isBinaryRightAssociative(ope::temporalOpe::NODE) &&        \
          isBinaryRightAssociative(items[0]->getOperator()) &&       \
          isSamePrecedence(ope::temporalOpe::NODE,                   \
                           items[0]->getOperator())) {               \
        leftRequiresBrackets = true;                                 \
      }                                                              \
      if (leftRequiresBrackets) {                                    \
        _ss << selCol("(", chooseTemporalOpColor(                    \
                               "(", ope::temporalOpe::NODE));        \
      }                                                              \
      if (putBrakets) {                                              \
        _ss << selCol("(", chooseTemporalOpColor(                    \
                               "(", ope::temporalOpe::NODE));        \
      }                                                              \
      items[0]->acceptVisitor(*this);                                \
      if (leftRequiresBrackets) {                                    \
        _ss << selCol(")", chooseTemporalOpColor(                    \
                               ")", ope::temporalOpe::NODE));        \
      }                                                              \
      _ss << " ";                                                    \
    }                                                                \
                                                                     \
    if (clc::svaAssert &&                                            \
        _printMode != PrintMode::ShowOnlyPermuationPlaceholders &&   \
        ope::temporalOpe::NODE ==                                    \
            ope::temporalOpe::PropertyAlways) {                      \
      std::string assert =                                           \
          "assert property (@(posedge " + clc::clk + ") ";           \
      _ss << selCol(assert, chooseTemporalOpColor(                   \
                                assert, ope::temporalOpe::NODE));    \
    } else {                                                         \
      _ss << selCol(opeToString(ope::temporalOpe::NODE, _lang),      \
                    chooseTemporalOpColor(                           \
                        opeToString(ope::temporalOpe::NODE, _lang),  \
                        ope::temporalOpe::NODE));                    \
      if (_lang != Language::SpotLTL && items.size() == 1) {         \
        _ss << " ";                                                  \
      }                                                              \
    }                                                                \
                                                                     \
    if (items.size() == 1 && putBrakets) {                           \
      _ss << selCol(                                                 \
          "(", chooseTemporalOpColor("(", ope::temporalOpe::NODE));  \
    }                                                                \
    if (items.size() == 2) {                                         \
      _ss << " ";                                                    \
    }                                                                \
    items.back()->acceptVisitor(*this);                              \
                                                                     \
    if (putBrakets) {                                                \
      _ss << selCol(                                                 \
          ")", chooseTemporalOpColor(")", ope::temporalOpe::NODE));  \
    }                                                                \
    if (wrapSelf) {                                                  \
      _ss << selCol(                                                 \
          ")", chooseTemporalOpColor(")", ope::temporalOpe::NODE));  \
    }                                                                \
    if (clc::svaAssert &&                                            \
        _printMode != PrintMode::ShowOnlyPermuationPlaceholders &&   \
        ope::temporalOpe::NODE ==                                    \
            ope::temporalOpe::PropertyAlways) {                      \
      _ss << selCol(                                                 \
          ")", chooseTemporalOpColor(")", ope::temporalOpe::NODE));  \
    }                                                                \
    _temporal_ope_stack.pop();                                       \
  }

#define SERE_BINARY(NODE)                                            \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    auto parent_op = _temporal_ope_stack.top();                      \
    bool needsCurlyBrackets = sereNeedsCurlyBrackets();              \
    _temporal_ope_stack.push(ope::temporalOpe::NODE);                \
    auto &items = o.getItems();                                      \
    messageErrorIf(items.empty(),                                    \
                   "Attempting to print an empty sere");             \
    messageErrorIf(                                                  \
        items.size() > 2,                                            \
        "Attempting to print a binary sere with more than 2 "        \
        "items");                                                    \
                                                                     \
    bool putBrackets =                                               \
        hasHigherPrecedence(parent_op, ope::temporalOpe::NODE) ||    \
        needsCurlyBrackets;                                          \
    auto [open, close] = getSereBrackets();                          \
                                                                     \
    if (putBrackets) {                                               \
      _ss << selCol(open, TEMP(open));                               \
    }                                                                \
    items[0]->acceptVisitor(*this);                                  \
    _ss << " "                                                       \
        << selCol(opeToString(ope::temporalOpe::NODE, _lang),        \
                  TEMP(opeToString(ope::temporalOpe::NODE, _lang)))  \
        << " ";                                                      \
    items[1]->acceptVisitor(*this);                                  \
    if (putBrackets) {                                               \
      _ss << selCol(close, TEMP(close));                             \
    }                                                                \
    _temporal_ope_stack.pop();                                       \
  }

#define SERE_WINDOW_BASED(NODE, IS_LEFT)                             \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    bool needsCurlyBrackets = sereNeedsCurlyBrackets();              \
    auto parent_op = _temporal_ope_stack.top();                      \
    _temporal_ope_stack.push(ope::temporalOpe::NODE);                \
    auto &items = o.getItems();                                      \
    messageErrorIf(items.empty(),                                    \
                   "Attempting to print an empty sere expression");  \
    messageErrorIf(                                                  \
        items.size() > 2,                                            \
        "Attempting to print a binary sere with more than 2 items"); \
    messageErrorIf(                                                  \
        !IS_LEFT && items.size() != 1,                               \
        "Attempting to print a unary window-based sere with "        \
        "more than 1 item");                                         \
    NODE *wbs = dynamic_cast<NODE *>(&o);                            \
    messageErrorIf(                                                  \
        wbs == nullptr,                                              \
        "Attempting to print a temporal expression with a "          \
        "non-window-based operator");                                \
    bool putBrackets =                                               \
        hasHigherPrecedence(parent_op, ope::temporalOpe::NODE) ||    \
        needsCurlyBrackets;                                          \
    auto [open, close] = getSereBrackets();                          \
    if (putBrackets) {                                               \
      _ss << selCol(open, TEMP(open));                               \
    }                                                                \
    std::string windowStr =                                          \
        selCol(wbs->windowToString(), TEMP(wbs->windowToString()));  \
                                                                     \
    if (IS_LEFT) {                                                   \
      if (items.size() > 1) {                                        \
        items[0]->acceptVisitor(*this);                              \
        _ss << " ";                                                  \
      }                                                              \
      _ss << selCol(windowStr, TEMP(windowStr)) << " ";              \
      items.back()->acceptVisitor(*this);                            \
    } else {                                                         \
      items[0]->acceptVisitor(*this);                                \
      _ss << selCol(windowStr, TEMP(windowStr));                     \
    }                                                                \
    if (putBrackets) {                                               \
      _ss << selCol(close, TEMP(close));                             \
    }                                                                \
    _temporal_ope_stack.pop();                                       \
  }

namespace {
/// Spot LTL: X, F, !, U (printed W) and R bind tighter than && and ||, and && tighter than ||;
/// a proposition with such a connective at the top needs brackets under them (H1d, F8, D-021)
bool spotNeedsBrackets(const PropositionPtr &p, ope::temporalOpe parent) {
  using T = ope::temporalOpe;
  auto op = p->getOperator();
  bool connective =
      (op == ope::PropositionAnd && getPropositionAndSize(p) > 1) ||
      op == ope::PropositionOr || op == ope::PropositionXor ||
      op == ope::PropositionEq || op == ope::PropositionNeq;
  if (!connective) {
    return false;
  }
  switch (parent) {
  case T::PropertyNext:
  case T::PropertyEventually:
  case T::PropertyNot:
  case T::BooleanLayerNot:
  case T::PropertyUntil:
  case T::PropertyRelease:
    return true;
  case T::PropertyAnd:
    return op != ope::PropositionAnd;
  default:
    return false;
  }
}
} // namespace

void PrinterVisitor::visit(BooleanLayerNot &o) {
  _temporal_ope_stack.push(ope::temporalOpe::BooleanLayerNot);
  _ss << selCol(opeToString(ope::temporalOpe::BooleanLayerNot),
                BOOL(opeToString(ope::BooleanLayerNot)));
  o.getBL()->acceptVisitor(*this);
  _temporal_ope_stack.pop();
}

void PrinterVisitor::visit(BooleanLayerPermutationPlaceholder &o) {
  if (_printMode == PrintMode::ShowAll) {
    if (!isUnary(*o.getPlaceholderPointer())) {
      _ss << selCol("(", TEMP("("));
    }
    (*o.getPlaceholderPointer())->acceptVisitor(*this);
    if (!isUnary(*o.getPlaceholderPointer())) {
      _ss << selCol(")", TEMP(")"));
    }
  } else {
    _ss << selCol(o.getToken(), VAR(o.getToken()));
  }
}
void PrinterVisitor::visit(BooleanLayerDTPlaceholder &o) {
  if (_printMode == PrintMode::ShowAll) {
    if (isEmptyPropositionAnd(*o.getPlaceholderPointer())) {
      std::string t = _lang == Language::SVA && !clc::legacySvaPrinting
                          ? "1'b1"
                          : "true";
      _ss << selCol(t, BOOL(t));
      return;
    }

    bool needsBrackets = !isUnary(*o.getPlaceholderPointer());
    auto parent_op = _temporal_ope_stack.top();
    needsBrackets &= !hasHigherPrecedence(
        (*o.getPlaceholderPointer())->getOperator(), parent_op);

    needsBrackets &=
        !isPropositionAnd(*o.getPlaceholderPointer()) ||
        getPropositionAndSize(*o.getPlaceholderPointer()) > 1;
    needsBrackets |= _lang == Language::SpotLTL &&
                     spotNeedsBrackets(*o.getPlaceholderPointer(), parent_op);

    if (needsBrackets) {
      _ss << selCol("(", TEMP("("));
    }

    (*o.getPlaceholderPointer())->acceptVisitor(*this);

    if (needsBrackets) {
      _ss << selCol(")", TEMP(")"));
    }
  } else if (_printMode ==
             PrintMode::ShowOnlyPermuationPlaceholders) {
    _ss << selCol(toString(o.getType()),
                  toColoredString(o.getType()));
  } else {
    _ss << selCol(o.getToken(), VAR(o.getToken()));
  }
}
void PrinterVisitor::visit(BooleanLayerInst &o) {
  if (_subst != nullptr && _subst->count(o.getProposition().get())) {
    _ss << _subst->at(o.getProposition().get());
    return;
  }
  bool needsBrackets = !isUnary(o.getProposition());
  auto parent_op = _temporal_ope_stack.top();
  needsBrackets &= !hasHigherPrecedence(
      o.getProposition()->getOperator(), parent_op);
  needsBrackets &= !isPropositionAnd(o.getProposition()) ||
                   getPropositionAndSize(o.getProposition()) > 1;
  needsBrackets |= _lang == Language::SpotLTL &&
                   spotNeedsBrackets(o.getProposition(), parent_op);

  if (_printMode != PrintMode::Hide) {
    if (needsBrackets) {
      _ss << selCol("(", TEMP("("));
    }
    messageErrorIf((o.getProposition()) == nullptr,
                   "Attempting to print a nullptr proposition");
    o.getProposition()->acceptVisitor(*this);
    if (needsBrackets) {
      _ss << selCol(")", TEMP(")"));
    }
  } else {
    _ss << selCol(o.getToken(), VAR(o.getToken()));
  }
}
void PrinterVisitor::visit(BooleanLayerFunction &o) {
  if (_printMode == PrintMode::Hide) {
    _ss << selCol(o.getToken(), VAR(o.getToken()));
  } else {
    o.getFunction()->acceptVisitor(*this);
  }
}

PROPERTY(PropertyAlways)
PROPERTY(PropertyEventually)
PROPERTY(PropertyNot)
PROPERTY(PropertyUntil)
PROPERTY(PropertyRelease)
PROPERTY(PropertyOr)
PROPERTY(PropertyAnd)
SERE_BINARY(SereAnd)
SERE_BINARY(SereOr)
SERE_BINARY(SereIntersect)

void PrinterVisitor::visit(PropertyNext &o) {
  _temporal_ope_stack.push(ope::temporalOpe::PropertyNext);
  _ss << selCol(opeToString(ope::PropertyNext, _lang),
                TEMP(opeToString(ope::PropertyNext, _lang)));
  if (o.getDelay() != 1) {
    _ss << selCol("[", TEMP("["));
    _ss << selCol(std::to_string(o.getDelay()),
                  TEMP(std::to_string(o.getDelay())));
    _ss << selCol("]", TEMP("]"));
  }
  if (o.getDelay() != 1 && _lang == Language::SpotLTL) {
    _ss << selCol("(", TEMP("("));
  }
  if (_lang != Language::SpotLTL) {
    _ss << " ";
  }
  o.getItems()[0]->acceptVisitor(*this);
  if (o.getDelay() != 1 && _lang == Language::SpotLTL) {
    _ss << selCol(")", TEMP(")"));
  }
  _temporal_ope_stack.pop();
}

namespace {
/// the last cycle of a sequence of fixed length, counting from 0 (a Boolean: 0); std::nullopt if
/// te is not a sequence (e.g. a property with nexttime) or its length is not fixed (H1d, F7)
std::optional<int> sequenceLastCycle(const TemporalExpressionPtr &te) {
  if (isBooleanLayer(te)) {
    return 0;
  }
  if (auto c = std::dynamic_pointer_cast<SereConcat>(te)) {
    auto l = sequenceLastCycle(c->getItems()[0]);
    auto r = sequenceLastCycle(c->getItems()[1]);
    if (!l || !r) {
      return std::nullopt;
    }
    return *l + (c->isOverlapping() ? 0 : 1) + *r;
  }
  if (auto d = std::dynamic_pointer_cast<SereDelay>(te)) {
    auto w = d->getWindow();
    if (w.first != w.second || w.first < 0) {
      return std::nullopt;
    }
    auto &items = d->getItems();
    std::optional<int> from = 0;
    if (items.size() == 2) {
      from = sequenceLastCycle(items[0]);
    }
    auto r = sequenceLastCycle(items.back());
    if (!from || !r) {
      return std::nullopt;
    }
    return *from + w.first + *r;
  }
  if (std::dynamic_pointer_cast<SereAnd>(te) || std::dynamic_pointer_cast<SereOr>(te) ||
      std::dynamic_pointer_cast<SereIntersect>(te)) {
    std::optional<int> last;
    for (const auto &i : te->getItems()) {
      auto l = sequenceLastCycle(i);
      if (!l || (last && *l != *last)) {
        return std::nullopt; // only operands of equal length have one end
      }
      last = l;
    }
    return last;
  }
  return std::nullopt;
}

/// true for the antecedent of an invariant G(true -> p)
bool isTrueAntecedent(const TemporalExpressionPtr &te) {
  auto inst = std::dynamic_pointer_cast<BooleanLayerInst>(te);
  if (inst == nullptr) {
    return false;
  }
  auto c = std::dynamic_pointer_cast<BooleanConstant>(inst->getProposition());
  return c != nullptr && c->evaluate(0);
}
} // namespace

void PrinterVisitor::visit(PropertyImplication &o) {
  // an invariant G(true -> p) is printed as G(p)
  if (!o.isMMImplication() && o.isOverlapping() &&
      isTrueAntecedent(o.getItems()[0])) {
    // printed exactly as the consequent of an implication
    _temporal_ope_stack.push(ope::temporalOpe::PropertyImplication);
    o.getItems()[1]->acceptVisitor(*this);
    _temporal_ope_stack.pop();
    return;
  }
  _temporal_ope_stack.push(ope::temporalOpe::PropertyImplication);

  // SystemVerilog: 'p |-> nexttime q' is printed 'p |=> q', and more nexttimes as '##n', when q
  // is boolean (equivalent: a sequence used as a property is weak by default, like nexttime);
  // nexttime is valid SystemVerilog but not accepted by common tools (Verilator, EBMC)
  // SystemVerilog: HARM's '->' starts the consequent with the antecedent, SVA's '|->' at its end
  // (H1d, F7, D-021). A multi-cycle antecedent is re-anchored at its end when it is a sequence of
  // fixed length and the consequent is Boolean after k nexttimes; otherwise 'implies', which
  // starts both sides together
  if (_lang == Language::SVA && !clc::legacySvaPrinting && !o.isMMImplication() &&
      !isBooleanLayer(o.getItems()[0])) {
    TemporalExpressionPtr consequent = o.getItems()[1];
    int k = o.isOverlapping() ? 0 : 1;
    while (auto next = std::dynamic_pointer_cast<PropertyNext>(consequent)) {
      k += (int)next->getDelay();
      consequent = next->getItems()[0];
    }
    auto last = sequenceLastCycle(o.getItems()[0]);
    if (last && isBooleanLayer(consequent)) {
      int j = k - *last;
      o.getItems()[0]->acceptVisitor(*this);
      std::string op = j == 0   ? " |-> "
                       : j == 1 ? " |=> "
                       : j > 1  ? " |-> ##" + std::to_string(j) + " "
                                : " |-> $past(";
      _ss << selCol(op, TIMPL(op));
      consequent->acceptVisitor(*this);
      if (j < 0) {
        std::string tail = ", " + std::to_string(-j) + ")";
        _ss << selCol(tail, TIMPL(tail));
      }
    } else {
      _ss << selCol("(", TIMPL("("));
      o.getItems()[0]->acceptVisitor(*this);
      std::string op = std::string(") implies ") + (o.isOverlapping() ? "" : "nexttime ");
      _ss << selCol(op, TIMPL(op));
      if (!o.isOverlapping()) {
        _ss << selCol("(", TIMPL("("));
      }
      o.getItems()[1]->acceptVisitor(*this);
      if (!o.isOverlapping()) {
        _ss << selCol(")", TIMPL(")"));
      }
    }
    _temporal_ope_stack.pop();
    return;
  }

  if (_lang == Language::SVA && !clc::legacySvaPrinting) {
    TemporalExpressionPtr consequent = o.getItems()[1];
    size_t shift = o.isOverlapping() ? 0 : 1;
    size_t nexts = 0;
    while (auto next =
               std::dynamic_pointer_cast<PropertyNext>(consequent)) {
      shift += next->getDelay();
      nexts++;
      consequent = next->getItems()[0];
    }
    if (nexts > 0 && isBooleanLayer(consequent)) {
      o.getItems()[0]->acceptVisitor(*this);
      if (shift == 1) {
        _ss << selCol(" |=> ", TIMPL(" |=> "));
      } else {
        std::string delay = " |-> ##" + std::to_string(shift) + " ";
        _ss << selCol(delay, TIMPL(delay));
      }
      consequent->acceptVisitor(*this);
      _temporal_ope_stack.pop();
      return;
    }
  }

  auto [open, close] = getSereBrackets();

  if (o.isMMImplication() && isBooleanLayer(o.getItems()[0]) &&
      _lang != Language::SVA) {
    _ss << selCol(open, TEMP(open));
  }
  o.getItems()[0]->acceptVisitor(*this);
  if (o.isMMImplication() && isBooleanLayer(o.getItems()[0]) &&
      _lang != Language::SVA) {
    _ss << selCol(close, TEMP(close));
  }
  _ss << selCol(" ", TIMPL(" "));
  if (o.isMMImplication() || _lang == Language::SVA) {
    _ss << selCol("|", TIMPL("|"));
  }
  if (o.isOverlapping()) {
    _ss << selCol("->", TIMPL("->"));
  } else {
    _ss << selCol("=>", TIMPL("=>"));
  }
  _ss << selCol(" ", TIMPL(" "));
  o.getItems()[1]->acceptVisitor(*this);
  _temporal_ope_stack.pop();
}

void PrinterVisitor::visit(SereFirstMatch &o) {
  bool needsCurlyBrackets = sereNeedsCurlyBrackets();
  auto [open, close] = getSereBrackets();
  _temporal_ope_stack.push(ope::temporalOpe::SereFirstMatch);

  _ss << (needsCurlyBrackets ? selCol(open, TEMP(open)) : "");
  _ss << selCol(opeToString(ope::SereFirstMatch, _lang),
                TEMP(opeToString(ope::SereFirstMatch, _lang)));
  _ss << selCol("(", TEMP("("));
  o.getItems()[0]->acceptVisitor(*this);
  _ss << selCol(")", TEMP(")"));
  _ss << (needsCurlyBrackets ? selCol(close, TEMP(close)) : "");

  _temporal_ope_stack.pop();
}

void PrinterVisitor::visit(SereConcat &o) {
  bool needsCurlyBrackets = sereNeedsCurlyBrackets();
  auto parent_op = _temporal_ope_stack.top();
  bool putBrackets =
      hasHigherPrecedence(parent_op, ope::temporalOpe::SereConcat) ||
      needsCurlyBrackets;
  auto [open, close] = getSereBrackets();
  _temporal_ope_stack.push(ope::temporalOpe::SereConcat);
  _ss << (putBrackets ? selCol(open, TEMP(open)) : "");

  o.getItems()[0]->acceptVisitor(*this);
  if (o.isOverlapping()) {
    if (_lang == Language::SVA) {
      _ss << selCol(" ##0 ", TEMP(" ##0 "));
    } else {
      _ss << selCol(":", TEMP(":"));
    }
  } else {
    if (_lang == Language::SVA) {
      _ss << selCol(" ##1 ", TEMP(" ##1 "));
    } else {
      _ss << selCol(";", TEMP(";"));
    }
  }
  o.getItems()[1]->acceptVisitor(*this);

  _ss << (putBrackets ? selCol(close, TEMP(close)) : "");
  _temporal_ope_stack.pop();
}

void PrinterVisitor::visit(SerePlus &o) {
  bool needsCurlyBrackets = sereNeedsCurlyBrackets();
  auto [open, close] = getSereBrackets();
  _temporal_ope_stack.push(ope::temporalOpe::SerePlus);
  _ss << (needsCurlyBrackets ? selCol(open, TEMP(open)) : "");

  o.getItems()[0]->acceptVisitor(*this);
  _ss << selCol("[", TEMP("["));
  _ss << selCol(opeToString(ope::SerePlus, _lang),
                TEMP(opeToString(ope::SerePlus, _lang)));
  _ss << selCol("]", TEMP("]"));

  _ss << (needsCurlyBrackets ? selCol(close, TEMP(close)) : "");
  _temporal_ope_stack.pop();
}

SERE_WINDOW_BASED(SereDelay, 1)
SERE_WINDOW_BASED(SereConsecutiveRep, 0)
SERE_WINDOW_BASED(SereNonConsecutiveRep, 0)
SERE_WINDOW_BASED(SereGoto, 0)

} // namespace expression
