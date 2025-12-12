
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
  CSVtraceReader(const std::vector<std::string> &files,
                 bool forceInt = false);
  /// @brief Constructor for single file trace
  CSVtraceReader(const std::string &file, bool forceInt = false);

private:
  /// @brief implementation of the actual trace reading
  virtual TracePtr readTrace(const std::string file) override;

  bool _forceInt = false;
};

using CSVtraceReaderPtr = std::shared_ptr<CSVtraceReader>;
} // namespace harm
