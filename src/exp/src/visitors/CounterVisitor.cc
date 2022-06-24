#include "visitors/CounterVisitor.hh"

//------------------------------------------------------------------------------
#define VARIABLE(LEAF) \
	void CounterVisitor::visit(LEAF &o) { _count++; }

#define CONSTANT(LEAF) \
	void CounterVisitor::visit(LEAF &o) {  }
#define BOOLEAN_CONSTANT(LEAF)                             \
	void CounterVisitor::visit(LEAF &o) {              \
	}

#define EXPRESSION(NODE)                                                   \
	void CounterVisitor::visit(expression::NODE &o) {                  \
		auto &items = o.getItems();                                \
                                                                           \
		if (!items.empty()) {                                      \
			auto iterStop = items.end();                       \
			auto iter = items.begin();                         \
                                                                           \
			if (items.size() > 1) {                            \
				--iterStop;                                \
				for (; iter != iterStop; ++iter) {         \
					(*iter)->acceptVisitor(*this);     \
				}                                          \
			}                                                  \
			(*iter)->acceptVisitor(*this);                     \
		}                                                          \
	}

#define TYPE_CAST(NODE)                                   \
	void CounterVisitor::visit(expression::NODE &o) { \
		o.getItem().acceptVisitor(*this);         \
	}

#define EXPRESSION_BOOLEAN_BIT_SELECTION(NODE)            \
	void CounterVisitor::visit(expression::NODE &o) { \
		o.getItem().acceptVisitor(*this);         \
	}

#define EXPRESSION_LOGIC_BIT_SELECTION(NODE)                  \
	void CounterVisitor::visit(expression::NODE &o) {     \
		if (o.getLowerBound() == o.getUpperBound()) { \
			o.getItem().acceptVisitor(*this);     \
		} else {                                      \
			o.getItem().acceptVisitor(*this);     \
		}                                             \
	}

#define EXPRESSION_NEXT(NODE)                                \
	void CounterVisitor::visit(expression::NODE &o) {    \
		o.getItem().acceptVisitor(*this);            \
	}
#define EXPRESSION_PAST(NODE)                             \
	void CounterVisitor::visit(expression::NODE &o) { \
		o.getItem().acceptVisitor(*this);         \
	}
//------------------------------------------------------------------------------

namespace expression {

CounterVisitor::CounterVisitor() : ExpVisitor(), _count(0){

}





// proposition
VARIABLE(BooleanVariable)
BOOLEAN_CONSTANT(BooleanConstant)
EXPRESSION(PropositionOr)
EXPRESSION(PropositionAnd)
EXPRESSION(PropositionXor)
EXPRESSION(PropositionEq)
EXPRESSION(PropositionNeq)
EXPRESSION_PAST(PropositionPast)

int CounterVisitor::get_count(){
	return _count;
}

void CounterVisitor::visit(expression::PropositionNot &o) {
	o.getItems()[0]->acceptVisitor(*this);
}

void CounterVisitor::visit(expression::LogicNot &o) {
	o.getItems()[0]->acceptVisitor(*this);
}


// numeric
VARIABLE(NumericVariable)
CONSTANT(NumericConstant)
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
CONSTANT(LogicConstant)
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

}  // namespace expression
