#pragma once
// CR1 (the miner portfolio's correctness review, C7a-7): the start of the VCD file each time step comes from, in a
// trace of several files concatenated (TraceReader fills it from the files' cuts; empty: one file). $past, $stable,
// $rose and $fell do not read across a file's start: each file is its own simulation.
#include <cstddef>
#include <vector>

namespace expression {

extern std::vector<size_t> traceFileStart;

/// whether `time - back` lies before the start of `time`'s file (or of the trace)
inline bool beforeFileStart(size_t time, size_t back) {
  if (time < back) {
    return true;
  }
  return time < traceFileStart.size() && time - back < traceFileStart[time];
}

} // namespace expression
