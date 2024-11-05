#include <algorithm>
#include <cctype>
#include <iostream>
#include <stddef.h>
#include <string>
#include <unordered_set>
#include <utility>

// clang-format off
// clang-format on
#include "ANTLRInputStream.h"
#include "CSVtraceReader.hh"
#include "CommonTokenStream.h"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "VarDeclarationParserHandler.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "internal/common.hpp"
#include "internal/csv_format.hpp"
#include "internal/csv_reader.hpp"
#include "internal/csv_row.hpp"
#include "message.hh"
#include "misc.hh"
#include "tree/ParseTreeWalker.h"
#include "varDeclarationLexer.h"
#include "varDeclarationParser.h"

namespace antlr4 {
namespace tree {
class ParseTree;
} // namespace tree
} // namespace antlr4

namespace harm {
using namespace csv;
using namespace expression;

CSVtraceReader::CSVtraceReader(const std::vector<std::string> &files)
    : TraceReader(files) {}

CSVtraceReader::CSVtraceReader(const std::string &file)
    : TraceReader(std::vector<std::string>({file})) {}

/// @brief parse a variable declaration
static VarDeclaration parseVariableDec(std::string varDecl);

static void addPrefixAndPostfixToLastWord(std::string &input,
                                          const std::string &prefix,
                                          const std::string &postfix);

/// @brief adds prefix and postfix to the last word of the input string
void addPrefixAndPostfixToLastWord(std::string &input,
                                   const std::string &prefix,
                                   const std::string &postfix) {
  if (input.empty()) {
    return;
  }

  auto lastSpacePos =
      std::find_if(input.rbegin(), input.rend(), ::isspace);

  if (lastSpacePos != input.rend()) {
    auto startPos = lastSpacePos.base();
    std::string lastWord(startPos, input.end());
    input.replace(startPos, input.end(), prefix + lastWord + postfix);
  } else {
    input = prefix + input + postfix;
  }
}

///parse a variable declaration
VarDeclaration parseVariableDec(std::string varDecl) {
  addPrefixAndPostfixToLastWord(varDecl, "«", "»");
  hparser::VarDeclarationParserHandler listenerLocDec;
  listenerLocDec.addErrorMessage("\t\t\tIn declaration: " + varDecl);
  antlr4::ANTLRInputStream inputLocDec(varDecl);
  varDeclarationLexer lexerLocDec(&inputLocDec);
  CommonTokenStream tokensLocDec(&lexerLocDec);
  varDeclarationParser parserPrecLocDec(&tokensLocDec);
  tree::ParseTree *treeLocDec = parserPrecLocDec.file();
  tree::ParseTreeWalker::DEFAULT.walk(&listenerLocDec, treeLocDec);

  return listenerLocDec.getVarDeclaration();
}

TracePtr CSVtraceReader::readTrace(const std::string file) {

  std::vector<VarDeclaration> vars_dt;
  //keeps track of the type of the variable for each column of the .csv file
  //one bucket for each type of variable
  std::vector<BooleanVariablePtr> boolVars;
  std::vector<FloatVariablePtr> numVars;
  std::vector<IntVariablePtr> intVars;
  std::unordered_set<std::string> varNames;

  messageInfo("Parsing " + file);

  CSVFormat format;
  format.delimiter(',');
  CSVReader reader(file, format);

  size_t number_of_entries = 0;
  std::string line;
  std::ifstream myfile(file);
  std::getline(myfile, line);
  while (std::getline(myfile, line)) {
    removeSpacesInPlace(line);
    //skip empty lines
    if (line == "") {
      continue;
    }
    ++number_of_entries;
  }

  if (number_of_entries < 1) {
    messageWarning("No data found in trace csv file:" + file);
    return nullptr;
  }

  //parse header of .csv file
  for (auto cn : reader.get_col_names()) {
    auto var = parseVariableDec(cn);
    messageWarningIf(varNames.count(var.getName()),
                     "Variable " + var.getName() +
                         " already declared!");
    varNames.insert(var.getName());
    vars_dt.push_back(var);
  }

  //make an empty trace
  const TracePtr &trace =
      generatePtr<Trace>(vars_dt, number_of_entries);

  //gather all variables of the trace
  for (auto &var : vars_dt) {
    if (isBool(var.getType())) {
      boolVars.push_back(trace->getBooleanVariable(var.getName()));
    } else if (isFloat(var.getType())) {
      numVars.push_back(trace->getFloatVariable(var.getName()));
    } else if (isInt(var.getType())) {
      intVars.push_back(trace->getIntVariable(var.getName()));
    } else {
      messageError("Variable " + var.getName() +
                   " not found in trace!");
    }
  }

  size_t time = 0;
  //for each row of the .csv file
  for (CSVRow &row : reader) {
    size_t bfieldIndex = 0;
    size_t ffieldIndex = 0;
    size_t ifieldIndex = 0;
    size_t fieldIndex = 0;
    //for each field of the row
    for (CSVField &field : row) {
      //varIndexToBucket[fieldIndex] is the type of the variable in the field, all vars are ordered by type and occurrence in the csv header
      if (vars_dt[fieldIndex].getType() == ExpType::Bool) {
        boolVars[bfieldIndex++]->assign(time,
                                        safeStoull(field.get(), 10));
      } else if (vars_dt[fieldIndex].getType() == ExpType::Float) {
        //float type is no longer supported
        numVars[ffieldIndex++]->assign(time, safeStod(field.get()));
      } else if (isInt(vars_dt[fieldIndex].getType())) {
        size_t base = vars_dt[fieldIndex].getBase();
        auto val = field.get();
        if (base == 2) {
          messageErrorIf(!isBase2(val),
                         "val '" + val +
                             "' is not a valid binary number");
          //substitute 'x' and 'z' from the string with 0
          if (val.size() > 64) {
            //if the number is too big, truncate it
            val.erase(0, val.size() - 64);
          }
          std::replace_if(
              val.begin(), val.end(),
              [](char c) { return c == 'x' || c == 'z'; }, '0');
        }
        if (intVars[ifieldIndex]->getType().first == ExpType::SInt) {
          intVars[ifieldIndex]->assign(time, safeStoll(val, base));
        } else {
          intVars[ifieldIndex]->assign(time, safeStoull(val, base));
        }
        ifieldIndex++;
      } else {
        messageError("Unknown var type in trace file: '" + file +
                     "'");
      }
      fieldIndex++;
    }
    time++;
  }

  return trace;
}

} // namespace harm
