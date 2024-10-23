#pragma once

#include "colors.hh"
#include <iostream>

/** @enum Trinay
 *  @brief Used to store the truth values of an assertion on the trace
 */
enum class Trinary { F = 0, T, U };

inline std::ostream &operator<<(std::ostream &os, Trinary t) {
  switch (t) {
  case Trinary::T:
    os << BOOL("T");
    break;
  case Trinary::F:
    os << GLOB("F");
    break;
  case Trinary::U:
    os << VAR("U");
    break;
  }
  return os;
}

//Boolean operators with Trinary type

inline Trinary operator!(Trinary t) {
  return (t == Trinary::U)   ? Trinary::U
         : (t == Trinary::T) ? Trinary::F
                             : Trinary::T;
}
inline Trinary operator||(Trinary t1, Trinary t2) {
  if (t1 == Trinary::U || t2 == Trinary::U)
    return Trinary::U;

  if (t1 == Trinary::T || t2 == Trinary::T)
    return Trinary::T;

  return Trinary::F;
}
inline Trinary operator&&(Trinary t1, Trinary t2) {
  if (t1 == Trinary::U || t2 == Trinary::U)
    return Trinary::U;

  if (t1 == Trinary::T && t2 == Trinary::T)
    return Trinary::T;

  return Trinary::F;
}
