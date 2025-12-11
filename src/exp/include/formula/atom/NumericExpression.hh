#pragma once

#include <stddef.h>
#include <type_traits>
#include <utility>

#include "../../clustering/include/ClusteringConfig.hh"
#include "Atom.hh"
#include "Float.hh"
#include "Int.hh"

namespace expression {
class ExpVisitor;
class Logic;
enum class ExpType;

template <typename ET>
using GetNumericExpType = std::conditional_t<
    std::is_same_v<ET, Float>, FloatExpression,
    std::conditional_t<std::is_same_v<ET, UInt> ||
                           std::is_same_v<ET, SInt>,
                       IntExpression, LogicExpression>>;

/// \brief NumericExpression is a wrapper class for FloatExpression or IntExpression or LogicExpression
class NumericExpression {

public:
  /// \brief constructor for FloatExpression
  NumericExpression(const FloatExpressionPtr &nume,
                    bool useCache = true);
  /// \brief constructor for IntExpression
  NumericExpression(const IntExpressionPtr &inte,
                    bool useCache = true);
  /// \brief constructor for LogicExpression
  NumericExpression(const LogicExpressionPtr &loge,
                    bool useCache = true);

  ~NumericExpression();

  template <typename T> T evaluate(size_t time);
  void acceptVisitor(ExpVisitor &vis);
  size_t getMaxTime();
  std::pair<ExpType, size_t> getType();

  /// \brief Returns the underlying expression of type ET
  template <typename ET> GenericPtr<ET> get();

  bool containsXZ(size_t time);

private:
  //only one of the following is not nullptr

  FloatExpressionPtr _floe = nullptr;
  IntExpressionPtr _inte = nullptr;
  LogicExpressionPtr _loge = nullptr;

  bool _useCache;

  // used only if _useCache is true
  double *_cachedd = nullptr;
  UInt *_cachedi = nullptr;
  Logic *_cachedl = nullptr;

public:
  //FIXME: this should not be here
  ///cluster configuration
  harm::ClusteringConfig _clsConfig;
};

using NumericExpressionPtr = std::shared_ptr<NumericExpression>;

} // namespace expression
