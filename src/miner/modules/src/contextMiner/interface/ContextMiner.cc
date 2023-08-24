#include "ContextMiner.hh"
#include "message.hh"
#include <sstream>

namespace harm {

ContextMiner::ContextMiner(std::string &configFile)
    : _configuration(nullptr), _xmlFile(nullptr), _doc(nullptr) {

  messageInfo("Parsing configuration file " + configFile);

  // find root node
  try {
    _xmlFile = new rapidxml::file<>(configFile.c_str());
    _doc = new rapidxml::xml_document<>();
    _doc->parse<0>(_xmlFile->data());
  } catch (rapidxml::parse_error &e) {
    std::stringstream ss;
    ss << "Parsing error in " << configFile << " "
       << "\n"
       << e.m_what << " at line " << e.m_lineNumber << std::endl;
    if (!reinterpret_cast<char *>(e.m_where)[0]) {
      ss << "Hint: you probably forgot to close a tag\n";
    }
    messageError(ss.str());
  }

  // specifications
  _configuration = _doc->first_node("harm");
  if (_configuration == nullptr) {
    messageError("harm node not found!");
  }
}

} // namespace harm
