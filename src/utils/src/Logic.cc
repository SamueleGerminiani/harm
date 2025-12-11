#include "Logic.hh"
#include "../../exp/include//expUtils/ExpType.hh"
#include "message.hh"
#include "misc.hh"

#include <algorithm>
#include <boost/multiprecision/cpp_int/add.hpp>
#include <boost/multiprecision/cpp_int/bitwise.hpp>
#include <boost/multiprecision/detail/no_et_ops.hpp>
#include <boost/multiprecision/detail/number_compare.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <cstdint>
#include <sstream>
#include <string>

namespace expression {

//-------------------------------------------------
//this code is necessary because boost decided not to handle integer overflow and underflow the same way as standard C++ built-in types (quite annoying)
SLogic signedToSLogic(ULogic a, size_t size) {
  if (a & ((ULogic)1 << (size - 1))) {
    //negative
    a = (((~((ULogic)0) >> size) << size) | a);
    a.backend().sign(1);
    SLogic b = a;
    SLogic c = b * -1;
    return c;
  } else {
    //positive
    a.backend().sign(0);
    a = (~((~((ULogic)0) >> size) << size) & a);
    SLogic b = a;
    return b;
  }
}

SLogic unsignedToSLogic(ULogic val, size_t size) {
  return (SLogic)(~((~((ULogic)0) >> size) << size) & val);
}
//-------------------------------------------------

bool Logic::containsXZ() const { return _x != 0 || _z != 0; }

SLogic Logic::getSignedValue() const {
  return _isSigned ? signedToSLogic(_int, _size)
                   : unsignedToSLogic(_int, _size);
}

//--------Logic class ----------------

Logic::Logic() {
  _size = 0;
  _isSigned = false;
  _int = 0;
  _x = 0;
  _z = 0;
}

ULogic Logic::getUnsignedValue() const {
  return (_int << (sizeOfLogic() * 8 - _size)) >>
         (sizeOfLogic() * 8 - _size);
}

Logic::Logic(size_t size, bool isSigned, ULogic int_, ULogic x,
             ULogic z)
    : _size(size), _isSigned(isSigned), _int(int_), _x(x), _z(z) {}

Logic::Logic(const std::string &binary, size_t size, bool isSigned) {

  messageWarningIf(
      size < binary.size(),
      "Declared Logic size '" + std::to_string(size) +
          "' is smaller than the given binary string size '" +
          std::to_string(binary.size()) +
          "', the MSBs will be ignored");

  if (size == (size_t)-1) {
    _size = binary.size();
  } else {
    _size = size;
  }

  messageErrorIf(_size > (sizeOfLogic() * 8) - 1,
                 "Logic size is too big, " +
                     std::to_string((sizeOfLogic() * 8) - 1) +
                     " is the maximum, got " + std::to_string(_size));

  _isSigned = isSigned;
  _int = 0;
  _x = 0;
  _z = 0;

  // if the binary string is smaller than the declared size, we need to trim the starting point
  size_t trimmedStart =
      size < binary.size() ? binary.size() - _size : 0;

  for (size_t i = trimmedStart; i < binary.size(); i++) {
    if (binary[i] == '1') {
      _int |= (ULogic(1) << (binary.size() - i - 1));
    } else if (binary[i] == 'x') {
      _x |= (ULogic(1) << (binary.size() - i - 1));
    } else if (binary[i] == 'z') {
      _z |= (ULogic(1) << (binary.size() - i - 1));
    }
  }
}

std::string Logic::toString() const {
  std::stringstream ss;
  if (_int == 0 && _x == 0 && _z == 0) {
    return "0";
  }

  for (int i = _size - 1; i >= 0; i--) {
    ss << (int)((_int & ((ULogic)1 << i)) > 0);
  }
  std::string intStr = ss.str();

  if (_x > 0 || _z > 0) {
    for (int i = _size - 1; i >= 0; i--) {
      if ((_x & ((ULogic)1 << i)) > 0) {
        intStr[_size - i - 1] = 'x';
      }
      if ((_z & ((ULogic)1 << i)) > 0) {
        intStr[_size - i - 1] = 'z';
      }
    }
  }

  auto cutFrom = intStr.find_first_not_of('0');
  if (cutFrom != std::string::npos) {
    intStr = intStr.substr(cutFrom);
  }

  return intStr;
}

Logic Logic::select(size_t lower_bound, size_t upper_bound) const {

  ULogic i = extractBits<ULogic>(_int, lower_bound, upper_bound);
  ULogic x = extractBits<ULogic>(_x, lower_bound, upper_bound);
  ULogic z = extractBits<ULogic>(_z, lower_bound, upper_bound);
  return Logic(upper_bound - lower_bound + 1, _isSigned, i, x, z);
}

Logic sum(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return Logic(1, 0, 0, 1, 0);
  } else {

    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    SLogic sum = op1 + op2;
    return Logic(resType.second, isSigned(resType.first), (ULogic)sum,
                 0, 0);
  }
  return Logic(1, 0, 0, 1, 0);
}

Logic sub(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return Logic(1, 0, 0, 1, 0);
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    SLogic sub = op1 - op2;
    return Logic(resType.second, isSigned(resType.first), (ULogic)sub,
                 0, 0);
  }
  return Logic(1, 0, 0, 1, 0);
}

Logic mul(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return Logic(1, 0, 0, 1, 0);
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    SLogic mul = op1 * op2;
    return Logic(resType.second, isSigned(resType.first), (ULogic)mul,
                 0, 0);
  }
  return Logic(1, 0, 0, 1, 0);
}
Logic div(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return Logic(1, 0, 0, 1, 0);
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    SLogic div = op1 / op2;
    return Logic(resType.second, isSigned(resType.first), (ULogic)div,
                 0, 0);
  }

  return Logic(1, 0, 0, 1, 0);
}
Logic band(const Logic &lhs, const Logic &rhs,
           const std::pair<ExpType, size_t> &resType) {

  SLogic op1 = isUnsigned(resType.first)
                   ? unsignedToSLogic(lhs._int, resType.second)
                   : signedToSLogic(lhs._int, resType.second);
  SLogic op2 = isUnsigned(resType.first)
                   ? unsignedToSLogic(rhs._int, resType.second)
                   : signedToSLogic(rhs._int, resType.second);
  ULogic lxz = lhs._x | lhs._z;
  ULogic rxz = rhs._x | rhs._z;
  ULogic xzToZero =
      (lxz & ~((ULogic)op2 | rxz)) | (rxz & ~((ULogic)op1 | lxz));
  SLogic int_ = op1 & op2 & ~xzToZero;
  ULogic newx = (lxz | rxz) & ~xzToZero;
  return Logic(resType.second, isSigned(resType.first), (ULogic)int_,
               newx, 0);
}
Logic bor(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {

  SLogic op1 = isUnsigned(resType.first)
                   ? unsignedToSLogic(lhs._int, resType.second)
                   : signedToSLogic(lhs._int, resType.second);
  SLogic op2 = isUnsigned(resType.first)
                   ? unsignedToSLogic(rhs._int, resType.second)
                   : signedToSLogic(rhs._int, resType.second);

  ULogic lxz = lhs._x | lhs._z;
  ULogic rxz = rhs._x | rhs._z;
  ULogic xzToOne = (lxz & (ULogic)op2) | (rxz & (ULogic)op1);
  SLogic int_ = op1 | op2 | xzToOne;
  ULogic newx = (lxz | rxz) & ~xzToOne;

  return Logic(resType.second, isSigned(resType.first), (ULogic)int_,
               newx, 0);
}
Logic bxor(const Logic &lhs, const Logic &rhs,
           const std::pair<ExpType, size_t> &resType) {

  SLogic op1 = isUnsigned(resType.first)
                   ? unsignedToSLogic(lhs._int, resType.second)
                   : signedToSLogic(lhs._int, resType.second);
  SLogic op2 = isUnsigned(resType.first)
                   ? unsignedToSLogic(rhs._int, resType.second)
                   : signedToSLogic(rhs._int, resType.second);

  ULogic lxz = lhs._x | lhs._z;
  ULogic rxz = rhs._x | rhs._z;
  SLogic int_ = (op1 ^ op2) & ~(lxz | rxz);
  ULogic newx = (lxz | rxz);

  return Logic(resType.second, isSigned(resType.first), (ULogic)int_,
               newx, 0);
}
Logic bls(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {

  SLogic op1 = isUnsigned(resType.first)
                   ? unsignedToSLogic(lhs._int, resType.second)
                   : signedToSLogic(lhs._int, resType.second);
  SLogic op2 = isUnsigned(resType.first)
                   ? unsignedToSLogic(rhs._int, resType.second)
                   : signedToSLogic(rhs._int, resType.second);
  messageWarningIf(op1 < 0, "left bit shift on negative values is "
                            "undefined behavior, got:" +
                                to_string(op1) + "");
  messageErrorIf(
      op2 < 0, "right side of left bit shift must be positive, got:" +
                   to_string(op2));
  messageErrorIf(op2 > resType.second,
                 "right side of left bit shift is greater than left "
                 "side size, got:" +
                     to_string(op2));
  SLogic int_ = op1 << (uint64_t)op2;
  ULogic x_ = lhs._x << (uint64_t)op2;
  ULogic z_ = lhs._z << (uint64_t)op2;
  return Logic(resType.second, isSigned(resType.first), (ULogic)int_,
               x_, z_);
}
Logic brs(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {

  SLogic op1 = isUnsigned(resType.first)
                   ? unsignedToSLogic(lhs._int, resType.second)
                   : signedToSLogic(lhs._int, resType.second);
  SLogic op2 = isUnsigned(resType.first)
                   ? unsignedToSLogic(rhs._int, resType.second)
                   : signedToSLogic(rhs._int, resType.second);
  messageErrorIf(
      op2 < 0,
      "right side of right bit shift must be positive, got:" +
          to_string(op2));
  messageErrorIf(op2 > resType.second,
                 "right side of right bit shift is greater than left "
                 "side size, got:" +
                     to_string(op2));
  SLogic int_ = op1 >> (uint64_t)op2;
  ULogic x_ = lhs._x >> (uint64_t)op2;
  ULogic z_ = lhs._z >> (uint64_t)op2;
  return Logic(resType.second, isSigned(resType.first), (ULogic)int_,
               x_, z_);
}

Logic bnot(const Logic &lhs,
           const std::pair<ExpType, size_t> &resType) {

  SLogic op1 = isUnsigned(resType.first)
                   ? unsignedToSLogic(lhs._int, resType.second)
                   : signedToSLogic(lhs._int, resType.second);
  SLogic _not = ~op1;

  return Logic(resType.second, isSigned(resType.first), (ULogic)_not,
               lhs._x | lhs._z, 0);
}
bool eq(const Logic &lhs, const Logic &rhs,
        const std::pair<ExpType, size_t> &resType) {
  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    return op1 == op2;
  }
  return 0;
}
bool neq(const Logic &lhs, const Logic &rhs,
         const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    return op1 != op2;
  }
  return 0;
}
bool gt(const Logic &lhs, const Logic &rhs,
        const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    return op1 > op2;
  }
  return 0;
}

bool gte(const Logic &lhs, const Logic &rhs,
         const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    return op1 >= op2;
  }
  return 0;
}

bool lt(const Logic &lhs, const Logic &rhs,
        const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    return op1 < op2;
  }
  return 0;
}

bool lte(const Logic &lhs, const Logic &rhs,
         const std::pair<ExpType, size_t> &resType) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = isUnsigned(resType.first)
                     ? unsignedToSLogic(lhs._int, resType.second)
                     : signedToSLogic(lhs._int, resType.second);
    SLogic op2 = isUnsigned(resType.first)
                     ? unsignedToSLogic(rhs._int, resType.second)
                     : signedToSLogic(rhs._int, resType.second);
    return op1 <= op2;
  }
  return 0;
}

bool operator==(const Logic &lhs, const Logic &rhs) {

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = !lhs._isSigned ? unsignedToSLogic(lhs._int, lhs._size)
                                : signedToSLogic(lhs._int, lhs._size);
    SLogic op2 = !rhs._isSigned ? unsignedToSLogic(rhs._int, rhs._size)
                                : signedToSLogic(rhs._int, rhs._size);
    return op1 == op2;
  }

  return true;
}

} // namespace expression
