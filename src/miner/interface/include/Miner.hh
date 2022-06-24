#pragma once

#include "modules.hh"

namespace harm {
/// @brief Miner declaration.
/// This class represents an assertion miner.
class Miner {

public:
  /// @brief Config_t declaration.
  /// This class collects a trace reader, a static analyser, a proposition
  /// miner, an assertion miner and an assetions printer

  struct Config_t {
    /// @brief Constructor.
    Config_t();

    /// @brief Destructor.
    ~Config_t();

    /// a pointer to a trace reader
    TraceReader *traceReader;
    /// a pointer to a context miner
    ContextMiner *contextMiner;
    /// a pointer to an assertion miner
    PropertyMiner *propertyMiner;
    /// a point to a property qualifier
    PropertyQualifier *propertyQualifier;

    /// @brief Unsupported constructor.
    Config_t(const Config_t &) = delete;

    /// @brief Unsupported operator
    Config_t &operator=(const Config_t &) = delete;
  };

  explicit Miner(Config_t &configuration);
  ~Miner() = default;

  void run();

private:
  Config_t &_config;

  void printStats();
  void _printWelcomeMessage();
};

} // namespace harm
