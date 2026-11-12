#pragma once

#include <memory>
#include <stddef.h>

#include "Int.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;
class Logic;

/// @brief H25 (D-039): SystemVerilog's $signed(e) and $unsigned(e) (IEEE 1800-2017 20.5): the bits and the width of
/// e, with the sign changed. A trace carries no signedness (a VCD vector is an unsigned logic), so this is how a
/// proposition reads a signal as the RTL declares it.
template <typename T> class SignCast : public T {

public:
  SignCast(GenericPtr<T> e, bool toSigned);

  SignCast(const SignCast &other) = delete;
  SignCast &operator=(const SignCast &other) = delete;
  virtual ~SignCast() = default;

  void acceptVisitor(ExpVisitor &vis) override;

  GenericPtr<T> &getItem() { return _e; }

  /// @brief true for $signed, false for $unsigned
  bool toSigned() const { return _toSigned; }

  /// @brief "$signed" or "$unsigned"
  const char *functionName() const {
    return _toSigned ? "$signed" : "$unsigned";
  }

private:
  void initEvaluate() override;

  GenericPtr<T> _e;
  bool _toSigned;

  using T::directEvaluate;
  using T::disableCache;
};

using IntSignCast = SignCast<IntExpression>;
using LogicSignCast = SignCast<LogicExpression>;
using IntSignCastPtr = std::shared_ptr<IntSignCast>;
using LogicSignCastPtr = std::shared_ptr<LogicSignCast>;

} // namespace expression
