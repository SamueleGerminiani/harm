#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "Float.hh"
#include "Int.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;
class Logic;
template <typename OT, typename ET> class Function;
template <typename OT, typename ET>
using FunctionPtr = std::shared_ptr<Function<OT, ET>>;
using FunctionPropositionPtr =
    std::shared_ptr<Function<Proposition, Proposition>>;

/// @brief An Function such as $stable $rose or $fell
/// OT is the type of the operand
/// ET is the type of the function: FloatExpression, IntExpression, LogicExpression, StringExpression, Proposition
template <typename OT, typename ET> class Function : public ET {

  using ReturnType = typename std::conditional<
      std::is_same<ET, FloatExpression>::value, Float,
      typename std::conditional<
          std::is_same<ET, IntExpression>::value, UInt,
          typename std::conditional<
              std::is_same<ET, LogicExpression>::value, Logic,
              bool>::type>::type>::type;

public:
  virtual ~Function();
  Function(const Function &other) = delete;

  /// @brief explicit copy of the Function
  virtual FunctionPtr<OT, ET> clone() = 0;

  /// @brief used to visit the Function
  virtual void acceptVisitor(ExpVisitor &vis) override = 0;

  /// @brief returns a string representation of the Function
  virtual std::string toString(bool sub = false) = 0;
  /// @brief returns a colored string representation of the Function
  virtual std::string toColoredString(bool sub = false) = 0;
  /// @brief returns the string name of the placeholder in the Function
  std::string getPlaceholderToken();
  /// @brief sets the pointer to the placeholder in the Function
  void setPlaceholderPointer(const PropositionPtrPtr &pp);

  /// @brief returns the pointer to the operand of the Function
  GenericPtr<OT> &getOperand();

  /// @brief sets the operand of the Function
  void setOperand(const GenericPtr<OT> &p);

  /// @brief set if the Function is used in the temporal layer of a template (truew) or the propositional layer (false)
  void setTemporal(bool temporal);

  /// @brief returns true if the Function is used in the temporal layer of a template
  bool isTemporal();

  /// @brief returns the pointer to the placeholder in the Function
  PropositionPtrPtr &getPlaceholderPointer();

  /// @brief returns the name of the Function
  std::string getFunctionName();

protected:
  /// @brief this constructor can only be called by the derived classes
  Function(ExpType type, size_t size, size_t max_time,
           const PropositionPtrPtr &phPtr, const std::string &ph);
  Function(ExpType type, size_t size, size_t max_time,
           const GenericPtr<OT> &op);
  Function() = default;

  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  virtual void initEvaluate() override = 0;

  /// @brief true if the Function is used in the temporal layer of a template
  bool _isTemporal = false;

  /// @brief pointer to the proposition that is the operand of the Function
  GenericPtr<OT> _op = nullptr;

  /// @brief pointer to the placeholder that is the operand of the Function (only used in the temporal layer)
  PropositionPtrPtr _phPtr = nullptr;

  /// @brief string representation of the placeholder
  std::string _ph = "";

  ///@brief the type of the Function
  std::string _funName = "$generic";

  using ET::_max_time;
  using ET::_size;
  using ET::_type;
};

// Helper function to check if an object is a Function
template <typename T> bool isFunction(const GenericPtr<T> &exp) {
  if (std::dynamic_pointer_cast<Function<Proposition, Proposition>>(
          exp)) {
    return true;
  } else if (std::dynamic_pointer_cast<
                 Function<FloatExpression, Proposition>>(exp)) {
    return true;
  } else if (std::dynamic_pointer_cast<
                 Function<IntExpression, Proposition>>(exp)) {
    return true;
  } else if (std::dynamic_pointer_cast<
                 Function<LogicExpression, Proposition>>(exp)) {
    return true;
  } else if (std::dynamic_pointer_cast<
                 Function<FloatExpression, FloatExpression>>(exp)) {
    return true;
  } else if (std::dynamic_pointer_cast<
                 Function<IntExpression, IntExpression>>(exp)) {
    return true;
  } else if (std::dynamic_pointer_cast<
                 Function<LogicExpression, LogicExpression>>(exp)) {
    return true;
  }

  return false;
}

} // namespace expression

#include "Function.i.hh"
