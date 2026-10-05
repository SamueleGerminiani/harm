
#pragma once

#include <stdexcept>
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

/// @brief Error raised by messageError while a ScopedThrowOnError is active (instead of exiting)
class HarmError : public std::runtime_error {
public:
  explicit HarmError(const std::string &message)
      : std::runtime_error(message) {}
};

/// @brief While an instance exists (in the current thread), messageError throws HarmError instead
/// of printing the error and terminating HARM. Used where a failure can be handled locally, e.g.
/// to skip an invalid proposition.
class ScopedThrowOnError {
public:
  ScopedThrowOnError();
  ~ScopedThrowOnError();
  ScopedThrowOnError(const ScopedThrowOnError &) = delete;
  ScopedThrowOnError &operator=(const ScopedThrowOnError &) = delete;
};

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

void dumpErrorToFile(std::string message, int custom_errno = -1,
                     int custom_signal = -1,
                     bool withException = false);
} // namespace hlog
