#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <math.h>
#include <string>
#include <vector>

#include "Context.hh"
#include "Permutator.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/NumericExpression.hh"
#include "globals.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest.h"

using namespace harm;
using namespace expression;

template <bool PrintPerms = false>
size_t getPermutations(
    const std::string &formula,
    const std::unordered_map<int, size_t> &domaIdToNumberOfProps) {
  std::unordered_map<int,
                     std::vector<expression::NumericExpressionPtr>>
      _domainIdToNumerics;
  std::unordered_map<int, std::vector<expression::PropositionPtr>>
      _domainIdToProps;
  std::vector<VarDeclaration> vars;
  //find the max value in locToNumberOfProps
  size_t maxVars = 0;
  for (auto &[loc, nProps] : domaIdToNumberOfProps) {
    maxVars = nProps > maxVars ? nProps : maxVars;
  }
  std::unordered_map<std::string, std::unordered_set<int>>
      phToIdsDomain;
  for (size_t i = 0; i < maxVars; i++) {
    vars.emplace_back("v" + std::to_string(i), ExpType::Bool, 1);
    phToIdsDomain["P" + std::to_string(i)];
  }
  for (auto &[loc, nProps] : domaIdToNumberOfProps) {
    if (loc != (int)Location::Ant && loc != (int)Location::Con &&
        loc != (int)Location::AntCon) {
      phToIdsDomain["P" + std::to_string(loc)].insert(loc);
    }
  }

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  for (auto &[id, number] : domaIdToNumberOfProps) {
    for (size_t j = 0; j < number; j++) {
      _domainIdToProps[(int)id].push_back(
          trace->getBooleanVariable("v" + std::to_string(j)));
    }
  }

  TemporalExpressionPtr te =
      hparser::parseTemporalExpression(formula, trace);
  if constexpr (PrintPerms) {
    std::cout << temp2ColoredString(
                     te, Language::SpotLTL,
                     PrintMode::ShowOnlyPermuationPlaceholders)
              << "\n";
  }
  TemplateImplication ti(te, trace, DTLimits());
  ti.setPhIds(phToIdsDomain);
  ti.genPermutations(_domainIdToProps, _domainIdToNumerics);
  if constexpr (PrintPerms) {
    for (size_t i = 0; i < ti.getNumberOfPermutations(); i++) {
      ti.loadPerm(i);
      std::cout << ti.getColoredAssertionStr() << "\n";
    }
  }
  return ti.getNumberOfPermutations();
}
int binomialCoefficient(const int n, const int k) {
  std::vector<int> aSolutions(k);
  aSolutions[0] = n - k + 1;

  for (int i = 1; i < k; ++i) {
    aSolutions[i] = aSolutions[i - 1] * (n - k + 1 + i) / (i + 1);
  }

  return aSolutions[k - 1];
}
TEST(PermutatorTest, genPermutations) {

  clc::outputLang = Language::SpotLTL;

  std::unordered_map<int, size_t> domaIdToNumberOfProps;

  //Binomial operator
  const size_t nProps = 10;
  domaIdToNumberOfProps[(int)Location::Con] = nProps;
  domaIdToNumberOfProps[(int)Location::Ant] = nProps;
  domaIdToNumberOfProps[(int)Location::AntCon] = nProps;
  //simple binomial--------------------------------------
  ASSERT_EQ(
      getPermutations("G(1 -> (P0 and P1))", domaIdToNumberOfProps),
      binomialCoefficient(nProps, 2));
  ASSERT_EQ(getPermutations("G(1 -> (P0 and P1 and P2))",
                            domaIdToNumberOfProps),
            binomialCoefficient(nProps, 3));
  ASSERT_EQ(getPermutations("G(1 -> (P0 and P1 and P2 and P4))",
                            domaIdToNumberOfProps),
            binomialCoefficient(nProps, 4));
  //complex binomial--------------------------------------
  ASSERT_EQ(getPermutations("G(1 -> (P0 and P1) || (P2 and P3))",
                            domaIdToNumberOfProps),
            binomialCoefficient(binomialCoefficient(nProps, 2), 2));

  //binomial with repeated placeholders: disables the optimization
  ASSERT_EQ(getPermutations("G(1 -> (P0 and XP1 and P0))",
                            domaIdToNumberOfProps),
            std::pow(nProps, 2));
  ASSERT_EQ(getPermutations("G(1 -> (P1 and XP0 and P0))",
                            domaIdToNumberOfProps),
            std::pow(nProps, 2));
  ASSERT_EQ(getPermutations("G(1 -> (P0 and XP0 and P1))",
                            domaIdToNumberOfProps),
            std::pow(nProps, 2));
  ASSERT_EQ(getPermutations("G(1 -> (P0 and (XP1 and P0)))",
                            domaIdToNumberOfProps),
            std::pow(nProps, 2));
  ASSERT_EQ(getPermutations("G(1 -> (P1 and (XP0 and P0)))",
                            domaIdToNumberOfProps),
            std::pow(nProps, 2));
  ASSERT_EQ(
      getPermutations("G(1 -> (XP0 and P1))", domaIdToNumberOfProps),
      std::pow(nProps, 2));

  //negated vs non-negated--------------------------------------
  ASSERT_EQ(
      getPermutations("G(1 -> (!P0 and P1))", domaIdToNumberOfProps),
      std::pow(nProps, 2));

  //simple binomial with different versions of the same operator: can be (nProps,2) * (nProps,2) or (nProps,4)
  ASSERT_EQ(getPermutations("G(1 -> (P0 and P1) and (P2 && P3))",
                            domaIdToNumberOfProps),
            binomialCoefficient(nProps, 2) *
                binomialCoefficient(nProps, 2));

  //riflessive--------------------------------------
  ASSERT_EQ(
      getPermutations("G(1 -> (P0 W P1))", domaIdToNumberOfProps),
      (nProps * nProps) - nProps);
  ASSERT_EQ(
      getPermutations("G(1 -> (P0 R P1))", domaIdToNumberOfProps),
      (nProps * nProps) - nProps);
  ASSERT_EQ(
      getPermutations("G(1 -> (P1 R P1))", domaIdToNumberOfProps),
      nProps);

  //Mul------------------------------------------------
  ASSERT_EQ(getPermutations("G(P0 ##1 P1 |-> P2 ##1 P3)",
                            domaIdToNumberOfProps),
            std::pow(nProps, 4));
  //ac------------------------------------------------
  ASSERT_EQ(
      getPermutations("G(P0 |-> P0 ##1 P1)", domaIdToNumberOfProps),
      std::pow(nProps, 2));
}

