#pragma once

#include "Trace.hh"

namespace harm {

/// @brief TraceReader declaration.
/// This is an interface for a generic trace reader module.
class TraceReader {

public:
  /// @brief Destructor
  virtual ~TraceReader() = default;

  /// @brief An implementation of this method reads the simulation traces and
  /// generates a TraceRepository as a result.
  /// @return A TraceRepository object.
  Trace *readTrace();

  /// @brief Unsupported constructor.
  TraceReader(const TraceReader &other) = delete;

  /// @brief Unsupported operator
  TraceReader &operator=(const TraceReader &other) = delete;

private:
  Trace *mergeTrace(const std::vector<Trace *> &traces);

protected:
  virtual Trace *readTrace(std::string file) = 0;

  /// @brief Constructor.
  TraceReader(const std::vector<std::string> &files, const std::string &clk);

  std::vector<std::string> _files;
  std::string _clk;
  Trace *_trace = nullptr;
};

} // namespace harm
