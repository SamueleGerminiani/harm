#pragma once
#include "Individual.hh"
#include "NSGA2_utils.hh"
#include "ProgressBar.hpp"
#include "Semaphore.hh"
#include "dea.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "utils.hh"
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace dea {

class NSGA2 {

public:
  NSGA2() = default;

  std::vector<std::tuple<size_t, double, Individual>>
  run(const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime,
      size_t maxIterations = 100, double minIncrement = 1.f,
      const std::vector<Individual> &initialPop =
          std::vector<Individual>());

private:
  void evalIndividual(
      Individual &individual,
      const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime,
      size_t t_id = 0, bool dontUseCache = false);

  void evalIndividuals(
      std::vector<Individual> &pop,
      const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime,
      bool dontUseCache = false);

  void trimPop(std::vector<Individual> &pop);

  void generateDominanceRank(
      std::vector<Individual> &pop,
      const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime);

  std::vector<std::vector<Individual>> generateFronts(
      const std::vector<Individual> &pop,
      const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime);
  std::vector<Individual> generateParetoFront(
      const std::vector<Individual> &pop,
      const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime);

  void
  crowdSort(std::vector<Individual> &pop,
            const std::unordered_map<std::string,
                                     std::unordered_set<std::string>>
                &geneToAssTime);

  void selectElites(std::vector<std::vector<Individual>> &fronts,
                    const std::unordered_map<
                        std::string, std::unordered_set<std::string>>
                        &geneToAssTime,
                    std::vector<Individual> &pop,
                    size_t allowedPopSize);

  std::pair<Individual, Individual>
  tournamentSelection(const std::vector<Individual> &pop);

  Individual crossover(std::pair<Individual, Individual> &parents);

  //Not used
  void mutateIndividual(
      Individual &child,
      const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime);

  void
  mutatePop(std::vector<Individual> &pop,
            const std::unordered_map<std::string,
                                     std::unordered_set<std::string>>
                &geneToAssTime);

  void addOffspring(std::vector<Individual> &pop,
                    const std::unordered_map<
                        std::string, std::unordered_set<std::string>>
                        &geneToAssTime);

  void genAndDumpRandomClusters(
      std::vector<Individual> paretoFront,
      const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime,
      std::vector<std::pair<size_t, double>>
          &beforePushMetricFrontData,
      size_t reps = 10);

  void dumpDamageToMetricFront(
      std::vector<Individual> paretoFront,
      const std::unordered_map<std::string,
                               std::unordered_set<std::string>>
          &geneToAssTime);
  void initPush();
  void repair(std::vector<Individual> &pop);

  bool _pushing = 0;
  std::unordered_map<std::string, std::pair<size_t, size_t>>
      _cachedIndividual;
  std::mutex _cacheGuard;
  bool _simulate = false;
  std::pair<size_t, size_t> _maxObjs;
  size_t _valuePrecision = 10000;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      _groupLabelToMutuallyExclusiveGenes;
  std::unordered_map<std::string, std::string>
      _geneToExclusiveGroupLabel;
};
} // namespace dea
