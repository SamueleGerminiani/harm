// H12 A2 (finding F-M2): the decision-tree scores are computed with every operation rounded, as on
// x86_64, on every platform. On arm64, GCC contracts `1 - a*b` into one fused instruction by default,
// which skips the rounding of the product: near-equal candidates then sort differently, and macOS
// arm64 mined other assertions than Linux x86_64.
// The references below round each operation through a volatile temporary, so they cannot be fused.
#include <cmath>
#include <cstring>
#include <gtest/gtest.h>
#include <string>

#include "TemplateImplication.hh"
#include "supportMethods.hh"

using namespace harm;

namespace {

double roundedCovScore(size_t atct, size_t atcf, size_t ct, size_t cf) {
  volatile double a = (double)atct / ct;
  volatile double b = 1.f - (double)atcf / cf;
  volatile double prod = a * b;
  return 1.f - prod;
}

double roundedEntropy(size_t at, size_t atct) {
  volatile double p = static_cast<double>(atct) / static_cast<double>(at);
  volatile double q = 1 - p;
  volatile double lp = log2(p);
  volatile double lq = log2(q);
  volatile double tp = (-1) * p * lp;
  volatile double tq = (-1) * q * lq;
  return tp + tq;
}

std::string bits(double d) {
  uint64_t u;
  std::memcpy(&u, &d, sizeof u);
  char buf[32];
  snprintf(buf, sizeof buf, "%016llx", (unsigned long long)u);
  return buf;
}

} // namespace

// A grid of counts; on arm64 with contraction, many of them give a different last bit
TEST(ScoreTest, covScoreRoundsEveryOperation) {
  size_t differ = 0, total = 0;
  std::string first;
  for (size_t ct : {7, 13, 50, 97, 1000})
    for (size_t cf : {3, 11, 64, 101, 999})
      for (size_t atct = 1; atct < ct && atct <= 40; atct++)
        for (size_t atcf = 0; atcf <= cf && atcf <= 40; atcf++) {
          OCCS occs{atct + atcf, atct, atcf};
          double got = getCovScore(occs, ct, cf);
          double want = roundedCovScore(atct, atcf, ct, cf);
          total++;
          if (bits(got) != bits(want)) {
            if (differ++ == 0)
              first = "ATCT=" + std::to_string(atct) + " ATCF=" + std::to_string(atcf) +
                      " CT=" + std::to_string(ct) + " CF=" + std::to_string(cf) + ": " +
                      bits(got) + " instead of " + bits(want);
          }
        }
  EXPECT_EQ(differ, 0u) << differ << " of " << total << " scores differ from the rounded ones; first: "
                        << first;
}

TEST(ScoreTest, entropyRoundsEveryOperation) {
  size_t differ = 0, total = 0;
  std::string first;
  for (size_t at = 2; at <= 300; at++)
    for (size_t atct = 1; atct < at; atct++) {
      OCCS occs{at, atct, at - atct};
      double got = getConditionalEntropy(occs, 1000);
      double want = roundedEntropy(at, atct);
      total++;
      if (bits(got) != bits(want)) {
        if (differ++ == 0)
          first = "AT=" + std::to_string(at) + " ATCT=" + std::to_string(atct) + ": " + bits(got) +
                  " instead of " + bits(want);
      }
    }
  EXPECT_EQ(differ, 0u) << differ << " of " << total
                        << " entropies differ from the rounded ones; first: " << first;
}
