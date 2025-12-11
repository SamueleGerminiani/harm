#pragma once

#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "message.hh"
#include <string>

namespace expression {

template <typename OT>
inline bool canSub(bool sub, bool _isTemporal, std::string _ph,
                   const PropositionPtrPtr &p) {

  messageErrorIf(!_isTemporal,
                 "Calling canSub with a non-temporal function");

  messageErrorIf(_ph == "", "Placeholder missing");

  if (!sub) {
    return false;
  }

  return *p != nullptr;
}

template <typename OT, typename ET>
Function<OT, ET>::Function(ExpType type, size_t size, size_t max_time,
                           const PropositionPtrPtr &phPtr,
                           const std::string &ph)
    : ET(type, size, max_time), _isTemporal(true), _phPtr(phPtr),
      _ph(ph) {}

template <typename OT, typename ET>
Function<OT, ET>::Function(ExpType type, size_t size, size_t max_time,
                           const GenericPtr<OT> &op)
    : ET(type, size, max_time), _isTemporal(false), _op(op) {}

template <typename OT, typename ET>
bool Function<OT, ET>::isTemporal() {
  return _isTemporal;
}

template <typename OT, typename ET>
std::string Function<OT, ET>::getPlaceholderToken() {
  messageErrorIf(!_isTemporal, "Attempted to get placeholder token "
                               "of a non-temporal function");
  return _ph;
}
template <typename OT, typename ET>
void Function<OT, ET>::setPlaceholderPointer(
    const PropositionPtrPtr &pp) {
  messageErrorIf(!_isTemporal, "Attempted to set placeholder pointer "
                               "of a non-temporal function");
  _phPtr = pp;
}

template <typename OT, typename ET>
PropositionPtrPtr &Function<OT, ET>::getPlaceholderPointer() {
  messageErrorIf(!_isTemporal, "Attempted to get placeholder pointer "
                               "of a non-temporal function");
  return _phPtr;
}

template <typename OT, typename ET>
void Function<OT, ET>::setOperand(const GenericPtr<OT> &p) {
  messageErrorIf(
      _isTemporal,
      "Attempted to the set operand of a temporal function");
  _op = p;
}

template <typename OT, typename ET>
GenericPtr<OT> &Function<OT, ET>::getOperand() {
  messageErrorIf(_isTemporal, "Attempted to get operand "
                              "of a temporal function");
  return _op;
}

template <typename OT, typename ET>
void Function<OT, ET>::setTemporal(bool temporal) {
  _isTemporal = temporal;
}

template <typename OT, typename ET> Function<OT, ET>::~Function() {}

template <typename OT, typename ET>
std::string Function<OT, ET>::Function::getFunctionName() {
  return _funName;
}
} // namespace expression
