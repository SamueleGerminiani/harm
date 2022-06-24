#include "visitors/ExpVisitor.hh"
#include "classes/atom/Variable.hh"

namespace expression {

BooleanVariable::BooleanVariable(unsigned int *v, const std::string &name, size_t max_time)
    : Atom<bool>(VarType::Bool, 1, max_time), _v(v),_name(name){}


bool BooleanVariable::evaluate(size_t time) {
    size_t tPos          = time >> 5;
    unsigned int _buffer = _v[tPos];

    return (_buffer & (1 << (time & 31))) != 0;
}

void BooleanVariable::assign(size_t time, bool value) {
    if (value)
        _v[time >> 5] |= 1 << (time & 31);
    else
        _v[time >> 5] &= ~(1 << (time & 31));
}

void BooleanVariable::acceptVisitor(ExpVisitor &vis) { vis.visit(*this); }

} // namespace oden
