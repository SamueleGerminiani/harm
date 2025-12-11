#pragma once

#include "Function.hh"
#include "colors.hh"
#include "expUtils/expUtils.hh"

namespace expression {
/// @brief class for the SystemVerilog $past function
template <typename OT, typename ET>
class Past : public Function<OT, ET> {
public:
  using ReturnType = typename std::conditional<
      std::is_same<ET, FloatExpression>::value, Float,
      typename std::conditional<
          std::is_same<ET, IntExpression>::value, UInt,
          typename std::conditional<
              std::is_same<ET, LogicExpression>::value, Logic,
              bool>::type>::type>::type;

  /// @brief constructor for the non temporal version
  Past(const GenericPtr<OT> &op, size_t shift, ExpType type,
       size_t size, size_t max_time = 0);
  /// @brief constructor for the temporal version
  Past(const PropositionPtrPtr &op, size_t shift, std::string ph,
       ExpType type, size_t size, size_t max_time = 0);
  Past() = delete;
  Past(const Past &other);
  ~Past() = default;
  virtual FunctionPtr<OT, ET> clone() override;
  void acceptVisitor(ExpVisitor &vis) override;
  std::string toString(bool sub = false) override;
  std::string toColoredString(bool sub = false) override;
  size_t getShift();

private:
  void initEvaluate() override;

  using Function<OT, ET>::_isTemporal;
  using Function<OT, ET>::_type;
  using Function<OT, ET>::_size;
  using Function<OT, ET>::_max_time;
  using Function<OT, ET>::_ph;
  using Function<OT, ET>::_op;
  using Function<OT, ET>::directEvaluate;
  using Function<OT, ET>::disableCache;
  using Function<OT, ET>::_phPtr;
  using Function<OT, ET>::_funName;
  /// @brief shift to the past
  size_t _shift = 1;
};
using PropositionPast = Past<Proposition, Proposition>;
using LogicPast = Past<LogicExpression, LogicExpression>;
using IntPast = Past<IntExpression, IntExpression>;
using FloatPast = Past<FloatExpression, FloatExpression>;

//smart pointer alias
using PropositionPastPtr = std::shared_ptr<PropositionPast>;
using LogicPastPtr = std::shared_ptr<LogicPast>;
using IntPastPtr = std::shared_ptr<IntPast>;
using FloatPastPtr = std::shared_ptr<FloatPast>;

/// @brief class for the SystemVerilog $stable function
template <typename OT, typename ET>
class Stable : public Function<OT, ET> {
public:
  /// @brief constructor for the non temporal version
  Stable(const GenericPtr<OT> &op, ExpType type, size_t size,
         size_t max_time = 0);
  /// @brief constructor for the temporal version
  Stable(const PropositionPtrPtr &phPtr, std::string ph, ExpType type,
         size_t size, size_t max_time = 0);
  Stable() = delete;
  Stable(const Stable &other);
  ~Stable() = default;
  virtual FunctionPtr<OT, ET> clone() override;
  void acceptVisitor(ExpVisitor &vis) override;
  std::string toString(bool sub = false) override;
  std::string toColoredString(bool sub = false) override;

private:
  void initEvaluate() override;

  using Function<OT, ET>::_isTemporal;
  using Function<OT, ET>::_type;
  using Function<OT, ET>::_size;
  using Function<OT, ET>::_max_time;
  using Function<OT, ET>::_ph;
  using Function<OT, ET>::_op;
  using Function<OT, ET>::directEvaluate;
  using Function<OT, ET>::disableCache;
  using Function<OT, ET>::_phPtr;
  using Function<OT, ET>::_funName;
};
using PropositionStable = Stable<Proposition, Proposition>;
using IntStable = Stable<IntExpression, Proposition>;
using LogicStable = Stable<LogicExpression, Proposition>;
using FloatStable = Stable<FloatExpression, Proposition>;

//smart pointer alias
using PropositionStablePtr = std::shared_ptr<PropositionStable>;
using IntStablePtr = std::shared_ptr<IntStable>;
using LogicStablePtr = std::shared_ptr<LogicStable>;
using FloatStablePtr = std::shared_ptr<FloatStable>;

/// @brief class for the SystemVerilog $rose function
template <typename OT, typename ET>
class Rose : public Function<OT, ET> {
public:
  /// @brief constructor for the non temporal version
  Rose(const GenericPtr<OT> &op, ExpType type, size_t size,
       size_t max_time = 0);
  /// @brief constructor for the temporal version
  Rose(const PropositionPtrPtr &phPtr, std::string ph, ExpType type,
       size_t size, size_t max_time = 0);
  Rose() = delete;
  Rose(const Rose &other);
  ~Rose() = default;
  virtual FunctionPtr<OT, ET> clone() override;
  void acceptVisitor(ExpVisitor &vis) override;
  std::string toString(bool sub = false) override;
  std::string toColoredString(bool sub = false) override;

private:
  void initEvaluate() override;

  using Function<OT, ET>::_isTemporal;
  using Function<OT, ET>::_type;
  using Function<OT, ET>::_size;
  using Function<OT, ET>::_max_time;
  using Function<OT, ET>::_ph;
  using Function<OT, ET>::_op;
  using Function<OT, ET>::directEvaluate;
  using Function<OT, ET>::disableCache;
  using Function<OT, ET>::_phPtr;
  using Function<OT, ET>::_funName;
};
using PropositionRose = Rose<Proposition, Proposition>;
using IntRose = Rose<IntExpression, Proposition>;
using LogicRose = Rose<LogicExpression, Proposition>;

//smart pointer alias
using PropositionRosePtr = std::shared_ptr<PropositionRose>;
using IntRosePtr = std::shared_ptr<IntRose>;
using LogicRosePtr = std::shared_ptr<LogicRose>;

/// @brief class for the SystemVerilog $fell function
template <typename OT, typename ET>
class Fell : public Function<OT, ET> {
public:
  /// @brief constructor for the non temporal version
  Fell(const GenericPtr<OT> &op, ExpType type, size_t size,
       size_t max_time = 0);
  /// @brief constructor for the temporal version
  Fell(const PropositionPtrPtr &phPtr, std::string ph, ExpType type,
       size_t size, size_t max_time = 0);
  Fell() = delete;
  Fell(const Fell &other);
  ~Fell() = default;
  virtual FunctionPtr<OT, ET> clone() override;
  void acceptVisitor(ExpVisitor &vis) override;
  std::string toString(bool sub = false) override;
  std::string toColoredString(bool sub = false) override;

private:
  void initEvaluate() override;

  using Function<OT, ET>::_isTemporal;
  using Function<OT, ET>::_type;
  using Function<OT, ET>::_size;
  using Function<OT, ET>::_max_time;
  using Function<OT, ET>::_ph;
  using Function<OT, ET>::_op;
  using Function<OT, ET>::directEvaluate;
  using Function<OT, ET>::disableCache;
  using Function<OT, ET>::_phPtr;
  using Function<OT, ET>::_funName;
};
using PropositionFell = Fell<Proposition, Proposition>;
using IntFell = Fell<IntExpression, Proposition>;
using LogicFell = Fell<LogicExpression, Proposition>;

//smart pointer alias
using PropositionFellPtr = std::shared_ptr<PropositionFell>;
using IntFellPtr = std::shared_ptr<IntFell>;
using LogicFellPtr = std::shared_ptr<LogicFell>;

} // namespace expression
#include "SVAfunction.i.hh"
