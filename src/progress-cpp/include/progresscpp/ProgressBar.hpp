#pragma once

#include "globals.hh"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace progresscpp {
class ProgressBar {
private:
  unsigned int ticks = 0;

  unsigned int total_ticks;
  unsigned int bar_width;
  const char complete_char = '=';
  const char incomplete_char = ' ';
  const std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();
  bool _finished = false;
  size_t _genericCounter = 0;
  bool _enableCounter = 0;
  std::string _message = "";

public:
  ProgressBar(unsigned int total, unsigned int width, char complete,
              char incomplete, const std::string &message)
      : total_ticks{total}, bar_width{width}, complete_char{complete},
        incomplete_char{incomplete}, _message(message) {}

  ProgressBar(unsigned int total, unsigned int width,
              const std::string &message)
      : total_ticks{total}, bar_width{width}, _message(message) {}

  unsigned int operator++() { return ++ticks; }
  void increment(size_t n) { ticks += n; };

  void enableCounter() {
    _enableCounter = 1;
    _genericCounter = 0;
  }
  void disableCounter() {
    _enableCounter = 0;
    _genericCounter = 0;
  }
  void incrementCounter() { _genericCounter++; }
  void incrementCounter(size_t n) { _genericCounter += n; }

  void setMessage(const std::string &message) { _message = message; }
  std::string getMessage() {
    return _message +
           (_enableCounter ? " " + std::to_string(_genericCounter) : "");
  }

  bool isFinished() { return _finished; }
  void display() const {
    float progress = (float)ticks / total_ticks;
    size_t pos = (int)(bar_width * progress);

    std::chrono::steady_clock::time_point now =
        std::chrono::steady_clock::now();
    auto time_elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time)
            .count();

    std::cout << "[";

    for (size_t i = 0; i < bar_width; ++i) {
      if (i < pos)
        std::cout << complete_char;
      else if (i == pos)
        std::cout << ">";
      else
        std::cout << incomplete_char;
    }
    std::cout << "] " << int(progress * 100.0) << "% "
              << float(time_elapsed) / 1000.0 << "s\r";
    std::cout << std::endl;
  }

  void done() { _finished = true; }
};

inline void jumpBack(size_t times) {
  for (size_t i = 0; i < times; i++) {
    std::cout << "\033[A";
    std::cout << "\33[2K";
  }
}
class ParallelProgressBar {
public:
  virtual ~ParallelProgressBar() {}
  void addInstance(size_t id, const std::string &message, unsigned int total,
                   unsigned int width) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.insert({{id, ProgressBar(total, width, message)}});
    if (!clc::psilent) {
      std::cout << _instances.at(id).getMessage() << "\n";
      _instances.at(id).display();
    }
    _order.push_back(id);
  }
  void increment(size_t id) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    ++_instances.at(id);
  }
  void increment(size_t id, size_t n) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.at(id).increment(n);
  }
  void print() {
    if (clc::psilent) {
      return;
    }
    jumpBack(_instances.size() * 2);

    for (auto &id : _order) {
      std::cout << _instances.at(id).getMessage() << "\n";
      _instances.at(id).display();
    }
  }
  void display() {
    std::lock_guard<std::mutex> lock{_pbGuard};
    if ((size_t)std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - _prevDisplayTime)
            .count() > _displayPrintDelay) {
      print();
      _prevDisplayTime = std::chrono::steady_clock::now();
    }
  }
  void done(size_t id) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.at(id).done();
    auto it2 = std::find(begin(_order), end(_order), id);
    size_t e2 = std::distance(_order.begin(), it2);
    std::swap(_order[e2], _order[0]);
    print();
    _instances.erase(id);
    _order.erase(begin(_order));
  }

  void done() {
    std::lock_guard<std::mutex> lock{_pbGuard};
    print();

    if (!clc::psilent) {
      std::cout << std::endl;
    }
    _order.clear();
    _instances.clear();
  }
  void enableCounter(size_t id) { _instances.at(id).enableCounter(); }
  void disableCounter(size_t id) { _instances.at(id).disableCounter(); }
  void incrementCounter(size_t id) { _instances.at(id).incrementCounter(); }
  void incrementCounter(size_t id, size_t n) {
    _instances.at(id).incrementCounter(n);
  }
  void changeMessage(size_t id, const std::string &message) {
    _instances.at(id).setMessage(message);
    display();
  }

private:
  std::unordered_map<size_t, ProgressBar> _instances;
  std::mutex _pbGuard;
  std::vector<size_t> _order;
  std::chrono::steady_clock::time_point _prevDisplayTime;
  const size_t _displayPrintDelay = 100;
};

} // namespace progresscpp
