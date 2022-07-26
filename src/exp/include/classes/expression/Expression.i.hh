#include <iostream>
namespace expression {

template <BinaryOperator O, typename OT, typename ET>
Expression<O, OT, ET>::Expression() : ET(), _items() {
    // ntd
}

template <BinaryOperator O, typename OT, typename ET>
void Expression<O, OT, ET>::addItem(OT *item) {
    _items.push_back(item);
}

template <BinaryOperator O, typename OT, typename ET>
void Expression<O, OT, ET>::removeItems() {

    while (!_items.empty())
        _items.pop_back();
}

template <BinaryOperator O, typename OT, typename ET>
void Expression<O, OT, ET>::popItem() {
    _items.pop_back();
}


template <BinaryOperator O, typename OT, typename ET>
std::vector<OT*> &Expression<O, OT, ET>::getItems() {
    return _items;
}

template <BinaryOperator O, typename OT, typename ET>
size_t Expression<O, OT, ET>::size() {
    return _items.size();
}

template <BinaryOperator O, typename OT, typename ET>
size_t Expression<O, OT, ET>::getMaxTime() {
    // Once we defined, we can change the sub-expressions (items).
    // Because Expression is a mutable object, we cannot store the max_time
    // value. We have to re-compute it every time.
    if (_items.empty())
        return 0;

    size_t min = _items[0]->getMaxTime();
    for (size_t i = 1; i < _items.size(); ++i) {
        size_t i_min = _items[i]->getMaxTime();
        if (min > i_min)
            min = i_min;
    }

    return min;
}


template <BinaryOperator O, typename OT, typename ET>
bool Expression<O, OT, ET>::empty() {
    return _items.empty();
}

template <typename T1> void addItems(T1 &base) {
    // ntd. base case for variadic function.
}

template <typename T1, typename T2, typename... T3>
void addItems(T1 &base, T2 arg1, T3... args) {
    base.addItem(arg1);
    addItems(base, args...);
}

template <typename T1, typename... T2> T1 *makeExpression(T2... args) {
    auto *ret = new T1();
    addItems(*ret, args...);
    return ret;
}
} 
