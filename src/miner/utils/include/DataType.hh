#pragma once

#include <string>

#include "expUtils/VarType.hh"
#include "Location.hh"

namespace harm {

/// @brief Variable declaration.
/// This class represents the declaration of a variable.
/// It consists of a name, a type, a size, and a direction.
/// @brief Variable direction.


class DataType {

  public:
    /// @brief Constructor.
    DataType();

    /// @brief Destructor.
    ~DataType() = default;

    /// @brief Sets the name of the variable
    /// @param name The string literal value to be set.
    void setName(const std::string &name);

    /// @brief Returns the name of the variable.
    /// @returns The string literal value.
    std::string getName() const;

    /// @brief Sets the type of the variable
    /// @param type The enum type value to be set.
    /// @param size The size of the variable.
    void setType(expression::VarType type, uint8_t size = 1);

    /// @brief Returns the type of the variable.
    /// @returns The enum type value.
    expression::VarType getType() const;

    /// @brief Returns the size of the variable.
    /// @returns The size value.
    uint8_t getSize() const;

    /// @brief Sets the direction of the variable
    /// @param dir The enum direction value to be set.
    void setLocation(Location dir);

    /// @brief Returns the direction of the variable.
    /// @returns The enum direction value.
    Location getLocation() const;

  private:
    /// @brief Stores the name of the variable.
    std::string _name;

    /// @brief Stores the type of the variable.
    expression::VarType _type;

    /// @brief Stores the size of the variable.
    uint8_t _size;

    /// @brief Stores the direction of the variable.
    Location _location;
};

} // namespace oden
