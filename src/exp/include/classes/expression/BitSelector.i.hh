namespace expression {

template <typename ET,typename RT>
BitSelector<ET,RT>::BitSelector(ET *e,  size_t upper_bound,size_t lower_bound)
    : RT(e->getType().first,upper_bound-lower_bound+1,e->getMaxTime()), _e(e), _upper_bound(upper_bound), _lower_bound(lower_bound) {
  // ntd
}

template <typename ET,typename RT> BitSelector<ET,RT>::~BitSelector() { delete _e; }

template <typename ET,typename RT> ET &BitSelector<ET,RT>::getItem() { return *_e; }

template <typename ET,typename RT>
    size_t BitSelector<ET,RT>::getUpperBound(){
        return _upper_bound;
    }
template <typename ET,typename RT>
    size_t BitSelector<ET,RT>::getLowerBound(){
        return _lower_bound;
    }

} // namespace oden
