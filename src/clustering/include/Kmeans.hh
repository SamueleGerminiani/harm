
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

/// @brief generate ranges using kmeans and the elbow method
template <typename T>
std::vector<std::pair<T, T>>
kmeansElbow(const std::vector<T> &elements, size_t max = 20,
            double minWCSS = 0.1f, bool keepOnlyBest = false);

#include "Kmeans.i.hh"
