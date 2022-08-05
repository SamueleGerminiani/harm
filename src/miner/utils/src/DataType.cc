#include "DataType.hh"


namespace harm {
    using namespace expression;

DataType::DataType()
    : _name(""), _type(VarType::Unknown), _size(1) {
    // ntd
}

void DataType::setName(const std::string &name) { _name = name; }

std::string DataType::getName() const { return _name; }

void DataType::setType(VarType type, size_t size) {
    _type = type;
    _size = size;
}

VarType DataType::getType() const { return _type; }

size_t DataType::getSize() const { return _size; }


} // namespace oden
