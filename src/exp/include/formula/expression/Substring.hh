#pragma once

#include "formula/atom/Atom.hh"

namespace expression {

/// @brief This class represents the substring operator, same syntax and semantics as in C++
class Substring : public StringExpression {

public:
  Substring(StringExpressionPtr e, size_t start,
            size_t nChars = (size_t)-1);

  Substring(const Substring &other) = delete;

  virtual ~Substring();

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  /// @brief Return the expression of the next operator
  /// @return A reference to the expression.
  StringExpressionPtr &getItem();

  /// @brief Return the expression of the next operator
  /// @return A reference to the expression.
  String toString();
  String toColoredString();

  /// @brief Assing operator
  Substring &operator=(const Substring &other) = delete;

  /// @brief Return the start index of the substring
  size_t getStartIndex();
  /// @brief Return the number of characters to be extracted
  size_t getNChars();

private:
  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  /// @brief The input string
  StringExpressionPtr _e;
  /// @brief The start index of the substring
  size_t _start = 0;
  /// @brief The number of characters to be extracted
  size_t _nChars;

  using StringExpression::directEvaluate;
  using StringExpression::disableCache;
};

} // namespace expression
