#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "TraceReader.hh"

namespace harm {
class Trace;

/// \class VCDtraceReader
/// This class is used to read a .vcd file
class VCDtraceReader : public TraceReader {
public:
  /// @brief Constructor for multiple files trace
  VCDtraceReader(const std::vector<std::string> &files,
                 const std::string &clk);
  /// @brief Constructor for single file trace
  VCDtraceReader(const std::string &file, const std::string &clk);

  std::unordered_map<std::string, std::unordered_set<std::string>>
  getScopeFullName_to_SignalsFullName() const;

private:
  /// @brief implementation of the actual trace reading
  virtual TracePtr readTrace(const std::string file) override;

  ///clock signal name
  std::string _clk = "";
  /// map between the whole vcd scope name and the whole signals name, used to generate the config file
  std::unordered_map<std::string, std::unordered_set<std::string>>
      _scopeFullName_to_SignalsFullName;
};

using VCDtraceReaderPtr = std::shared_ptr<VCDtraceReader>;
} // namespace harm
