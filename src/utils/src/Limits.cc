#include "Limits.hh"
#include "Float.hh"
#include "Int.hh"
#include "Logic.hh"
#include "message.hh"
#include <cstddef>
#include <type_traits>

using namespace expression;

//--------------------max---------------------

template <> Float max(size_t nBits) {
  return std::numeric_limits<Float>::max();
}

template <> bool max(size_t nBits) {
  return std::numeric_limits<bool>::max();
}

template <> SLogic max(size_t nBits) {
  messageErrorIf(nBits < 2 || nBits > sizeOfLogic() * 8 - 1,
                 "nBits must be between 2 and " +
                     std::to_string(sizeOfLogic() * 8 - 1) +
                     " for type SLogic");
  return Logic(nBits, 1, (ULogic)((SLogic)1 << (nBits - 1)) - 1, 0, 0)
      .getSignedValue();
}

template <> ULogic max(size_t nBits) {
  messageErrorIf(nBits < 1 || nBits > sizeOfLogic() * 8 - 1,
                 "nBits must be between 1 and " +
                     std::to_string(sizeOfLogic() * 8 - 1) +
                     " for type ULogic, got " +
                     std::to_string(nBits));
  return Logic(nBits, 0, std::numeric_limits<ULogic>::max(), 0, 0)
      .getUnsignedValue();
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

template <> SLogic min(size_t nBits) {
  messageErrorIf(nBits < 2 || nBits > sizeOfLogic() * 8 - 1,
                 "nBits must be between 2 and " +
                     std::to_string(sizeOfLogic() * 8 - 1) +
                     " for type SLogic");
  return Logic(nBits, 1, (ULogic)((ULogic)1 << (nBits - 1)), 0, 0)
      .getSignedValue();
}
template <> ULogic min(size_t nBits) { return (ULogic)0; }

template <> UInt min(size_t nBits) { return (UInt)0; }

template <> SInt min(size_t nBits) {
  messageErrorIf(nBits < 2 || nBits > sizeof(UInt) * 8,
                 "nBits must be between 2 and " +
                     std::to_string(sizeof(UInt) * 8) +
                     " for type SInt");
  SInt absValues = std::numeric_limits<SInt>::min();
  size_t shift = sizeof(UInt) * 8 - nBits;
  return (SInt)(absValues >> shift);
}
