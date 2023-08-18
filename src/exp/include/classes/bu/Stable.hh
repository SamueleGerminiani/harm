#pragma once

#include "classes/function/Function.hh"
#include <string>
#include <climits>

namespace expression {


template <typename T> class Stable : public Function<bool> {

  public:
    /// @brief Constructor.
    /// @param v Pointer to variable's values
    /// @param name The name of the variable
    /// @param max_time the largest simulation time that can be provided to
    /// the method evaluate.
	Stable(T *operand, size_t max_time);

    /// @brief copy Constructor.
    /// @param other The other variable to be copied.
    Stable(const Stable &other)=default;
    Stable &operator=(const Stable &other)=delete;

    /// @brief Destructor.
    virtual ~Stable();

    /// @brief Return the expression of the stable operator
    /// @return A reference to the expression.
    T &getItem();

    /// @brief 
    /// @param time The simulation time
    /// @return The evaluation at the given simulation time
    bool evaluate(size_t time) override;

  private:
    T* _operand;
};

}

#include "Stable.i.hh"

