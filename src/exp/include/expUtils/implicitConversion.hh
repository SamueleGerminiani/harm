#pragma once

#include "ExpType.hh"
#include "message.hh"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>

namespace expression {
inline std::pair<ExpType, size_t>
applyCStandardConversion(const std::pair<ExpType, size_t> &e1,
                         const std::pair<ExpType, size_t> &e2) {

  std::pair<ExpType, size_t> curr_e1 = e1;
  std::pair<ExpType, size_t> curr_e2 = e2;

  messageErrorIf((e1.first == ExpType::Float && e1.second == 32) ||
                     (e2.first == ExpType::Float && e2.second == 32),
                 "float no longer supported, must use double");

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

  // If both operands are integers (or logics), then, integer promotions (logic promotion):
  if ((isInt(curr_e1.first) /* || isLogic(curr_e1.first)*/) &&
      curr_e1.second < 32) {
    curr_e1.first = ExpType::SInt;
    curr_e1.second = 32;
  }
  if ((isInt(curr_e2.first) /* || isLogic(curr_e2.first)*/) &&
      curr_e2.second < 32) {
    curr_e2.first = ExpType::SInt;
    curr_e2.second = 32;
  }

  //if both share the same type, then that is the common type
  if (curr_e1 == curr_e2) {
    return curr_e1;
  }

  // If the types have the same signedness (both signed or both unsigned), the operand whose type has the lesser conversion rank1 is implicitly converted2 to the other type (simply extend he size)
  if (curr_e1.first == curr_e2.first) {
    curr_e1.second = std::max(curr_e1.second, curr_e2.second);
    curr_e2.second = std::max(curr_e1.second, curr_e2.second);
    //the type must be the same after balancing
    messageErrorIf(curr_e1 != curr_e2, "C conversion error");
    return std::make_pair(curr_e1.first, curr_e1.second);
  }

  //if types are still different
  if (curr_e1 != curr_e2) {
    messageErrorIf(
        (isSigned(curr_e1.first) && isSigned(curr_e2.first)) ||
            (isUnsigned(curr_e1.first) && isUnsigned(curr_e2.first)),
        "C conversion error: operands should have different "
        "signedness at "
        "this point");
    // operands have different sign

    /* If the unsigned type has conversion rank greater than or equal to the rank of the signed type, then the operand with the signed type is implicitly converted to the unsigned type.
       */
    if ((isUnsigned(curr_e1.first) &&
         curr_e1.second > curr_e2.second) ||
        (isUnsigned(curr_e2.first) &&
         curr_e2.second > curr_e1.second)) {
      // convert the other operand to unsigned
      if (isUnsigned(curr_e1.first)) {
        // convert second operand
        curr_e2 = curr_e1;
      } else {
        // convert first operand
        curr_e1 = curr_e2;
      }

    } else {
      //Else, the unsigned type has conversion rank less than the signed type:

      /* If the signed type can represent all values of the unsigned type, then the operand with the unsigned type is implicitly converted to the signed type.
       */
      if ((isSigned(curr_e1.first) &&
           (curr_e1.second - 1) >= curr_e2.second) ||
          (isSigned(curr_e2.first) &&
           (curr_e2.second - 1) >= curr_e1.second)) {

        if (isSigned(curr_e1.first)) {
          // convert second operand
          curr_e2 = curr_e1;
        } else {
          // convert first operand
          curr_e1 = curr_e2;
        }

      } else {
        /*Else, both operands undergo implicit conversion to the unsigned type counterpart of the signed operand's type.*/
        curr_e1.first =
            isUnsigned(curr_e1.first) ? curr_e1.first : curr_e2.first;
        curr_e2.first =
            isUnsigned(curr_e1.first) ? curr_e1.first : curr_e2.first;
        curr_e1.second = std::max(curr_e1.second, curr_e2.second);
        curr_e2.second = std::max(curr_e1.second, curr_e2.second);
      }
    }
  }

  messageErrorIf(!(curr_e1.first == curr_e2.first &&
                   curr_e1.second == curr_e2.second),
                 "C conversion error");

  return std::make_pair(curr_e1.first, curr_e1.second);
}
} // namespace expression
