#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_set>
#include <utility>

#include "Trace.hh"
#include "VCDFile.hpp"
#include "VCDFileParser.hpp"
#include "VCDTypes.hpp"
#include "VCDValue.hpp"
#include "VCDtraceReader.hh"
#include "VarDeclaration.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "misc.hh"

namespace harm {

using namespace expression;

VCDtraceReader::VCDtraceReader(const std::vector<std::string> &files,
                               const std::string &clk)
    : TraceReader(files) {
  _clk = clk;
}

VCDtraceReader::VCDtraceReader(const std::string &file,
                               const std::string &clk)
    : TraceReader(std::vector<std::string>({file})) {
  _clk = clk;
}

bool isInt(VCDVarType vcdType) {
  return vcdType == VCDVarType::VCD_VAR_INTEGER;
}

static bool isScopeUniqueChild(VCDScope *scope) {
  std::unordered_set<std::string> names;
  for (auto &child : scope->parent->children) {
    if (names.count(child->name)) {
      return false;
    }
    names.insert(child->name);
  }
  return true;
}
static VCDScope *findChildWithMostSignals(VCDScope *scope) {
  //gather children with same name as scope
  std::vector<VCDScope *> children;
  for (auto &child : scope->parent->children) {
    if (child->name == scope->name) {
      children.push_back(child);
    }
  }

  auto max = std::max_element(
      children.begin(), children.end(), [](VCDScope *a, VCDScope *b) {
        return a->signals.size() < b->signals.size();
      });
  //debug
  // std::cout << (*max)->name << "\n";
  // std::cout << (*max)->signals.size() << "\n";
  return *max;
}

///find VCDScope 'scope' in the given vcd file
static std::pair<std::string, VCDScope *>
findScope(VCDFile *vcd_trace, const std::string &scope) {
  std::deque<VCDScope *> scopes;
  std::vector<std::string> scopeName;
  scopes.push_front(vcd_trace->root_scope);
  std::pair<std::string, VCDScope *> candidate =
      std::make_pair(std::string(), nullptr);
  while (!scopes.empty()) {
    VCDScope *currScope = scopes.front();
    std::string full_name = "";
    if (!scopeName.empty()) {
      scopeName.push_back(currScope->name + "::");
      full_name = std::accumulate(scopeName.begin(), scopeName.end(),
                                  std::string{});
      full_name.erase(full_name.size() - 2, 2);
    } else {
      scopeName.push_back("");
      full_name = "";
    }

    scopes[0] = nullptr;

    //debug
    //    std::cout << std::string(scopeName.size(), '\t') << full_name << " " << currScope->signals.size() << " \n";

    //second option of || is to allow backward compatibility with older versions of harm
    if (full_name == scope || ("::" + full_name == scope)) {
      if (!isScopeUniqueChild(currScope)) {
        messageWarning("Scope '" + full_name +
                       "' is not unique, using the one containing "
                       "the most signals");
        return std::make_pair(full_name,
                              findChildWithMostSignals(currScope));
      }
      return std::make_pair(full_name, currScope);
    }

    if (!currScope->children.empty()) {
      // add children
      for (auto s : currScope->children) {
        scopes.push_front(s);
      }
    } else {
      while (!scopes.empty() && scopes.front() == nullptr) {
        scopes.pop_front();
        scopeName.pop_back();
      }
    }
  }

  messageErrorIf(candidate.second == nullptr,
                 "Scope '" + scope + "' not found !");
  return candidate;
}
static bool isIgnored(VCDVarType type) {

  if (type == VCDVarType::VCD_VAR_PARAMETER) {
    return 1;
  }
  return 0;
}

///retrieve the signals in the given scope 'rootScope', return type
static std::unordered_map<std::string, std::vector<VCDSignal *>>
getSignalsInScope(
    VCDScope *rootScope,
    std::unordered_map<std::string, std::unordered_set<std::string>>
        &scopeFullName_to_SignalsFullName) {
  std::unordered_map<std::string, std::vector<VCDSignal *>>
      _nameToSignal;
  size_t maxDepth =
      clc::vcdUnroll ? clc::vcdUnroll : clc::vcdRecursive;

  std::deque<VCDScope *> scopes;
  std::vector<std::string> scopeName;

  scopes.push_back(rootScope);
  while (!scopes.empty()) {
    VCDScope *currScope = scopes.front();
    scopeName.push_back(scopeName.empty() ? ""
                                          : currScope->name + "::");
    scopes[0] = nullptr;

    std::string scopeNameStr = std::accumulate(
        scopeName.begin(), scopeName.end(), std::string{});
    for (auto signal : currScope->signals) {
      if (isIgnored(signal->type)) {
        continue;
      }

      std::string signalFullName = scopeNameStr + signal->reference;

      messageWarningIf(_nameToSignal.count(signalFullName) &&
                           signal->size != 1,
                       "Multiple definitions of signal '" +
                           signalFullName + "' in trace!");
      _nameToSignal[signalFullName].push_back(signal);
      if (clc::vcdUnroll) {
        scopeFullName_to_SignalsFullName[scopeNameStr].insert(
            signalFullName);
      }
    }

    // add children to front
    if (!currScope->children.empty() &&
        (scopeName.size() <= maxDepth) &&
        find_if(currScope->children.begin(),
                currScope->children.end(), [](VCDScope *s) {
                  return s->type == VCDScopeType::VCD_SCOPE_MODULE;
                }) != currScope->children.end()) {
      for (auto s : currScope->children) {
        if (s->type == VCDScopeType::VCD_SCOPE_MODULE) {
          scopes.push_front(s);
        }
      }
    } else {
      //return to parent
      while (!scopes.empty() && scopes.front() == nullptr) {
        scopes.pop_front();
        scopeName.pop_back();
      }
    }
  }

  return _nameToSignal;
}

VCDBit getSingleBitValue(VCDTimedValue *tv) {
  if (tv->value->get_value_vector() != nullptr) {
    return (*tv->value->get_value_vector())[0];
  } else {
    return tv->value->get_value_bit();
  }
}

char vcdBitToChar(VCDBit bit) {
  switch (bit) {
  case VCDBit::VCD_0:
    return '0';
  case VCDBit::VCD_1:
    return '1';
  case VCDBit::VCD_X:
    return '0';
  case VCDBit::VCD_Z:
    return '0';
  }
  messageError("Unknown VCD bit value");
  return '0';
}

void handleSplittedSignal(
    const TracePtr &trace, VCDSignalValues *clkV,
    const std::pair<std::string, std::vector<VCDSignalValues *>>
        &n_vv,
    std::vector<VCDSignal *> &signal) {

  GenericPtr<void> l = nullptr;

  l = trace->getIntVariable(n_vv.first);

  auto sigsV = n_vv.second;

  size_t index[n_vv.second.size()];
  std::fill(index, index + n_vv.second.size(), 0);
  size_t time = 0;
  //index of last sample for each sub signal
  size_t lastChange[n_vv.second.size()];
  for (size_t i = 0; i < n_vv.second.size(); i++) {
    lastChange[i] = sigsV[i]->size() - 1;
  }

  //for each rising edge of the clock
  for (auto &v_t : *clkV) {

    if (getSingleBitValue(v_t) == VCDBit::VCD_1) {
      //find the next sample time
      for (size_t i = 0; i < n_vv.second.size(); i++) {
        while (index[i] < lastChange[i] &&
               v_t->time >= (*sigsV[i])[index[i] + 1]->time) {
          index[i]++;
        }
      }
      std::string val = "";
      //build the bit vector, each splitted signal contributes a bit
      for (size_t i = 0; i < signal.size(); i++) {
        if (i >= (signal.size() - n_vv.second.size())) {
          val +=
              vcdBitToChar(getSingleBitValue((*sigsV[i])[index[i]]));
        } else {
          val += '0';
        }
      }

      // truncating
      if (val.size() > 64) {
        val.erase(0, val.size() - 64);
      }
      std::static_pointer_cast<IntVariable>(l)->assign(
          time, safeStoull(val, 2));
      time++;
    }
  }
}

void handleWholeSignal(
    const TracePtr &trace, VCDSignalValues *clkV,
    const std::pair<std::string, std::vector<VCDSignalValues *>>
        &n_vv,
    std::vector<VCDSignal *> &signal) {
  messageErrorIf(
      n_vv.second.size() > 1,
      "Internal error: whole signal has more than one value vector");

  //pointer to the variable
  GenericPtr<void> l = nullptr;

  if (signal[0]->size > 1) {
    l = trace->getIntVariable(n_vv.first);
  } else {
    l = trace->getBooleanVariable(n_vv.first);
  }

  VCDSignalValues *sigV = n_vv.second[0];

  size_t index = 0;
  size_t time = 0;
  //index of last sample
  const size_t lastChange = sigV->size() - 1;

  //for each rising edge of the clock
  for (auto &v_t : *clkV) {
    if (getSingleBitValue(v_t) == VCDBit::VCD_1) {
      while (index < lastChange &&
             v_t->time >= (*sigV)[index + 1]->time) {
        index++;
      }
      std::string val = "";
      //build the bit vector
      if (signal[0]->size > 1) {
        for (auto &b : *(*sigV)[index]->value->get_value_vector()) {
          val += vcdBitToChar(b);
        }
      } else {
        val = vcdBitToChar(getSingleBitValue((*sigV)[index]));
        messageErrorIf(val.size() > 1,
                       "Unexpected size of boolean signal");
      }

      // truncating
      if (val.size() > 64) {
        val.erase(0, val.size() - 64);
      }
      if (signal[0]->size > 1) {
        std::static_pointer_cast<IntVariable>(l)->assign(
            time, safeStoull(val, 2));
      } else {
        std::static_pointer_cast<BooleanVariable>(l)->assign(
            time, val == "1");
      }
      time++;
    }
  }
}

void handleFloatSignal(
    const TracePtr &trace, VCDSignalValues *clkV,
    const std::pair<std::string, std::vector<VCDSignalValues *>>
        &n_vv,
    std::vector<VCDSignal *> &signal) {

  expression::FloatVariablePtr n;
  n = trace->getFloatVariable(n_vv.first);

  VCDSignalValues *sigV = n_vv.second[0];

  size_t index = 0;
  size_t time = 0;
  //index of last sample
  const size_t lastChange = sigV->size() - 1;
  //for each rising edge of the clock
  for (auto &v_t : *clkV) {
    if (getSingleBitValue(v_t) == VCDBit::VCD_1) {
      //find the next sample time
      while (index < lastChange &&
             v_t->time >= (*sigV)[index + 1]->time) {
        index++;
      }
      //add the value to the trace
      n->assign(time, (*sigV)[index]->value->get_value_real());
      time++;
    }
  }
}

TracePtr VCDtraceReader::readTrace(const std::string file) {

  _scopeFullName_to_SignalsFullName.clear();

  messageInfo("Parsing " + file);

  //hack to remove unknown scopes: they make the vcd parser fail
#ifdef __linux__
  systemCustom(("sed -i '/$scope unknown/d' " + file).c_str());
#elif __APPLE__
  systemCustom(("sed -i '' '/$scope unknown/d' " + file).c_str());
#endif

  //external library
  VCDFileParser parser;
  VCDFile *vcd_trace = parser.parse_file(file);
  TracePtr trace = nullptr;

  messageErrorIf(!vcd_trace, "VCD parser failed on trace " + file);

  std::pair<std::string, VCDScope *> rootScope;
  if (clc::selectedScope != "") {
    rootScope = findScope(vcd_trace, clc::selectedScope);
    //debug
    //messageInfo("Found scope: " + rootScope.first);
  } else {
    rootScope = std::make_pair(vcd_trace->root_scope->name,
                               vcd_trace->root_scope);
  }

  //retrieve the signals in the given scope
  //note that one signal 'name' might be related to multiple 'VCDSignal', this happens when there are split signals, for example: sig1 -> {sig1[0],sig1[1],sig2[3]}
  std::unordered_map<std::string, std::vector<VCDSignal *>>
      _nameToSignal = getSignalsInScope(
          rootScope.second, _scopeFullName_to_SignalsFullName);

  //sort the split signals in ascending order of index
  for (auto &n_s : _nameToSignal) {
    std::sort(begin(n_s.second), end(n_s.second),
              [](VCDSignal *e1, VCDSignal *e2) {
                return e1->lindex > e2->lindex;
              });
  }

  //    debug
  //    for (auto n : _nameToSignal) {
  //      std::cout << n.first << "\n";
  //    }

  //name of signal to its value (can be more than one if signal is splitted)
  std::unordered_map<std::string, std::vector<VCDSignalValues *>>
      _nameToValues;
  //gather the values of each signal
  for (auto &n_ss : _nameToSignal) {
    for (auto &s : n_ss.second) {
      _nameToValues[n_ss.first].push_back(
          vcd_trace->get_signal_values(s->hash));
    }

    // Check if splitted signals are of size == 1
    if (_nameToValues.at(n_ss.first).size() > 1) {
      for (auto &v : n_ss.second) {
        if (v->size != 1) {
          std::cout << "ALL SIGNALS:"
                    << "\n";
          for (auto &v1 : n_ss.second) {
            std::cout << "\t\t\tName: " << n_ss.first << "\n";
            std::cout << "\t\t\tSize: " << v1->size << "\n";
            std::cout << "\t\t\tLindex: " << v1->lindex << "\n";
            std::cout << "\t\t\tRindex: " << v1->rindex << "\n";
            std::cout << "\t\t\tHash: " << v1->hash << "\n";
            std::cout << "---------------------------------"
                      << "\n";
          }
          messageError(
              "the sub-parts of a splitted signal must be of size "
              "equal to 1");
        }
      }
    }
  }

  //    debug
  //    for (auto &n_s : _nameToSignal) {
  //        std::cout << n_s.first <<","<<_nameToValues.at(n_s.first).size()<<"\n";
  //    }

  //----------- generate variables ----------------------
  std::vector<VarDeclaration> vars;
  std::unordered_set<std::string> vfloats;

  //check clock signal
  if (_nameToValues.count(_clk) == 0) {
    std::stringstream ss;
    ss << "Available signals:\n";
    for (auto &n_s : _nameToSignal) {
      ss << "\t\t\t" << n_s.first << "\n";
    }
    messageError("Can not find clock signal '" + _clk + "'\n" +
                 ss.str());
  }

  VCDSignalValues *clkV = _nameToValues.at(_clk)[0];

  //gather the variables as VarDeclaration
  for (auto &n_ss : _nameToSignal) {
    for (auto &s : n_ss.second) {

      //        debug
      //        std::cout << "Type:" << s->type << "\n";

      std::string type;

      //all the different types of VCD variables are mapped to 4 types: int, bool, double, logic
      if (s->type == VCDVarType::VCD_VAR_REAL ||
          s->type == VCDVarType::VCD_VAR_REALTIME) {
        // double
        type = "double";
        vfloats.insert(n_ss.first);
        vars.push_back(toVarDeclaration(n_ss.first, type, 64));
      } else {
        if (isInt(s->type)) {
          type = "int";
        } else {
          type = "logic";
        }

        // logic & bool
        if (s->size > 1) {
          // intact bit vector
          vars.push_back(toVarDeclaration(n_ss.first, type, s->size));
        } else if (n_ss.second.size() > 1) {
          // splitted bit vector
          vars.push_back(
              toVarDeclaration(n_ss.first, type, n_ss.second.size()));
          break;
        } else {
          // boolean: logic of size 1
          vars.push_back(toVarDeclaration(n_ss.first, type, 1));
        }
      }
    }
  }

  //----------- generate variables end----------------------

  //debug
  //for (auto &e : vars) {
  //  std::cout << e.getName() << "," << (int)e.getSize() << ","
  //            << e.getType() << "\n";
  //}

  //find the length of the trace by counting the number of rising edges of the clock
  size_t traceLength = 0;
  for (auto &v_t : *clkV) {
    if (getSingleBitValue(v_t) == VCDBit::VCD_1) {
      traceLength++;
    }
  }

  if (traceLength == 0) {
    messageWarning(
        "Trace '" + file +
        "' does not contain clock posedges and will be ignored");
    return nullptr;
  }

  //make a new empty trace
  trace = generatePtr<Trace>(vars, traceLength);

  //populate the trace
  for (const auto &n_vv : _nameToValues) {
    auto &signal = _nameToSignal.at(n_vv.first);
    if (vfloats.count(n_vv.first)) {
      // float
      handleFloatSignal(trace, clkV, n_vv, signal);
    } else {
      // logic and bool
      if (n_vv.second.size() > 1) {
        //signal is splitted
        handleSplittedSignal(trace, clkV, n_vv, signal);
      } else {
        //signal is whole
        handleWholeSignal(trace, clkV, n_vv, signal);
      }
    }
  }

  //delete the vcd trace generated by the third party library
  delete vcd_trace;

  return trace;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
VCDtraceReader::getScopeFullName_to_SignalsFullName() const {
  return _scopeFullName_to_SignalsFullName;
}

} // namespace harm
