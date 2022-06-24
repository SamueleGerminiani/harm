#pragma once

#include <cstddef>

namespace harm {

#define DIV(a, b) (static_cast<double>((a)) / static_cast<double>((b)))

double getEntropy(size_t occurrences, size_t traceLength);
double getConditionalEntropy(size_t occProposition,size_t occGoal, size_t traceLength) ;

} // miner
