
namespace expression {

template <typename T>
Constant<T>::Constant(T value, ExpType type, size_t size,
                      size_t max_time)
    : Atom<T>(type, size, max_time), _value(value) {
  initEvaluate();
}
template <typename T> Constant<T>::Constant(const Constant &other) {
  _type = other._type;
  _size = other._size;
  _max_time = other._max_time;
  _value = other._value;
  initEvaluate();
}

template <typename T> void Constant<T>::initEvaluate() {
  directEvaluate = [this](size_t time) { return _value; };
  disableCache();
}

template <typename T> void Constant<T>::set(T value) {
  _value = value;
}

} // namespace expression
