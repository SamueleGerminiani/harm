#include "visitors/ColoredPrinterVisitor.hh"
#include <bitset>
#include "colors.hh"

//------------------------------------------------------------------------------
#define VARIABLE(LEAF) \
	void ColoredPrinterVisitor::visit(LEAF &o) { _ss << VAR(o.getName()); }

#define LOGIC_CONSTANT(LEAF) \
	void ColoredPrinterVisitor::visit(LEAF &o) {\
        if (o.getType().first==VarType::ULogic) {\
            _ss<< VAR(std::to_string((uint64_t)o.evaluate(0)));\
        }else{\
            _ss<< VAR(std::to_string((int64_t)o.evaluate(0)));\
        }\
    }

#define REAL_CONSTANT(LEAF) \
	void ColoredPrinterVisitor::visit(LEAF &o) { _ss <<o.evaluate(0); }
#define BOOLEAN_CONSTANT(LEAF)                                       \
	void ColoredPrinterVisitor::visit(LEAF &o) {                 \
		_ss << (o.evaluate(0) ? CONST(std::string("true")) : CONST(std::string("false"))); \
	}

#define EXPRESSION(NODE)                                                  \
	void ColoredPrinterVisitor::visit(expression::NODE &o) {          \
		auto &items = o.getItems();                               \
                                                                          \
        _ss<<BOOL("(");\
		if (!items.empty()) {                                     \
			auto iterStop = items.end();                      \
			auto iter = items.begin();                        \
                                                                          \
			if (items.size() > 1) {                           \
				--iterStop;                               \
				for (; iter != iterStop; ++iter) {        \
					(*iter)->acceptVisitor(*this);    \
					_ss << " "                        \
					    << BOOL(operators[ope::NODE]) \
					    << " ";                       \
				}                                         \
			}                                                 \
			(*iter)->acceptVisitor(*this);                    \
		} else {                                                  \
			_ss << CONST(std::string("true"));                                 \
		}                                                         \
        _ss<<BOOL(")");\
	}

#define TYPE_CAST_TO_BOOL(NODE)                                  \
	void ColoredPrinterVisitor::visit(expression::NODE &o) { \
		/*  _ss << BOOL("(bool)");*/                     \
		o.getItem().acceptVisitor(*this);                \
		_ss << "";                                       \
	}
#define TYPE_CAST_TO_NUMERIC(NODE)                               \
	void ColoredPrinterVisitor::visit(expression::NODE &o) { \
		/*	if(o.getType().second==32){                   \
				_ss << BOOL("(float)");          \
			}else{                                   \
				_ss << BOOL("(double)");         \
			}                                        \
			*/                                       \
		o.getItem().acceptVisitor(*this);                \
	}


#define EXPRESSION_LOGIC_BIT_SELECTION(NODE)                     \
	void ColoredPrinterVisitor::visit(expression::NODE &o) { \
		if (o.getLowerBound() == o.getUpperBound()) {    \
			o.getItem().acceptVisitor(*this);        \
			_ss << VAR("[");                              \
			_ss << VAR(std::to_string(o.getLowerBound()));                \
			_ss << VAR("]");                              \
		} else {                                         \
			o.getItem().acceptVisitor(*this);        \
			_ss << VAR("[");                              \
			_ss << VAR(std::to_string(o.getUpperBound()));                \
			_ss << VAR(":");                              \
			_ss << VAR(std::to_string(o.getLowerBound()));                \
			_ss << VAR("]");                              \
		}                                                \
	}

#define EXPRESSION_PAST(NODE)                                    \
	void ColoredPrinterVisitor::visit(expression::NODE &o) { \
		_ss << "$past(";                                 \
		o.getItem().acceptVisitor(*this);                \
		_ss << ", " << o.getOffset() << ")";             \
	}
//------------------------------------------------------------------------------

namespace expression {

ColoredPrinterVisitor::ColoredPrinterVisitor() : ExpVisitor(), _ss() {
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

void ColoredPrinterVisitor::clear() {
	_ss.clear();
	_ss.str(std::string());
}

std::string ColoredPrinterVisitor::get() {
	std::string ret = _ss.str();
	clear();
	return ret;
}

// proposition
VARIABLE(BooleanVariable)
BOOLEAN_CONSTANT(BooleanConstant)
EXPRESSION(PropositionAnd)
EXPRESSION(PropositionOr)
EXPRESSION(PropositionXor)
EXPRESSION(PropositionEq)
EXPRESSION(PropositionNeq)
EXPRESSION_PAST(PropositionPast)

void ColoredPrinterVisitor::visit(expression::PropositionNot &o) {
	_ss << BOOL(operators[ope::PropositionNot]);
	o.getItems()[0]->acceptVisitor(*this);
}

void ColoredPrinterVisitor::visit(expression::LogicNot &o) {
	_ss << BOOL(operators[ope::LogicNot]);
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
TYPE_CAST_TO_BOOL(NumericToBool)

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
TYPE_CAST_TO_NUMERIC(LogicToNumeric)
TYPE_CAST_TO_BOOL(LogicToBool)
EXPRESSION(LogicLShift)
EXPRESSION(LogicRShift)

}  // namespace expression
