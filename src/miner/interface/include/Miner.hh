#pragma once
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace harm {
class Context;
using ContextPtr = std::shared_ptr<Context>;
class Trace;
using TracePtr = std::shared_ptr<Trace>;
class ContextMiner;
using ContextMinerPtr = std::shared_ptr<ContextMiner>;
class PropertyMiner;
using PropertyMinerPtr = std::shared_ptr<PropertyMiner>;
class PropertyQualifier;
using PropertyQualifierPtr = std::shared_ptr<PropertyQualifier>;
class TraceReader;
using TraceReaderPtr = std::shared_ptr<TraceReader>;

/// \class Miner
/// \brief This class contains a collection of modules implementing the functionalities of an assertion miner.
class Miner {

public:
  /// \struct ModulesConfig
  /// This struct collects a trace reader, a context miner, a property miner and property qualifier
  struct ModulesConfig {
    /// @brief Constructor.
    ModulesConfig();

    /// @brief Destructor.
    ~ModulesConfig();

    /// a pointer to a trace reader
    TraceReaderPtr traceReader = nullptr;
    /// a pointer to a context miner
    ContextMinerPtr contextMiner = nullptr;
    /// a pointer to an assertion miner
    PropertyMinerPtr propertyMiner = nullptr;
    /// a point to a property qualifier
    PropertyQualifierPtr propertyQualifier = nullptr;

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

  /// @brief Print/Dump the statistics of mining (stored in the hs::namespace)
  void handleStatistics();

  /// @brief --dump-prop-table (H15, D-031): every context's propositions and their values
  void writePropTable(const std::vector<ContextPtr> &contexts,
                      const TracePtr &trace,
                      const std::vector<std::pair<std::string, size_t>> &files);
};

} // namespace harm
