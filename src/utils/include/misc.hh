#pragma once
#include <ostream>
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
