#pragma once

#include <stddef.h>
#include <type_traits>
#include <vector>

#include "Float.hh"
#include "Int.hh"
#include "expUtils/ope.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;

/// @brief CstyleExpression declaration.
/// This class represents a generic float, int or boolean expression.
template <ope::ope O, typename OT, typename ET>
class GenericExpression : public ET {

  using ReturnType = typename std::conditional<
      std::is_same<ET, FloatExpression>::value, Float,
      typename std::conditional<
          std::is_same<ET, IntExpression>::value, UInt,
          bool>::type>::type;

public:
  /// @brief Constructor.
  GenericExpression();

  GenericExpression(const GenericExpression &other) = delete;

  /// @brief Destructor.
  ~GenericExpression() {}

  /// @brief Remove all the children of the current expression
  void removeItems();

  /// @brief Remove one child of the current expression
  void popItem();

  /// @brief Accepts a visitor to visit the current expression.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  /// @brief Sets the the largest simulation time that can be provided to the method evaluate.
  /// setMaxTime is available only for epressions for which the type is not know during the construction
  void setMaxTime(size_t time);

  ope::ope getOperator() override;

  /// @brief Sets the the type of the expression
  // setype is available only for epressions for which the type is not know during the construction
  void setType(ExpType type, size_t size);

  /// @brief Assign operator
  GenericExpression &
  operator=(const GenericExpression &other) = delete;

  /// @brief Adds a new expression
  /// @param item The expression to be added in the current one.
  void addItem(const GenericPtr<OT> &item);

  /// @brief Return the list of subexpressions.
  /// @return A reference to the list of subexpressions.
  std::vector<GenericPtr<OT>> &getItems();

  /// @brief Return the number of subexpressions.
  /// @return number of subexpressions.
  size_t size();

  /// @brief Returns true, if the expression has no subexpressions.
  /// @return True if the expression size is 0, false otherwise.
  bool empty();

private:
  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  /// children of the expression
  std::vector<GenericPtr<OT>> _items;
  /// @brief The operator of the expression.
  const ope::ope _ope;

  using ET::_max_time;
  using ET::_size;
  using ET::_type;
  using ET::directEvaluate;
  using ET::disableCache;
};

// proposition
using PropositionAnd = GenericExpression<ope::ope::PropositionAnd,
                                         Proposition, Proposition>;
using PropositionOr = GenericExpression<ope::ope::PropositionOr,
                                        Proposition, Proposition>;
using PropositionXor = GenericExpression<ope::ope::PropositionXor,
                                         Proposition, Proposition>;
using PropositionEq = GenericExpression<ope::ope::PropositionEq,
                                        Proposition, Proposition>;
using PropositionNeq = GenericExpression<ope::ope::PropositionNeq,
                                         Proposition, Proposition>;
using PropositionNot = GenericExpression<ope::ope::PropositionNot,
                                         Proposition, Proposition>;

// float
using FloatSum = GenericExpression<ope::ope::FloatSum,
                                   FloatExpression, FloatExpression>;
using FloatSub = GenericExpression<ope::ope::FloatSub,
                                   FloatExpression, FloatExpression>;
using FloatMul = GenericExpression<ope::ope::FloatMul,
                                   FloatExpression, FloatExpression>;
using FloatDiv = GenericExpression<ope::ope::FloatDiv,
                                   FloatExpression, FloatExpression>;
using FloatEq = GenericExpression<ope::ope::FloatEq, FloatExpression,
                                  Proposition>;
using FloatNeq = GenericExpression<ope::ope::FloatNeq,
                                   FloatExpression, Proposition>;
using FloatGreater = GenericExpression<ope::ope::FloatGreater,
                                       FloatExpression, Proposition>;
using FloatGreaterEq =
    GenericExpression<ope::ope::FloatGreaterEq, FloatExpression,
                      Proposition>;
using FloatLess = GenericExpression<ope::ope::FloatLess,
                                    FloatExpression, Proposition>;
using FloatLessEq = GenericExpression<ope::ope::FloatLessEq,
                                      FloatExpression, Proposition>;

// int
using IntSum =
    GenericExpression<ope::ope::IntSum, IntExpression, IntExpression>;
using IntSub =
    GenericExpression<ope::ope::IntSub, IntExpression, IntExpression>;
using IntMul =
    GenericExpression<ope::ope::IntMul, IntExpression, IntExpression>;
using IntDiv =
    GenericExpression<ope::ope::IntDiv, IntExpression, IntExpression>;
using IntBAnd = GenericExpression<ope::ope::IntBAnd, IntExpression,
                                  IntExpression>;
using IntBOr =
    GenericExpression<ope::ope::IntBOr, IntExpression, IntExpression>;
using IntBXor = GenericExpression<ope::ope::IntBXor, IntExpression,
                                  IntExpression>;
using IntEq =
    GenericExpression<ope::ope::IntEq, IntExpression, Proposition>;
using IntNeq =
    GenericExpression<ope::ope::IntNeq, IntExpression, Proposition>;
using IntGreater = GenericExpression<ope::ope::IntGreater,
                                     IntExpression, Proposition>;
using IntGreaterEq = GenericExpression<ope::ope::IntGreaterEq,
                                       IntExpression, Proposition>;
using IntLess =
    GenericExpression<ope::ope::IntLess, IntExpression, Proposition>;
using IntLessEq = GenericExpression<ope::ope::IntLessEq,
                                    IntExpression, Proposition>;
using IntNot =
    GenericExpression<ope::ope::IntNot, IntExpression, IntExpression>;
using IntLShift = GenericExpression<ope::ope::IntLShift,
                                    IntExpression, IntExpression>;
using IntRShift = GenericExpression<ope::ope::IntRShift,
                                    IntExpression, IntExpression>;

//smart pointer alias

using PropositionAndPtr = std::shared_ptr<PropositionAnd>;
using PropositionOrPtr = std::shared_ptr<PropositionOr>;
using PropositionXorPtr = std::shared_ptr<PropositionXor>;
using PropositionEqPtr = std::shared_ptr<PropositionEq>;
using PropositionNeqPtr = std::shared_ptr<PropositionNeq>;
using PropositionNotPtr = std::shared_ptr<PropositionNot>;
using FloatSumPtr = std::shared_ptr<FloatSum>;
using FloatSubPtr = std::shared_ptr<FloatSub>;
using FloatMulPtr = std::shared_ptr<FloatMul>;
using FloatDivPtr = std::shared_ptr<FloatDiv>;
using FloatEqPtr = std::shared_ptr<FloatEq>;
using FloatNeqPtr = std::shared_ptr<FloatNeq>;
using FloatGreaterPtr = std::shared_ptr<FloatGreater>;
using FloatGreaterEqPtr = std::shared_ptr<FloatGreaterEq>;
using FloatLessPtr = std::shared_ptr<FloatLess>;
using FloatLessEqPtr = std::shared_ptr<FloatLessEq>;
using IntSumPtr = std::shared_ptr<IntSum>;
using IntSubPtr = std::shared_ptr<IntSub>;
using IntMulPtr = std::shared_ptr<IntMul>;
using IntDivPtr = std::shared_ptr<IntDiv>;
using IntBAndPtr = std::shared_ptr<IntBAnd>;
using IntBOrPtr = std::shared_ptr<IntBOr>;
using IntBXorPtr = std::shared_ptr<IntBXor>;
using IntEqPtr = std::shared_ptr<IntEq>;
using IntNeqPtr = std::shared_ptr<IntNeq>;
using IntGreaterPtr = std::shared_ptr<IntGreater>;
using IntGreaterEqPtr = std::shared_ptr<IntGreaterEq>;
using IntLessPtr = std::shared_ptr<IntLess>;
using IntLessEqPtr = std::shared_ptr<IntLessEq>;
using IntNotPtr = std::shared_ptr<IntNot>;
using IntLShiftPtr = std::shared_ptr<IntLShift>;
using IntRShiftPtr = std::shared_ptr<IntRShift>;

inline bool isPropositionNot(const PropositionPtr &e) {
  return std::dynamic_pointer_cast<PropositionNot>(e) != nullptr;
}
inline bool isIntNot(const PropositionPtr &e) {
  return std::dynamic_pointer_cast<IntNot>(e) != nullptr;
}
inline bool isNot(const PropositionPtr &e) {
  return isPropositionNot(e) || isIntNot(e);
}
inline bool isPropositionAnd(const PropositionPtr &e) {
  return std::dynamic_pointer_cast<PropositionAnd>(e) != nullptr;
}
inline size_t getPropositionAndSize(const PropositionPtr &e) {
  messageErrorIf(!isPropositionAnd(e), "Not a PropositionAnd");
  return std::dynamic_pointer_cast<PropositionAnd>(e)->size();
}

inline bool isEmptyPropositionAnd(const PropositionPtr &e) {
  return isPropositionAnd(e) &&
         std::dynamic_pointer_cast<PropositionAnd>(e)->empty();
}

} // namespace expression

#include "GenericExpression.i.hh"
