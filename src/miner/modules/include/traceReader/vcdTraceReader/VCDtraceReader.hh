
#include "TraceReader.hh"

namespace harm {

/// \class VCDtraceReader
/// This class implements the logic to read a .vcd file
class VCDtraceReader : public TraceReader {
public:
  VCDtraceReader(const std::vector<std::string> &files, const std::string &clk);
  VCDtraceReader(const std::string &file, const std::string &clk);

  std::unordered_map<std::string, std::unordered_set<std::string>>
      _scopeFullName_to_SignalsFullName;
private:
  virtual Trace *readTrace(const std::string file) override;
  std::string _clk = "";

};
} // namespace harm
