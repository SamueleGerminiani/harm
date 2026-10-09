#pragma once

#include "ExpType.hh"
#include "message.hh"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>

namespace expression {
/// the common type of two operands; since D-035, SystemVerilog's rules (the name is historical)
inline std::pair<ExpType, size_t>
applyCStandardConversion(const std::pair<ExpType, size_t> &e1,
                         const std::pair<ExpType, size_t> &e2) {

  std::pair<ExpType, size_t> curr_e1 = e1;
  std::pair<ExpType, size_t> curr_e2 = e2;

  messageErrorIf((e1.first == ExpType::Float && e1.second == 32) ||
                     (e2.first == ExpType::Float && e2.second == 32),
                 "float no longer supported, must use double");
  messageErrorIf(e1.first == ExpType::String ||
                     e2.first == ExpType::String,
                 "string type no supported in C conversion");

  // Float & Double
  if (curr_e1.first == ExpType::Float &&
      curr_e2.first != ExpType::Float) {
    return curr_e1;
  } else if (curr_e2.first == ExpType::Float &&
             curr_e1.first != ExpType::Float) {
    return curr_e2;
  } else if (curr_e2.first == ExpType::Float &&
             curr_e1.first == ExpType::Float) {
    return curr_e1.second > curr_e2.second ? curr_e1 : curr_e2;
  }

  messageErrorIf(
      !((isInt(curr_e1.first) || isLogic(curr_e1.first)) &&
        (isInt(curr_e2.first) || isLogic(curr_e2.first))),
      "C conversion error: types should be both integers or logics "
      "at this point, instead got: " +
          to_string(curr_e1.first) + " and " +
          to_string(curr_e2.first));

  // D-035: SystemVerilog's rules (IEEE 1800-2017 11.8.1), for every operation:
  //  - the result is unsigned if any operand is unsigned, signed if both are signed;
  //  - it is as wide as the wider operand; a C integer narrower than 32 bits counts as 32 bits
  //    wide (C's promotion, and SystemVerilog's 32-bit context of an unsized literal); its
  //    signedness is unchanged (the operations extend each operand from its own width);
  //  - it is a 4-state logic if any operand is a logic, a 2-valued integer otherwise.
  auto width = [](const std::pair<ExpType, size_t> &e) {
    return isInt(e.first) && e.second < 32 ? (size_t)32 : e.second;
  };
  const bool sgn = isSigned(curr_e1.first) && isSigned(curr_e2.first);
  const bool logic = isLogic(curr_e1.first) || isLogic(curr_e2.first);
  const size_t w = std::max(width(curr_e1), width(curr_e2));
  curr_e1.first = logic ? (sgn ? ExpType::SLogic : ExpType::ULogic)
                        : (sgn ? ExpType::SInt : ExpType::UInt);
  curr_e1.second = w;
  curr_e2 = curr_e1;

  messageErrorIf(!(curr_e1.first == curr_e2.first &&
                   curr_e1.second == curr_e2.second),
                 "C conversion error");

  return std::make_pair(curr_e1.first, curr_e1.second);
}
} // namespace expression
