// H11f (finding F-L9): warning.log/error.log under concurrent writers. Several processes (ctest -j:
// the gtests share build/) or threads append to the same file by a read-modify-write; a truncation
// by one writer made another one's deleteLastLine read zero lines and run off its vector.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <regex>
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
  // H30 (T3): the sink holds every warning, whole
  EXPECT_EQ(count(sink.str(), "\033[1;33m[WARNING] "), threads * each);
  EXPECT_EQ(count(sink.str(), "\tMessage: concurrent warning "), threads * each);
}

// H30: the console prints one message at a time. LogTest.concurrentThreadsKeepOneValidLog crashed
// now and then on Linux: messages were printed outside any lock, into one shared string stream.
namespace {

// a stream buffer that notices two threads inside it at once; a short pause per write makes such
// an overlap near certain when the writers are not serialised. The text is kept under its own lock.
class OverlapBuf : public std::streambuf {
public:
  std::atomic<int> inside{0};
  std::atomic<bool> overlap{false};
  std::string text() {
    std::lock_guard<std::mutex> g(_m);
    return _text;
  }

protected:
  std::streamsize xsputn(const char *s, std::streamsize n) override {
    enter();
    {
      std::lock_guard<std::mutex> g(_m);
      _text.append(s, n);
    }
    inside--;
    return n;
  }
  int_type overflow(int_type c) override {
    if (traits_type::eq_int_type(c, traits_type::eof())) {
      return traits_type::not_eof(c);
    }
    char ch = traits_type::to_char_type(c);
    xsputn(&ch, 1);
    return c;
  }

private:
  void enter() {
    if (++inside > 1) {
      overlap = true;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(20));
  }
  std::mutex _m;
  std::string _text;
};

// runs f in 8 threads, 200 times each, with std::cout on an OverlapBuf; returns the printed text
template <typename F> std::string printConcurrently(F f, bool &overlap) {
  const size_t threads = 8, each = 200;
  OverlapBuf buf;
  std::streambuf *saved = std::cout.rdbuf(&buf);
  std::vector<std::thread> ts;
  for (size_t k = 0; k < threads; k++) {
    ts.emplace_back([&, k] {
      for (size_t i = 0; i < each; i++) {
        f(std::to_string(k) + "." + std::to_string(i));
      }
    });
  }
  for (auto &t : ts) {
    t.join();
  }
  std::cout.rdbuf(saved);
  overlap = buf.overlap;
  return buf.text();
}

// every one of the 8 x 200 messages appears once, as one unbroken block
void expectWholeMessages(const std::string &text, const std::string &head, const std::string &tail) {
  size_t notOnce = 0;
  for (size_t k = 0; k < 8; k++) {
    for (size_t i = 0; i < 200; i++) {
      notOnce += count(text, "msg " + std::to_string(k) + "." + std::to_string(i) + "\n") != 1;
    }
  }
  EXPECT_EQ(notOnce, 0u) << "messages not printed exactly once";
  std::regex block(head + "msg [0-9]+\\.[0-9]+\n" + tail);
  size_t n = std::distance(std::sregex_iterator(text.begin(), text.end(), block), std::sregex_iterator());
  EXPECT_EQ(n, 1600u);
}

} // namespace

// T1
TEST(LogTest, consoleWarningsDoNotInterleave) {
  InTempDir tmp;
  bool overlap = true;
  std::string text = printConcurrently([](const std::string &id) { messageWarning("msg " + id); }, overlap);
  EXPECT_FALSE(overlap) << "two threads printed at once";
  expectWholeMessages(text,
                      "\033\\[1;33m\\[WARNING\\] [^\n]* - File: [^\n]* -- Line: [0-9]+\n\tMessage: ",
                      "\033\\[0m");
}

// T2
TEST(LogTest, consoleInfosDoNotInterleave) {
  InTempDir tmp;
  bool overlap = true;
  std::string text = printConcurrently([](const std::string &id) { messageInfo("msg " + id); }, overlap);
  EXPECT_FALSE(overlap) << "two threads printed at once";
  expectWholeMessages(text, "\033\\[1m\\[INFO\\] [^\n]* - Message: ", "\033\\[0m");
}

// T4: the printed text is unchanged
TEST(LogTest, consoleTextIsUnchanged) {
  InTempDir tmp;
  std::ostringstream sink;
  std::streambuf *saved = std::cout.rdbuf(sink.rdbuf());
  hlog::_harm_internal_messageInfo("an info");
  hlog::_harm_internal_messageWarning("f.cc", 7, "a warning");
  std::cout.rdbuf(saved);
  std::regex time(" [0-9][0-9]:[0-9][0-9]:[0-9][0-9] ");
  EXPECT_EQ(std::regex_replace(sink.str(), time, " T "),
            "\033[1m[INFO] T - Message: an info\n\033[0m"
            "\033[1;33m[WARNING] T - File: f.cc -- Line: 7\n\tMessage: a warning\n\033[0m");
}

TEST(LogTestDeathTest, consoleErrorTextIsUnchanged) {
  InTempDir tmp;
  ::testing::GTEST_FLAG(death_test_style) = "threadsafe";
  EXPECT_DEATH(hlog::_harm_internal_messageError("f.cc", 9, "an error"),
               "\\[ERROR\\] [0-9:]+ - File: f\\.cc at line 9\nMessage: an error\n");
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
