namespace expression {

template <typename ET, typename RT> TypeCast<ET, RT>::~TypeCast() {}

template <typename ET, typename RT>
GenericPtr<ET> &TypeCast<ET, RT>::getItem() {
  return _e;
}

template <typename ET, typename RT> void TypeCast<ET, RT>::popItem() {
  _e.reset();
}

} // namespace expression
