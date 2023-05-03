#pragma once
#include "message.hh"
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

inline size_t dirtyTimerSeconds(std::string id, bool start_stop) {
  static std::unordered_map<std::string, std::chrono::steady_clock::time_point>
      idToStart;
  if (start_stop) {
    idToStart[id] = std::chrono::steady_clock::now();
    return -1;
  } else {
    messageErrorIf(!idToStart.count(id), "Use of undefined timer '" + id + "'");
    return std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::steady_clock::now() - idToStart.at(id))
        .count();
  }
}
inline bool isTimeOut(std::string id, size_t time) {
  return dirtyTimerSeconds(id, 0) >= time;
}

void inline fileAppendContent(const std::string &name,
                              const std::string &content) {
  std::ofstream outfile;
  outfile.open(name, std::ios_base::app);
  outfile << content;
}
void inline fileDumpContent(const std::string &name,
                            const std::string &content) {
  std::ofstream outfile;
  outfile.open(name);
  outfile << content;
}

void inline systemCustom(std::string command) {
  int status = system(command.c_str());
  if (status < 0) {
    std::cout << "System error: " << '\n';
  } else {
    if (!WIFEXITED(status)) {
      std::cout << "Program exited abnormaly\n";
    }
  }
}
