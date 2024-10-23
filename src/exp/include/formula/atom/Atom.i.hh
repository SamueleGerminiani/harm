

namespace expression {

template <typename T>
Atom<T>::Atom(ExpType type, size_t size, size_t max_time)
    : _type(type), _size(size), _max_time(max_time) {
  // ntd
}

template <typename T> size_t Atom<T>::getMaxTime() {
  return _max_time;
}

template <typename T> std::pair<ExpType, size_t> Atom<T>::getType() {
  return std::make_pair(_type, _size);
}

template <typename T> ope::ope Atom<T>::getOperator() {
  return ope::ope::NoOp;
}

template <typename T> void Atom<T>::disableCache() {
  if (_cache != nullptr) {
    delete[] _cache;
    _cache = nullptr;
  }
  evaluate = directEvaluate;
}

template <typename T> void Atom<T>::fillCache() {
  if (_cache == nullptr) {
    _cache = new T[_max_time];
  }
  for (size_t i = 0; i < _max_time; i++) {
    _cache[i] = directEvaluate(i);
  }
}

template <typename T> void Atom<T>::enableCache() {
  evaluate = [this](size_t time) { return _cache[time]; };
  fillCache();
}

template <typename T> bool Atom<T>::isCacheEnabled() {
  return _cache != nullptr;
}

template <typename T> Atom<T>::~Atom() { disableCache(); }

} // namespace expression
