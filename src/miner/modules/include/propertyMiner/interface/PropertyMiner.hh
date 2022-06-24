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
    /// TraceRepository to mine temporal assertions by combing temporal
    /// operators with the propositions of a given context of influence.
    /// @param context A context of influence.
    /// @param traceRepository A repository of simulation traces.
    virtual void mineProperties(Context &context,
                                Trace *traceRepository) = 0;

    /// @brief Unsupported constructor.
    PropertyMiner(const PropertyMiner &other) = delete;

    /// @brief Unsupported operator
    PropertyMiner &operator=(const PropertyMiner &other) = delete;

  protected:
    /// @brief Constructor.
    
    explicit PropertyMiner();

    /// @brief The xml node containing the configuration
    /// parameters for the module.

};

} // namespace oden
