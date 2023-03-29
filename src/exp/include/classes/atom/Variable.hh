#pragma once

#include "Atom.hh"
#include <string>
#include <climits>

namespace expression {

// Forwards declaration

/// @brief ExpressionVariable<ULogic> declaration.
/// This class represents a Logic variable.
class LogicVariable : public Atom<ULogic> {
  public:
    /// @brief Constructor for Logic.
    /// @param v A pointer to the variable's values.
    /// @param size The size of the logic value.
    /// @param name the name of the variable.
    /// @param max_time the largest simulation time that can be provided to
    /// the method evaluate.
	  LogicVariable(ULogic *v,const std::string &name,VarType type, size_t size, size_t max_time);

    /// @brief copy Constructor.
    /// @param other The other variable to be copied.
    LogicVariable(const LogicVariable &other)=default;

    /// @brief Assignment operator
    /// @param other The other variable to be copied
    LogicVariable &operator=(const LogicVariable &other)=delete;

    /// @brief Destructor.
    ~LogicVariable() override = default;


    /// @brief Returns the value of the variable in the given simulation time.
    /// @param time The simulation time.
    /// @return The value of the variable.
    ULogic evaluate(size_t time) override;

    /// @brief Sets the value of the variable in a given simulation time.
    /// @param time The simulation time.
    /// @param value The value set for the variable.
    void assign(size_t time, ULogic value);


    /// @brief Accepts a visitor to visit the current object.
    /// @param vis The visitor.
    void acceptVisitor(ExpVisitor &vis) override;

    std::string getName(){return _name;}
    // declare friend class to allow it access private variables
    friend class TraceChangerVisitor;

  private:
    // A pointer to variable's values
    // This pointer must not be deallocated as values are stored in a Trace!
    ULogic *_v;

    std::string _name;

    // mask to get a Logic value from a ULogic value.
    ULogic _mask;

    // number of values stored in ULogic.
    size_t _valuesInside;

    size_t _val4Logic = sizeof(expression::ULogic) * CHAR_BIT;
};

class NumericVariable : public Atom<Numeric> {
  public:
    /// @brief Constructor for Numeric.
    /// @param v A pointer to the variable's values
    /// @param name the name of the variable
    /// @param max_time the largest simulation time that can be provided to
    /// the method evaluate.
	  NumericVariable(Numeric *v, const std::string &name, VarType type, size_t size, size_t max_time) ;

    /// @brief copy Constructor.
    /// @param other The other variable to be copied.
    NumericVariable(const NumericVariable &other)=default;

    NumericVariable &operator=(const NumericVariable &other)=delete;
    /// @brief Destructor.
    ~NumericVariable() override = default;

    /// @brief Returns the value of the variable in the given simulation time.
    /// @param time The simulation time.
    /// @return The value of the variable.
    Numeric evaluate(size_t time) override;

    /// @brief Sets the value of the variable in a given simulation time.
    /// @param time The simulation time.
    /// @param value The value set for the variable.
    void assign(size_t time, Numeric value);

    /// @brief Assignment operator.
    /// @param other The other variable to be copied.

    /// @brief Accepts a visitor to visit the current object.
    /// @param vis The visitor.
    void acceptVisitor(ExpVisitor &vis) override;

    std::string getName(){return _name;}
    // declare friend class to allow it access private variables
    friend class TraceChangerVisitor;

  private:
    // A pointer to variable's values
    // This pointer must not be deallocated as values are stored in a Trace!
    Numeric *_v;
    std::string _name;
};

class BooleanVariable : public Atom<bool> {

  public:
    /// @brief Constructor.
    /// @param v Pointer to variable's values
    /// @param name The name of the variable
    /// @param max_time the largest simulation time that can be provided to
    /// the method evaluate.
	  BooleanVariable(unsigned int *v, const std::string &name, size_t max_time);

    /// @brief copy Constructor.
    /// @param other The other variable to be copied.
    BooleanVariable(const BooleanVariable &other)=default;
    BooleanVariable &operator=(const BooleanVariable &other)=delete;

    /// @brief Destructor.
    ~BooleanVariable() override = default;

    /// @brief Returns the value of the variable in the given simulation time
    /// @param time The simulation time
    /// @return The value of the boolean variable
    bool evaluate(size_t time) override;

    /// @brief Sets the value of the variable in a given simulation time
    /// @param time The simulation time
    /// @param value The value set for the variable
    void assign(size_t time, bool value);

    /// @brief Assignment operator
    /// @param other The other variable to be copied.

    /// @brief Accepts a visitor to visit the current object.
    /// @param vis The visitor.
    void acceptVisitor(ExpVisitor &vis) override;
    std::string getName(){return _name;}


    // declare friend class to allow it access private variables
    friend class TraceChangerVisitor;

  private:
    // A pointer to variable's values
    // This pointer must not be deallocated as values are stored in a Trace!
    unsigned int *_v;
    std::string _name;
};

} // namespace oden

