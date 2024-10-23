#pragma once

#include "TemporalExpression.hh"
#include "expUtils/ope.hh"
#include "formula/atom/Atom.hh"
#include <memory>

namespace expression {

/**
 * @brief A generic class for SERE (Sequential Extended Regular Expressions) operations.
 * This class represents a temporal expression with a specified operator.
 * @tparam Operator The temporal operator for the SERE.
 */
template <ope::temporalOpe Operator>
class GenericSere : public TemporalExpression {
public:
  GenericSere() : TemporalExpression() {}
  GenericSere(TemporalExpressionPtr item)
      : TemporalExpression(item) {}
  GenericSere(std::vector<TemporalExpressionPtr> items)
      : TemporalExpression(items) {}

  GenericSere(const GenericSere &other) = delete;
  virtual ~GenericSere() {}

  //the derived class needs thid method, although it will be overriden by the specialization
  void acceptVisitor(ExpVisitor &vis) override {}
  ope::temporalOpe getOperator() override { return _op; }

private:
  const ope::temporalOpe _op = Operator;
};

using SereAnd = GenericSere<ope::temporalOpe::PropertyAnd>;
using SereOr = GenericSere<ope::temporalOpe::PropertyOr>;
using SereIntersect = GenericSere<ope::temporalOpe::SereIntersect>;
using SereFirstMatch = GenericSere<ope::temporalOpe::SereFirstMatch>;

using SereAndPtr = std::shared_ptr<SereAnd>;
using SereOrPtr = std::shared_ptr<SereOr>;
using SereIntersectPtr = std::shared_ptr<SereIntersect>;
using SereFirstMatchPtr = std::shared_ptr<SereFirstMatch>;

/**
 * @brief A class for SERE concatenation operation.
 * This class represents a temporal expression with the SereConcat operator.
 */
class SereConcat : public GenericSere<ope::temporalOpe::SereConcat> {
public:
  SereConcat() : GenericSere<ope::temporalOpe::SereConcat>() {}
  SereConcat(TemporalExpressionPtr left, TemporalExpressionPtr right,
             bool overlapping = false)
      : GenericSere<ope::temporalOpe::SereConcat>({left, right}),
        _overlapping(overlapping) {}

  virtual ~SereConcat() {}
  SereConcat(const SereConcat &other) = delete;
  void acceptVisitor(ExpVisitor &vis) override;
  size_t isOverlapping() { return _overlapping; }
  void setOverlapping(bool overlapping) {
    _overlapping = overlapping;
  }

private:
  bool _overlapping = false;
};

/**
 * @brief A class for the SERE plus operation.
 * This class represents a temporal expression with the SerePlus operator.
 */
class SerePlus : public GenericSere<ope::temporalOpe::SerePlus> {
public:
  SerePlus() : GenericSere<ope::temporalOpe::SerePlus>() {}
  SerePlus(TemporalExpressionPtr right)
      : GenericSere<ope::temporalOpe::SerePlus>({right}) {}

  virtual ~SerePlus() {}
  SerePlus(const SerePlus &other) = delete;
  void acceptVisitor(ExpVisitor &vis) override;
};

/**
 * @brief A class for window-based SERE operations.
 * This class represents a temporal expression with a specified operator and a time window.
 * @tparam Operator The temporal operator for the SERE.
 * @tparam Binary Indicates whether the operator is binary.
 */
template <ope::temporalOpe Operator, bool Binary>
class WindowBasedSere : public GenericSere<Operator> {
public:
  WindowBasedSere() : GenericSere<Operator>() {}

  template <bool B = Binary, typename = std::enable_if_t<B>>
  WindowBasedSere(TemporalExpressionPtr left,
                  TemporalExpressionPtr right,
                  const std::pair<int, int> &window = {1, 1})
      : GenericSere<Operator>({left, right}), _window(window) {}

  WindowBasedSere(TemporalExpressionPtr right,
                  const std::pair<int, int> &window = {1, 1})
      : GenericSere<Operator>({right}), _window(window) {}

  WindowBasedSere(const WindowBasedSere &other) = delete;

  virtual ~WindowBasedSere() {}
  void acceptVisitor(ExpVisitor &vis) override;

  std::pair<int, int> getWindow() { return _window; }
  void setWindow(const std::pair<int, int> &window) {
    _window = window;
  }

  /**
   * @brief Converts the window to a string representation.
   * @return String representation of the window.
   */
  std::string windowToString() {
    std::stringstream ss;
    std::string leftStr = std::to_string(_window.first);
    std::string rightStr =
        (_window.second != -1 ? std::to_string(_window.second) : "$");

    if constexpr (Operator == ope::temporalOpe::SereDelay) {
      ss << "##";
      if (_window.first != _window.second) {
        ss << "[" << leftStr << ":" << rightStr << "]";
      } else {
        ss << leftStr;
      }
    } else {
      if constexpr (Operator ==
                    ope::temporalOpe::SereConsecutiveRep) {
        if (_window.first == 0 && _window.second == -1) {
          ss << "[" << opeToString(Operator) << "]";
          return ss.str();
        }
      }

      ss << "[" << opeToString(Operator) << leftStr;
      if (_window.first != _window.second) {
        ss << ":" << rightStr;
      }
      ss << "]";
    }
    return ss.str();
  }

private:
  std::pair<int, int> _window;
};

using SereDelay = WindowBasedSere<ope::temporalOpe::SereDelay, true>;
using SereConsecutiveRep =
    WindowBasedSere<ope::temporalOpe::SereConsecutiveRep, false>;
using SereGoto = WindowBasedSere<ope::temporalOpe::SereGoto, false>;
using SereNonConsecutiveRep =
    WindowBasedSere<ope::temporalOpe::SereNonConsecutiveRep, false>;

using SereConcatPtr = std::shared_ptr<SereConcat>;
using SerePlusPtr = std::shared_ptr<SerePlus>;
using SereDelayPtr = std::shared_ptr<SereDelay>;
using SereConsecutiveRepPtr = std::shared_ptr<SereConsecutiveRep>;
using SereGotoPtr = std::shared_ptr<SereGoto>;
using SereNonConsecutiveRepPtr =
    std::shared_ptr<SereNonConsecutiveRep>;
//------------------------------------------------------------------------------

//Utils

inline bool isSereAnd(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereAnd>(exp) != nullptr;
}

inline bool isSereOr(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereOr>(exp) != nullptr;
}

inline bool isSereIntersect(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereIntersect>(exp) != nullptr;
}

inline bool isSereFirstMatch(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereFirstMatch>(exp) != nullptr;
}

inline bool isSereConcat(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereConcat>(exp) != nullptr;
}

inline bool isSereDelay(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereDelay>(exp) != nullptr;
}

inline bool isSereConsecutiveRep(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereConsecutiveRep>(exp) !=
         nullptr;
}

inline bool isSereGoto(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereGoto>(exp) != nullptr;
}

inline bool
isSereNonConsecutiveRep(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SereNonConsecutiveRep>(exp) !=
         nullptr;
}

inline bool isSerePlus(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<SerePlus>(exp) != nullptr;
}

inline bool isSere(const TemporalExpressionPtr &exp) {
  return isSereAnd(exp) || isSereOr(exp) || isSereIntersect(exp) ||
         isSereFirstMatch(exp) || isSereConcat(exp) ||
         isSereDelay(exp) || isSereConsecutiveRep(exp) ||
         isSereGoto(exp) || isSereNonConsecutiveRep(exp);
}

inline bool isOverlappingConcat(const TemporalExpressionPtr &exp) {
  return isSereConcat(exp) &&
         std::dynamic_pointer_cast<SereConcat>(exp)->isOverlapping();
}

inline bool isWindowBasedSere(const TemporalExpressionPtr &exp) {
  return isSereDelay(exp) || isSereConsecutiveRep(exp) ||
         isSereGoto(exp) || isSereNonConsecutiveRep(exp);
}

/**
 * @brief Get the window of a window-based Sere.
 * @param exp Pointer to the temporal expression.
 * @return The window of the Sere as a pair of integers.
 */
inline std::pair<int, int>
getWindow(const TemporalExpressionPtr &exp) {
  if (isSereDelay(exp)) {
    return std::dynamic_pointer_cast<SereDelay>(exp)->getWindow();
  } else if (isSereConsecutiveRep(exp)) {
    return std::dynamic_pointer_cast<SereConsecutiveRep>(exp)
        ->getWindow();
  } else if (isSereGoto(exp)) {
    return std::dynamic_pointer_cast<SereGoto>(exp)->getWindow();
  } else if (isSereNonConsecutiveRep(exp)) {
    return std::dynamic_pointer_cast<SereNonConsecutiveRep>(exp)
        ->getWindow();
  }
  return {0, 0};
}

/**
 * @brief Check if a temporal expression may have multiple matches.
 * @param exp Pointer to the temporal expression.
 * @return True if the expression has multiple matches, false otherwise.
 */
inline bool isMultipleMatch(const TemporalExpressionPtr &exp) {
  bool ret = false;
  bool inFirstMatch = false;

  std::function<void(const TemporalExpressionPtr &)> enter =
      [&](const TemporalExpressionPtr &current) {
        if (isSereFirstMatch(current)) {
          inFirstMatch = true;
        }
      };
  std::function<void(const TemporalExpressionPtr &)> exit =
      [&](const TemporalExpressionPtr &current) {
        if (isSereFirstMatch(current)) {
          inFirstMatch = false;
        } else if (isWindowBasedSere(current) && !inFirstMatch &&
                   getWindow(current).first !=
                       getWindow(current).second) {
          ret = true;
        }
      };

  traverse(exp, enter, exit);

  return ret;
}

} // namespace expression

