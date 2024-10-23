#include "Limits.hh"
#include "Float.hh"
#include "Int.hh"
#include "message.hh"
#include <cstddef>
#include <limits>
#include <type_traits>

using namespace expression;

//--------------------max---------------------

template <> Float max(size_t nBits) {
  return std::numeric_limits<Float>::max();
}

template <> bool max(size_t nBits) {
  return std::numeric_limits<bool>::max();
}

template <> UInt max(size_t nBits) {
  messageErrorIf(nBits < 1 || nBits > sizeof(UInt) * 8,
                 "nBits must be between 1 and " +
                     std::to_string(sizeof(UInt) * 8) +
                     " for type SUnt");
  auto absValues = std::numeric_limits<UInt>::max();
  size_t shift = sizeof(UInt) * 8 - nBits;
  return (absValues << shift) >> shift;
}

template <> SInt max(size_t nBits) {
  messageErrorIf(nBits < 2 || nBits > sizeof(UInt) * 8,
                 "nBits must be between 2 and " +
                     std::to_string(sizeof(UInt) * 8) +
                     " for type SInt");
  UInt absValues = std::numeric_limits<UInt>::max();
  size_t shift = (sizeof(UInt) * 8 - nBits) + 1;
  return (SInt)((absValues << shift) >> shift);
}

//--------------------min---------------------

template <> Float min(size_t nBits) {
  return std::numeric_limits<Float>::min();
}

template <> bool min(size_t nBits) {
  return std::numeric_limits<bool>::min();
}

