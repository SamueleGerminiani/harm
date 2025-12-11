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
#define VARIABLE(LEAF)                                               \
  void PrinterVisitor::visit(LEAF &o) {                              \
    _ss << selCol(o.getName(), VAR(o.getName()));                    \
  }

#define INT_CONSTANT(LEAF)                                           \
  void PrinterVisitor::visit(LEAF &o) {                              \
    if (o.getType().first == ExpType::UInt) {                        \
      UInt val = (UInt)o.evaluate(0);                                \
      _ss << selCol(std::to_string(val) +                            \
                        (std::log2(val) > 63.f ? "ull" : ""),        \
                    VAR(std::to_string(val) +                        \
                        (std::log2(val) > 63.f ? "ull" : "")));      \
    } else {                                                         \
      _ss << selCol(std::to_string((SInt)o.evaluate(0)),             \
                    VAR(std::to_string((SInt)o.evaluate(0))));       \
    }                                                                \
  }

#define REAL_CONSTANT(LEAF)                                          \
  void PrinterVisitor::visit(LEAF &o) {                              \
    _ss << std::setprecision(17) << o.evaluate(0);                   \
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
      _ss << selCol(std::to_string(o.getType().second) + "'b" +      \
                        o.evaluate(0).toString(),                    \
                    VAR(std::to_string(o.getType().second) + "'b" +  \
                        o.evaluate(0).toString()));                  \
    }                                                                \
  }

#define BOOLEAN_CONSTANT(LEAF)                                       \
  void PrinterVisitor::visit(LEAF &o) {                              \
    _ss << (o.evaluate(0) ? selCol(std::string("true"),              \
                                   BOOL(std::string("true")))        \
                          : selCol(std::string("false"),             \
                                   BOOL(std::string("false"))));     \
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
        hasHigherPrecedence(parent_op, ope::ope::NODE);              \
    if (putBrakets) {                                                \
      _ss << selCol("(", BOOL("("));                                 \
    }                                                                \
    if (items.size() > 1) {                                          \
      --iterStop;                                                    \
      for (; iter != iterStop; ++iter) {                             \
        (*iter)->acceptVisitor(*this);                               \
        _ss << " "                                                   \
            << selCol(opeToString(ope::NODE),                        \
                      BOOL(opeToString(ope::NODE)))                  \
            << " ";                                                  \
      }                                                              \
    }                                                                \
    (*iter)->acceptVisitor(*this);                                   \
    if (putBrakets) {                                                \
      _ss << selCol(")", BOOL(")"));                                 \
    }                                                                \
    _ope_stack.pop();                                                \
  }

#define TYPE_CAST(NODE)                                              \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    o.getItem()->acceptVisitor(*this);                               \
  }

#define EXP_OPE_BIT_SELECTION(NODE)                                  \
  void PrinterVisitor::visit(expression::NODE &o) {                  \
    if (o.getLowerBound() == o.getUpperBound()) {                    \
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

void PrinterVisitor::visit(expression::PropositionNot &o) {
  _ope_stack.push(ope::ope::PropositionNot);
  _ss << selCol(opeToString(ope::PropositionNot),
                BOOL(opeToString(ope::PropositionNot)));
  o.getItems()[0]->acceptVisitor(*this);
  _ope_stack.pop();
}

void PrinterVisitor::visit(expression::IntNot &o) {
  _ope_stack.push(ope::ope::IntNot);
  _ss << selCol(opeToString(ope::IntNot),
                BOOL(opeToString(ope::IntNot)));
  o.getItems()[0]->acceptVisitor(*this);
  _ope_stack.pop();
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

void PrinterVisitor::visit(FloatSetMembership &o) {
  _ope_stack.push(ope::ope::FloatSetMembership);
  o.getItem()->acceptVisitor(*this);
  if (_colored) {
    _ss << BOOL(" " + ope::opeToString(ope::ope::FloatSetMembership) +
                " ");
    _ss << VAR(o.valuesToString());
    _ss << " ";

  } else {
    _ss << " " + ope::opeToString(ope::ope::FloatSetMembership) + " ";
    _ss << o.valuesToString();
    _ss << " ";
  }
  _ope_stack.pop();
}

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
TYPE_CAST(IntToFloat)
TYPE_CAST(IntToBool)
TYPE_CAST(IntToLogic)
UNARY_FUNCTION(IntPast)
UNARY_FUNCTION(IntStable)
UNARY_FUNCTION(IntRose)
UNARY_FUNCTION(IntFell)

void PrinterVisitor::visit(IntSetMembership &o) {
  _ope_stack.push(ope::ope::IntSetMembership);
  o.getItem()->acceptVisitor(*this);
  if (_colored) {
    _ss << BOOL(" " + ope::opeToString(ope::ope::IntSetMembership) +
                " ");
    _ss << VAR(o.valuesToString());
    _ss << " ";
  } else {
    _ss << " " + ope::opeToString(ope::ope::IntSetMembership) + " ";
    _ss << o.valuesToString();
    _ss << " ";
  }
  _ope_stack.pop();
}

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
  _ope_stack.push(ope::ope::LogicNot);
  _ss << selCol(opeToString(ope::LogicNot),
                BOOL(opeToString(ope::LogicNot)));
  o.getItems()[0]->acceptVisitor(*this);
  _ope_stack.pop();
}

void PrinterVisitor::visit(LogicSetMembership &o) {
  _ope_stack.push(ope::ope::LogicSetMembership);
  o.getItem()->acceptVisitor(*this);
  if (_colored) {
    _ss << BOOL(" " + ope::opeToString(ope::ope::LogicSetMembership) +
                " ");
    _ss << VAR(o.valuesToString());
    _ss << " ";

  } else {
    _ss << " " + ope::opeToString(ope::ope::LogicSetMembership) + " ";
    _ss << o.valuesToString();
    _ss << " ";
  }
  _ope_stack.pop();
}

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
         hasHigherPrecedence(parent_op, ope::temporalOpe::NODE)) ||  \
        ope::temporalOpe::NODE == ope::temporalOpe::PropertyAlways;  \
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
      _ss << selCol("true", BOOL("true"));
      return;
    }

    bool needsBrackets = !isUnary(*o.getPlaceholderPointer());

    needsBrackets &=
        !isPropositionAnd(*o.getPlaceholderPointer()) ||
        getPropositionAndSize(*o.getPlaceholderPointer()) > 1;

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
  bool needsBrackets = !isUnary(o.getProposition());
  needsBrackets &= !isPropositionAnd(o.getProposition()) ||
                   getPropositionAndSize(o.getProposition()) > 1;

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

void PrinterVisitor::visit(PropertyImplication &o) {
  _temporal_ope_stack.push(ope::temporalOpe::PropertyImplication);

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
