// H11f (finding F-L9): warning.log/error.log under concurrent writers. Several processes (ctest -j:
// the gtests share build/) or threads append to the same file by a read-modify-write; a truncation
// by one writer made another one's deleteLastLine read zero lines and run off its vector.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "message.hh"
#include "misc.hh"
#include "gtest/gtest_pred_impl.h"

namespace {

// a fresh directory, made the working directory for the test (the log files are relative)
struct InTempDir {
  std::filesystem::path old, dir;
  InTempDir() {
    old = std::filesystem::current_path();
    dir = std::filesystem::temp_directory_path() /
          ("harm_logtest_" + std::to_string(getpid()) + "_" +
           ::testing::UnitTest::GetInstance()->current_test_info()->name());
    std::filesystem::remove_all(dir);
    std::filesystem::create_directories(dir);
    std::filesystem::current_path(dir);
  }
  ~InTempDir() {
    std::filesystem::current_path(old);
    std::filesystem::remove_all(dir);
  }
};

std::string slurp(const std::string &f) {
  std::ifstream in(f);
  std::stringstream ss;
  ss << in.rdbuf();
  return ss.str();
}

size_t count(const std::string &s, const std::string &what) {
  size_t n = 0;
  for (size_t p = s.find(what); p != std::string::npos; p = s.find(what, p + 1)) {
    n++;
  }
  return n;
}

// one JSON array of records written by dumpWarningToFile: "[", then "{...}" separated by ",", "]"
void expectValidLog(const std::string &text, size_t records) {
  ASSERT_FALSE(text.empty());
  EXPECT_EQ(text.rfind("[\n", 0), 0u) << text.substr(0, 200);
  EXPECT_EQ(text.substr(text.size() - 2), "]\n");
  EXPECT_EQ(count(text, "\"message\""), records);
  EXPECT_EQ(count(text, "{\n"), records);
  EXPECT_EQ(count(text, "}\n"), records);
  EXPECT_EQ(count(text, "]\n"), 1u);
  EXPECT_EQ(count(text, "[\n"), 1u);
}

void warnMany(size_t n) {
  for (size_t i = 0; i < n; i++) {
    messageWarning("concurrent warning " + std::to_string(i));
  }
}

} // namespace

// A1: the crash itself, without a race
TEST(LogTest, deleteLastLineOnAnEmptyFile) {
  InTempDir tmp;
  { std::ofstream("empty.log"); }
  deleteLastLine("empty.log");
  EXPECT_TRUE(isFileEmpty("empty.log"));
}

// A2: processes (ctest -j, the gtests share a working directory)
TEST(LogTest, concurrentProcessesKeepOneValidLog) {
  InTempDir tmp;
  const size_t procs = 8, each = 200;
  std::vector<pid_t> kids;
  for (size_t k = 0; k < procs; k++) {
    pid_t p = fork();
    ASSERT_GE(p, 0);
    if (p == 0) {
      if (!freopen("/dev/null", "w", stdout)) {
        _exit(3);
      }
      warnMany(each);
      _exit(0);
    }
    kids.push_back(p);
  }
  for (pid_t p : kids) {
    int status = 0;
    waitpid(p, &status, 0);
    EXPECT_TRUE(WIFEXITED(status) && WEXITSTATUS(status) == 0)
        << "a writer died, signal " << (WIFSIGNALED(status) ? WTERMSIG(status) : 0);
  }
  expectValidLog(slurp("warning.log"), procs * each);
}

// A3: HARM's own threads
TEST(LogTest, concurrentThreadsKeepOneValidLog) {
  InTempDir tmp;
  const size_t threads = 8, each = 200;
  std::vector<std::thread> ts;
  std::streambuf *saved = std::cout.rdbuf();
  std::ostringstream sink;
  std::cout.rdbuf(sink.rdbuf());
  for (size_t k = 0; k < threads; k++) {
    ts.emplace_back([&] { warnMany(each); });
  }
  for (auto &t : ts) {
    t.join();
  }
  std::cout.rdbuf(saved);
  expectValidLog(slurp("warning.log"), threads * each);
}
