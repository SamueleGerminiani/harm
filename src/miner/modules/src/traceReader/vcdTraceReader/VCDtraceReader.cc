#include "VCDtraceReader.hh"
#include "VCDFileParser.hpp"
#include "exp.hh"
#include "expUtils/VarType.hh"
#include "expUtils/expUtils.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"

#include <bitset>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_set>

namespace harm {

using namespace expression;

VCDtraceReader::VCDtraceReader(const std::vector<std::string> &files,
                               const std::string &clk)
    : TraceReader(files) {
  _clk = clk;
}

VCDtraceReader::VCDtraceReader(const std::string &file, const std::string &clk)
    : TraceReader(std::vector<std::string>({file})) {
  _clk = clk;
}

///var declaration to cpp class
static DataType toDataType(std::string name, std::string type, size_t size) {
  DataType ret;
  auto type_size = variableTypeFromString(type, size);

  //optimization: 1 bit logic to bool
  if ((type_size.first == VarType::SLogic ||
       type_size.first == VarType::ULogic) &&
      type_size.second == 1) {
    type_size.first = VarType::Bool;
    type_size.second = 1;
  }

  ret.setName(name);
  ret.setType(type_size.first, type_size.second);

  return ret;
}

///utility function to find the prefix common to all variables (improves readability)
static size_t findCommonPrefixLength(VCDScope *vcd_scope) {
  std::deque<VCDScope *> scopes;
  std::vector<std::string> scopeName;
  std::string name = "";
  // find common prefix
  size_t commonPrefixSize = 0;
  scopes.push_back(vcd_scope);
  while (!scopes.empty()) {
    VCDScope *currScope = scopes.front();
    scopeName.push_back(currScope->name + "::");
    if (!currScope->signals.empty()) {
      std::string commonPrefix =
          (std::accumulate(scopeName.begin(), scopeName.end(), std::string{}));
      commonPrefixSize = commonPrefix.size();
      return commonPrefixSize;
      break;
    }
    if (!currScope->children.empty()) {
      // add children
      for (auto s : currScope->children) {
        scopes.push_front(s);
      }
    }
  }
  messageError("No signals in scope '" + vcd_scope->name + "'");
  return 0;
}

///find scope 'scope' in the given vcd file
static VCDScope *findScope(VCDFile *vcd_trace, const std::string &scope) {
  std::deque<VCDScope *> scopes;
  std::vector<std::string> scopeName;
  scopes.push_front(vcd_trace->root_scope);
  while (!scopes.empty()) {
    VCDScope *currScope = scopes.front();
    scopeName.push_back(currScope->name + "::");
    scopes[0] = nullptr;

    std::string name =
        std::accumulate(scopeName.begin(), scopeName.end(), std::string{});
    name.erase(name.size() - 2, 2);
    if (name == scope) {
      return currScope;
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

  messageError("Scope '" + scope + "' not found !");
  return nullptr;
}

///retrieve the signals in the given scope 'rootScope', return type
static std::unordered_map<std::string, std::vector<VCDSignal *>>
getSignalsInScope(VCDScope *rootScope, size_t commonPrefixSize = 0,
                  bool recursive = 1) {
  std::unordered_map<std::string, std::vector<VCDSignal *>> _nameToSignal;
  if (!recursive) {
    for (auto signal : rootScope->signals) {
      // ignore
      if (signal->type ==
          VCDVarType::VCD_VAR_PARAMETER /*|| signal->size > 64*/) {
        continue;
      }
      _nameToSignal[signal->reference].push_back(signal);
    }
    return _nameToSignal;
  }

  std::deque<VCDScope *> scopes;
  std::vector<std::string> scopeName;

  scopes.push_back(rootScope);
  while (!scopes.empty()) {
    VCDScope *currScope = scopes.front();
    scopeName.push_back(currScope->name + "::");
    scopes[0] = nullptr;

    for (auto signal : currScope->signals) {
      // ignore
      if (signal->type ==
          VCDVarType::VCD_VAR_PARAMETER /*|| signal->size > 64*/) {
        continue;
      }

      std::string name =
          std::accumulate(scopeName.begin(), scopeName.end(), std::string{}) +
          signal->reference;
      name.erase(0, commonPrefixSize);

      _nameToSignal[name].push_back(signal);
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

  return _nameToSignal;
}

Trace *VCDtraceReader::readTrace(const std::string file) {

  messageInfo("Parsing " + file);

  //hack to remove unknown scopes: they make the vcd parser fail
#ifdef linux
  system(("sed -i '/$scope unknown/d' " + file).c_str());
#endif

  //external library
  VCDFileParser parser;
  VCDFile *vcd_trace = parser.parse_file(file);
  Trace *trace = nullptr;

  messageErrorIf(!vcd_trace, "VCD parser failed on trace " + file);

  VCDScope *rootScope = nullptr;
  if (clc::selectedScope != "") {
    rootScope = findScope(vcd_trace, clc::selectedScope);
  } else {
    rootScope = vcd_trace->root_scope;
  }

  //change the name of this 'run' of harm (used when printing/dumping stats), only if the user did not already define a name, same thing for the scope
  if (hs::name == "") {
    if (clc::selectedScope == "") {
      hs::name = rootScope->name;
    } else {
      hs::name = clc::selectedScope;
    }
  }

  //retrieve the signals in the given scope
  //note that one signal 'name' might be related to multiple 'VCDSignal', this happens when there are split signals, for example: sig1 -> {sig1[0],sig1[1],sig2[3]}
  size_t commonPrefixSize = findCommonPrefixLength(rootScope);
  std::unordered_map<std::string, std::vector<VCDSignal *>> _nameToSignal =
      getSignalsInScope(rootScope, commonPrefixSize, clc::vcdRecursive);

  //sort the split signals in ascending order of index
  for (auto &n_s : _nameToSignal) {
    std::sort(
        begin(n_s.second), end(n_s.second),
        [](VCDSignal *e1, VCDSignal *e2) { return e1->lindex > e2->lindex; });
  }

  //    debug
  //    for (auto n : _nameToSignal) {
  //      std::cout << n.first << "\n";
  //    }

  std::unordered_map<std::string, std::vector<VCDSignalValues *>> _nameToValues;
  for (auto &n_ss : _nameToSignal) {
    for (auto &s : n_ss.second) {
      _nameToValues[n_ss.first].push_back(
          vcd_trace->get_signal_values(s->hash));
    }

    // Check if splitted signals are of size == 1
    if (_nameToValues.at(n_ss.first).size() > 1) {
      for (auto &v : n_ss.second) {
        if (v->size != 1) {
          std::cout << "the sub-part of a splitted signal must be of size "
                       "equal to 1"
                    << "\n";
          std::cout << "ALL SIGNALS:"
                    << "\n";
          for (auto &v1 : n_ss.second) {
            std::cout << "\t\t\tName: " << n_ss.first << "\n";
            std::cout << "\t\t\tSize: " << v1->size << "\n";
            std::cout << "\t\t\tLindex: " << v1->lindex << "\n";
            std::cout << "\t\t\tRindex: " << v1->rindex << "\n";
            std::cout << "\t\t\tHash: " << v1->hash << "\n";
          }
          assert(0);
          exit(1);
        }
      }
    }
  }
  // FIXME: can we definitely remove this?
  // remove signals with size > 64
  // std::vector<std::string> gt64names;
  // for (auto &n_vv : _nameToValues) {
  //  if (n_vv.second.size() > 64) {
  //    gt64names.push_back(n_vv.first);
  //  }
  //}
  // for (auto n : gt64names) {
  //  _nameToValues.erase(n);
  //  _nameToSignal.erase(n);
  //}

  //harm dose not support logic types larger than 64 bits
  std::vector<std::string> gt64names;
  for (auto &n_vv : _nameToValues) {
    if (n_vv.second.size() > 64) {
      messageWarning("Truncating '" + n_vv.first + "' to 64 bits");
    }
  }

  //    debug
  //    for (auto &n_s : _nameToSignal) {
  //        std::cout << n_s.first <<","<<_nameToValues.at(n_s.first).size()<<
  //        "\n";
  //    }

  //----------- generate variables ----------------------
  std::vector<DataType> vars;
  std::unordered_set<std::string> vfloats;

  //check clock signal
  if (_nameToValues.count(_clk) == 0) {
    std::stringstream ss;
    ss << "Available signals:\n";
    for (auto &n_s : _nameToSignal) {
      ss << "\t\t\t" << n_s.first << "\n";
    }
    messageError("Can not find clock signal '" + _clk + "'\n" + ss.str());
  }

  VCDSignalValues *clkV = _nameToValues.at(_clk)[0];
  // erase clk signal: it will not be part of the final trace
  _nameToValues.erase(_clk);
  _nameToSignal.erase(_clk);

  for (auto &n_ss : _nameToSignal) {

    for (auto &s : n_ss.second) {

      //        debug
      //        std::cout << "Type:" << s->type << "\n";
      std::string type;
      if (s->type == VCDVarType::VCD_VAR_REAL ||
          s->type == VCDVarType::VCD_VAR_REALTIME) {
        // float
        type = "float";
        vfloats.insert(n_ss.first);
        vars.push_back(toDataType(n_ss.first, type, 32));
      } else {
        if (s->type == VCDVarType::VCD_VAR_INTEGER) {
          type = "integer";
        } else {
          type = "wire";
        }

        // logic & bool
        if (s->size > 1) {
          // intact bit vector
          vars.push_back(
              toDataType(n_ss.first, type, s->size > 64 ? 64 : s->size));
        } else if (n_ss.second.size() > 1) {
          // splitted bit vector
          vars.push_back(
              toDataType(n_ss.first, type,
                         n_ss.second.size() > 64 ? 64 : n_ss.second.size()));
          break;
        } else {
          // boolean
          vars.push_back(toDataType(n_ss.first, type, 1));
        }
      }
    }
  }

  //----------- generate variables end----------------------

  //debug
  //    for (auto &e : vars) {
  //      std::cout << e.getName() << "," << (int)e.getSize() << "\n";
  //    }

  //find the length of the trace
  size_t traceLength = 0;
  for (auto &v_t : *clkV) {
    if (v_t->value->get_value_bit() == VCDBit::VCD_1) {
      traceLength++;
    }
  }

  trace = new Trace(vars, traceLength);
  //populate the trace
  for (auto &n_vv : _nameToValues) {
    auto &signal = _nameToSignal.at(n_vv.first);
    if (vfloats.count(n_vv.first)) {
      // float
      expression::NumericVariable *n;
      n = trace->getNumericVariable(n_vv.first);

      VCDSignalValues *sigV = n_vv.second[0];

      size_t index = 0;
      size_t time = 0;
      const size_t lastChange = sigV->size() - 1;
      for (auto &v_t : *clkV) {

        if (v_t->value->get_value_bit() == VCDBit::VCD_1) {
          while (index < lastChange && v_t->time >= (*sigV)[index + 1]->time) {
            index++;
          }
          n->assign(time, (*sigV)[index]->value->get_value_real());
          time++;
        }
      }

      delete n;

    } else {
      // logic and bool

      if (n_vv.second.size() > 1) {
        expression::LogicVariable *l;
        l = trace->getLogicVariable(n_vv.first);
        auto sigsV = n_vv.second;

        size_t index[n_vv.second.size()];
        std::fill(index, index + n_vv.second.size(), 0);
        size_t time = 0;
        size_t lastChange[n_vv.second.size()];
        for (size_t i = 0; i < n_vv.second.size(); i++) {
          lastChange[i] = sigsV[i]->size() - 1;
        }

        for (auto &v_t : *clkV) {

          if (v_t->value->get_value_bit() == VCDBit::VCD_1) {
            for (size_t i = 0; i < n_vv.second.size(); i++) {
              while (index[i] < lastChange[i] &&
                     v_t->time >= (*sigsV[i])[index[i] + 1]->time) {
                index[i]++;
              }
            }
            std::string val = "";
            for (size_t i = 0; i < signal.size(); i++) {

              if (i >= (signal.size() - n_vv.second.size()) &&
                  (*sigsV[i])[index[i]]->value->get_value_bit() ==
                      VCDBit::VCD_1) {
                val += '1';
              } else {
                val += '0';
              }
            }
            // truncating
            if (val.size() > 64) {
              val.erase(0, val.size() - 64);
            }
            l->assign(time, std::stoull(val, nullptr, 2));
            time++;
          }
        }

        delete l;
      } else if (signal[0]->size > 1) {
        expression::LogicVariable *l;
        l = trace->getLogicVariable(n_vv.first);
        VCDSignalValues *sigV = n_vv.second[0];

        size_t index = 0;
        size_t time = 0;
        const size_t lastChange = sigV->size() - 1;
        for (auto &v_t : *clkV) {

          if (v_t->value->get_value_bit() == VCDBit::VCD_1) {
            while (index < lastChange &&
                   v_t->time >= (*sigV)[index + 1]->time) {
              index++;
            }
            std::string val = "";
            for (auto &b : *(*sigV)[index]->value->get_value_vector()) {
              if (b == VCDBit::VCD_1) {
                val += '1';
              } else {
                val += '0';
              }
            }
            // truncating
            if (val.size() > 64) {
              val.erase(0, val.size() - 64);
            }
            l->assign(time, std::stoull(val, nullptr, 2));
            time++;
          }
        }

        delete l;
      } else {
        // FIXME: this should be removable
        expression::BooleanVariable *p;
        size_t bitIndex = n_vv.second.size() - 1;
        for (auto sigV : n_vv.second) {
          std::string i = "";
          if (n_vv.second.size() > 1) {
            i = "[" + std::to_string(bitIndex--) + "]";
          }

          p = trace->getBooleanVariable(n_vv.first + i);

          size_t index = 0;
          size_t time = 0;
          const size_t lastChange = sigV->size() - 1;
          for (auto &v_t : *clkV) {

            if (v_t->value->get_value_bit() == VCDBit::VCD_1) {
              while (index < lastChange &&
                     v_t->time >= (*sigV)[index + 1]->time) {
                index++;
              }

              p->assign(time, (*sigV)[index]->value->get_value_bit() ==
                                  VCDBit::VCD_1);
              time++;
            }
          }

          delete p;
        }
      }
    }
  }

  delete vcd_trace;
  return trace;
}

} // namespace harm
