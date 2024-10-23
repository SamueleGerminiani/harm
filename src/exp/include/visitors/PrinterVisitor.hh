#pragma once
#include <sstream>
#include <stack>
#include <string>

#include "expUtils/ope.hh"
#include "visitors/ExpVisitor.hh"
#include "visitors/visitorExpList.hh"

#include "Language.hh"

namespace expression {
enum class PrintMode;

namespace ope {
enum ope : int;
}

/// @brief PrinterVisitor generates a string given an expression.
class PrinterVisitor : public ExpVisitor {
public:
  /// @brief if colored is true, the string will be colored.
  PrinterVisitor(Language lang, bool colored, PrintMode mode);

  /// @brief Destructor.
  ~PrinterVisitor() override = default;

  /// @brief Clean up the internal string buffer.
  void clear();

  /// @brief Returns a string-representation of the visited expression
  std::string get();

  ///@brief returns true if the sere requires curly brackets
  bool sereNeedsCurlyBrackets();

  std::pair<std::string, std::string> getSereBrackets();

  VISITOR_EXP_LIST(, visitor_override);

protected:
  /// @brief stream to store the string representation of the expression
  std::stringstream _ss;
  /// @brief The language of the expression being printed
  Language _lang;
  /// @brief If true, the string will be colored
  bool _colored;
  /// @brief If true, the string will abstract the boolean layer
  PrintMode _printMode;
  /// @brief Stack of operators visited in the expression
  std::stack<ope::ope> _ope_stack;
  /// @brief Stack of temporal operators visited in the expression
  std::stack<ope::temporalOpe> _temporal_ope_stack;
};

} // namespace expression
