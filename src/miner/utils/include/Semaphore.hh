#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

//This file contains a semaphore implementation + several helper functions

class basic_semaphore {
public:
  basic_semaphore(const basic_semaphore &) = delete;
  basic_semaphore(basic_semaphore &&) = delete;
  basic_semaphore &operator=(const basic_semaphore &) = delete;
  basic_semaphore &operator=(basic_semaphore &&) = delete;

  basic_semaphore(size_t count) : mCount(count) {}

  void notify() {
    std::lock_guard<std::mutex> lock{mMutex};
    ++mCount;
    mCv.notify_one();
  }
  void notify(size_t n) {
    for (size_t i = 0; i < n; i++) {
      notify();
    }
  }
  void addNotifyOnce(size_t n) {
    std::lock_guard<std::mutex> lock{mMutex};
    mCount += n;
    mCv.notify_one();
  }

  void wait() {
    std::unique_lock<std::mutex> lock{mMutex};
    mCv.wait(lock, [&] { return mCount > 0; });
    --mCount;
  }

  void wait(size_t n) {
    for (size_t i = 0; i < n; i++) {
      wait();
    }
  }

  bool try_wait() {
    std::lock_guard<std::mutex> lock{mMutex};

    if (mCount > 0) {
      --mCount;
      return true;
    }

    return false;
  }
  size_t getAvailable() {
    std::lock_guard<std::mutex> lock{mMutex};
    return mCount;
  }
  void reset() {
    std::lock_guard<std::mutex> lock{mMutex};
    mCount = 0;
  }

  template <class Rep, class Period>
  bool wait_for(const std::chrono::duration<Rep, Period> &d) {
    std::unique_lock<std::mutex> lock{mMutex};
    auto finished = mCv.wait_for(lock, d, [&] { return mCount > 0; });

    if (finished)
      --mCount;

    return finished;
  }

  template <class Clock, class Duration>
  bool wait_until(const std::chrono::time_point<Clock, Duration> &t) {
    std::unique_lock<std::mutex> lock{mMutex};
    auto finished =
        mCv.wait_until(lock, t, [&] { return mCount > 0; });

    if (finished)
      --mCount;

    return finished;
  }

private:
  std::mutex mMutex;
  std::condition_variable mCv;
  size_t mCount = 0;
};

using Semaphore = basic_semaphore;

template <typename T> class ProtectedQueueNotify {
public:
  ProtectedQueueNotify() : _s(Semaphore(0)) {}
  void push(const T &r) {
    std::lock_guard<std::mutex> lock{_guard};
    _q.push(r);
    _s.notify();
  }
  T pop() {
    _s.wait();
    std::lock_guard<std::mutex> lock{_guard};
    T v = _q.front();
    _q.pop();
    return v;
  }

private:
  std::queue<T> _q;
  std::mutex _guard;
  Semaphore _s;
};

template <typename Container, typename Key, typename Item>
void insertGuard(Container &c, Key &k, Item i, std::mutex &m) {
  std::lock_guard<std::mutex> lock{m};
  c.insert({{k, i}});
}

template <typename Container, typename Key>
void eraseGuard(Container &c, Key &k, std::mutex &m) {
  std::lock_guard<std::mutex> lock{m};
  c.erase(k);
}

template <typename Container>
bool emptyGuard(Container &c, std::mutex &m) {
  std::lock_guard<std::mutex> lock{m};
  return c.empty();
}

template <typename Container, typename Key>
bool countGuard(Container &c, Key &k, std::mutex &m) {
  std::lock_guard<std::mutex> lock{m};
  return c.count(k);
}

template <typename Container, typename Key>
auto atGuard(Container &c, Key &k, std::mutex &m)
    -> decltype(c.begin()->second) {
  std::lock_guard<std::mutex> lock{m};
  return c.at(k);
}
