namespace expression {

template <typename ET, typename RT>
BitSelector<ET, RT>::BitSelector(const GenericPtr<ET> &e,
                                 size_t lower_bound,
                                 size_t upper_bound)
    : RT(e->getType().first, upper_bound - lower_bound + 1,
         e->getMaxTime()),
      _e(e), _lower_bound(lower_bound), _upper_bound(upper_bound) {
  initEvaluate();
  // ntd
}

template <typename ET, typename RT>
BitSelector<ET, RT>::~BitSelector() {}

template <typename ET, typename RT>
GenericPtr<ET> &BitSelector<ET, RT>::getItem() {
  return _e;
}

template <typename ET, typename RT>
size_t BitSelector<ET, RT>::getUpperBound() {
  return _upper_bound;
}
template <typename ET, typename RT>
size_t BitSelector<ET, RT>::getLowerBound() {
  return _lower_bound;
}

template <typename ET, typename RT>
void BitSelector<ET, RT>::setSourceIndices(long left, long right) {
  _source_left = left;
  _source_right = right;
}
template <typename ET, typename RT>
long BitSelector<ET, RT>::getSourceLeft() {
  return _source_left;
}
template <typename ET, typename RT>
long BitSelector<ET, RT>::getSourceRight() {
  return _source_right;
}

} // namespace expression
