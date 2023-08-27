/*!
@file
@brief Definition of the VCDFileParser class
*/

#include "VCDFileParser.hpp"
#include "VCDScanner.hpp"

VCDFileParser::VCDFileParser() {

  this->start_time = -std::numeric_limits<decltype(start_time)>::max();
  this->end_time = std::numeric_limits<decltype(end_time)>::max();

  this->trace_scanning = false;
  this->trace_parsing = false;
}

VCDFileParser::~VCDFileParser() { VCDParserlex_destroy(); }

VCDFile *VCDFileParser::parse_file(const std::string &filepath) {

  this->filepath = filepath;

  scan_begin();

  this->fh = new VCDFile();
  VCDFile *tr = this->fh;

  this->fh->root_scope = new VCDScope;
  this->fh->root_scope->name = std::string("$root");
  this->fh->root_scope->type = VCD_SCOPE_ROOT;

  this->scopes.push(this->fh->root_scope);

  this->fh->root_scope = new VCDScope;
  this->fh->root_scope->name = std::string("");
  this->fh->root_scope->type = VCD_SCOPE_ROOT;

  this->scopes.push(this->fh->root_scope);

  tr->add_scope(scopes.top());

  VCDParser::parser parser(*this);

  parser.set_debug_level(trace_parsing);

  int result = parser.parse();

  scopes.pop();

  scan_end();

  if (result == 0) {
    this->fh = nullptr;
    return tr;
  } else {
    tr = nullptr;
    delete this->fh;
    return nullptr;
  }
}

void VCDFileParser::error(const VCDParser::location &l, const std::string &m) {
  
  std::cerr << "line " << l.begin.line << " column " << l.begin.column << std::endl;
  std::cerr << " : " << m << std::endl;
}

void VCDFileParser::error(const std::string &m) {
  std::cerr << " : " << m << std::endl;
}

#ifdef VCD_PARSER_STANDALONE

void print_scope_signals(VCDScope *scope) {
  for (VCDSignal *signal : scope->signals) {

    std::cout << "\t" << signal->hash << "\t" << signal->reference;

    if (signal->size > 1) {
      std::cout << "[" << signal->lindex << ":" << signal->rindex << "]";
    } else if (signal->lindex >= 0) {
      std::cout << "[" << signal->lindex << "]";
    }

    std::cout << std::endl;
  }
}

void traverse_scope(std::string parent, VCDScope *scope) {
  std::string local_parent = parent;

  if (parent.length())
    local_parent += ".";
  local_parent += scope->name;
  std::cout << "Scope: " << local_parent << std::endl;
  print_scope_signals(scope);
  for (auto child : scope->children) {
    std::cout << "Child:\n";
    traverse_scope(local_parent, child);
  }
}

#endif
