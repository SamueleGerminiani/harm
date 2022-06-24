#include "DataType.hh"


namespace harm {
    using namespace expression;

DataType::DataType()
    : _name(""), _type(VarType::Unknown), _size(1),
      _location(Location::Ant) {
    // ntd
}

void DataType::setName(const std::string &name) { _name = name; }

std::string DataType::getName() const { return _name; }

void DataType::setType(VarType type, uint8_t size) {
    _type = type;
    _size = size;
}

VarType DataType::getType() const { return _type; }

uint8_t DataType::getSize() const { return _size; }

void DataType::setLocation(Location dir) { _location = dir; }

Location DataType::getLocation() const { return _location; }

} // namespace oden
