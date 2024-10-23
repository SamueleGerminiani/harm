#pragma once
#include <cstddef>
namespace expression {
enum class ExpType;
}

/// \brief Returns the maximum value of the given type and size.
template <typename T> T max(size_t nBits);
/// \brief Returns the minimum value of the given type and size.
template <typename T> T min(size_t nBits);
