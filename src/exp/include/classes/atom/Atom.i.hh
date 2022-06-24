

namespace expression {

template <typename T>
Atom<T>::Atom(VarType type, uint8_t size, size_t max_time)
    : _type(type),_size(size) , _max_time(max_time) {
	// ntd
}

template <typename T>
size_t Atom<T>::getMaxTime() {
	return _max_time;
}

template <typename T>
void Atom<T>::setType(VarType type, uint8_t size) {
	_type = type;
	_size = size;
}
template <typename T>
std::pair<VarType,uint8_t> Atom<T>::getType(){
	return std::make_pair(_type,_size);
}
}  // namespace expression
