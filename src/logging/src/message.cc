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
#include <fcntl.h>
#include <fstream>
#include <mutex>
#include <sstream>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>

namespace hlog {

namespace {
// H11f (F-L9): warning.log and error.log are rewritten in place (read, drop the closing "]",
// append), so every writer holds an exclusive lock for the whole update: flock against other
// processes (ctest -j runs the tests in one directory), a mutex against this process's threads.
std::mutex logMutex;
// a log write that fails reports through messageError, which writes the log again: such a nested
// write is skipped (the message is still printed), instead of waiting for its own lock
thread_local bool inLogWrite = false;

class LogLock {
public:
  explicit LogLock(const char *file)
      : _guard(logMutex), _fd(open(file, O_RDWR | O_CREAT, 0644)) {
    inLogWrite = true;
    if (_fd >= 0) {
      flock(_fd, LOCK_EX);
    }
  }
  ~LogLock() {
    if (_fd >= 0) {
      flock(_fd, LOCK_UN);
      close(_fd);
    }
    inLogWrite = false;
  }
  LogLock(const LogLock &) = delete;
  LogLock &operator=(const LogLock &) = delete;
  int fd() const { return _fd; }

private:
  std::lock_guard<std::mutex> _guard;
  int _fd;
};
// H21: appends one record to the JSON array in file, holding lock. A file that ends with the line
// "]" gets the record written over that line, so a message costs the same however long the log is;
// the bytes are those of the read-modify-write below, which stays for an empty file and for a file
// that does not end so (edited by hand, or cut by a crash)
void appendRecord(const LogLock &lock, const char *file, const std::string &record) {
  int fd = lock.fd();
  struct stat st;
  if (fd >= 0 && fstat(fd, &st) == 0 && st.st_size >= 2) {
    off_t size = st.st_size;
    char tail[3] = {0, 0, 0};
    off_t from = size >= 3 ? size - 3 : 0;
    ssize_t n = pread(fd, tail, size - from, from);
    bool endsWithBracketLine =
        n == size - from && tail[n - 2] == ']' && tail[n - 1] == '\n' && (n == 2 || tail[0] == '\n');
    if (endsWithBracketLine) {
      std::string text = ",\n" + record + "]\n";
      if (pwrite(fd, text.data(), text.size(), size - 2) == (ssize_t)text.size()) {
        return;
      }
    }
  }
  if (!isFileEmpty(file)) {
    deleteLastLine(file);
    std::ofstream(file, std::ios::app) << ",\n" << record << "]\n";
  } else {
    std::ofstream(file, std::ios::app) << "[\n" << record << "]\n";
  }
}
} // namespace

//number of active ScopedThrowOnError in this thread
static thread_local size_t throwOnErrorDepth = 0;
ScopedThrowOnError::ScopedThrowOnError() { throwOnErrorDepth++; }
ScopedThrowOnError::~ScopedThrowOnError() { throwOnErrorDepth--; }

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
  if (inLogWrite) {
    return;
  }
  LogLock lock("error.log");

  removeDoubleQuotes(message);

  std::ostringstream file;
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

  appendRecord(lock, "error.log", file.str());
}

void dumpWarningToFile(std::string message) {
  if (inLogWrite) {
    return;
  }
  LogLock lock("warning.log");

  removeDoubleQuotes(message);

  std::ostringstream file;
  file << "{\n";
  file << "\"time\" : \"" << NowTime() << "\"," << std::endl;
  file << "\"message\" : \"" << message << "\"";
  file << "}\n";

  appendRecord(lock, "warning.log", file.str());
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

  if (throwOnErrorDepth > 0) {
    throw HarmError(message);
  }

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
