#pragma once

#include "PointerUtils.hh"
#include "expUtils/ope.hh"
#include <vector>

namespace expression {

class TemporalExpression;
using TemporalExpressionPtr = std::shared_ptr<TemporalExpression>;

class ExpVisitor;

/**
 * @brief Base class for temporal expressions.
 * This class represents a generic temporal expression, which can contain other temporal expressions as items.
 */
class TemporalExpression {

protected:
  TemporalExpression() {}
  TemporalExpression(const TemporalExpressionPtr &item)
      : _items({item}) {}
  TemporalExpression(const std::vector<TemporalExpressionPtr> &items)
      : _items(items) {}

public:
  // WARNING: Temporal operators are not allowed to destroy the propositions, only the temporal operators
  virtual ~TemporalExpression() {}

  /// Get the list of temporal expression items
  std::vector<TemporalExpressionPtr> &getItems() { return _items; }

  void addItem(const TemporalExpressionPtr &item) {
    _items.push_back(item);
  }
  void popItem() { _items.pop_back(); }
  void removeItems() { _items.clear(); }
  size_t size() { return _items.size(); }
  bool empty() { return _items.empty(); }
  TemporalExpressionPtr &operator[](size_t i) { return _items[i]; }

  virtual void acceptVisitor(ExpVisitor &vis) = 0;

  virtual ope::temporalOpe getOperator() {
    return ope::temporalOpe::TemporalNoOp;
  }

  /// List of temporal expression items
  std::vector<TemporalExpressionPtr> _items;
};

/**
 * @brief Traverse the temporal expression tree and apply a function to each node.
 * @tparam Func Type of the function to be applied.
 * @param self Pointer to the root of the temporal expression tree.
 * @param func Function to apply to each node.
 */
template <typename Func>
void traverse(TemporalExpressionPtr &self, Func func) {
  if (func(self))
    return;
  for (auto &item : self->getItems())
    traverse(item, func);
}

// const version
template <typename Func>
void traverse(const TemporalExpressionPtr &self, Func func) {
  if (func(self))
    return;
  for (const auto &item : self->getItems())
    traverse(item, func);
}

/**
 * @brief Traverse the temporal expression tree with enter and exit functions for each node.
 * @tparam Func Type of the functions to be applied.
 * @param self Pointer to the root of the temporal expression tree.
 * @param enter Function to apply when entering a node.
 * @param exit Function to apply when exiting a node.
 */
template <typename Func>
void traverse(TemporalExpressionPtr &self, Func enter, Func exit) {
  enter(self);
  for (auto &item : self->getItems()) {
    traverse(item, enter, exit);
  }
  exit(self);
}

// const version
template <typename Func>
void traverse(const TemporalExpressionPtr &self, Func enter,
              Func exit) {
  enter(self);
  for (const auto &item : self->getItems()) {
    traverse(item, enter, exit);
  }
  exit(self);
}

} // namespace expression

