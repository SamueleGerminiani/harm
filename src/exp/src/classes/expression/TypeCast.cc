#include "classes/expression/TypeCast.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

template <>
LogicToNumeric::TypeCast(LogicExpression *e)
    : NumericExpression(VarType::Numeric,64,e->getMaxTime()), _e(e){
  // ntd
}
template <>
LogicToBool::TypeCast(LogicExpression *e)
    : Proposition(VarType::Bool,1,e->getMaxTime()), _e(e){
  // ntd
}

template <>
NumericToBool::TypeCast(NumericExpression *e)
    : Proposition(VarType::Bool,1,e->getMaxTime()), _e(e){
  // ntd
}
template <>
void LogicToNumeric::acceptVisitor(
  ExpVisitor &vis) {
  vis.visit(*this);
}

template <>
void LogicToBool::acceptVisitor(
  ExpVisitor &vis) {
  vis.visit(*this);
}
template <>
void NumericToBool::acceptVisitor(
  ExpVisitor &vis) {
  vis.visit(*this);
}



template <>
Numeric LogicToNumeric::evaluate(size_t time) {
         return _e->evaluate(time);
}
template <>
bool LogicToBool::evaluate(size_t time) {
         return _e->evaluate(time);
}
template <>
bool NumericToBool::evaluate(size_t time) {
         return _e->evaluate(time);
}

} // namespace oden
