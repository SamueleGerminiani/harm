#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <unordered_set>

#include "classes/atom/Atom.hh"
#include "expUtils/VarType.hh"

namespace expression {

/// @brief An Function such as $stable $rose or $fell
template <typename OT, typename ET> class Function : public ET {
  using ReturnType = typename std::conditional<
      std::is_same<ET, NumericExpression>::value, Numeric,
      typename std::conditional<std::is_same<ET, LogicExpression>::value,
                                ULogic, bool>::type>::type;

public:
  /// @brief Destructor.
  virtual ~Function() override = default;

  /// @brief Returns the value of the atom in the given simulation time
  /// @param time The simulation time
  /// @return The value of the atom
  virtual ReturnType evaluate(size_t time) override =0 ;

  virtual void acceptVisitor(ExpVisitor &vis) override = 0;

  /// @brief Returns the largest simulation time that can be provided to
  /// the method evaluate.
  virtual size_t getMaxTime() override;

  virtual void setType(VarType type, size_t size);

  virtual std::pair<VarType, size_t> getType();

  virtual std::string toString(bool sub = false) = 0;
  virtual std::string toColoredString(bool sub = false) = 0;

protected:
  /// @brief Constructor of an Function
  /// @param max_time the largest simulation time that can be provided to
  /// the method evaluate.
  Function(VarType type = VarType::Bool, size_t size = 1, size_t max_time = 0,
           bool isTemporal = false);

  VarType _type;
  size_t _size;
  size_t _max_time;
  bool _isTemporal;
};

template <typename OT, typename ET> class Stable : public Function<OT, ET> {
public:
  Stable(OT *op, VarType type, size_t size, size_t max_time = 0);
  Stable(OT **op, std::string ph, VarType type, size_t size,
         size_t max_time = 0);
  ~Stable() override;
  bool evaluate(size_t time) override;
  void acceptVisitor(ExpVisitor &vis) override;
  std::string toString(bool sub = false) override;
  std::string toColoredString(bool sub = false) override;
  //not todo
private:
  using Function<OT, ET>::_isTemporal;
  OT **_op;
  std::string _ph = "";
};
using PropositionStable = Stable<Proposition, Proposition>;
using LogicStable = Stable<LogicExpression, Proposition>;
using NumericStable = Stable<NumericExpression, Proposition>;
} // namespace expression

#include "Function.i.hh"
