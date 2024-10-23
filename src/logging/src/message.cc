#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "globals.hh"
#include "message.hh"

namespace hlog {

std::string NowTime() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  char buffer[100];
  tm r;
  strftime(buffer, sizeof(buffer), "%X", localtime_r(&tv.tv_sec, &r));
  char result[100];
  snprintf(result, 100, "%s", buffer);
  return result;
}

void _harm_internal_messageInfo(const std::string &message) {
  if (clc::isilent == 0) {
    std::cout << "\e[1m[INFO] " << NowTime() << " - "
              << "Message: " << message << std::endl
              << "\033[0m";
    std::cout.flush();
  }
}

void _harm_internal_messageWarning(const std::string &file,
                                   unsigned int line,
                                   const std::string &message) {

  if (clc::wsilent == 0) {
    std::cout << "\033[1;33m[WARNING] " << NowTime() << " - "
              << "File: " << file << " -- "
              << "Line: " << line << std::endl
              << "\tMessage: " << message << std::endl
              << "\033[0m";

    std::cout.flush();
  }
}

void _harm_internal_messageError(const std::string &file,
                                 unsigned int line,
                                 const std::string &message) {

  std::cerr << "\033[1;31m[ERROR] " << NowTime() << " - "
            << "File: " << file << " "
            << "at line " << line << std::endl
            << "Message: " << message << std::endl
            << "\033[0m";

  std::cerr.flush();
  assert(0);
  exit(1);
}

} // namespace hlog
