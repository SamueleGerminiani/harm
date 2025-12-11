#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include <cstring>
#include <fstream>

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

void dumpErrorToFile(std::string message, int custom_errno,
                     int custom_signal, bool withException) {

  if (!isFileEmpty("error.log")) {
    deleteLastLine("error.log");
    std::ofstream file;
    file.open("error.log", std::ios::app);
    file << ",\n";
    file.close();
  } else {
    std::ofstream file;
    file.open("error.log", std::ios::app);
    file << "[\n";
    file.close();
  }

  removeDoubleQuotes(message);

  std::ofstream file;
  file.open("error.log", std::ios::app);
  file << "{\n";
  file << "\"time\" : \"" << NowTime() << "\"," << std::endl;
  file << "\"message\" : \"" << message << "\"";

  if (custom_signal != -1) {
    file << ",\n\"signal\" : [\"" << custom_signal << "\",\""
         << strsignal(custom_signal) << "\"]";
  }

  if (withException) {
    try {
      throw; // Re-throw the current exception
    } catch (const std::exception &ex) {
      file << ",\n\"exception\" : \"" << ex.what() << "\"";
    }
  }

  if (custom_errno != -1) {
    file << ",\n\"errno\" : [\"" << custom_errno << "\",\""
         << strerror(custom_errno) << "\"]";
  }

  file << "\n";

  file << "}\n";

  file << "]\n";

  file.close();
}

void dumpWarningToFile(std::string message) {

  if (!isFileEmpty("warning.log")) {
    deleteLastLine("warning.log");
    std::ofstream file;
    file.open("warning.log", std::ios::app);
    file << ",\n";
    file.close();
  } else {
    std::ofstream file;
    file.open("warning.log", std::ios::app);
    file << "[\n";
    file.close();
  }

  removeDoubleQuotes(message);

  std::ofstream file;
  file.open("warning.log", std::ios::app);
  file << "{\n";
  file << "\"time\" : \"" << NowTime() << "\"," << std::endl;
  file << "\"message\" : \"" << message << "\"";
  file << "}\n";
  file << "]\n";

  file.close();
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
  dumpWarningToFile(message);

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

  dumpErrorToFile(message);

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
