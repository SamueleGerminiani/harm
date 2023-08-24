#pragma once

#include "modules.hh"

namespace harm {
/// \class Miner
/// \brief This class contains a collection of modules implementing the functionaltiies of an assertion miner.
class Miner {

public:
  /// \struct ModulesConfig
  /// This class collects a trace reader, a context miner and a property miner
  struct ModulesConfig {
    /// @brief Constructor.
    ModulesConfig();

    /// @brief Destructor.
    ~ModulesConfig();

    /// a pointer to a trace reader
    TraceReader *traceReader;
    /// a pointer to a context miner
    ContextMiner *contextMiner;
    /// a pointer to an assertion miner
    PropertyMiner *propertyMiner;
    /// a point to a property qualifier
    PropertyQualifier *propertyQualifier;

    /// @brief Unsupported constructor.
    ModulesConfig(const ModulesConfig &) = delete;

    /// @brief Unsupported operator
    ModulesConfig &operator=(const ModulesConfig &) = delete;
  };

  explicit Miner(ModulesConfig &configuration);
  ~Miner() = default;

  /// run the miner
  void run();

private:
  ModulesConfig &_config;

  /// @brief Print the statistics of mining (stored in the hs:: namespace)
  void printStats();
};

} // namespace harm
