namespace expression {

template <typename ET, typename RT> TypeCast<ET, RT>::~TypeCast() {
  if (_e != nullptr) {
    delete _e;
  }
}

template <typename ET, typename RT> ET &TypeCast<ET, RT>::getItem() {
  return *_e;
}

template <typename ET, typename RT> void TypeCast<ET, RT>::popItem() {
  _e = nullptr;
}

} // namespace expression
