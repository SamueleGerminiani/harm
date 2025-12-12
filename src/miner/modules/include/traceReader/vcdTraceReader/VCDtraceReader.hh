#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "TraceReader.hh"

namespace harm {
class Trace;

struct VCDTraceReaderConfig {
  std::string _clk = "";
  std::string _selectedScope = "";
  size_t _vcdUnroll = 0;
  size_t _vcdRecursive = true;
  bool _forceInt = false;
};

/// \class VCDtraceReader
/// This class is used to read a .vcd file
class VCDtraceReader : public TraceReader {
public:
  /// @brief Constructor for multiple files trace
  VCDtraceReader(
      const std::vector<std::string> &files,
      const VCDTraceReaderConfig &config = VCDTraceReaderConfig());
  /// @brief Constructor for single file trace
  VCDtraceReader(
      const std::string &file,
      const VCDTraceReaderConfig &config = VCDTraceReaderConfig());

  std::unordered_map<std::string, std::unordered_set<std::string>>
  getScopeFullName_to_SignalsFullName() const;

private:
  /// @brief implementation of the actual trace reading
  virtual TracePtr readTrace(const std::string file) override;

  /// map between the whole vcd scope name and the whole signals name, used to generate the config file
  std::unordered_map<std::string, std::unordered_set<std::string>>
      _scopeFullName_to_SignalsFullName;

  VCDTraceReaderConfig _config;
};

using VCDtraceReaderPtr = std::shared_ptr<VCDtraceReader>;

} // namespace harm
