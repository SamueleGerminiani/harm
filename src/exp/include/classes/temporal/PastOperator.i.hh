
namespace expression {

template <typename ET>
PastOperator<ET>::PastOperator(ET *e, size_t offset)
    : ET(e->getType().first,e->getType().second,e->getMaxTime()), _e(e), _offset(offset) {
    // ntd
}

template <typename ET> PastOperator<ET>::~PastOperator() { delete _e; }

template <typename ET> ET &PastOperator<ET>::getItem() { return *_e; }

template <typename ET> size_t PastOperator<ET>::getOffset() { return _offset; }

} // namespace oden
