
#include <string>
#include <vector>

#include "TraceReader.hh"

namespace harm {
class Trace;

/// \class CSVtraceReader
/// This class is used to read a .csv file
class CSVtraceReader : public TraceReader {
public:
  /// @brief Constructor for multiple files trace
  CSVtraceReader(const std::vector<std::string> &files);
  /// @brief Constructor for single file trace
  CSVtraceReader(const std::string &file);

private:
  /// @brief implementation of the actual trace reading
  virtual TracePtr readTrace(const std::string file) override;
};

using CSVtraceReaderPtr = std::shared_ptr<CSVtraceReader>;
} // namespace harm
