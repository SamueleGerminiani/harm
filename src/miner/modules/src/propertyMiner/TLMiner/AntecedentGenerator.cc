#include <algorithm>
#include <iterator>
#include <mutex>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "AntecedentGenerator.hh"
#include "DTLimits.hh"
#include "DTOperator.hh"
#include "TemplateImplication.hh"
#include "Trinary.hh"
#include "expUtils/expUtils.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "misc.hh"
#include "supportMethods.hh"

namespace expression {
class NumericExpression;
} // namespace expression

#define numLeavesOffset 1'000'000

namespace harm {
std::mutex dtTreeIDmutex;

/// @brief analyse the trace to find a set of values on which to perform the clustering
std::pair<std::vector<size_t>, std::vector<size_t>>
gatherInterestingValues(const TemplateImplicationPtr &t, int depth);

AntecedentGenerator::AntecedentGenerator()
    : _onSets(), _offSets(), _saveOffset(true) {
  // ntd
}

void AntecedentGenerator::makeAntecedents(
    const TemplateImplicationPtr &t,
    const DecTreeVariables &dcVariables,
    const NumericDecTreeExp &numericCandidates) {

  _knownSolutions.clear();
  _CT = 0;
  _CF = 0;

  std::set<size_t> unusedVars;
  for (size_t i = 0; i < dcVariables.size(); ++i)
    unusedVars.insert(i);

  std::set<size_t> unusedNumerics;
  for (size_t i = 0; i < numericCandidates.size(); ++i) {
    unusedNumerics.insert(i);
  }

  OCCS occs = computeOccs(t);

  auto [CT, CF] = t->getCT_CF();
  _CT = CT;
  _CF = CF;

  double initialScore = 0.f;
  if (t->getDT()->getLimits()._heuristic == DTHeuristic::ENTROPY) {
    initialScore = getConditionalEntropy(occs, t->getTraceLength());
  } else if (t->getDT()->getLimits()._heuristic ==
             DTHeuristic::COVERAGE) {
    initialScore = getCovScore(occs, _CT, _CF);
  } else {
    messageError("Unknown heuristic");
  }

  runDecisionTree(unusedVars, dcVariables, unusedNumerics,
                  numericCandidates, t, initialScore);
}

inline void AntecedentGenerator::findCandidates(
    size_t candidate, const DecTreeVariables &dcVariables,
    const TemplateImplicationPtr &t,
    std::unordered_set<DiscoveredLeaf, DiscoveredLeafHash>
        &discSolutions,
    std::vector<CandidateDec> &candidates, int depth,
    double currScore) {

  DTOperatorPtr dto = t->getDT();

  // the 2 propositions of X
  std::vector<PropositionPtr> propPtr;
  propPtr.push_back(dcVariables.at(candidate).first);
  propPtr.push_back(dcVariables.at(candidate).second);

  // for each proposition that belongs to a unused variable
  for (size_t propI = 0;
       propI < (dto->getLimits()._useNegatedProps ? 2 : 1); ++propI) {

    if (dto->isTaken(candidate, propI, depth))
      continue;

    PropositionPtr prop = propPtr[propI];

    // add the new proposition of a unused variable in the current
    // antecedent
    dto->addItem(prop, depth);

    // ignore this prop if the template contains a known solution
    if (isKnownSolution(dto, 1)) {
      dto->popItem(depth);
      continue;
    }

    OCCS res = computeOccs(t);

    // is the new antecedent at least once satisfied? (avoid vacuity)
    if (res.AToccs > 0 && checkFitness(t, res)) {

      if (res.ATCToccs == 0 || res.ATCToccs == res.AToccs) {
        dto->addLeaf(prop, candidate, propI, depth);
        discSolutions.insert(DiscoveredLeaf(candidate, depth, propI));
        storeSolution(t, res.ATCToccs == 0);
      } else {
        double score = 0.f;
        if (t->getDT()->getLimits()._heuristic ==
            DTHeuristic::ENTROPY) {
          score = getConditionalEntropy(res, t->getTraceLength());
        } else if (t->getDT()->getLimits()._heuristic ==
                   DTHeuristic::COVERAGE) {
          score = getCovScore(res, _CT, _CF);
        } else {
          messageError("Unknown heuristic");
        }
        double gain = currScore - score;

        candidates.emplace_back(candidate, depth, (bool)propI,
                                propPtr[propI], gain, score, false);
      }
    }

    dto->popItem(depth);
  }
}

inline std::pair<std::vector<size_t>, std::vector<size_t>>
gatherInterestingValues(const TemplateImplicationPtr &t, int depth) {

  std::vector<size_t> positives;
  std::vector<size_t> negatives;

  DTOperatorPtr dto = t->_dtOp;

  //Used to simulate if the numeric is true
  PropositionPtr tc = generatePtr<BooleanConstant>(
      true, ExpType::Bool, 1, t->getTraceLength());
  PropositionPtr fc = generatePtr<BooleanConstant>(
      false, ExpType::Bool, 1, t->getTraceLength());

  std::vector<Trinary> truthValueBeforeAddingTrue;
  std::vector<Trinary> truthValueAfterAddingTrue;

  for (size_t i = 0; i < t->getTraceLength(); i++) {
    truthValueBeforeAddingTrue.push_back(t->evaluate(i));
  }

  dto->addItem(tc, depth);
  t->setCacheAntFalse();

  for (size_t i = 0; i < t->getTraceLength(); i++) {
    truthValueAfterAddingTrue.push_back(t->evaluate(i));
  }

  std::vector<size_t> undecided;

  for (size_t i = 0; i < t->getTraceLength(); i++) {
    if (truthValueBeforeAddingTrue[i] == Trinary::T &&
        truthValueAfterAddingTrue[i] != Trinary::T) {
      //this branch can be taken only if the DT is ..##.. or .. ..&#1..
      //ATCT would be reduced or ATCF/AU/CU would be increased
      //INTERESTING NEGATIVE
      negatives.push_back(i);
    } else if (truthValueBeforeAddingTrue[i] == Trinary::F &&
               truthValueAfterAddingTrue[i] != Trinary::F) {
      //ATCF reduced without negatively impacting ATCT
      //INTERESTING POSITIVIVE
      positives.push_back(i);
    } else {
      undecided.push_back(i);
    }
  }

  std::unordered_map<size_t, Trinary> antTruthValueAfterAddingFalse;
  std::unordered_map<size_t, Trinary> truthValueAfterAddingFalse;

  dto->substitute(depth, -1, fc);
  t->setCacheAntFalse();
  for (auto time : undecided) {
    antTruthValueAfterAddingFalse[time] = t->evaluate_ant(time);
    truthValueAfterAddingFalse[time] = t->evaluate(time);
  }
  dto->substitute(depth, -1, fc);

  for (auto time : undecided) {
    if (truthValueAfterAddingTrue.at(time) == Trinary::T &&
        antTruthValueAfterAddingFalse.at(time) == Trinary::F) {
      //INTERESTING POSITIVE
      positives.push_back(time);
    } else if (truthValueAfterAddingTrue.at(time) == Trinary::F &&
               truthValueAfterAddingFalse.at(time) == Trinary::T) {
      //substitution with false covers a failure
      //INTERESTING NEGATIVE
      negatives.push_back(time);
    } else {
      //subtitution with false did not produce a failure
      //REAL NOT INTERESTING
    }
  }

  dto->popItem(depth);
  t->setCacheAntFalse();

  return {positives, negatives};
}

inline std::vector<PropositionPtr>
AntecedentGenerator::gatherPropositionsFromNumerics(
    NumericExpressionPtr cn, const TemplateImplicationPtr &t,
    int depth) {

  // 1. Gather IV
  auto [positives, negatives] = gatherInterestingValues(t, depth);

  //debug
  //std::cout << num2String(*cn) << "\n";
  //std::cout << "\t P:";
  //for (auto i : ivs.first) {
  //  std::cout << cn->evaluate<SInt>(i) << " ";
  //}
  //std::cout << "\n";

  //std::cout << "\t N:";
  //for (auto i : ivs.second) {
  //  std::cout << cn->evaluate<SInt>(i) << " ";
  //}
  //std::cout << "\n";

  // 2. Generation of propositions
  std::vector<PropositionPtr> props =
      genPropsThroughClustering(positives, cn, true);

  //for (auto p : props) {
  //  std::cout << prop2String(*p) << "\n";
  //}
  //std::cout << "-----------------------"
  //          << "\n";

  return props;
}

inline void AntecedentGenerator::findCandidatesNumeric(
    size_t candidate, const NumericDecTreeExp &dcVariables,
    const TemplateImplicationPtr &t,
    std::unordered_set<DiscoveredLeaf, DiscoveredLeafHash>
        &discSolutions,
    std::vector<CandidateDec> &candidates, int depth,
    double currScore) {
  //FIXME: discSolutions is not used here

  DTOperatorPtr dto = t->getDT();

  if (dto->isTaken(candidate + numLeavesOffset, 0, depth)) {
    return;
  }

  // retrieve the propositions (props)
  std::vector<PropositionPtr> props = gatherPropositionsFromNumerics(
      dcVariables.at(candidate), t, depth);

  for (auto prop : props) {

    // add the new proposition of a unused variable in the current
    // antecedent
    dto->addItem(prop, depth);

    // ignore this prop if the template contains a known solution
    if (isKnownSolution(dto, 1)) {
      dto->popItem(depth);
      continue;
    }

    OCCS res = computeOccs(t);

    // is the new antecedent at least once satisfied? (avoid vacuity)
    if (res.AToccs > 0 && checkFitness(t, res)) {
      if (res.ATCToccs == 0 || res.ATCToccs == res.AToccs) {
        storeSolution(t, res.ATCToccs == 0);
      } else {
        double score = 0.f;
        if (t->getDT()->getLimits()._heuristic ==
            DTHeuristic::ENTROPY) {
          score = getConditionalEntropy(res, t->getTraceLength());
        } else if (t->getDT()->getLimits()._heuristic ==
                   DTHeuristic::COVERAGE) {
          score = getCovScore(res, _CT, _CF);
        } else {
          messageError("Unknown heuristic");
        }
        double gain = currScore - score;

        candidates.emplace_back(candidate, depth, false, prop, gain,
                                score, true);
      }
    }
    dto->popItem(depth);
  }
}
bool AntecedentGenerator::isKnownSolution(
    const DTOperatorPtr &dto, bool checkOnly,
    const std::optional<DTSolution> &ovveridenSolution) {

  DTSolution solution;
  if (ovveridenSolution.has_value()) {
    solution = ovveridenSolution.value();
  } else {
    solution = dto->getSolution();
  }
  solution.sortByWidth();

  std::stringstream ss;
  if (dto->isMultiDimensional()) {
    for (auto &pack : solution.getMultidimensionalSolution()) {
      for (auto &p : pack) {
        ss << prop2String(p) << "$";
      }
      ss << "$";
    }
  } else {
    for (auto &p : solution.getUnidimensionalSolution()) {
      ss << prop2String(p) << "$";
    }
  }

  if (_knownSolutions.count(ss.str())) {
    return true;
  }
  if (!checkOnly) {
    _knownSolutions.insert(ss.str());
  }

  return false;
}
void AntecedentGenerator::runDecisionTree(
    std::set<size_t> &unusedVars, const DecTreeVariables &dcVariables,
    std::set<size_t> &unusedNumerics,
    const NumericDecTreeExp &numericCandidates,
    const TemplateImplicationPtr &t, double currScore) {

  DTOperatorPtr dto = t->getDT();

  std::unordered_set<DiscoveredLeaf, DiscoveredLeafHash>
      discSolutions;

  auto candidate = unusedVars.begin();
  auto candidateNumeric = unusedNumerics.begin();

  std::vector<CandidateDec> candidates;

  if (dto->getNChoices() < dto->getLimits()._maxAll) {
    for (; candidate != unusedVars.end() ||
           candidateNumeric != unusedNumerics.end();) {
      if (dto->isUnordered()) {
        //Unordered ..#&.. ..##..
        for (size_t i = 0; i < dto->getLimits()._maxDepth; i++) {
          if (dto->canInsertAtDepth(i)) {
            if (candidate != unusedVars.end())
              findCandidates(*candidate, dcVariables, t,
                             discSolutions, candidates, i, currScore);

            if (candidateNumeric != unusedNumerics.end())
              findCandidatesNumeric(
                  *candidateNumeric, numericCandidates, t,
                  discSolutions, candidates, i, currScore);
          }
        }
      } else {
        //Ordered ..#&.. ..##.. ..&&..
        if (dto->isMultiDimensional()) {
          //..#&..
          if (dto->canInsertAtDepth(dto->getCurrentDepth())) {
            if (candidate != unusedVars.end())
              findCandidates(*candidate, dcVariables, t,
                             discSolutions, candidates,
                             dto->getCurrentDepth(), currScore);

            if (candidateNumeric != unusedNumerics.end())
              findCandidatesNumeric(
                  *candidateNumeric, numericCandidates, t,
                  discSolutions, candidates, dto->getCurrentDepth(),
                  currScore);
          }
          if (dto->canInsertAtDepth(dto->getCurrentDepth() + 1)) {
            if (candidate != unusedVars.end())
              findCandidates(*candidate, dcVariables, t,
                             discSolutions, candidates,
                             dto->getCurrentDepth() + 1, currScore);

            if (candidateNumeric != unusedNumerics.end())
              findCandidatesNumeric(
                  *candidateNumeric, numericCandidates, t,
                  discSolutions, candidates,
                  dto->getCurrentDepth() + 1, currScore);
          }
        } else {
          //..##.. ..&&..
          if (dto->canInsertAtDepth(-1)) {
            if (candidate != unusedVars.end())
              findCandidates(*candidate, dcVariables, t,
                             discSolutions, candidates, -1,
                             currScore);

            if (candidateNumeric != unusedNumerics.end()) {
              findCandidatesNumeric(
                  *candidateNumeric, numericCandidates, t,
                  discSolutions, candidates, -1, currScore);
            }
          }
        }
      }

      if (candidate != unusedVars.end())
        candidate++;

      if (candidateNumeric != unusedNumerics.end())
        candidateNumeric++;

    } // for
  }

  std::sort(begin(candidates), end(candidates),
            [](const CandidateDec &e1, const CandidateDec &e2) {
              return e1._gain > e2._gain;
            });

  if (!candidates.empty()) {
    //-1E : keep only best
    if (dto->getLimits()._effort < 0.f) {
      candidates.erase(begin(candidates) + 1, end(candidates));
#if DEBUG
      messageErrorIf(candidates.size() > 1,
                     "More than one candidate when E is < 0");
#endif
      //0E : keep all bests
    } else if (dto->getLimits()._effort == 0.f) {
      double max = candidates[0]._gain;
      //delete all with G < max
      candidates.erase(std::remove_if(begin(candidates),
                                      end(candidates),
                                      [max](const CandidateDec &e) {
                                        return e._gain < max;
                                      }),
                       end(candidates));
      //check that all candidates have the same G

#if DEBUG
      for (auto &e : candidates) {
        messageErrorIf(
            e._gain != max,
            "Found a candidate with different G when E is 0");
      }
#endif
      //E in [0,1] : keep top _dtRange percentage
    } else if (dto->getLimits()._effort > 0.f &&
               dto->getLimits()._effort <= 1.f) {
      size_t toKeep = candidates.size() * dto->getLimits()._effort;
      toKeep = toKeep == 0 ? 1 : toKeep;
      candidates.erase(begin(candidates) + toKeep, end(candidates));

      //E > 1 : keep top N
    } else {
      size_t toKeep = dto->getLimits()._effort;
      toKeep =
          toKeep > candidates.size() ? candidates.size() : toKeep;
      candidates.erase(begin(candidates) + toKeep, end(candidates));
#if DEBUG
      messageErrorIf(candidates.size() != toKeep,
                     "Wrong number of candidates when E > 1");
#endif
    }
  }

  for (auto &cand : candidates) {
    dto->addItem(cand._prop, cand._depth);
    dto->addLeaf(cand._prop,
                 cand._id +
                     (cand._ofNumericOrigin ? numLeavesOffset : 0),
                 cand._negated, cand._depth);

    if (cand._ofNumericOrigin) {
      if (dto->getLimits()._dontReuseNumeric)
        unusedNumerics.erase(cand._id);
    } else {
      if (dto->getLimits()._dontReuseProp)
        unusedVars.erase(cand._id);
    }

    runDecisionTree(unusedVars, dcVariables, unusedNumerics,
                    numericCandidates, t, cand._score);

    if (cand._ofNumericOrigin) {
      if (dto->getLimits()._dontReuseNumeric)
        unusedNumerics.insert(cand._id);
    } else {
      if (dto->getLimits()._dontReuseProp)
        unusedVars.insert(cand._id);
    }

    if (cand._ofNumericOrigin) {
      dto->removeLeaf(cand._id + numLeavesOffset, cand._negated,
                      cand._depth);

    } else {
      if (!discSolutions.count(
              DiscoveredLeaf(cand._id, cand._depth, cand._negated))) {
        //remove leaf only if we are not also removing a discovered solution (discSolutions are not found in findCandidatesNumeric)
        dto->removeLeaf(cand._id, cand._negated, cand._depth);
      }
    }
    dto->popItem(cand._depth);
  } // for candidates

  for (auto &dl : discSolutions) {
    dto->removeLeaf(dl._id, dl._negated, dl._depth);
  }
}
void AntecedentGenerator::storeSolution(
    const TemplateImplicationPtr &t, bool isOffset) {

  DTOperatorPtr dto = t->getDT();

  if (isOffset && !_saveOffset) {
    return;
  }

  // Let's save the current propositions
  DTSolution sol = dto->getMinimizedSolution(isOffset);

  if (isKnownSolution(dto, 0, sol) ||
      dto->isSolutionInconsequential(sol)) {
    return;
  }

  //print items
  //std::cout << "---------------------"
  //          << "\n";
  //for (auto &i : items) {
  //  std::cout << prop2String(i) << "\n";
  //}
  //std::cout << "---------------------"
  //          << "\n";

  //add solution
  if (isOffset) {
    _offSets.push_back(sol);
  } else {
    _onSets.push_back(sol);
  }
}
bool AntecedentGenerator::checkFitness(
    const TemplateImplicationPtr &t, const OCCS &occs) {
  //std::cout << occs.ATCToccs << " vs " << _CT << "\n";

  if (t->getDT()->getLimits()._requirePerfectFitness) {
    return occs.ATCToccs == _CT ||
           (t->getDT()->getLimits()._saveOffset &&
            occs.ATCFoccs == _CF);
  }
  return true;
}

} // namespace harm
