#pragma once
#include <iostream>

namespace expression {
enum class ExpType {
  Bool = 0,
  UInt,
  SInt,
  ULogic,
  SLogic,
  Float,
  String,
  Unknown
};
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
  case ExpType::ULogic:
    os << "ULogic";
    break;
  case ExpType::SLogic:
    os << "SLogic";
    break;
  case ExpType::Float:
    os << "Float";
    break;
  case ExpType::String:
    os << "String";
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
  case ExpType::ULogic:
    return "ULogic";
  case ExpType::SLogic:
    return "SLogic";
  case ExpType::Float:
    return "Float";
  case ExpType::String:
    return "String";
  case ExpType::Unknown:
    return "Unknown";
  }
  return "Unknown";
}

inline bool isString(ExpType t) { return t == ExpType::String; }
inline bool isFloat(ExpType t) { return t == ExpType::Float; }
inline bool isBool(ExpType t) { return t == ExpType::Bool; }
inline bool isInt(ExpType t) {
  return t == ExpType::UInt || t == ExpType::SInt;
}
inline bool isLogic(ExpType t) {
  return t == ExpType::ULogic || t == ExpType::SLogic;
}
inline bool isUnsigned(ExpType t) {
  return t == ExpType::UInt || t == ExpType::ULogic;
}
inline bool isSigned(ExpType t) {
  return t == ExpType::SInt || t == ExpType::SLogic ||
         t == ExpType::Float;
}
} // namespace expression
