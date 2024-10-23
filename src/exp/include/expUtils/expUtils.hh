#pragma once

#include "Language.hh"
#include "PrintMode.hh"
#include "formula/atom/Atom.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/temporal/TemporalExpression.hh"
#include <iosfwd>
#include <memory>
#include <stddef.h>
#include <string>
#include <utility>
#include <vector>

namespace expression {
enum class PrintMode;
class NumericExpression;
using NumericExpressionPtr = std::shared_ptr<NumericExpression>;
enum class ExpType;
} // namespace expression
namespace harm {
class Trace;
using TracePtr = std::shared_ptr<Trace>;
} // namespace harm

namespace expression {
void sortPropositions(std::vector<PropositionPtr> &props);
size_t getNumVariables(const std::vector<PropositionPtr> &props);
size_t getNumVariables(const PropositionPtr &p);
size_t getRepetitions(const std::vector<PropositionPtr> &props);
std::vector<std::pair<std::string, std::pair<ExpType, size_t>>>
getVars(const Proposition &p);
void changeTrace(const PropositionPtr &p,
                 const harm::TracePtr &newTrace);
void changeTrace(const TemporalExpressionPtr &te,
                 const harm::TracePtr &newTrace);

#define dec_expToString(prefix, type)                                \
  std::string prefix##2String(const type &o);                        \
  std::string prefix##2ColoredString(const type &exp);

#define dec_expOutOp(prefix, type)                                   \
  std::ostream &operator<<(std::ostream &os, const type &o);

#define dec_expStringStreamOp(prefix, type)                          \
  std::stringstream &operator<<(std::stringstream &os, const type &o);

#define dec_expCopyOp(suffix, type) type copy(const type &o);

TemporalExpressionPtr copy(const TemporalExpressionPtr &o,
                           bool removePlaceholders = false);

#define dec_expGetVars(suffix, type)                                 \
  std::vector<std::pair<std::string, std::pair<ExpType, size_t>>>    \
  getVars(const type &o);

// clang-format off
dec_expToString(prop, PropositionPtr)
std::string temp2String(const TemporalExpressionPtr &exp, const Language lang, const PrintMode mode);
dec_expToString(float, FloatExpressionPtr)
dec_expToString(int, IntExpressionPtr)
dec_expToString(num, NumericExpressionPtr)


dec_expOutOp(prop, PropositionPtr)
std::string temp2ColoredString(const TemporalExpressionPtr &exp,const Language lang, const PrintMode mode);
dec_expOutOp(float, FloatExpressionPtr)
dec_expOutOp(int, IntExpressionPtr)
dec_expOutOp(num, NumericExpressionPtr)

dec_expCopyOp(Proposition, PropositionPtr)
dec_expCopyOp(Float, FloatExpressionPtr)
dec_expCopyOp(Int, IntExpressionPtr)
dec_expCopyOp(num, NumericExpressionPtr)

dec_expGetVars(Proposition, PropositionPtr)
dec_expGetVars(TemporalExpression, TemporalExpressionPtr)
dec_expGetVars(Float, FloatExpressionPtr)
dec_expGetVars(Int, IntExpressionPtr)
    // clang-format on

    template <typename T>
    std::string exp2String(const GenericPtr<T> &exp) {
  if constexpr (std::is_same_v<T, Proposition>) {
    return prop2String(exp);
  } else if constexpr (std::is_same_v<T, FloatExpression>) {
    return float2String(exp);
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    return int2String(exp);
  } else {
    messageError("Unknown Expression in exp2String");
  }
  return "";
}

template <typename T>
std::string exp2ColoredString(const GenericPtr<T> &exp) {
  if constexpr (std::is_same_v<T, Proposition>) {
    return prop2ColoredString(exp);
  } else if constexpr (std::is_same_v<T, FloatExpression>) {
    return float2ColoredString(exp);
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    return int2ColoredString(exp);
  } else {
    messageError("Unknown Expression in exp2ColoredString");
  }
  return "";
}

bool isConstantTrue(const PropositionPtr &p);

template <typename T> bool isUnary(const GenericPtr<T> &exp) {
  return isConstant(exp) || isVariable(exp) || isTypeCast(exp) ||
         isNot(exp);
}
//returns true if the expression does not contain any temporal operators other than next/delay and not
bool isSimple(const TemporalExpressionPtr &exp);

std::string printAST_terminal(const TemporalExpressionPtr &exp,
                              const Language lang,
                              const PrintMode mode);
} // namespace expression
