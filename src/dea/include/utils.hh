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

