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

namespace {
ULogic maskOf(size_t width) {
  return width == 0 ? ULogic(0) : ((ULogic(1) << width) - 1);
}
} // namespace

/// D-035: an operand as SystemVerilog extends it to the result (IEEE 1800-2017 11.8.2): from
/// its own width, sign-extended when the result is signed (both operands are then signed),
/// zero-extended otherwise; x and z bits extend with it
static Logic operandAt(const Logic &l, const std::pair<ExpType, size_t> &resType) {
  const size_t width = std::max(resType.second, l._size);
  const bool signExtend = isSigned(resType.first) && l._isSigned;
  ULogic m = maskOf(l._size);
  ULogic x = l._x & m, z = l._z & m;
  ULogic i = l._int & m & ~(x | z);
  if (signExtend && l._size > 0 && width > l._size) {
    ULogic high = maskOf(width) & ~m;
    ULogic msb = ULogic(1) << (l._size - 1);
    if (x & msb) {
      x |= high;
    } else if (z & msb) {
      z |= high;
    } else if (i & msb) {
      i |= high;
    }
  }
  ULogic rm = maskOf(resType.second);
  return Logic(resType.second, isSigned(resType.first), i & rm, x & rm, z & rm);
}

/// D-035: an all-x value of the result type (an arithmetic operand with x/z, a division by
/// zero: IEEE 1800-2017 11.4.2)
static Logic allX(const std::pair<ExpType, size_t> &resType) {
  return Logic(resType.second, isSigned(resType.first), 0, maskOf(resType.second), 0);
}

/// D-035: an operand's value for an operation of type resType, as SystemVerilog extends it: its
/// own-width value, sign-extended when the result and the operand are signed, zero-extended
/// otherwise (one conversion: the fast path of operandAt, for the value bits)
static inline SLogic valueAt(const Logic &l, const std::pair<ExpType, size_t> &resType) {
  return isSigned(resType.first) && l._isSigned ? signedToSLogic(l._int, l._size)
                                                : unsignedToSLogic(l._int, l._size);
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

Logic sum(const Logic &lhs_, const Logic &rhs_,
          const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return allX(resType);
  } else {

    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    SLogic sum = op1 + op2;
    return Logic(resType.second, isSigned(resType.first), (ULogic)sum,
                 0, 0);
  }
  return allX(resType);
}

Logic sub(const Logic &lhs_, const Logic &rhs_,
          const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return allX(resType);
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    SLogic sub = op1 - op2;
    return Logic(resType.second, isSigned(resType.first), (ULogic)sub,
                 0, 0);
  }
  return allX(resType);
}

Logic mul(const Logic &lhs_, const Logic &rhs_,
          const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return allX(resType);
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    SLogic mul = op1 * op2;
    return Logic(resType.second, isSigned(resType.first), (ULogic)mul,
                 0, 0);
  }
  return allX(resType);
}
Logic div(const Logic &lhs_, const Logic &rhs_,
          const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return allX(resType);
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    if (op2 == 0) {
      return allX(resType);
    }
    SLogic div = op1 / op2;
    return Logic(resType.second, isSigned(resType.first), (ULogic)div,
                 0, 0);
  }

  return allX(resType);
}
namespace {
ULogic lowMask(size_t width) {
  return width == 0 ? ULogic(0) : ((ULogic(1) << width) - 1);
}

/// the value of 'l' extended (or kept) to 'width' bits, with the bits above its size cleaned
Logic extendTo(const Logic &l, size_t width, bool signExtend) {
  ULogic m = lowMask(l._size);
  ULogic x = l._x & m, z = l._z & m;
  ULogic i = l._int & m & ~(x | z);
  if (signExtend && l._size > 0 && width > l._size) {
    ULogic high = lowMask(width) & ~m;
    ULogic msb = ULogic(1) << (l._size - 1);
    if (x & msb) {
      x |= high;
    } else if (z & msb) {
      z |= high;
    } else if (i & msb) {
      i |= high;
    }
  }
  return Logic(width, l._isSigned, i, x, z);
}
} // namespace

Logic resize(const Logic &l, size_t width, bool signExtend) {
  if (width <= l._size) {
    ULogic m = lowMask(width);
    return Logic(width, l._isSigned, l._int & m, l._x & m, l._z & m);
  }
  return extendTo(l, width, signExtend);
}

Logic concat(const std::vector<Logic> &items) {
  size_t width = 0;
  ULogic i = 0, x = 0, z = 0;
  for (const auto &item : items) {
    width += item._size;
    messageErrorIf(width > (sizeOfLogic() * 8) - 1,
                   "Concatenation is wider than the maximum logic size (" +
                       std::to_string((sizeOfLogic() * 8) - 1) + ")");
    Logic l = extendTo(item, item._size, false);
    i = (i << item._size) | l._int;
    x = (x << item._size) | l._x;
    z = (z << item._size) | l._z;
  }
  return Logic(width, false, i, x, z);
}

bool caseEq(const Logic &lhs, const Logic &rhs) {
  size_t width = std::max(lhs._size, rhs._size);
  bool signExtend = lhs._isSigned && rhs._isSigned;
  Logic l = extendTo(lhs, width, signExtend);
  Logic r = extendTo(rhs, width, signExtend);
  return l._int == r._int && l._x == r._x && l._z == r._z;
}

Logic band(const Logic &lhs_, const Logic &rhs_,
           const std::pair<ExpType, size_t> &resType) {
  // D-035: with x or z bits, both operands fully extended (x/z included); otherwise their
  // values from their own width (valueAt), the fast path
  const bool xz = lhs_.containsXZ() || rhs_.containsXZ();
  Logic lx, rx;
  if (xz) {
    lx = operandAt(lhs_, resType);
    rx = operandAt(rhs_, resType);
  }
  const Logic &lhs = xz ? lx : lhs_;
  const Logic &rhs = xz ? rx : rhs_;

  SLogic op1 = valueAt(lhs, resType);
  SLogic op2 = valueAt(rhs, resType);
  ULogic lxz = lhs._x | lhs._z;
  ULogic rxz = rhs._x | rhs._z;
  ULogic xzToZero =
      (lxz & ~((ULogic)op2 | rxz)) | (rxz & ~((ULogic)op1 | lxz));
  SLogic int_ = op1 & op2 & ~xzToZero;
  ULogic newx = (lxz | rxz) & ~xzToZero;
  return Logic(resType.second, isSigned(resType.first), (ULogic)int_,
               newx, 0);
}
Logic bor(const Logic &lhs_, const Logic &rhs_,
          const std::pair<ExpType, size_t> &resType) {
  // D-035: with x or z bits, both operands fully extended (x/z included); otherwise their
  // values from their own width (valueAt), the fast path
  const bool xz = lhs_.containsXZ() || rhs_.containsXZ();
  Logic lx, rx;
  if (xz) {
    lx = operandAt(lhs_, resType);
    rx = operandAt(rhs_, resType);
  }
  const Logic &lhs = xz ? lx : lhs_;
  const Logic &rhs = xz ? rx : rhs_;

  SLogic op1 = valueAt(lhs, resType);
  SLogic op2 = valueAt(rhs, resType);

  ULogic lxz = lhs._x | lhs._z;
  ULogic rxz = rhs._x | rhs._z;
  ULogic xzToOne = (lxz & (ULogic)op2) | (rxz & (ULogic)op1);
  SLogic int_ = op1 | op2 | xzToOne;
  ULogic newx = (lxz | rxz) & ~xzToOne;

  return Logic(resType.second, isSigned(resType.first), (ULogic)int_,
               newx, 0);
}
Logic bxor(const Logic &lhs_, const Logic &rhs_,
           const std::pair<ExpType, size_t> &resType) {
  // D-035: with x or z bits, both operands fully extended (x/z included); otherwise their
  // values from their own width (valueAt), the fast path
  const bool xz = lhs_.containsXZ() || rhs_.containsXZ();
  Logic lx, rx;
  if (xz) {
    lx = operandAt(lhs_, resType);
    rx = operandAt(rhs_, resType);
  }
  const Logic &lhs = xz ? lx : lhs_;
  const Logic &rhs = xz ? rx : rhs_;

  SLogic op1 = valueAt(lhs, resType);
  SLogic op2 = valueAt(rhs, resType);

  ULogic lxz = lhs._x | lhs._z;
  ULogic rxz = rhs._x | rhs._z;
  SLogic int_ = (op1 ^ op2) & ~(lxz | rxz);
  ULogic newx = (lxz | rxz);

  return Logic(resType.second, isSigned(resType.first), (ULogic)int_,
               newx, 0);
}
/// D-035: shifts as SystemVerilog's (IEEE 1800-2017 11.4.10): the amount is unsigned and
/// self-determined (its own width); an x/z amount gives x; a shift by the result's width or more
/// gives 0 (>>> of a negative signed value: all ones); << and >> fill with 0, >>> with the sign
/// bit (x and z included) of a signed result
static Logic shift(const Logic &lhs_, const Logic &rhs,
                   const std::pair<ExpType, size_t> &resType, int kind) {
  const size_t w = resType.second;
  const bool sgn = isSigned(resType.first);
  if (rhs.containsXZ()) {
    return allX(resType);
  }
  const Logic l = operandAt(lhs_, resType);
  ULogic n = rhs._int & maskOf(rhs._size);
  ULogic m = maskOf(w);
  ULogic i = l._int, x = l._x, z = l._z;
  if (kind == 0) {
    if (n >= w) {
      return Logic(w, sgn, 0, 0, 0);
    }
    size_t k = (size_t)n;
    return Logic(w, sgn, (i << k) & m, (x << k) & m, (z << k) & m);
  }
  const bool arithmetic = kind == 2 && sgn && w > 0;
  ULogic msb = w > 0 ? ULogic(1) << (w - 1) : ULogic(0);
  // the fill: 0, or the sign bit for >>> on a signed result
  ULogic fi = 0, fx = 0, fz = 0;
  if (arithmetic) {
    fx = (x & msb) ? m : ULogic(0);
    fz = (z & msb) ? m : ULogic(0);
    fi = (!(x & msb) && !(z & msb) && (i & msb)) ? m : ULogic(0);
  }
  if (n >= w) {
    return Logic(w, sgn, fi, fx, fz);
  }
  size_t k = (size_t)n;
  ULogic top = m & ~(m >> k);
  return Logic(w, sgn, (i >> k) | (fi & top), (x >> k) | (fx & top),
               (z >> k) | (fz & top));
}
Logic bls(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {
  return shift(lhs, rhs, resType, 0);
}
Logic brs(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType) {
  return shift(lhs, rhs, resType, 1);
}
Logic bars(const Logic &lhs, const Logic &rhs,
           const std::pair<ExpType, size_t> &resType) {
  return shift(lhs, rhs, resType, 2);
}

Logic bnot(const Logic &lhs_,
           const std::pair<ExpType, size_t> &resType) {
  if (!lhs_.containsXZ()) {
    // the fast path: the value from its own width, inverted (bits above the width are ignored
    // by every reader, which extends from the width)
    return Logic(resType.second, isSigned(resType.first),
                 (ULogic)(~valueAt(lhs_, resType)), 0, 0);
  }
  const Logic lhs = operandAt(lhs_, resType);
  // D-035: an x or z bit stays x, and its value bit stays 0 (the truth test reads value bits)
  ULogic xz = lhs._x | lhs._z;
  ULogic int_ = ~lhs._int & maskOf(resType.second) & ~xz;
  return Logic(resType.second, isSigned(resType.first), int_, xz, 0);
}
bool eq(const Logic &lhs_, const Logic &rhs_,
        const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;
  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    return op1 == op2;
  }
  return 0;
}
bool neq(const Logic &lhs_, const Logic &rhs_,
         const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    return op1 != op2;
  }
  return 0;
}
bool gt(const Logic &lhs_, const Logic &rhs_,
        const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    return op1 > op2;
  }
  return 0;
}

bool gte(const Logic &lhs_, const Logic &rhs_,
         const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    return op1 >= op2;
  }
  return 0;
}

bool lt(const Logic &lhs_, const Logic &rhs_,
        const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
    return op1 < op2;
  }
  return 0;
}

bool lte(const Logic &lhs_, const Logic &rhs_,
         const std::pair<ExpType, size_t> &resType) {
  // D-035: values extended from their own width (valueAt); x/z handled before
  const Logic &lhs = lhs_;
  const Logic &rhs = rhs_;

  if (lhs.containsXZ() || rhs.containsXZ()) {
    return 0;
  } else {
    SLogic op1 = valueAt(lhs, resType);
    SLogic op2 = valueAt(rhs, resType);
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
