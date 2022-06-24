#include "visitors/ExpVisitor.hh"
#include "classes/atom/Variable.hh"

namespace expression {

NumericVariable::NumericVariable(Numeric *v, const std::string &name, VarType type, uint8_t size, size_t max_time) : Atom<Numeric>(type, size, max_time), _v(v), _name(name){
    // ntd
     }


Numeric NumericVariable::evaluate(size_t time) { return _v[time]; }

void NumericVariable::assign(size_t time, Numeric value) { _v[time] = value; }


void NumericVariable::acceptVisitor(ExpVisitor &vis) { vis.visit(*this); }

} 
