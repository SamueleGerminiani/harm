#pragma once

#include <climits>
#include <map>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Float.hh"
#include "Int.hh"
#include "VarDeclaration.hh"
#include "formula/atom/Variable.hh"

namespace expression {
enum class ExpType;
} // namespace expression

namespace harm {

/// @brief Trace declaration.
/// This class represents a simulation trace.
class Trace {

public:
  /// @brief Constructor.
  /// @param variables The variables to be set in the trace.
  /// @param length The length of the trace (number of simulation instants).
  Trace(std::vector<VarDeclaration> &variables, size_t length);

  Trace(const Trace &other) = delete;
  Trace &operator=(const Trace &) = delete;

  ~Trace();

  /// @brief Returns the length of the trace.
  size_t getLength() const;

  std::vector<VarDeclaration> getVariables();

  /// @brief Returns the BooleanVariable given its name.
  /// @param name The name of the boolean variable
  expression::BooleanVariablePtr
  getBooleanVariable(const std::string &name) const;

  /// @brief Returns the int variable given its name.
  /// @param name The name of the int variable
  expression::IntVariablePtr
  getIntVariable(const std::string &name) const;

  /// @brief Returns the float variable given its name.
  /// @param name The name of the float variable
  expression::FloatVariablePtr
  getFloatVariable(const std::string &name) const;

  /// @brief Returns the boolean sub-trace containing the values of a boolean variable
  unsigned int *
  getBooleanVariableValues(const std::string &name) const;

  /// @brief Returns the int sub-trace containing the values of a int variable
  expression::UInt *
  getIntVariableValues(const std::string &name) const;

  /// @brief Returns the float sub-trace containing the values of a float variable
  expression::Float *
  getFloatVariableValues(const std::string &name) const;

  ///@bfried returns a copy of the declarations of the variables in the trace
  std::vector<VarDeclaration> getDeclarations();

  ///@brief returns the variables in the trace as a map
  std::unordered_map<std::string,
                     std::pair<expression::ExpType, size_t>>
  getDeclarationsAsMap();

  /// @brief Returns the size of a variable given its name
  size_t getVarSize(std::string varName);

  /// @brief Returns the type of a variable given its name
  expression::ExpType getExpType(const std::string &name);

  /// @brief prints the trace in the range [start, start+n]
  std::string printTrace(size_t start, size_t n);

  /// @brief gets how many cuts are in the trace (cuts are instants where the trace contains an implicit reset)
  std::vector<size_t> &getCuts();

  /// @brief sets the cuts in the trace
  void setCuts(const std::vector<size_t> &cuts);

private:
  /// @brief The float sub-trace containing the values of each Float
  /// variable
  expression::Float *_floatTrace = nullptr;

  /// @brief The boolean sub-trace containing the values of each Boolean
  /// variable
  unsigned int *_booleanTrace = nullptr;

  /// @brief The int sub-trace containing the values of each Int variable
  expression::UInt *_intTrace = nullptr;

  /// @brief The length of the trace (number of simulation instants).
  size_t _length;

  /// indexes of the subtraces merged from multiple traces or that contained resets
  std::vector<size_t> _cuts;

  std::map<std::string, size_t> _varName2size;

  /// @brief The mapping between variable's name and values
  std::map<std::string, uintptr_t> _varName2varValues;
  /// @brief The mapping between logic variable's name and their type
  std::map<std::string, expression::ExpType> _varName2Type;

  /// @brief list of variables in the trace
  std::vector<VarDeclaration> _variables;

  /// @brief utility function to allocate the memory of the trace
  void allocateTrace(std::vector<VarDeclaration> &variables);
  /// @brief utility function to allocate the pointers to acces the memory of the trace
  void allocatePointers(std::vector<VarDeclaration> &variables);

  static_assert(CHAR_BIT == 8, "A byte does not contain 8 bits!");
  const size_t _val4Int = sizeof(expression::UInt) * CHAR_BIT;
};

//smart pointer
using TracePtr = std::shared_ptr<Trace>;

/// @brief Dumps the trace in a CSV file
void dumpTraceAsCSV(const harm::TracePtr &trace,
                    const std::string &filename);

} // namespace harm
