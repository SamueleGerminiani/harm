#pragma once
#include <iostream>

namespace expression {
enum class ExpType { Bool = 0, UInt, SInt, Float, Unknown };
inline std::ostream &operator<<(std::ostream &os, const ExpType &t) {
  switch (t) {
  case ExpType::Bool:
    os << "Bool";
    break;
  case ExpType::UInt:
    os << "UInt";
    break;
  case ExpType::SInt:
    os << "SInt";
    break;
  case ExpType::Float:
    os << "Float";
    break;
  case ExpType::Unknown:
    os << "Unknown";
    break;
  }

  return os;
}

inline std::string to_string(ExpType t) {
  switch (t) {
  case ExpType::Bool:
    return "Bool";
  case ExpType::UInt:
    return "UInt";
  case ExpType::SInt:
    return "SInt";
  case ExpType::Float:
    return "Float";
  case ExpType::Unknown:
    return "Unknown";
  }
  return "Unknown";
}

inline bool isFloat(ExpType t) { return t == ExpType::Float; }
inline bool isBool(ExpType t) { return t == ExpType::Bool; }
inline bool isInt(ExpType t) {
  return t == ExpType::UInt || t == ExpType::SInt;
}
inline bool isUnsigned(ExpType t) { return t == ExpType::UInt; }
inline bool isSigned(ExpType t) {
  return t == ExpType::SInt || t == ExpType::Float;
}
} // namespace expression
