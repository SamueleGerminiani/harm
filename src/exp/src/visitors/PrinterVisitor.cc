#include "visitors/PrinterVisitor.hh"
#include <bitset>

//------------------------------------------------------------------------------
#define VARIABLE(LEAF)                                                         \
  void PrinterVisitor::visit(LEAF &o) { _ss << o.getName(); }

#define LOGIC_CONSTANT(LEAF)                                                   \
  void PrinterVisitor::visit(LEAF &o) {                                        \
    if (o.getType().first == VarType::ULogic) {                                \
      _ss << (std::to_string((ULogic)o.evaluate(0)));                          \
    } else {                                                                   \
      _ss << (std::to_string((SLogic)o.evaluate(0)));                          \
    }                                                                          \
  }

#define REAL_CONSTANT(LEAF)                                                    \
  void PrinterVisitor::visit(LEAF &o) { _ss << o.evaluate(0); }

#define BOOLEAN_CONSTANT(LEAF)                                                 \
  void PrinterVisitor::visit(LEAF &o) {                                        \
    _ss << (o.evaluate(0) ? "true" : "false");                                 \
  }

#define EXPRESSION(NODE)                                                       \
  void PrinterVisitor::visit(expression::NODE &o) {                            \
    auto &items = o.getItems();                                                \
    _ss << "(";                                                                \
                                                                               \
    if (!items.empty()) {                                                      \
      auto iterStop = items.end();                                             \
      auto iter = items.begin();                                               \
                                                                               \
      if (items.size() > 1) {                                                  \
        --iterStop;                                                            \
        for (; iter != iterStop; ++iter) {                                     \
          (*iter)->acceptVisitor(*this);                                       \
          _ss << " " << operators[ope::NODE] << " ";                           \
        }                                                                      \
      }                                                                        \
      (*iter)->acceptVisitor(*this);                                           \
    } else {                                                                   \
      _ss << "true";                                                           \
    }                                                                          \
    _ss << ")";                                                                \
  }

#define TYPE_CAST(NODE)                                                        \
  void PrinterVisitor::visit(expression::NODE &o) {                            \
    _ss << "";                                                                 \
    o.getItem().acceptVisitor(*this);                                          \
    _ss << "";                                                                 \
  }

#define EXPRESSION_LOGIC_BIT_SELECTION(NODE)                                   \
  void PrinterVisitor::visit(expression::NODE &o) {                            \
    if (o.getLowerBound() == o.getUpperBound()) {                              \
      o.getItem().acceptVisitor(*this);                                        \
      _ss << "[";                                                              \
      _ss << o.getLowerBound();                                                \
      _ss << "]";                                                              \
    } else {                                                                   \
      o.getItem().acceptVisitor(*this);                                        \
      _ss << "[";                                                              \
      _ss << o.getUpperBound();                                                \
      _ss << ":";                                                              \
      _ss << o.getLowerBound();                                                \
      _ss << "]";                                                              \
    }                                                                          \
  }

#define EXPRESSION_NEXT(NODE)                                                  \
  void PrinterVisitor::visit(expression::NODE &o) {                            \
    _ss << "nexttime[" << o.getOffset() << "](";                               \
    o.getItem().acceptVisitor(*this);                                          \
    _ss << ")";                                                                \
  }
#define EXPRESSION_PAST(NODE)                                                  \
  void PrinterVisitor::visit(expression::NODE &o) {                            \
    _ss << "$past(";                                                           \
    o.getItem().acceptVisitor(*this);                                          \
    _ss << ", " << o.getOffset() << ")";                                       \
  }
//------------------------------------------------------------------------------

namespace expression {

PrinterVisitor::PrinterVisitor() : ExpVisitor(), _ss() {
  // proposition
  operators[ope::PropositionNot] = std::string("!");
  operators[ope::PropositionAnd] = std::string("&&");
  operators[ope::PropositionOr] = std::string("||");
  operators[ope::PropositionXor] = std::string("^");
  operators[ope::PropositionEq] = std::string("==");
  operators[ope::PropositionNeq] = std::string("!=");

  // numeric
  operators[ope::NumericSum] = std::string("+");
  operators[ope::NumericSub] = std::string("-");
  operators[ope::NumericMul] = std::string("*");
  operators[ope::NumericDiv] = std::string("/");
  operators[ope::NumericEq] = std::string("==");
  operators[ope::NumericNeq] = std::string("!=");
  operators[ope::NumericGreater] = std::string(">");
  operators[ope::NumericGreaterEq] = std::string(">=");
  operators[ope::NumericLess] = std::string("<");
  operators[ope::NumericLessEq] = std::string("<=");

  // logic
  operators[ope::LogicSum] = std::string("+");
  operators[ope::LogicSub] = std::string("-");
  operators[ope::LogicMul] = std::string("*");
  operators[ope::LogicDiv] = std::string("/");
  operators[ope::LogicBAnd] = std::string("&");
  operators[ope::LogicBOr] = std::string("|");
  operators[ope::LogicBXor] = std::string("^");
  operators[ope::LogicNot] = std::string("~");
  operators[ope::LogicEq] = std::string("==");
  operators[ope::LogicNeq] = std::string("!=");
  operators[ope::LogicGreater] = std::string(">");
  operators[ope::LogicGreaterEq] = std::string(">=");
  operators[ope::LogicLess] = std::string("<");
  operators[ope::LogicLessEq] = std::string("<=");
  operators[ope::LogicLShift] = std::string("<<");
  operators[ope::LogicRShift] = std::string(">>");

  // temporal
  operators[ope::Past] = std::string("$past");
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

// proposition
VARIABLE(BooleanVariable)
BOOLEAN_CONSTANT(BooleanConstant)
EXPRESSION(PropositionOr)
EXPRESSION(PropositionXor)
EXPRESSION(PropositionEq)
EXPRESSION(PropositionNeq)
EXPRESSION_PAST(PropositionPast)

void PrinterVisitor::visit(expression::PropositionAnd &o) {

  auto &items = o.getItems();

  if (!items.empty()) {
    auto iterStop = items.end();
    auto iter = items.begin();

    //_ss << "(";
    if (items.size() > 1) {
      --iterStop;
      for (; iter != iterStop; ++iter) {
        (*iter)->acceptVisitor(*this);
        _ss << " " << operators[ope::PropositionAnd] << " ";
      }
    }
    (*iter)->acceptVisitor(*this);
    //_ss << ")";
  } else {
    //	_ss << "(.." << operators[ope::PropositionAnd] << "..)";
    _ss << ".." << operators[ope::PropositionAnd] << "..";
  }
}

void PrinterVisitor::visit(expression::PropositionNot &o) {
  _ss << operators[ope::PropositionNot];
  o.getItems()[0]->acceptVisitor(*this);
}

void PrinterVisitor::visit(expression::LogicNot &o) {
  _ss << operators[ope::LogicNot];
  o.getItems()[0]->acceptVisitor(*this);
}

// numeric
VARIABLE(NumericVariable)
REAL_CONSTANT(NumericConstant)
EXPRESSION(NumericSum)
EXPRESSION(NumericSub)
EXPRESSION(NumericMul)
EXPRESSION(NumericDiv)
EXPRESSION(NumericEq)
EXPRESSION(NumericNeq)
EXPRESSION(NumericGreater)
EXPRESSION(NumericGreaterEq)
EXPRESSION(NumericLess)
EXPRESSION(NumericLessEq)
EXPRESSION_PAST(NumericPast)
TYPE_CAST(NumericToBool)

// logic
VARIABLE(LogicVariable)
LOGIC_CONSTANT(LogicConstant)
EXPRESSION(LogicSum)
EXPRESSION(LogicSub)
EXPRESSION(LogicMul)
EXPRESSION(LogicDiv)
EXPRESSION(LogicBAnd)
EXPRESSION(LogicBOr)
EXPRESSION(LogicBXor)
EXPRESSION(LogicEq)
EXPRESSION(LogicNeq)
EXPRESSION(LogicGreater)
EXPRESSION(LogicGreaterEq)
EXPRESSION(LogicLess)
EXPRESSION(LogicLessEq)
EXPRESSION_PAST(LogicPast)
EXPRESSION_LOGIC_BIT_SELECTION(LogicBitSelector)
TYPE_CAST(LogicToNumeric)
TYPE_CAST(LogicToBool)
EXPRESSION(LogicLShift)
EXPRESSION(LogicRShift)

} // namespace expression
