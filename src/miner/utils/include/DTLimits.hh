#pragma once

#include "colors.hh"
#include "message.hh"
#include <iostream>

namespace harm {

/*! \enum class DTHeuristic
     *
     *  What type of heuristic to use for DT operations
     */
enum class DTHeuristic { ENTROPY, COVERAGE, UNSET };

enum class DTO_Type { And, Next, NextAnd, NCReps, GoTo, None };

///to string
inline std::string toString(const DTHeuristic &heur) {
  switch (heur) {
  case DTHeuristic::ENTROPY:
    return "ENTROPY";
  case DTHeuristic::COVERAGE:
    return "COVERAGE";
  case DTHeuristic::UNSET:
    return "UNSET";
  }
  return "UNSET";
}

inline std::string toString(const DTO_Type &type) {
  switch (type) {
  case DTO_Type::And:
    return "..&&..";
  case DTO_Type::Next:
    return "..##..";
  case DTO_Type::NextAnd:
    return "..#&..";
  case DTO_Type::NCReps:
    return "..[=]..";
  case DTO_Type::GoTo:
    return "..[->]..";
  case DTO_Type::None:
    return "None";
  }
  messageError("Unknown DTO_Type");
  return "";
}

inline std::string toColoredString(const DTO_Type &type) {
  switch (type) {
  case DTO_Type::And:
    return BOOL("..&&..");
  case DTO_Type::Next:
    return TEMP("..##..");
  case DTO_Type::NextAnd:
    return TEMP("..#&..");
  case DTO_Type::NCReps:
    return TEMP("..[=]..");
  case DTO_Type::GoTo:
    return TEMP("..[->]..");
  case DTO_Type::None:
    return "None";
  }
  messageError("Unknown DTO_Type");
  return "";
}

///ovveride cout for DTHeuristic
inline std::ostream &operator<<(std::ostream &os,
                                const DTHeuristic &heur) {
  os << toString(heur);
  return os;
}

///ovveride cout for DTO_Type
inline std::ostream &operator<<(std::ostream &os,
                                const DTO_Type &type) {
  os << toString(type);
  return os;
}

struct DTOParam {
  size_t _step = 0;
  std::string _separator = "";
  DTO_Type _type = DTO_Type::None;
};
struct DTLimits {
  DTLimits(const DTLimits &o) = default;

  DTLimits() {}

  size_t _maxDepth = 3;
  size_t _maxWidth = 3;
  size_t _maxAll = 3;
  double _effort = -0.1f;
  bool _isUnordered = 0;
  bool _saveOffset = 0;
  bool _useNegatedProps = 1;
  DTHeuristic _heuristic = DTHeuristic::COVERAGE;
  bool _requirePerfectFitness = 0;
  DTOParam _dto_param;
  bool _dontReuseNumeric = 0;
  bool _dontReuseProp = 0;
};
} // namespace harm
