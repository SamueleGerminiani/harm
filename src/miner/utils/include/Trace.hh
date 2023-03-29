#pragma once

#include "DataType.hh"
#include "Logic.hh"
#include "exp.hh"

#include <climits>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace harm {

using VarDeclaration = std::tuple<std::string, expression::VarType, size_t>;

/// @brief Trace declaration.
/// This class represents a simulation trace.
class Trace {

public:
  /// @brief Constructor.
  /// @param variables The variables to be set in the trace.
  /// @param length The length of the trace (number of simulation instants).
  Trace(std::vector<DataType> &variables, size_t length);

  /// @brief Copy constructor
  Trace(const Trace &other) = delete;
  std::vector<Trace *> newTracesWithSAFault(const std::string &varName);

  /// @brief Destructor.
  ~Trace();

  /// @brief Returns the length of the trace.
  size_t getLength() const;

  std::vector<DataType> getVariables() { return _variables; }

  /// @brief Returns the BooleanVariable given its name.
  /// @param name The name of the boolean variable
  /// @return An instance of BooleanVariable
  expression::BooleanVariable *
  getBooleanVariable(const std::string &name) const;

  /// @brief Returns the logic variable given its name.
  /// @param name The name of the logic variable
  /// @return An instance of ExpressionVariable<Logic>
  expression::LogicVariable *getLogicVariable(const std::string &name) const;

  /// @brief Returns the numeric variable given its name.
  /// @param name The name of the numeric variable
  /// @return An instance of ExpressionVariable<Numeric>
  expression::NumericVariable *
  getNumericVariable(const std::string &name) const;

  unsigned int *getBooleanVariableValues(const std::string &name) const;

  expression::ULogic *getLogicVariableValues(const std::string &name) const;

  expression::Numeric *getNumericVariableValues(const std::string &name) const;

  /// @brief Assignment operator
  /// @param other The other trace to be copied.
  Trace &operator=(const Trace &other) = delete;

  void setLength(size_t length) { _length = length; }
  std::vector<VarDeclaration> getDeclarations() {
    std::vector<VarDeclaration> ret;

    for (auto v : _variables) {
      ret.emplace_back(v.getName(), _varName2Type.at(v.getName()),
                       _name2size.at(v.getName()));
    }
    return ret;
  }

  size_t getVarSize(std::string varName) {
    messageErrorIf(_name2size.count(varName) == 0,
                   "Did not find variable '" + varName + "'");
    return _name2size.at(varName);
  }
  expression::VarType getVarType(const std::string &name) {
    return _varName2Type.at(name);
  }

  std::string printTrace(size_t start, size_t n);
  std::vector<size_t> &getCuts();
  void setCuts(const std::vector<size_t> &cuts);

private:
  /// @brief The numeric sub-trace containing the values of each Numeric
  /// variable
  double *_numeriTrace;

  /// @brief The boolean sub-trace containing the values of each Boolean
  /// variable
  unsigned int *_booleanTrace;

  /// @brief The logic sub-trace containing the values of each Logic variable
  expression::ULogic *_logicTrace;

  /// @brief The length of the trace
  size_t _length;

  std::vector<size_t> _cuts;

  std::map<std::string, size_t> _name2size;

  /// @brief The mapping between variable's name and values
  std::map<std::string, uintptr_t> _varName2varValues;
  std::map<std::string, expression::VarType> _varName2Type;

  std::vector<DataType> _variables;

  void _allocateTrace(std::vector<DataType> &variables);
  void _allocatePointers(std::vector<DataType> &variables);

  static_assert(CHAR_BIT == 8, "A byte does not contain 8 bits!");
  size_t _val4Logic = sizeof(expression::ULogic) * CHAR_BIT;
};

} // namespace harm
