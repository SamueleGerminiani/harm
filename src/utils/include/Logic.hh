#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <boost/multiprecision/number.hpp>
#include <stddef.h>
#include <string>
#include <utility>
#include <variant>

namespace expression {
enum class ExpType;
}

namespace expression {
using ULogic = boost::multiprecision::uint512_t;
using SLogic = boost::multiprecision::int512_t;
SLogic signedToSLogic(ULogic a, size_t size);
SLogic usignedToSLogic(ULogic a, size_t size);

//return the size of the logic in bytes, 16 bytes are used by boost for the sign
inline size_t sizeOfLogic() { return sizeof(SLogic) - 16; }

class Logic {
public:
  Logic();
  /// @brief Construct a Logic object from an integer
  Logic(size_t size, bool isSigned, ULogic int_, ULogic x, ULogic z);
  /// @brief Construct a Logic object from a string
  Logic(const std::string &binary, size_t size = (size_t)-1,
        bool isSigned = false);
  ~Logic() = default;
  /// @brief Get the content of the Logic object as unsigned integer
  ULogic getUnsignedValue() const;
  /// @brief Get the content of the Logic object as signed integerq
  SLogic getSignedValue() const;
  /// @brief Print the content of the Logic object as binary string
  std::string toString() const;
  /// @brief Bit selection
  Logic select(size_t lower_bound, size_t upper_bound) const;
  /// @brief true if the Logic object containts logic
  bool containsXZ() const;

  ///number of bits
  size_t _size = 0;
  ///true if signed
  bool _isSigned;
  ///integer content
  ULogic _int;
  ///all the 1s in the binary representation are the Xs in the logic, these values are 0s in _int
  ULogic _x;
  ///all the 1s in the binary representation are the Zs in the logic, these values are 0s in _int
  ULogic _z;
};

//the following functions need the result type to handle implicit conversions

Logic sum(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType);
Logic sub(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType);
Logic mul(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType);
Logic div(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType);
Logic band(const Logic &lhs, const Logic &rhs,
           const std::pair<ExpType, size_t> &resType);
Logic bor(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType);
Logic bxor(const Logic &lhs, const Logic &rhs,
           const std::pair<ExpType, size_t> &resType);
Logic bls(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType);
Logic brs(const Logic &lhs, const Logic &rhs,
          const std::pair<ExpType, size_t> &resType);
Logic bnot(const Logic &lhs,
           const std::pair<ExpType, size_t> &resType);
bool eq(const Logic &lhs, const Logic &rhs,
        const std::pair<ExpType, size_t> &resType);
bool neq(const Logic &lhs, const Logic &rhs,
         const std::pair<ExpType, size_t> &resType);
bool gt(const Logic &lhs, const Logic &rhs,
        const std::pair<ExpType, size_t> &resType);

bool gte(const Logic &lhs, const Logic &rhs,
         const std::pair<ExpType, size_t> &resType);

bool lt(const Logic &lhs, const Logic &rhs,
        const std::pair<ExpType, size_t> &resType);

bool lte(const Logic &lhs, const Logic &rhs,
         const std::pair<ExpType, size_t> &resType);

/// @brief Can be used safely only if both lhs and rhs have same the type
bool operator==(const Logic &lhs, const Logic &rhs);

} // namespace expression

/// @brief Hash function for Logic objects
template <> struct std::hash<expression::Logic> {
  std::string operator()(const expression::Logic &k) const {
    return k.toString();
  }
};
