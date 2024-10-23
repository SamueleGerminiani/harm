#pragma once

#include "TemporalExpression.hh"
#include "expUtils/ope.hh"
#include "formula/atom/Atom.hh"

namespace expression {

//------------ Generic Properties ----------------------------------------------

/// @brief GenericProperty class template representing temporal expressions with a specific operator.
template <ope::temporalOpe Operator>
class GenericProperty : public TemporalExpression {
public:
  GenericProperty() : TemporalExpression() {}
  GenericProperty(TemporalExpressionPtr item)
      : TemporalExpression(item) {}
  GenericProperty(std::vector<TemporalExpressionPtr> items)
      : TemporalExpression(items) {}
  GenericProperty(const GenericProperty &other) = delete;
  virtual ~GenericProperty() {}

  void acceptVisitor(ExpVisitor &vis) override {}

  ope::temporalOpe getOperator() override { return _op; }

private:
  /// The operator associated with this property.
  const ope::temporalOpe _op = Operator;
};

using PropertyAlways =
    GenericProperty<ope::temporalOpe::PropertyAlways>;
using PropertyEventually =
    GenericProperty<ope::temporalOpe::PropertyEventually>;
using PropertyUntil =
    GenericProperty<ope::temporalOpe::PropertyUntil>;
using PropertyRelease =
    GenericProperty<ope::temporalOpe::PropertyRelease>;
using PropertyAnd = GenericProperty<ope::temporalOpe::PropertyAnd>;
using PropertyOr = GenericProperty<ope::temporalOpe::PropertyOr>;
using PropertyNot = GenericProperty<ope::temporalOpe::PropertyNot>;

// Smart pointer aliases
using PropertyAlwaysPtr = std::shared_ptr<PropertyAlways>;
using PropertyEventuallyPtr = std::shared_ptr<PropertyEventually>;
using PropertyUntilPtr = std::shared_ptr<PropertyUntil>;
using PropertyReleasePtr = std::shared_ptr<PropertyRelease>;
using PropertyAndPtr = std::shared_ptr<PropertyAnd>;
using PropertyOrPtr = std::shared_ptr<PropertyOr>;
using PropertyNotPtr = std::shared_ptr<PropertyNot>;

//------------------------------------------------------------------------------

/// @brief PropertyNext class representing the 'next' temporal property.
class PropertyNext
    : public GenericProperty<ope::temporalOpe::PropertyNext> {
public:
  PropertyNext()
      : GenericProperty<ope::temporalOpe::PropertyNext>() {}

  PropertyNext(TemporalExpressionPtr item, size_t delay = 1)
      : GenericProperty<ope::temporalOpe::PropertyNext>(item),
        _delay(delay) {}

  virtual ~PropertyNext() {}

  PropertyNext(const PropertyNext &other) = delete;

  void acceptVisitor(ExpVisitor &vis) override;

  /// Get the delay associated with the 'next' property.
  size_t getDelay() { return _delay; }

  /// Set the delay value for the 'next' property.
  void setDelay(size_t delay) { _delay = delay; }

private:
  /// The delay value for the 'next' property.
  size_t _delay = 1;
};

/// @brief PropertyImplication class representing the implication temporal property.
class PropertyImplication
    : public GenericProperty<ope::temporalOpe::PropertyImplication> {

public:
  PropertyImplication()
      : GenericProperty<ope::temporalOpe::PropertyImplication>() {}

  PropertyImplication(TemporalExpressionPtr antedent,
                      TemporalExpressionPtr consequent,
                      bool mmImplication = false,
                      bool overlapping = false)
      : GenericProperty<ope::temporalOpe::PropertyImplication>(
            {antedent, consequent}),
        _mmImplication(mmImplication), _overlapping(overlapping) {}

  virtual ~PropertyImplication() {}
  PropertyImplication(const PropertyImplication &other) = delete;

  void acceptVisitor(ExpVisitor &vis) override;

  /// Check if the implication is a multi-match implication.
  bool isMMImplication() { return _mmImplication; }

  /// Check if the implication involves overlapping.
  bool isOverlapping() { return _overlapping; }

  void setMMImplication(bool mmImplication) {
    _mmImplication = mmImplication;
  }

  void setOverlapping(bool overlapping) {
    _overlapping = overlapping;
  }

private:
  /// Flag for multi-match implication.
  bool _mmImplication = false;

  /// Flag for overlapping in implication.
  bool _overlapping = false;
};

// Smart pointer aliases
using PropertyNextPtr = std::shared_ptr<PropertyNext>;
using PropertyImplicationPtr = std::shared_ptr<PropertyImplication>;

//------------------------------------------------------------------------------

// Utility functions for checking specific temporal properties

inline bool isPropertyAlways(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyAlways>(exp) != nullptr;
}

inline bool isPropertyEventually(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyEventually>(exp) !=
         nullptr;
}

inline bool isPropertyUntil(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyUntil>(exp) != nullptr;
}

inline bool isPropertyRelease(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyRelease>(exp) != nullptr;
}

inline bool isPropertyAnd(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyAnd>(exp) != nullptr;
}

inline bool isPropertyOr(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyOr>(exp) != nullptr;
}

inline bool isPropertyNot(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyNot>(exp) != nullptr;
}

inline bool isPropertyNext(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyNext>(exp) != nullptr;
}

inline bool isPropertyImplication(const TemporalExpressionPtr &exp) {
  return std::dynamic_pointer_cast<PropertyImplication>(exp) !=
         nullptr;
}

inline bool isSereImplication(const TemporalExpressionPtr &exp) {
  return isPropertyImplication(exp) &&
         std::dynamic_pointer_cast<PropertyImplication>(exp)
             ->isMMImplication();
}

inline bool
isOverlappingImplication(const TemporalExpressionPtr &exp) {
  return isPropertyImplication(exp) &&
         std::dynamic_pointer_cast<PropertyImplication>(exp)
             ->isOverlapping();
}

inline TemporalExpressionPtr &
getAntecedent(const TemporalExpressionPtr &exp) {
  messageErrorIf(!isPropertyImplication(exp),
                 "The expression is not an implication");
  return std::dynamic_pointer_cast<PropertyImplication>(exp)
      ->getItems()[0];
}

inline TemporalExpressionPtr &
getConsequent(const TemporalExpressionPtr &exp) {
  messageErrorIf(!isPropertyImplication(exp),
                 "The expression is not an implication");
  return std::dynamic_pointer_cast<PropertyImplication>(exp)
      ->getItems()[1];
}

inline size_t getPropertyNextDelay(const TemporalExpressionPtr &exp) {
  messageErrorIf(!isPropertyNext(exp),
                 "The expression is not a next property");
  return std::dynamic_pointer_cast<PropertyNext>(exp)->getDelay();
}

} // namespace expression

