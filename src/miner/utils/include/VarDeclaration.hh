#pragma once

#include <stddef.h>
#include <string>

namespace expression {
enum class ExpType;
} // namespace expression

namespace harm {

/// @brief \class VarDeclaration
/// This class represents the declaration of a variable.
class VarDeclaration {

public:
  VarDeclaration();
  VarDeclaration(const std::string &name, expression::ExpType type,
                 size_t size);

  ~VarDeclaration() = default;

  /// @brief Sets the name of the variable
  /// @param name The string literal value to be set.
  void setName(const std::string &name);

  /// @brief Returns the name of the variable.
  /// @returns The string literal value.
  std::string getName() const;

  /// @brief Sets the type of the variable
  /// @param type The enum type value to be set.
  /// @param size The size of the variable.
  void setType(expression::ExpType type, size_t size = 1);

  /// @brief Returns the type of the variable.
  /// @returns The enum type value.
  expression::ExpType getType() const;

  /// @brief Returns the size of the variable.
  /// @returns The size value.
  size_t getSize() const;

  /// @brief Sets the base of the integer/logic variable
  void setBase(size_t base);

/// @brief Returns the base of the integer/logic variable
  size_t getBase();

private:
  /// @brief Stores the name of the variable.
  std::string _name;

  /// @brief Stores the type of the variable.
  expression::ExpType _type;

  /// @brief Stores the size of the variable.
  size_t _size;

  /// @brief Stores the base of the variable (only for int/logic types)
  size_t _base;
};

} // namespace harm
