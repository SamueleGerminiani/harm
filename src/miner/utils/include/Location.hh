#pragma once
#include <iostream>
#include <limits.h>

namespace harm {
/** @enum Location
 *  @brief Used to specify where to execute a certain procedure or to specify where a certain item belongs
 */
enum class Location { Ant = INT_MIN, Con, AntCon, DecTree, None };

inline std::ostream &operator<<(std::ostream &os,
                                const Location &loc) {
  switch (loc) {
  case Location::Ant:
    os << "Ant";
    break;
  case Location::Con:
    os << "Con";
    break;
  case Location::AntCon:
    os << "AntCon";
    break;
  case Location::DecTree:
    os << "DecTree";
    break;
  case Location::None:
    os << "None";
    break;
  }
  return os;
}

inline std::string toString(const Location &loc) {
  switch (loc) {
  case Location::Ant:
    return "Ant";
  case Location::Con:
    return "Con";
  case Location::AntCon:
    return "AntCon";
  case Location::DecTree:
    return "DecTree";
  case Location::None:
    return "None";
  }
  return "";
}

inline std::string domainIdToString(int domainId) {
  if (toString((Location)domainId) != "") {
    return toString((Location)domainId);
  } else {
    return std::to_string(domainId);
  }
}

inline std::string getDomainType(int domainId) {
  if (toString((Location)domainId) != "") {
    return "Global";
  } else {
    return "Restricted";
  }
}

} // namespace harm
