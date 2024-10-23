#include <cmath>

#include "TemplateImplication.hh"
#include "Trinary.hh"
#include "supportMethods.hh"

namespace harm {

OCCS computeOccs(const TemplateImplicationPtr &t) {
  OCCS res{0, 0};

  t->setCacheAntFalse();

  for (size_t i = 0; i < t->getTraceLength(); i++) {
    if (t->evaluate_ant(i) != Trinary::T) {
      continue;
    }
    if (t->evaluate(i) == Trinary::T) {
      ++res.AToccs;
      ++res.ATCToccs;
    } else if (t->evaluate(i) == Trinary::F) {
      ++res.AToccs;
      ++res.ATCFoccs;
    }
  }

  return res;
}

double getConditionalEntropy(const OCCS &occs, size_t traceLength) {
  size_t AToccs = occs.AToccs;
  size_t ATCToccs = occs.ATCToccs;

  // P(Y|X=x)
  double propConTrueGivenAntTrue =
      static_cast<double>(ATCToccs) / static_cast<double>(AToccs);

  // P(!Y|X=x)
  double propConFalseGivenAntTrue = 1 - propConTrueGivenAntTrue;

  // H(Y|X=x)
  double entropyConGivenAntTrue =
      ((-1) * propConTrueGivenAntTrue *
           log2(propConTrueGivenAntTrue) +
       (-1) * propConFalseGivenAntTrue *
           log2(propConFalseGivenAntTrue));

  return entropyConGivenAntTrue;
}

double getCovScore(const OCCS &occs, size_t CT, size_t CF) {
  return 1.f - ((double)occs.ATCToccs / CT *
                (1.f - (double)occs.ATCFoccs / CF));
}

} // namespace harm
