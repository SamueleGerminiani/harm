#pragma once

#include "Context.hh"
#include "Trace.hh"
#include "Template.hh"

namespace harm {

/// @brief PropertyMiner declaration.
/// This is an interface for a generic property miner module.
class PropertyMiner {

  public:
    /// @brief Destructor.
    virtual ~PropertyMiner() = default;

    /// @brief An implementation of this method analyzes the traces of a
    /// to mine Assertions
    virtual void mineProperties(Context &context,
                                Trace *trace) = 0;

    /// @brief Unsupported constructor.
    PropertyMiner(const PropertyMiner &other) = delete;

    /// @brief Unsupported operator
    PropertyMiner &operator=(const PropertyMiner &other) = delete;

  protected:
    /// @brief Constructor.
    explicit PropertyMiner();

};

} // namespace oden
