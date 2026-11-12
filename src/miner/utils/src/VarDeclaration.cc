#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "message.hh"

namespace harm {
using namespace expression;

VarDeclaration::VarDeclaration(const std::string &name,
                               expression::ExpType type, size_t size)
    : _name(name), _type(type), _size(size) {}

VarDeclaration::VarDeclaration()
    : _name(""), _type(ExpType::Unknown), _size(1) {
  // ntd
}

void VarDeclaration::setName(const std::string &name) {
  _name = name;
}

std::string VarDeclaration::getName() const { return _name; }

void VarDeclaration::setType(ExpType type, size_t size) {
  _type = type;
  _size = size;
}

ExpType VarDeclaration::getType() const { return _type; }

size_t VarDeclaration::getSize() const { return _size; }

size_t VarDeclaration::getInputBase() const {
  messageErrorIf(_type != expression::ExpType::SInt &&
                     _type != expression::ExpType::UInt,
                 "Base is only defined for integer types got " +
                     to_string(_type) + " for variable " + _name);

  return _input_base;
}
void VarDeclaration::setInputBase(size_t input_base) {
  _input_base = input_base;
}

void VarDeclaration::setRange(long left, long right) {
  _left = left;
  _right = right;
}
bool VarDeclaration::hasRange() const { return _left >= 0 && _right >= 0; }
long VarDeclaration::getLeft() const { return _left; }
long VarDeclaration::getRight() const { return _right; }
} // namespace harm
