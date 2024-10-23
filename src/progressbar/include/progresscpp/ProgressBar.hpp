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

inline void jumpBack(size_t times) {
  for (size_t i = 0; i < times; i++) {
    std::cout << "\033[A";
    std::cout << "\33[2K";
  }
}

///class to manage a single instance of a progress bar
class ProgressBar {
private:
  ///current number of ticks
  unsigned int ticks = 0;
  ///total number of ticks
  unsigned int total_ticks;
  ///width of the progress bar in terms of number of characters
  unsigned int bar_width;
  ///character used to represent the advancement of the progress bar
  const char complete_char = '=';
  const char incomplete_char = ' ';
  const std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();
  ///true if the progress bar has finished
  bool _finished = false;
  ///counter to be displayed in the progress bar
  size_t _genericCounter = 0;
  ///true if the counter is enabled
  bool _counterEnabled = 0;
  ///message to be displayed in the progress bar
  std::string _message = "";

public:
  ProgressBar(unsigned int total, unsigned int width,
              const std::string &message)
      : total_ticks{total}, bar_width{width}, _message(message) {}

  unsigned int operator++() { return ++ticks; }

  void increment(size_t n) { ticks += n; };

  void enableCounter() {
    _counterEnabled = 1;
    _genericCounter = 0;
  }

  void disableCounter() {
    _counterEnabled = 0;
    _genericCounter = 0;
  }

  void incrementCounter() { _genericCounter++; }

  void incrementCounter(size_t n) { _genericCounter += n; }

  void setMessage(const std::string &message) { _message = message; }

  std::string getMessage() {
    return _message + (_counterEnabled
                           ? " " + std::to_string(_genericCounter)
                           : "");
  }

  bool isFinished() { return _finished; }

  void display() const {
    float progress = (float)ticks / total_ticks;
    size_t pos = (int)(bar_width * progress);

    std::chrono::steady_clock::time_point now =
        std::chrono::steady_clock::now();
    auto time_elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            now - start_time)
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

///class to manage multiple instances of a progress bar
class ParallelProgressBar {
public:
  virtual ~ParallelProgressBar() {}
  ///add a new instance of the parallel progress bar
  void addInstance(size_t id, const std::string &message,
                   unsigned int total, unsigned int width) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    //add the instance
    _instances.insert({{id, ProgressBar(total, width, message)}});

    //print unless progress bars are disables
    if (!clc::psilent) {
      std::cout << _instances.at(id).getMessage() << "\n";
      _instances.at(id).display();
    }

    //keep track of the printing order
    _order.push_back(id);
  }

  //advance the progress bar with the given id by one
  void increment(size_t id) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    ++_instances.at(id);
  }
  //advance the progress bar with the given id by n
  void increment(size_t id, size_t n) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.at(id).increment(n);
  }

  ///display the all the instances of the progress bar
  void display() {
    std::lock_guard<std::mutex> lock{_pbGuard};

    //print unless with are going too fast according to _displatPrintDelay
    if ((size_t)std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - _prevDisplayTime)
            .count() > _displayPrintDelay) {
      printToOut();
      _prevDisplayTime = std::chrono::steady_clock::now();
    }
  }

  ///terminate the progress bar with the given id
  void done(size_t id) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.at(id).done();
    //move the completed instance to the top
    auto it2 = std::find(begin(_order), end(_order), id);
    size_t e2 = std::distance(_order.begin(), it2);
    std::swap(_order[e2], _order[0]);
    printToOut();
    _instances.erase(id);
    _order.erase(begin(_order));
  }

  ///terminate the progress bar
  void done() {
    std::lock_guard<std::mutex> lock{_pbGuard};
    printToOut();

    if (!clc::psilent) {
      std::cout << std::endl;
    }
    _order.clear();
    _instances.clear();
  }

  //change the message in the progress bar
  void changeMessage(size_t id, const std::string &message) {
    _pbGuard.lock();
    _instances.at(id).setMessage(message);
    _pbGuard.unlock();
    display();
  }
  void enableCounter(size_t id) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.at(id).enableCounter();
  }
  void disableCounter(size_t id) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.at(id).disableCounter();
  }
  void incrementCounter(size_t id) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.at(id).incrementCounter();
  }
  void incrementCounter(size_t id, size_t n) {
    std::lock_guard<std::mutex> lock{_pbGuard};
    _instances.at(id).incrementCounter(n);
  }

private:
  void printToOut() {
    //print unless progress bars are disabled
    if (clc::psilent) {
      return;
    }

    //bring cout to the begining of the progress bar
    jumpBack(_instances.size() * 2);

    //print following the order
    for (auto &id : _order) {
      //print the message in its own line
      std::cout << _instances.at(id).getMessage() << std::endl;
      //print the rest of the progress bar
      _instances.at(id).display();
    }
  }

  ///keep track of the instances
  std::unordered_map<size_t, ProgressBar> _instances;
  ///mutex to protect the parallel printing
  std::mutex _pbGuard;
  ///keep track of the printing order
  std::vector<size_t> _order;
  std::chrono::steady_clock::time_point _prevDisplayTime;
  //print at most once every x milliseconds
  const size_t _displayPrintDelay = 100;
};

} // namespace progresscpp
