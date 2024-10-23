#pragma once

#include <cstddef>

namespace harm {
class TemplateImplication;

struct OCCS {
  size_t AToccs;   // how many times is the ant satisfied?
  size_t ATCToccs; // how many times ATCT?
  size_t ATCFoccs; // how many times ATCF?
};

double getConditionalEntropy(const OCCS &occs, size_t traceLength);

OCCS computeOccs(const TemplateImplicationPtr &t);

double getCovScore(const OCCS &occs, size_t CT, size_t CF);

} // namespace harm
