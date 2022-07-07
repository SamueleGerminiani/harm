#pragma once

#include "VarType.hh"
#include "message.hh"

#include <algorithm>
#include <cstdint>
#include <utility>

namespace expression {
inline std::pair<VarType, size_t>
applyCStandardConversion(const std::pair<VarType, size_t> &e1,
                         const std::pair<VarType, size_t> &e2) {
  std::pair<VarType, size_t> curr_e1 = e1;
  std::pair<VarType, size_t> curr_e2 = e2;

  // DEBUG
  /*
  std::cout<<"INPUT:\n";
  std::cout<<curr_e1.first<<","<<(int)curr_e1.second<<" &&
  "<<curr_e2.first<<","<<(int)curr_e2.second<<"\n";
  */

  // Float & Double
  if (e1.first == VarType::Numeric) {
    if (e2.first != VarType::Numeric) {
      return std::make_pair(e1.first, e1.second);
    } else {
      return std::make_pair(e1.first, std::max(e1.second, e2.second));
    }
  } else if (e2.first == VarType::Numeric) {
    if (e1.first != VarType::Numeric) {
      return std::make_pair(e2.first, e2.second);
    } else {
      return std::make_pair(e2.first, std::max(e1.second, e2.second));
    }
  }

  // Integer promotion
  if (curr_e1.second < 32) {
    curr_e1.first = VarType::SLogic;
    curr_e1.second = 32;
  }
  if (curr_e2.second < 32) {
    curr_e2.first = VarType::SLogic;
    curr_e2.second = 32;
  }

  // Balancing

  // check if we must only extend the size (sign is the same)
  if (curr_e1.first == curr_e2.first) {
    curr_e1.second = std::max(curr_e1.second, curr_e2.second);
    curr_e2.second = std::max(curr_e1.second, curr_e2.second);
    messageErrorIf(
        !(curr_e1.first == curr_e2.first && curr_e1.second == curr_e2.second),
        "C conversion error");
    return std::make_pair(curr_e1.first, curr_e1.second);
  }

  // If both operand are still of different types
  if (curr_e1.first != curr_e2.first || curr_e1.second != curr_e2.second) {
    /* If one operand is interger and has conversion rank at least as high
     as the second operand*/
    if ((curr_e1.first == VarType::ULogic && e1.second >= e2.second) ||
        (curr_e2.first == VarType::ULogic && e2.second >= e1.second)) {
      // convert the other operand to unsigned
      if (curr_e1.first == VarType::ULogic && e1.second >= e2.second) {
        // convert second operand
        curr_e2.first = VarType::ULogic;
        curr_e2.second = curr_e1.second;

      } else {
        // convert first operand
        curr_e1.first = VarType::ULogic;
        curr_e1.second = curr_e2.second;
      }

    } else {
      /* Otherwise, there is a signed operand, if that operand can contain
       all the values of the unsigned one, convert the unsigned operand to
       signed*/
      if (curr_e1.first == VarType::SLogic) {
        // convert second operand
        if ((curr_e1.second - 1) >= curr_e2.second) {
          curr_e2.first = VarType::SLogic;
          curr_e2.second = curr_e1.second;
        } else {
          // Turn all to unsigned
          curr_e2.first = VarType::ULogic;
          curr_e2.second = curr_e1.second;
        }
      } else {
        // convert first operand
        if ((curr_e2.second - 1) >= curr_e1.second) {
          curr_e1.first = VarType::SLogic;
          curr_e1.second = curr_e2.second;
        } else {
          // Turn all to unsigned
          curr_e1.first = VarType::ULogic;
          curr_e1.second = curr_e2.second;
        }
      }
    }
  }

  // DEBUG
  /*
  std::cout<<"OUTPUT:\n";
  std::cout<<curr_e1.first<<","<<(int)curr_e2.second<<" &&
  "<<curr_e1.first<<","<<(int)curr_e2.second<<"\n";
  */
  messageErrorIf(
      !(curr_e1.first == curr_e2.first && curr_e1.second == curr_e2.second),
      "C conversion error");

  return std::make_pair(curr_e1.first, curr_e1.second);
}
} // namespace expression
