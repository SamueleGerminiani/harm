
namespace expression {

template <typename T>
Stable<T>::Stable(T *operand, size_t offset)
    : Function<bool>(operand->getType().first,operand->getType().second,operand->getMaxTime()), _operand(operand) {
    // ntd
}

template <typename T> Stable<T>::~Stable() { delete _operand; }

template <typename T> T &Stable<T>::getItem() { return *_operand; }


} // namespace oden
