#include "classes/atom/Constant.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

template <> bool Constant<bool>::evaluate(size_t) { return _value; }

template <> Numeric Constant<Numeric>::evaluate(size_t) { return _value; }

template <> Logic Constant<Logic>::evaluate(size_t) { return _value; }

template <> void Constant<bool>::acceptVisitor(ExpVisitor &vis) {
    vis.visit(*this);
}

template <> void Constant<Numeric>::acceptVisitor(ExpVisitor &vis) {
    vis.visit(*this);
}

template <> void Constant<Logic>::acceptVisitor(ExpVisitor &vis) {
    vis.visit(*this);
}

template <>
Constant<Logic>::Constant(Logic value,VarType type,uint8_t size, size_t max_time)
    : Atom<Logic>(type,size,max_time), _value(value) {
    // ntd
}
template <>
Constant<Numeric>::Constant(Numeric value,VarType type,uint8_t size, size_t max_time)
    : Atom<Numeric>(type,size,max_time), _value(value) {
    // ntd
}
template <>
Constant<bool>::Constant(bool value,VarType type,uint8_t size, size_t max_time)
    : Atom<bool>(type,size,max_time), _value(value) {
    // ntd
}
}
