#pragma once

#include <iostream>

namespace harm {
struct BDTLimits {
  BDTLimits(const BDTLimits &o) = default;
  explicit BDTLimits(size_t maxDepth, size_t maxWidth, size_t maxAll,
                     double bdtRange, bool isRandomConstructed, bool saveOffset,bool useNegatedProps)
      : _maxDepth(maxDepth), _maxWidth(maxWidth), _maxAll(maxAll),
        _bdtRange(bdtRange), _isRandomConstructed(isRandomConstructed),
        _saveOffset(saveOffset) , _useNegatedProps(useNegatedProps) {
    // not todo
  }

  BDTLimits() {}

  size_t _maxDepth=3;
  size_t _maxWidth=3;
  size_t _maxAll=3;
  double _bdtRange=0.f;
  bool _isRandomConstructed=1;
  bool _saveOffset=0;
  bool _useNegatedProps=1;
};
}
