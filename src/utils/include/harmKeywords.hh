#pragma once
#include <string>
#include <unordered_set>

namespace harm {

/// H23 (D-037): HARM's keywords and the temporal grammar's operator words. A variable with one of
/// these names is declared as any other, and written in a formula as a SystemVerilog escaped
/// identifier ('\W ': a backslash, the name, a blank); a bare keyword keeps its meaning.
inline const std::unordered_set<std::string> &keywordNames() {
  static const std::unordered_set<std::string> names = {
      "inside", "true", "false", "substr", "and", "or", "not", "eventually", "s_eventually",
      "nexttime", "next", "X", "until", "W", "always", "G", "first_match", "F", "R", "intersect"};
  return names;
}

inline bool isKeywordName(const std::string &name) { return keywordNames().count(name) != 0; }

/// '\name ', the escaped form of a variable's name
inline std::string escapedName(const std::string &name) { return "\\" + name + " "; }

} // namespace harm
