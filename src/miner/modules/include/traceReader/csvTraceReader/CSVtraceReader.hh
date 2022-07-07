
#include "TraceReader.hh"

namespace harm {

class CSVtraceReader : public TraceReader {
public:
  CSVtraceReader(const std::vector<std::string> &files);
  CSVtraceReader(const std::string &file);

private:
  virtual Trace *readTrace(const std::string file) override;
  /* data */
};
std::pair<std::string, std::pair<std::string, size_t>>
parseVariable(std::string varDecl);
DataType toDataType(std::string name, std::string type, size_t size);
} // namespace harm
