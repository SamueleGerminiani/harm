#pragma once

#include <iostream>

namespace harm {
struct DTLimits {
  DTLimits(const DTLimits &o) = default;
  explicit DTLimits(size_t maxDepth, size_t maxWidth, size_t maxAll,
                     double dtRange, bool isRandomConstructed, bool saveOffset,bool useNegatedProps)
      : _maxDepth(maxDepth), _maxWidth(maxWidth), _maxAll(maxAll),
        _dtRange(dtRange), _isRandomConstructed(isRandomConstructed),
        _saveOffset(saveOffset) , _useNegatedProps(useNegatedProps) {
    // not todo
  }

  DTLimits() {}

  size_t _maxDepth=3;
  size_t _maxWidth=3;
  size_t _maxAll=3;
  double _dtRange=0.f;
  bool _isRandomConstructed=1;
  bool _saveOffset=0;
  bool _useNegatedProps=1;
};
}
