#include "NSGA2.hh"
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

std::vector<std::tuple<size_t, double, Individual>> NSGA2::run(
    const std::unordered_map<
        std::string, std::unordered_set<std::string>> &geneToAssTime,
    size_t maxIterations, double minIncrement,
    const std::vector<Individual> &initialPop) {

  //clear all gnuplot windows
  if (!clc::ve_dont_plot) {
    systemCustom("killall gnuplot");
  }

  //stats utility vars
  size_t secondsPhase1 = 0;
  size_t secondsPhase2 = 0;
  double dominancePhase1 = 0.f;
  double dominancePhase2 = 0.f;
  std::vector<std::pair<size_t, double>> dominance_plot_data;
  double maxDominance = -1;

  //get max possible value for the objectives (all token together)
  //needed for the normalization
  _maxObjs = getMaxObjectivesValues(geneToAssTime);
  bool saveParetoMetricBeforePush = 0;
  //contains the data of the pareto front using the `damage` metric
  std::vector<std::pair<size_t, double>> beforePushMetricFrontData;
  //contain the population being elaborated
  std::vector<Individual> pop;

  if (initialPop.empty()) {
    pop = samplePopulation(geneToAssTime, 1, geneToAssTime.size());
  } else {
    //reccomended option for this use case
    pop = initialPop;
  }

  //The pop size will not exceed this value
  size_t allowedPopSize = pop.size();

  //there are used for the halting criteria
  double prevDominance = 0;
  double dominance = DBL_MAX;
  dirtyTimerSeconds("startNSGA2", 1);
  //used to slow down the plot speed
  dirtyTimerSeconds("plotRate", 1);

  if (clc::ve_only_sim) {
    //skip nsga2 with `damage` metric

    //simulate the golden once to have something to compare
    messageInfo("Simulating the golden design...");
    systemCustom("bash " + clc::ve_shPath + " golden " +
                 clc::ve_ftPath + " 1 0" +
                 (clc::ve_debugScript ? "" : " > /dev/null"));
    dirtyTimerSeconds("startPush", 1);

    //set the variables for the push phase
    _pushing = 1;
    _simulate = !_simulate;
    _maxObjs.second = _valuePrecision;
  }

  for (size_t i = 0; i < maxIterations; i++) {
    std::cout << "Population size " << pop.size() << "\n";
    //keep track how long each iteratin takes
    dirtyTimerSeconds("startIteration", 1);

    //skip the first iteration: nothing to mutate or crossover
    if (i > 0) {
      //mutation on the entire population
      mutatePop(pop, geneToAssTime);
      addOffspring(pop, geneToAssTime);
      removeDuplicates(pop);
    }

    auto fronts = generateFronts(pop, geneToAssTime);
    selectElites(fronts, geneToAssTime, pop, allowedPopSize);

    //prepare data for printing---------------------------------
    std::vector<std::pair<size_t, size_t>> chart_data;
    for (auto &individual : generateParetoFront(pop, geneToAssTime)) {
      evalIndividual(individual, geneToAssTime);
      chart_data.push_back(individual._objective);
    }
    //convert damage/error to double, and normalize it
    std::vector<std::pair<size_t, double>> front_plot_data;
    for (const auto &[x, y] : chart_data) {
      front_plot_data.emplace_back(x, ((double)y / _valuePrecision));
    }

    //Get the dominance of the front to decide if we need to continue
    dominance = getDominatedSurface(
        chart_data, std::make_pair(_maxObjs.first, _valuePrecision));
    double increment =
        ((dominance - prevDominance) / dominance) * 100.f;
    //----------------------------------------------------------

    if (saveParetoMetricBeforePush) {
      saveParetoMetricBeforePush = 0;
      dominancePhase1 = dominance;
      beforePushMetricFrontData = front_plot_data;
    }

    //plot debugging charts-------------------------------------
    if (_pushing) {
      plotBeforeAfter(
          beforePushMetricFrontData, front_plot_data,
          "Number of tokens", clc::ve_metricName,
          "Dominance: " + std::to_string(dominance * 100) + "%",
          "Before push", "After push",
          std::make_pair(0.f, _maxObjs.first),
          std::make_pair(0.f, 1.f), 1);

      if (clc::ve_plotDominance) {
        dominance_plot_data.emplace_back(
            dirtyTimerSeconds("startNSGA2", 0), dominance);
        maxDominance =
            maxDominance > dominance_plot_data.back().second
                ? maxDominance
                : dominance_plot_data.back().second;
        plotDominance(
            dominance_plot_data, "Time(s)", "Dominance",
            "Dominance in time",
            std::make_pair(0.f, dirtyTimerSeconds("startNSGA2", 0)),
            std::make_pair(0.f, maxDominance), 1);
      }
    } else {
      plotErrorDamage(
          front_plot_data, "Number of tokens", std::string("Damage"),
          "Dominance: " + std::to_string(dominance * 100) + "%",
          std::make_pair(0.f, _maxObjs.first),
          std::make_pair(0.f, 1.f), 1);
    }

    //print monitoring info-------------------------------------
    auto duration = dirtyTimerSeconds("startIteration", 0);
    std::cout << "Iteration: " << i << "th\n";
    std::cout << "Duration: " << duration << "s\n";
    std::cout << "PrevDominance: " << prevDominance << "\n";
    std::cout << "Dominance: " << dominance << "\n";
    std::cout << "Dominance increment: " << increment << "%\n";

    //halting conditions---------------------------------------
    if (increment <= minIncrement) {
      if (!clc::ve_only_sim &&
          !isTimeOutSeconds("startNSGA2", clc::ve_minTime)) {
        goto continueUpdate;
      }

      if (_pushing) {
        if (!isTimeOutSeconds("startPush", clc::ve_minPushTime)) {
          goto continueUpdate;
        }

      } else {
        //save the best front using only the damage
        if (clc::ve_dump_dmg_vs_metric) {
          dumpDamageToMetricFront(
              generateParetoFront(pop, geneToAssTime), geneToAssTime);
        }
        secondsPhase1 = dirtyTimerSeconds("startNSGA2", 0);
        plotErrorDamage(
            front_plot_data, "Number of tokens",
            std::string("Damage"),
            "Dominance " + std::to_string(dominance * 100) + "%",
            std::make_pair(0.f, _maxObjs.first),
            std::make_pair(0.f, 1.f), 1,
            clc::ve_dumpTo + "/" + clc::ve_technique + "_" +
                "damage.csv",
            clc::ve_dumpTo + "/" + clc::ve_technique + "_damage.png");

        if (clc::ve_push) {
          //start phase 2
          initPush();
          prevDominance = 0;
          dominance = DBL_MAX;
          continue;
        }
      }

      break;

    } else {
      if (_pushing) {
        if (isTimeOutSeconds("startPush", clc::ve_maxPushTime)) {
          break;
        }
      }
    }
    //-----------------------------------------------------

  continueUpdate:;
    prevDominance = dominance;
    allowedPopSize = allowedPopSize <= 100
                         ? std::min(100ul, initialPop.size())
                         : allowedPopSize * 0.9;
  }

  if (clc::ve_push) {
    secondsPhase2 = dirtyTimerSeconds("startPush", 0);
    dominancePhase2 = dominance;
  }
  if (clc::ve_only_sim) {
    dominancePhase1 = dominance;
  }

  messageInfo("NSGA2 has finished!");

  //dump temporal statistics
  fileAppendContent(clc::ve_dumpTo + "/" + clc::ve_technique + "_" +
                        "time.csv",
                    std::to_string(secondsPhase1) + ";" +
                        std::to_string(secondsPhase2) + "\n");
  //dump dominance stat
  fileDumpContent(clc::ve_dumpTo + "/" + clc::ve_technique + "_" +
                      "dominance.csv",
                  "dominancePhase1;dominancePhase2;increment\n");
  fileAppendContent(
      clc::ve_dumpTo + "/" + clc::ve_technique + "_" +
          "dominance.csv",
      std::to_string(dominancePhase1) + ";" +
          std::to_string(dominancePhase2) + ";" +
          std::to_string(dominancePhase2 - dominancePhase1) + "\n");

  //organize the return structure
  std::vector<std::tuple<size_t, double, Individual>> ret;

  for (auto &individual : generateParetoFront(pop, geneToAssTime)) {
    evalIndividual(individual, geneToAssTime);
    double err_damage =
        (_pushing && clc::ve_metricDirection)
            ? 1.f - (double)individual._objective.second /
                        (double)_valuePrecision
            : (double)individual._objective.second /
                  (double)_valuePrecision;
    ret.emplace_back(individual._objective.first, err_damage,
                     individual);
  }

  if (clc::ve_genRand) {
    genAndDumpRandomClusters(generateParetoFront(pop, geneToAssTime),
                             geneToAssTime, beforePushMetricFrontData,
                             50);
  }

  return ret;
}

void NSGA2::evalIndividual(
    Individual &individual,
    const std::unordered_map<
        std::string, std::unordered_set<std::string>> &geneToAssTime,
    size_t t_id, bool dontUseCache) {

  std::string si = serializeIndividual(individual);

  if (!dontUseCache &&
      countGuard(_cachedIndividual, si, _cacheGuard)) {
    individual._objective =
        atGuard(_cachedIndividual, si, _cacheGuard);
    return;
  }

  if (!_simulate) {

    std::unordered_set<std::string> uniqueFeatures;
    for (const auto &gene : individual._genes) {
      for (const auto &feature : geneToAssTime.at(gene)) {
        uniqueFeatures.insert(feature);
      }
    }

    auto obj = std::make_pair<size_t, size_t>(
        individual._genes.size(), uniqueFeatures.size());

    obj.second = ((double)obj.second / (double)_maxObjs.second) *
                 _valuePrecision;

    messageErrorIf(obj.first == 0, "?");
    std::string si = serializeIndividual(individual);
    if (!dontUseCache) {
      _cacheGuard.lock();
      _cachedIndividual[si] = obj;
      _cacheGuard.unlock();
    }

    individual._objective = obj;

  } else {

    systemCustom("bash " + clc::ve_shPath + " \"" +
                 toScriptList(individual._genes) + "\" " +
                 clc::ve_ftPath + " 1 " + std::to_string(t_id) +
                 (clc::ve_debugScript ? "" : " > /dev/null"));

    std::string metricFile =
        clc::ve_ftPath + "/" + std::to_string(t_id) + ".txt";

    messageErrorIf(!std::filesystem::exists(metricFile),
                   "Can not find metric file '" + metricFile +
                       "' after simulating!\n\n");

    std::ifstream inputFile(metricFile);
    double metricValue;
    inputFile >> metricValue;
    inputFile.close();

    systemCustom("rm " + metricFile);

    metricValue = metricValue < 0.f ? 0.f : metricValue;
    metricValue =
        clc::ve_metricDirection ? 1.f - metricValue : metricValue;

    //debug
    //std::cout << metricValue << "\n";

    auto obj = std::make_pair<size_t, size_t>(
        individual._genes.size(), metricValue * _valuePrecision);
    if (!dontUseCache) {
      _cacheGuard.lock();
      _cachedIndividual[serializeIndividual(individual)] = obj;
      _cacheGuard.unlock();
    }
    individual._objective = obj;
  }
}

void NSGA2::evalIndividuals(
    std::vector<Individual> &pop,
    const std::unordered_map<
        std::string, std::unordered_set<std::string>> &geneToAssTime,
    bool dontUseCache) {

  Semaphore maxThreads(clc::maxThreads);
  Semaphore completed(0);

  progresscpp::ParallelProgressBar pb;
  if (_pushing) {
    pb.addInstance(0, "Calculating objectives...", pop.size(), 70);
  } else {
    std::cout << "Calculating objectives..."
              << "\n";
  }

  for (size_t toBeServed = 0; toBeServed < pop.size(); toBeServed++) {

    maxThreads.wait();

    std::thread([this, toBeServed, &maxThreads, &pop, &geneToAssTime,
                 &completed, &pb, &dontUseCache]() {
      evalIndividual(pop[toBeServed], geneToAssTime, toBeServed,
                     dontUseCache);
      maxThreads.addNotifyOnce(1);
      completed.addNotifyOnce(1);
      if (_pushing) {
        pb.increment(0);
        pb.display();
      }
    }).detach();
  }
  completed.wait(pop.size());
  if (_pushing) {
    pb.done(0);
  }
}

void NSGA2::trimPop(std::vector<Individual> &pop) {

  size_t lower = (size_t)((clc::ve_metricDirection
                               ? (1.f - clc::ve_metricInterval.second)
                               : clc::ve_metricInterval.first) *
                          (double)_valuePrecision);
  size_t upper = (size_t)((clc::ve_metricDirection
                               ? (1.f - clc::ve_metricInterval.first)
                               : clc::ve_metricInterval.second) *
                          (double)_valuePrecision);

  for (size_t i = 0; i < pop.size(); i++) {
    auto &ind = pop[i];
    if (ind._objective.second < lower ||
        ind._objective.second > upper) {
      ind._genes.clear();
    }
  }

  pop.erase(
      std::remove_if(begin(pop), end(pop),
                     [](Individual &e) { return e._genes.empty(); }),
      pop.end());
}

void NSGA2::generateDominanceRank(
    std::vector<Individual> &pop,
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {

  // Store the objective values for each individual
  evalIndividuals(pop, geneToAssTime);

  //init the ranks
  for (auto &ind : pop) {
    ind._rank = 0;
  }

  if (_pushing) {
    trimPop(pop);
  }

  for (size_t i = 0; i < pop.size(); i++) {
    for (size_t j = 0; j < pop.size(); j++) {
      if (i == j)
        continue;

      auto &a = pop[i]._objective;
      auto &b = pop[j]._objective;

      if ((a.first <= b.first && a.second >= b.second) &&
          (a.first < b.first || a.second > b.second)) {
        pop[i]._rank++;
      }
    }
  }
}

std::vector<std::vector<Individual>> NSGA2::generateFronts(
    const std::vector<Individual> &pop,
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {

  //we do not want to break pop
  std::vector<Individual> pop_copy = pop;

  generateDominanceRank(pop_copy, geneToAssTime);

  std::vector<std::vector<Individual>> fronts(pop_copy.size());

  // Store the list of pop in each front
  for (auto &ind : pop_copy) {
    fronts.at(ind._rank).push_back(ind);
  }

  // Remove empty fronts
  fronts.erase(
      std::remove_if(fronts.begin(), fronts.end(),
                     [](const std::vector<Individual> &front) {
                       return front.empty();
                     }),
      fronts.end());

  return fronts;
}
std::vector<Individual> NSGA2::generateParetoFront(
    const std::vector<Individual> &pop,
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {

  //we do not want to break pop
  std::vector<Individual> pop_copy = pop;
  generateDominanceRank(pop_copy, geneToAssTime);

  std::vector<Individual> topFront;

  for (auto &ind : pop_copy) {
    if (ind._rank == 0) {
      topFront.push_back(ind);
    }
  }
  return topFront;
}

void NSGA2::crowdSort(
    std::vector<Individual> &pop,
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {

  size_t min[2] = {(size_t)-1, (size_t)-1};
  size_t max[2] = {0, 0};
  size_t diff[2] = {0, 0};

  // Evaluate all pop in the population
  for (size_t i = 0; i < pop.size(); i++) {
    evalIndividual(pop[i], geneToAssTime);
    min[0] = pop[i]._objective.first < min[0]
                 ? pop[i]._objective.first
                 : min[0];
    max[0] = pop[i]._objective.first > max[0]
                 ? pop[i]._objective.first
                 : max[0];
    min[1] = pop[i]._objective.second < min[1]
                 ? pop[i]._objective.second
                 : min[1];
    max[1] = pop[i]._objective.second > max[1]
                 ? pop[i]._objective.second
                 : max[1];
  }
  diff[0] = max[0] - min[0];
  diff[1] = max[1] - min[1];

  // Initialize the crowding distance of all pop to zero
  std::vector<double> crowdingDist(pop.size(), 0.0);

  // Sort the pop in each rank based on objective function values
  for (size_t k = 0; k < 2; k++) {
    //init
    std::vector<size_t> sortedIndividuals(pop.size());
    std::iota(sortedIndividuals.begin(), sortedIndividuals.end(), 0);

    std::sort(sortedIndividuals.begin(), sortedIndividuals.end(),
              [&k, &pop](const size_t &i, const size_t &j) {
                if (k == 0) {
                  return pop[i]._objective.first <
                         pop[j]._objective.first;
                } else {
                  return pop[i]._objective.second <
                         pop[j]._objective.second;
                }
              });

    // Set the crowding distance of the boundary solutions to infinity
    crowdingDist[sortedIndividuals[0]] =
        crowdingDist[sortedIndividuals[pop.size() - 1]] = INFINITY;

    // Calculate the crowding distance of all other solutions in the current rank
    for (size_t i = 1; i < pop.size() - 1; i++) {
      if (k == 0) {
        crowdingDist[sortedIndividuals[i]] +=
            diff[k] > 0
                ? (pop[sortedIndividuals[i + 1]]._objective.first -
                   pop[sortedIndividuals[i - 1]]._objective.first) /
                      (float)(diff[k])
                : 0.f;
      } else {
        crowdingDist[sortedIndividuals[i]] +=
            diff[k] > 0
                ? (pop[sortedIndividuals[i + 1]]._objective.second -
                   pop[sortedIndividuals[i - 1]]._objective.second) /
                      (float)(diff[k])
                : 0.f;
      }
    }
  }

  //need to associate the individual with a score for sorting
  std::vector<std::pair<Individual, double>> popWithCD;
  for (size_t i = 0; i < pop.size(); i++) {
    popWithCD.push_back(std::make_pair(pop[i], crowdingDist[i]));
  }
  std::sort(popWithCD.begin(), popWithCD.end(),
            [](std::pair<Individual, double> &e1,
               std::pair<Individual, double> &e2) {
              return e1.second > e2.second;
            });

  pop.clear();

  for (auto &e : popWithCD) {
    pop.push_back(e.first);
  }
}

void NSGA2::selectElites(
    std::vector<std::vector<Individual>> &fronts,
    const std::unordered_map<
        std::string, std::unordered_set<std::string>> &geneToAssTime,
    std::vector<Individual> &pop, size_t allowedPopSize) {

  pop.clear();

  //used to avoid repetitions of pop with the same score
  std::set<std::pair<size_t, size_t>> alreadyInUse;

  for (auto &front : fronts) {
    if (front.size() + pop.size() <= allowedPopSize) {
      //front fits entirely
      for (auto &individual : front) {
        evalIndividual(individual, geneToAssTime);
        if (!alreadyInUse.count(individual._objective)) {
          alreadyInUse.insert(individual._objective);
          pop.push_back(individual);
        }
      }
    } else if (pop.size() < allowedPopSize) {
      //front does not fit, need crowd sorting
      crowdSort(front, geneToAssTime);
      for (auto &individual : front) {
        evalIndividual(individual, geneToAssTime);
        //check if already in use
        if (!alreadyInUse.count(individual._objective)) {
          alreadyInUse.insert(individual._objective);
          pop.push_back(individual);
        }

        if (pop.size() == allowedPopSize) {
          return;
        }
      }
    }
  }
}

std::pair<Individual, Individual>
NSGA2::tournamentSelection(const std::vector<Individual> &pop) {

  std::pair<Individual, Individual> parents;

  //select first parent
  std::random_device rd1;
  std::mt19937 rng1(rd1());
  std::uniform_int_distribution<int> dist(0, pop.size() - 1);

  int a1 = 0;
  int b1 = 0;

  while (a1 == b1) {
    a1 = dist(rng1);
    b1 = dist(rng1);
  }

  parents.first = pop[a1]._rank > pop[b1]._rank ? pop[b1] : pop[a1];

  //select second parent
  std::random_device rd2;
  std::mt19937 rng2(rd2());

  int a2 = 0;
  int b2 = 0;

  while (a2 == b2) {
    a2 = dist(rng2);
    b2 = dist(rng2);
  }
  parents.second = pop[a2]._rank > pop[b2]._rank ? pop[b2] : pop[a2];

  return parents;
}

Individual
NSGA2::crossover(std::pair<Individual, Individual> &parents) {

  std::unordered_set<std::string> kidGenes;

  //merge the genes
  for (auto &gene : parents.first._genes) {
    kidGenes.insert(gene);
  }
  for (auto &gene : parents.second._genes) {
    kidGenes.insert(gene);
  }

  return kidGenes;
}

//Not used
void NSGA2::mutateIndividual(
    Individual &child,
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {}

void NSGA2::mutatePop(
    std::vector<Individual> &pop,
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {
  std::vector<Individual> mutatedPop = pop;
  for (auto &ind : pop) {
    if (getRandomBool()) {
      //add a random individual of the same size
      mutatedPop.push_back(
          samplePopulation(geneToAssTime, ind._genes.size(), 1)
              .front());
    } else {
      //create a new individual with a single random element
      auto tmpInd = ind;
      tmpInd._genes.insert(getRandomItem(geneToAssTime).first);
      mutatedPop.push_back(tmpInd);
    }
  }
  pop = mutatedPop;
}

void NSGA2::addOffspring(
    std::vector<Individual> &pop,
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {

  std::vector<Individual> offSpring;

  //we do not want to break pop
  std::vector<Individual> pop_copy = pop;

  generateDominanceRank(pop_copy, geneToAssTime);

  //each iteration generates and adds one child
  for (size_t i = 0; i < pop_copy.size() && pop_copy.size() > 1;
       i++) {
    auto parents = tournamentSelection(pop_copy);
    auto child = crossover(parents);
    mutateIndividual(child, geneToAssTime);
    offSpring.push_back(child);
  }

  //add the offpring to the elite population
  pop.insert(std::end(pop), std::begin(offSpring),
             std::end(offSpring));
}

void NSGA2::genAndDumpRandomClusters(
    std::vector<Individual> paretoFront,
    const std::unordered_map<
        std::string, std::unordered_set<std::string>> &geneToAssTime,
    std::vector<std::pair<size_t, double>> &beforePushMetricFrontData,
    size_t reps) {

  messageInfo("Generating random clusters...");

  std::vector<std::pair<size_t, double>> afterPushData;
  std::vector<std::pair<size_t, double>> randomData;
  //    std::vector<Individual> randomRepresentatives;

  //keep track the elaborated pop
  size_t geObIndex = 0;

  for (auto &individual : paretoFront) {
    evalIndividual(individual, geneToAssTime);
    afterPushData.emplace_back(
        individual._objective.first,
        (((double)individual._objective.second / _valuePrecision)));

    //gather random pop
    std::vector<Individual> randomIndividuals;
    for (size_t i = 0; i < reps; i++) {
      randomIndividuals.push_back(getRandomIndividual(
          geneToAssTime, individual._genes.size()));
    }

    double avgRandom = 0.f;

    std::vector<std::pair<double, Individual>> candidatesRand;

    std::cout << geObIndex++ << "/" << paretoFront.size() << "\n";

    //eval random pop
    evalIndividuals(randomIndividuals, geneToAssTime);

    for (auto &ind : randomIndividuals) {
      double rnd =
          (((double)ind._objective.second / _valuePrecision));
      avgRandom += rnd;
      //        candidatesRand.emplace_back(rnd, ind);
    }

    avgRandom /= (double)randomIndividuals.size();

    //sort by distance from the avg
    //      std::sort(begin(candidatesRand), end(candidatesRand),
    //                [&avgRandom](std::pair<double, Individual> &e1,
    //                             std::pair<double, Individual> &e2) {
    //                  return std::abs(e1.first - avgRandom) <
    //                         std::abs(e2.first - avgRandom);
    //                });

    //store a good rand candidate (close to the average)
    //      randomRepresentatives.push_back(candidatesRand.front().second);

    randomData.emplace_back(individual._genes.size(), avgRandom);
  }

  plotBeforeAfterRandom(
      beforePushMetricFrontData, afterPushData, randomData,
      "Number of tokens",
      (_pushing ? clc::ve_metricName : std::string("Damage")), "",
      "Before push", "After push", "Random",
      std::make_pair(0.f, _maxObjs.first), std::make_pair(0.f, 1.f),
      1, clc::ve_dumpTo + "/" + clc::ve_technique + "_" + "bar.csv",
      clc::ve_dumpTo + "/" + clc::ve_technique + "_bar.png");

  std::ofstream out(clc::ve_dumpTo + "/" + clc::ve_technique +
                    "_randCandidates.csv");

  //  std::sort(randomRepresentatives.begin(), randomRepresentatives.end(),
  //            [](Individual &e1, Individual &e2) {
  //              return e1._genes.size() < e2._genes.size();
  //            });

  //  //dump verilog defines
  //  out << "size,define\n";
  //  for (auto &rp : randomRepresentatives) {
  //    out << rp._genes.size() << ","
  //        << (clc::ve_technique == "br" ? toDefineBR(rp._genes, 0)
  //                                      : toDefineSR(rp._genes))
  //        << "\n";
  //  }
  //  out.close();
}
void NSGA2::dumpDamageToMetricFront(
    std::vector<Individual> paretoFront,
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {
  messageInfo("Dumping damage to metric front...");

  std::vector<double> norm_damage;
  evalIndividuals(paretoFront, geneToAssTime, true);
  for (auto &individual : paretoFront) {
    norm_damage.push_back((double)individual._objective.second /
                          _valuePrecision);
  }

  _simulate = 1;

  std::vector<double> norm_metric;
  evalIndividuals(paretoFront, geneToAssTime, true);
  for (auto &individual : paretoFront) {
    norm_metric.push_back((double)individual._objective.second /
                          _valuePrecision);
  }
  _simulate = 0;

  std::ofstream out(clc::ve_dumpTo + "/" + clc::ve_technique +
                    std::string("_dmg_vs_metric") + ".csv");

  out << "damage,metric\n";
  for (size_t i = 0; i < norm_damage.size(); i++) {
    out << norm_damage[i] << ", " << norm_metric[i] << "\n";
  }
}

void NSGA2::initPush() {

  printPushing();
  dirtyTimerSeconds("startPush", 1);
  _pushing = 1;
  _simulate = !_simulate;
  _cachedIndividual.clear();
  _maxObjs.second = _valuePrecision;
  //simulate golden
  messageInfo("Simulating the golden design...");
  systemCustom("bash " + clc::ve_shPath + " golden " +
               clc::ve_ftPath + " 1 0" +
               (clc::ve_debugScript ? "" : " > /dev/null"));
}

} // namespace dea
