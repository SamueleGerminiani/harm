
#pragma once
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
template <typename T>
std::vector<std::pair<T, T>> kdeElbow(std::vector<T> elements, size_t max = 20, double SDmin_red = 0.1f, bool keepOnlyBest=false);
#include "KDE.i.hh"
