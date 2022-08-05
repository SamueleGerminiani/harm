#pragma once

#include "Trace.hh"

namespace harm {

/// @\class TraceReader
/// This is an interface for a generic trace reader module.
class TraceReader {

public:
  /// @brief Destructor
  virtual ~TraceReader() = default;

  /// @brief An implementation of this method reads the simulation traces and
  /// generates a Trace
  Trace *readTrace();

  /// @brief Unsupported constructor.
  TraceReader(const TraceReader &other) = delete;

  /// @brief Unsupported operator
  TraceReader &operator=(const TraceReader &other) = delete;

private:
  /// @brief used when multiple traces are given as input
  Trace *mergeTrace(const std::vector<Trace *> &traces);

protected:
  /// @brief the actual trace reader
  virtual Trace *readTrace(std::string file) = 0;

  /// @brief Constructor.
  TraceReader(const std::vector<std::string> &files);

  ///list of paths to trace files
  std::vector<std::string> _files;

  ///the final generated trace
  Trace *_trace = nullptr;
};

} // namespace harm
