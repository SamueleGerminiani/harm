// H11f (finding F-L9): warning.log/error.log under concurrent writers. Several processes (ctest -j:
// the gtests share build/) or threads append to the same file by a read-modify-write; a truncation
// by one writer made another one's deleteLastLine read zero lines and run off its vector.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <chrono>
#include <cstdio>
#include <cstring>
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

// H21: a message is appended at a constant cost, not by rewriting the whole file
namespace {

// the record's time replaced by T, so that texts written at different times compare equal
std::string withoutTimes(std::string s) {
  const std::string key = "\"time\" : \"";
  for (size_t p = s.find(key); p != std::string::npos; p = s.find(key, p + 1)) {
    size_t b = p + key.size(), e = s.find('"', b);
    s.replace(b, e - b, "T");
  }
  return s;
}

std::string warningRecord(const std::string &message) {
  return "{\n\"time\" : \"T\",\n\"message\" : \"" + message + "\"}\n";
}

// silences the warnings' printing for the scope
struct QuietCout {
  std::streambuf *saved = std::cout.rdbuf();
  std::ostringstream sink;
  QuietCout() { std::cout.rdbuf(sink.rdbuf()); }
  ~QuietCout() { std::cout.rdbuf(saved); }
};

} // namespace

// A1: before, every warning read and rewrote the whole file (H19: a 21,636-line warning.log slowed
// Z3EquivalenceTest 15-fold)
TEST(LogTest, appendCostDoesNotGrowWithTheFile) {
  InTempDir tmp;
  const size_t before = 50000, added = 2000;
  {
    std::ofstream out("warning.log");
    out << "[\n";
    for (size_t i = 0; i < before; i++) {
      out << (i ? ",\n" : "") << warningRecord("old warning " + std::to_string(i));
    }
    out << "]\n";
  }
  QuietCout quiet;
  auto start = std::chrono::steady_clock::now();
  for (size_t i = 0; i < added; i++) {
    messageWarning("new warning " + std::to_string(i));
  }
  double seconds =
      std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
  EXPECT_LT(seconds, 2.0);
  expectValidLog(slurp("warning.log"), before + added);
}

// A2: the bytes are those written before H21
TEST(LogTest, sameBytesAsBefore) {
  InTempDir tmp;
  {
    QuietCout quiet;
    messageWarning("first");
    messageWarning("second");
    messageWarning("third");
  }
  EXPECT_EQ(withoutTimes(slurp("warning.log")),
            "[\n" + warningRecord("first") + ",\n" + warningRecord("second") + ",\n" +
                warningRecord("third") + "]\n");
  hlog::dumpErrorToFile("an error");
  hlog::dumpErrorToFile("another", 2);
  EXPECT_EQ(withoutTimes(slurp("error.log")),
            "[\n{\n\"time\" : \"T\",\n\"message\" : \"an error\"\n}\n,\n"
            "{\n\"time\" : \"T\",\n\"message\" : \"another\",\n\"errno\" : [\"2\",\"" +
                std::string(strerror(2)) + "\"]\n}\n]\n");
}

// A3: a file that does not end with the line "]" (edited by hand, cut by a crash) is handled as
// before: its last line is replaced
TEST(LogTest, unterminatedFileKeepsTheOldBehaviour) {
  InTempDir tmp;
  for (std::string start : {std::string("[\n{\n\"time\" : \"T\",\n\"message\" : \"a\"}\n"),
                            std::string("[\n") + warningRecord("b") + "x]\n",
                            std::string("[\n") + warningRecord("c") + "]"}) {
    { std::ofstream("warning.log") << start; }
    {
      QuietCout quiet;
      messageWarning("new");
    }
    std::string kept = start.substr(0, start.rfind('\n', start.size() - 2) + 1);
    if (start.back() != '\n') {
      kept = start.substr(0, start.rfind('\n') + 1);
    }
    EXPECT_EQ(withoutTimes(slurp("warning.log")), kept + ",\n" + warningRecord("new") + "]\n")
        << start;
  }
}
