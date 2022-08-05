
#include "TraceReader.hh"

namespace harm {

/// \class VCDtraceReader
/// This class implements the logic to read a .vcd file
class VCDtraceReader : public TraceReader {
public:
  VCDtraceReader(const std::vector<std::string> &files, const std::string &clk);
  VCDtraceReader(const std::string &file, const std::string &clk);

private:
  virtual Trace *readTrace(const std::string file) override;
  std::string _clk="";
};
} // namespace harm
