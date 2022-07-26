#pragma once
#include "Atom.hh"

namespace expression {
class CachedProposition : public Proposition {
public:
  CachedProposition(Proposition *prop);
  ~CachedProposition();
  virtual bool evaluate(size_t time);

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  virtual void acceptVisitor(ExpVisitor &vis);

  /// @brief Returns the largest simulation time that can be provided to
  /// the method evaluate.
  virtual size_t getMaxTime();
  virtual Proposition *getItem();

  void setType(VarType type, size_t size);

  std::pair<VarType, size_t> getType();
  Proposition *get();

private:
  Proposition *_prop = nullptr;
  bool *_cached = nullptr;
};

} // namespace expression
