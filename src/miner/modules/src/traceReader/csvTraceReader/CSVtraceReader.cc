#include "CSVtraceReader.hh"
#include "csv.hpp"
#include "exp.hh"
#include "expUtils/VarType.hh"
#include "expUtils/expUtils.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "varDeclarationParser.hh"

#include <bitset>
#include <cctype>
#include <iostream>

namespace harm {
using namespace csv;
using namespace expression;

CSVtraceReader::CSVtraceReader(const std::vector<std::string> &files)
    : TraceReader(files) {}

CSVtraceReader::CSVtraceReader(const std::string &file)
    : TraceReader(std::vector<std::string>({file})) {}

///var declaration to cpp class
DataType toDataType(std::string name, std::string type, size_t size) {
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
static void addPrefixAndPostfixToLastWord(std::string& input, const std::string& prefix, const std::string& postfix) {
    if (input.empty()) {
        return;
    }

    auto lastSpacePos = std::find_if(input.rbegin(), input.rend(), ::isspace);

    if (lastSpacePos != input.rend()) {
        auto startPos = lastSpacePos.base();
        std::string lastWord(startPos, input.end());
        input.replace(startPos, input.end(), prefix + lastWord + postfix);
    } else {
        input = prefix + input + postfix;
    }
}

///parse a variable declaration
std::pair<std::string, std::pair<std::string, size_t>>
parseVariable(std::string varDecl) {
    addPrefixAndPostfixToLastWord(varDecl, "«", "»");
  hparser::VarDeclarationParserHandler listenerLocDec;
  listenerLocDec.addErrorMessage("\t\t\tIn declaration: " + varDecl);
  antlr4::ANTLRInputStream inputLocDec(varDecl);
  varDeclarationLexer lexerLocDec(&inputLocDec);
  CommonTokenStream tokensLocDec(&lexerLocDec);
  varDeclarationParser parserPrecLocDec(&tokensLocDec);
//    //print tokens
//    std::map<size_t, std::string> indexToToken;
//    for (auto [token,index] : parserPrecLocDec.getTokenTypeMap()) {
//        indexToToken[index] = token;
//    }
//    for (auto &i : lexerLocDec.getAllTokens()) {
//        std::cout << i->toString() <<" "<<indexToToken.at(i->getType())<<"\n";
//    }
  tree::ParseTree *treeLocDec = parserPrecLocDec.file();
  tree::ParseTreeWalker::DEFAULT.walk(&listenerLocDec, treeLocDec);
//  std::cout <<listenerLocDec.getVarDeclaration().first  << "\n";
//  std::cout <<listenerLocDec.getVarDeclaration().second.second  << "\n";

  return listenerLocDec.getVarDeclaration();
}

Trace *CSVtraceReader::readTrace(const std::string file) {

  std::vector<DataType> vars_dt;
  std::vector<VarType> varIndexToBucket;
  std::vector<BooleanVariable *> boolVars;
  std::vector<NumericVariable *> numVars;
  std::vector<LogicVariable *> logVars;
  std::unordered_set<std::string> varNames;
  messageInfo("Parsing " + file);

  CSVFormat format;
  format.delimiter(',');
  CSVReader reader(file, format);
  for (auto cn : reader.get_col_names()) {
    auto var = parseVariable(cn);
    messageWarningIf(varNames.count(var.first), "Variable " + var.first + " already declared!");
    varNames.insert(var.first);
    vars_dt.push_back(
        toDataType(var.first, var.second.first, var.second.second));


    if (vars_dt.back().getType() == VarType::Bool) {
      varIndexToBucket.push_back(VarType::Bool);
    } else if (vars_dt.back().getType() == VarType::Numeric) {
      varIndexToBucket.push_back(VarType::Numeric);
    } else if (vars_dt.back().getType() == VarType::SLogic) {
      varIndexToBucket.push_back(VarType::SLogic);
    } else if (vars_dt.back().getType() == VarType::ULogic) {
      varIndexToBucket.push_back(VarType::ULogic);
    } else {
      messageError("Unknown var type!");
    }
  }

  size_t number_of_entries = 0;
  std::string line;
  std::ifstream myfile(file);
  std::getline(myfile, line);
  while (std::getline(myfile, line)) {
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
    //workaround
    if (!std::isdigit(line[0]) && !(line[0] == '-')) {
      break;
    }
    ++number_of_entries;
  }
  messageErrorIf(number_of_entries <= 1, "No data found in csv file:" + file);

  Trace *trace = new Trace(vars_dt, number_of_entries);

  for (auto &var : vars_dt) {
    if (var.getType() == VarType::Bool) {
      boolVars.push_back(trace->getBooleanVariable(var.getName()));
    } else if (var.getType() == VarType::Numeric) {
      numVars.push_back(trace->getNumericVariable(var.getName()));
    } else {
      logVars.push_back(trace->getLogicVariable(var.getName()));
    }
  }

  size_t time = 0;
  for (CSVRow &row : reader) {
    size_t bfieldIndex = 0;
    size_t nfieldIndex = 0;
    size_t lfieldIndex = 0;
    size_t fieldIndex = 0;
    for (CSVField &field : row) {
      if (varIndexToBucket[fieldIndex] == VarType::Bool) {
        boolVars[bfieldIndex++]->assign(time, field.get<bool>());
      } else if (varIndexToBucket[fieldIndex] == VarType::Numeric) {
        if (numVars[nfieldIndex]->getType().second == 64) {
          numVars[nfieldIndex++]->assign(time, field.get<double>());
        } else {
          numVars[nfieldIndex++]->assign(time, field.get<float>());
        }
      } else {
        if (logVars[lfieldIndex]->getType().first == VarType::SLogic) {
          logVars[lfieldIndex++]->assign(time, field.get<SLogic>());
        } else {
          logVars[lfieldIndex++]->assign(time, field.get<ULogic>());
        }
      }
      fieldIndex++;
    }
    time++;
  }

  for (auto i : boolVars) {
    delete i;
  }
  for (auto i : logVars) {
    delete i;
  }
  for (auto i : numVars) {
    delete i;
  }

  return trace;
}

} // namespace harm
