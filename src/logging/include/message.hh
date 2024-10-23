
#pragma once

#include <string>

namespace hlog {

/// @brief Prints information message.
/// @param message is the actual message to print.
void _harm_internal_messageInfo(const std::string &message);

/// @brief Prints warning message.
/// @param file is expanded by macro to the raising point of the message.
/// @param line is expanded by macro to the raising point of the message.
/// @param message is the actual message to print.
void _harm_internal_messageWarning(const std::string &file,
                                   unsigned int line,
                                   const std::string &message);

/// @brief Prints an error message, which causes exit.
/// @param file is expanded by macro to the raising point of the message.
/// @param line is expanded by macro to the raising point of the message.
/// @param message is the actual message to print.
void _harm_internal_messageError(const std::string &file,
                                 unsigned int line,
                                 const std::string &message);

#define messageInfo(message)                                         \
  hlog::_harm_internal_messageInfo((message))

#define messageInfoIf(condition, message)                            \
  if (condition)                                                     \
  hlog::_harm_internal_messageInfo((message))

#define messageWarning(message)                                      \
  hlog::_harm_internal_messageWarning(__FILE__, __LINE__, (message))

#define messageWarningIf(condition, message)                         \
  if (condition)                                                     \
  hlog::_harm_internal_messageWarning(__FILE__, __LINE__, (message))

#define messageError(message)                                        \
  hlog::_harm_internal_messageError(__FILE__, __LINE__, (message))

#define messageErrorIf(condition, message)                           \
  if (condition)                                                     \
  hlog::_harm_internal_messageError(__FILE__, __LINE__, (message))

} // namespace hlog
