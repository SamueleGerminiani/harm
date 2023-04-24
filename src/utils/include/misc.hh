#pragma once
#include <ostream>
#include <iostream>
#include <string>

template <typename T>
inline std::string to_string_with_precision(const T a_value, const int n = 6) {
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return out.str();
}
inline int **copy_matrix(int **mat, int size1, int size2) {
  int row;
  int **res = new int *[size1];
  for (row = 0; row < size1; row++) {
    res[row] = new int[size2];
    memcpy(res[row], mat[row], size2 * sizeof(int));
  }
  return res;
}
void inline systemCustom(std::string command) {
  int status = system(command.c_str());
  if (status < 0) {
    std::cout << "System error: " << '\n';
  } else {
    if (!WIFEXITED(status)) {
      std::cout << "Program exited abnormaly\n";
    }
  }
}

inline std::string selectStringAfter(std::string str, std::string pattern) {
  // Find the position of the pattern in the string
  size_t pos = str.find(pattern);

  // If the pattern is not found, return an empty string
  if (pos == std::string::npos) {
    return "";
  }

  // Return the substring after the pattern
  return str.substr(pos + pattern.length());
}

inline bool patternExists(std::string str, std::string pattern) {
    // Find the position of the pattern in the string
    size_t pos = str.find(pattern);

    // If the pattern is found, return true
    if (pos != std::string::npos) {
        return true;
    }

    // If the pattern is not found, return false
    return false;
}
