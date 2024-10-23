#pragma once

#include <memory>
#include <string>
#include <vector>

namespace harm {
class Trace;
using TracePtr = std::shared_ptr<Trace>;

/// @\class TraceReader
/// This is an interface for a generic trace reader module.
class TraceReader {

public:
  /// @brief Destructor
  virtual ~TraceReader() = default;

  /// @brief this method reads the trace from the given file(s), the actual reading is delegated to the protected method 'readTrace' that must be implemented by the derived classes
  harm::TracePtr readTrace();

  /// @brief Unsupported constructor.
  TraceReader(const TraceReader &other) = delete;

  /// @brief Unsupported operator
  TraceReader &operator=(const TraceReader &other) = delete;

private:
  /// @brief used when multiple traces are given as input
  harm::TracePtr
  mergeTrace(const std::vector<harm::TracePtr> &traces);
  /// @brief used when a reset is given as input (the trace is cut according to the reset)
  void addCutsWithReset(const harm::TracePtr &trace);

protected:
  /// @brief the actual trace reading
  virtual harm::TracePtr readTrace(std::string file) = 0;

  /// @brief Constructor.
  TraceReader(const std::vector<std::string> &traceFiles);

  ///list of paths to trace files
  std::vector<std::string> _traceFiles;

  ///the final generated trace
  harm::TracePtr _trace = nullptr;
};

} // namespace harm
