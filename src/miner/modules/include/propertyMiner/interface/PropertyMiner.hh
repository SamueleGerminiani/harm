#pragma once
#include <memory>

namespace harm {
class Context;
using ContextPtr = std::shared_ptr<Context>;
class Trace;
using TracePtr = std::shared_ptr<Trace>;

/// @brief PropertyMiner declaration.
/// This is an interface for a generic property miner module.
class PropertyMiner {

public:
  /// @brief Destructor.
  virtual ~PropertyMiner() = default;

  /// @brief An implementation of this method analyzes the traces of a
  /// to mine Assertions
  virtual void mineProperties(const ContextPtr &context,
                              const harm::TracePtr &trace) = 0;

  /// @brief Unsupported constructor.
  PropertyMiner(const PropertyMiner &other) = delete;

  /// @brief Unsupported operator
  PropertyMiner &operator=(const PropertyMiner &other) = delete;

protected:
  /// @brief Constructor.
  explicit PropertyMiner();
};
using PropertyMinerPtr = std::shared_ptr<PropertyMiner>;

} // namespace harm
