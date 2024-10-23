#include "PointerUtils.hh"
#include <iostream>

namespace expression {

template <ope::ope O, typename OT, typename ET>
GenericExpression<O, OT, ET>::GenericExpression()
    : ET(), _items(), _ope(O) {
  initEvaluate();
}

template <ope::ope O, typename OT, typename ET>
ope::ope GenericExpression<O, OT, ET>::getOperator() {
  return _ope;
}

template <ope::ope O, typename OT, typename ET>
void GenericExpression<O, OT, ET>::addItem(
    const GenericPtr<OT> &item) {
  _items.push_back(item);
}

template <ope::ope O, typename OT, typename ET>
void GenericExpression<O, OT, ET>::removeItems() {

  while (!_items.empty())
    _items.pop_back();
}

template <ope::ope O, typename OT, typename ET>
void GenericExpression<O, OT, ET>::popItem() {
  _items.pop_back();
}

template <ope::ope O, typename OT, typename ET>
std::vector<GenericPtr<OT>> &
GenericExpression<O, OT, ET>::getItems() {
  return _items;
}

template <ope::ope O, typename OT, typename ET>
size_t GenericExpression<O, OT, ET>::size() {
  return _items.size();
}

template <ope::ope O, typename OT, typename ET>
void GenericExpression<O, OT, ET>::setMaxTime(size_t time) {
  _max_time = time;
}

template <ope::ope O, typename OT, typename ET>
void GenericExpression<O, OT, ET>::setType(ExpType type,
                                           size_t size) {
  _type = type;
  _size = size;
}

template <ope::ope O, typename OT, typename ET>
bool GenericExpression<O, OT, ET>::empty() {
  return _items.empty();
}

//--------Utilities----------------------------------

template <typename T1> void addItems(GenericPtr<T1> &base) {
  // ntd. base case for variadic function.
}

template <typename T1, typename T2, typename... T3>
void addItems(GenericPtr<T1> &base, T2 arg1, T3... args) {
  base->addItem(arg1);
  //set max time of base
  base->setMaxTime(arg1->getMaxTime());
  addItems(base, args...);
}

template <typename T1, typename... T2>
GenericPtr<T1> makeGenericExpression(T2... args) {
  static_assert(
      sizeof...(args) > 0,
      "makeGenericExpression() would like to have at "
      "least one object, otherwise it cant know the max time...");
  GenericPtr<T1> ret = generatePtr<T1>();
  //default type is bool, need to be changed from outside (if needed)
  ret->setType(ExpType::Bool, 1);
  addItems(ret, args...);
  return ret;
}
template <typename T1, typename... T2>
GenericPtr<T1> makeGenericExpression(size_t max_time) {
  GenericPtr<T1> ret = generatePtr<T1>();
  //default type is bool, need to be changed from outside (if needed)
  ret->setType(ExpType::Bool, 1);
  ret->setMaxTime(max_time);
  return ret;
}
} // namespace expression
