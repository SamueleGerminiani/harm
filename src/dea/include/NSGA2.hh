#pragma once
#include "ProgressBar.hpp"
#include "Semaphore.hh"
#include "evaluator.hh"
#include "globals.hh"
#include "message.hh"
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

class NSGA2 {

public:
  struct Individual {
  public:
    Individual() = default;
    Individual(const std::unordered_set<std::string> &_genes,
               const std::pair<size_t, size_t> &objective, const size_t &rank)
        : _genes(_genes), _objective(objective), _rank(rank) {
      //not todo
    }
    Individual(const std::unordered_set<std::string> &_genes) : _genes(_genes) {
      //not todo
    }

  public:
    std::unordered_set<std::string> _genes;
    std::pair<size_t, size_t> _objective;
    size_t _rank = 0;
  };

  NSGA2() = default;
  double customLog(double base, double x) {
    return std::log(x) / std::log(base);
  }

  double inline logScale(double value) {
    if (value == 0.f) {
      return 0.f;
    }
    double base = 1.1f;
    return customLog(base, value + 1.f) *
           (_valuePrecision / customLog(base, _valuePrecision + 1.f));
  }

  std::vector<std::tuple<size_t, double, Individual>>
  run(const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime,
      size_t maxIterations = 100, double minIncrement = 1.f,
      const std::vector<Individual> &initialPop = std::vector<Individual>()) {

    //clear all gnuplot windows
    systemCustom("killall gnuplot");

    //stats utility vars
    size_t secondsPhase1 = 0;
    size_t secondsPhase2 = 0;
    double dominancePhase1 = 0.f;
    double dominancePhase2 = 0.f;
    std::vector<std::pair<size_t, double>> dominance_plot_data;
    double maxDominance = -1;

    //get max possible value for the objectives (all token together)
    _maxObjs = getMaxObjectivesValues(geneToAssTime);
    bool saveParetoMetricBeforePush = 0;
    std::vector<std::pair<size_t, double>> beforePushMetricFrontData;
    std::vector<Individual> pop;

    if (initialPop.empty()) {
      pop = samplePopulation(geneToAssTime, 1, geneToAssTime.size());
    } else {
      pop = initialPop;
    }

    size_t allowedPopSize = pop.size();

    //used for the halting criteria
    double prevDominance = 0;
    double dominance = DBL_MAX;
    dirtyTimerSeconds("startNSGA2", 1);

    dirtyTimerSeconds("plotRate", 1);

    if (clc::ve_only_sim) {
      //simulate golden
      messageInfo("Simulating the golden design...");
      systemCustom("bash " + clc::ve_shPath + " golden " + clc::ve_ftPath +
                   " 1 0" + (clc::ve_debugScript ? "" : " > /dev/null"));
      dirtyTimerSeconds("startPush", 1);
      _pushing = 1;
      _simulate = !_simulate;
      _maxObjs.second = _valuePrecision;
    }

    for (size_t i = 0; i < maxIterations; i++) {
      std::cout << "Population size " << pop.size() << "\n";
      //keep track how long each iteratin takes
      dirtyTimerSeconds("startIteration", 1);

      //skip the first iteration
      if (i > 0) {
        //mutation on the entire population
        mutatePop(pop, geneToAssTime);
        addOffspring(pop, geneToAssTime);
        removeDuplicates(pop);
      }

      auto fronts = generateFronts(pop, geneToAssTime);
      selectElites(fronts, geneToAssTime, pop, allowedPopSize);

      //prepare data for printing
      std::vector<std::pair<size_t, size_t>> chart_data;
      for (auto &individual : generateParetoFront(pop, geneToAssTime)) {
        evalIndividual(individual, geneToAssTime);
        chart_data.push_back(individual._objective);
      }

      dominance = getDominatedSurface(
          chart_data, std::make_pair(_maxObjs.first, _valuePrecision));
      double increment = ((dominance - prevDominance) / dominance) * 100.f;

      //convert damage/error to double, and normalize it
      std::vector<std::pair<size_t, double>> front_plot_data;
      for (const auto &[x, y] : chart_data) {
        front_plot_data.emplace_back(x, ((double)y / _valuePrecision));
      }

      if (saveParetoMetricBeforePush) {
        saveParetoMetricBeforePush = 0;
        dominancePhase1 = dominance;
        beforePushMetricFrontData = front_plot_data;
      }

      if (_pushing) {
        plotBeforeAfter(beforePushMetricFrontData, front_plot_data,
                        "Number of tokens", clc::ve_metricName,
                        "Dominance: " + std::to_string(dominance * 100) + "%",
                        "Before push", "After push",
                        std::make_pair(0.f, _maxObjs.first),
                        std::make_pair(0.f, 1.f), 1);

        if (clc::ve_plotDominance) {
          dominance_plot_data.emplace_back(dirtyTimerSeconds("startNSGA2", 0),
                                           dominance);
          maxDominance = maxDominance > dominance_plot_data.back().second
                             ? maxDominance
                             : dominance_plot_data.back().second;
          plotDominance(dominance_plot_data, "Time(s)", "Dominance",
                        "Dominance in time",
                        std::make_pair(0.f, dirtyTimerSeconds("startNSGA2", 0)),
                        std::make_pair(0.f, maxDominance), 1);
        }

      } else {

        plotErrorDamage(
            front_plot_data, "Number of tokens", std::string("Damage"),
            "Dominance: " + std::to_string(dominance * 100) + "%",
            std::make_pair(0.f, _maxObjs.first), std::make_pair(0.f, 1.f), 1);
      }

      auto duration = dirtyTimerSeconds("startIteration", 0);

      std::cout << "Iteration: " << i << "th\n";
      std::cout << "Duration: " << duration << "s\n";
      std::cout << "PrevDominance: " << prevDominance << "\n";
      std::cout << "Dominance: " << dominance << "\n";
      std::cout << "Dominance increment: " << increment << "%\n";

      //terminal condition
      if (increment <= minIncrement) {
        if (!clc::ve_only_sim && !isTimeOut("startNSGA2", clc::ve_minTime)) {
          goto continueUpdate;
        }

        if (_pushing) {
          if (!isTimeOut("startPush", clc::ve_minPushTime)) {
            goto continueUpdate;
          }

        } else {
          secondsPhase1 = dirtyTimerSeconds("startNSGA2", 0);
          plotErrorDamage(
              front_plot_data, "Number of tokens", std::string("Damage"),
              "Dominance " + std::to_string(dominance * 100) + "%",
              std::make_pair(0.f, _maxObjs.first), std::make_pair(0.f, 1.f), 1,
              clc::ve_dumpTo + "/" + clc::ve_technique + "_" + "damage.cvs",
              clc::ve_dumpTo + "/" + clc::ve_technique + "_damage.png");

          if (clc::ve_push) {
            std::cout << "######  #     #  #####  #     # ### #     #  #####\n";
            std::cout
                << "#     # #     # #     # #     #  #  ##    # #     #\n";
            std::cout << "#     # #     # #       #     #  #  # #   # #\n";
            std::cout
                << "######  #     #  #####  #######  #  #  #  # #  ####\n";
            std::cout
                << "#       #     #       # #     #  #  #   # # #     #\n";
            std::cout
                << "#       #     # #     # #     #  #  #    ## #     #\n";
            std::cout << "#        #####   #####  #     # ### #     #  #####\n";

            //dump frontier before push
            dirtyTimerSeconds("startPush", 1);
            _pushing = 1;
            _simulate = !_simulate;
            _cachedIndividual.clear();
            _maxObjs.second = _valuePrecision;
            prevDominance = 0;
            dominance = DBL_MAX;
            saveParetoMetricBeforePush = 1;
            //simulate golden
            messageInfo("Simulating the golden design...");
            systemCustom("bash " + clc::ve_shPath + " golden " +
                         clc::ve_ftPath + " 1 0" +
                         (clc::ve_debugScript ? "" : " > /dev/null"));
            continue;
          }
        }

        break;

      } else {
        if (_pushing) {
          if (isTimeOut("startPush", clc::ve_maxPushTime)) {
            break;
          }
        }
      }

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
        clc::ve_dumpTo + "/" + clc::ve_technique + "_" + "dominance.csv",
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
              : (double)individual._objective.second / (double)_valuePrecision;
      ret.emplace_back(individual._objective.first, err_damage, individual);
    }

    if (clc::ve_genRand) {
      genAndDumpRandomClusters(generateParetoFront(pop, geneToAssTime),
                               geneToAssTime, beforePushMetricFrontData, 50);
    }

    return ret;
  }

private:
  std::string serializeIndividual(const Individual &individual) {
    std::set<std::string> sorted_individual(individual._genes.begin(),
                                            individual._genes.end());
    std::stringstream ss;
    for (const auto &token : sorted_individual) {
      ss << token << ",";
    }
    return ss.str();
  }
  std::string toDefineBR(const std::unordered_set<std::string> &individual,
                         bool escape = 1) {
    std::string define = "";
    std::unordered_map<std::string, std::string> idToMask;
    std::unordered_map<std::string, size_t> idToSize;
    for (auto &token : individual) {
      std::istringstream iss(token);
      std::string tmp;
      std::string id, size, bit;
      std::getline(iss, tmp, ',');
      id = tmp;
      std::getline(iss, tmp, ',');
      size = tmp;
      std::getline(iss, tmp, ',');
      bit = tmp;
      if (!idToMask.count(id)) {
        idToMask[id] = std::string(std::stoull(size), '1');
      }
      idToSize[id] = std::stoull(size);
      idToMask[id][idToSize.at(id) - (std::stoull(bit) + 1)] = '0';
    }

    for (auto &[id, mask] : idToMask) {
      if (escape) {
        define += " +define+" + id + " +define+MASK_" + id + "=" +
                  std::to_string(idToSize.at(id)) + "\\'b" + mask;
      } else {
        define += " +define+" + id + " +define+MASK_" + id + "=" +
                  std::to_string(idToSize.at(id)) + "'b" + mask;
      }
    }

    return define;
  }
  std::string toDefineSR(const std::unordered_set<std::string> &individual) {
    std::string define = "";
    std::unordered_map<std::string, std::string> idToMask;
    std::unordered_map<std::string, size_t> idToSize;
    for (auto &token : individual) {
      define += " +define+" + token;
    }

    return define;
  }

  std::string toScriptList(const std::unordered_set<std::string> &individual) {
    std::string list = "";
    std::unordered_map<std::string, std::string> idToMask;
    std::unordered_map<std::string, size_t> idToSize;
    for (auto &token : individual) {
      list += token + ";";
    }

    list.pop_back();

    return list;
  }

  void evalIndividual(
      Individual &individual,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime,
      size_t t_id = 0) {

    std::string si = serializeIndividual(individual);

    if (countGuard(_cachedIndividual, si, _cacheGuard)) {
      individual._objective = atGuard(_cachedIndividual, si, _cacheGuard);
      return;
    }

    if (!_simulate) {

      std::unordered_set<std::string> uniqueFeatures;
      for (const auto &gene : individual._genes) {
        for (const auto &feature : geneToAssTime.at(gene)) {
          uniqueFeatures.insert(feature);
        }
      }

      auto obj = std::make_pair<size_t, size_t>(individual._genes.size(),
                                                uniqueFeatures.size());

      obj.second =
          ((double)obj.second / (double)_maxObjs.second) * _valuePrecision;

      messageErrorIf(obj.first == 0, "?");
      std::string si = serializeIndividual(individual);
      _cacheGuard.lock();
      _cachedIndividual[si] = obj;
      _cacheGuard.unlock();

      individual._objective = obj;

    } else {

      systemCustom("bash " + clc::ve_shPath + " \"" +
                   toScriptList(individual._genes) + "\" " + clc::ve_ftPath +
                   " 1 " + std::to_string(t_id) +
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
      metricValue = clc::ve_metricDirection ? 1.f - metricValue : metricValue;

      //debug
      //std::cout << metricValue << "\n";

      auto obj = std::make_pair<size_t, size_t>(individual._genes.size(),
                                                metricValue * _valuePrecision);
      _cacheGuard.lock();
      _cachedIndividual[serializeIndividual(individual)] = obj;
      _cacheGuard.unlock();
      individual._objective = obj;
    }
  }

  void evalIndividuals(
      std::vector<Individual> &pop,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime) {

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
                   &completed, &pb]() {
        evalIndividual(pop[toBeServed], geneToAssTime, toBeServed);
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

  void trimPop(std::vector<Individual> &pop) {

    size_t lower =
        (size_t)((clc::ve_metricDirection ? (1.f - clc::ve_metricInterval.second)
                                          : clc::ve_metricInterval.first) *
                 (double)_valuePrecision);
    size_t upper =
        (size_t)((clc::ve_metricDirection ? (1.f - clc::ve_metricInterval.first)
                                          : clc::ve_metricInterval.second) *
                 (double)_valuePrecision);

    for (size_t i = 0; i < pop.size(); i++) {
      auto &ind = pop[i];
      if (ind._objective.second < lower || ind._objective.second > upper) {
        ind._genes.clear();
      }
    }

    pop.erase(std::remove_if(begin(pop), end(pop),
                             [](Individual &e) { return e._genes.empty(); }),
              pop.end());
  }

  void generateDominanceRank(
      std::vector<Individual> &pop,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
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

  std::vector<std::vector<Individual>> generateFronts(
      const std::vector<Individual> &pop,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
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
    fronts.erase(std::remove_if(fronts.begin(), fronts.end(),
                                [](const std::vector<Individual> &front) {
                                  return front.empty();
                                }),
                 fronts.end());

    return fronts;
  }
  std::vector<Individual> generateParetoFront(
      const std::vector<Individual> &pop,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
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

  bool getRandomBool() {
    std::time_t seed = std::time(nullptr) + getpid();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(generator);
  }

  template <typename T, typename U>
  std::pair<T, U> getRandomItem(const std::unordered_map<T, U> &map) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, map.size() - 1);
    int randomIndex = distribution(generator);

    auto it = map.begin();
    std::advance(it, randomIndex);
    return *it;
  }
  Individual getRandomIndividual(
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime,
      size_t numberOfGenes) {

    messageErrorIf(numberOfGenes == 0, "requested number of genes is 0");
    messageErrorIf(numberOfGenes > geneToAssTime.size(),
                   "requested number of genes is higher than max");

    std::vector<std::string> allGenes;
    for (auto &[id, genes] : geneToAssTime) {
      allGenes.push_back(id);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the tokens
    std::shuffle(allGenes.begin(), allGenes.end(), g);

    Individual individual;
    for (size_t i = 0; i < numberOfGenes; i++) {
      individual._genes.insert(allGenes[i]);
    }

    return individual;
  }

  std::vector<Individual> samplePopulation(
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime,
      size_t sizeOfIndividual, size_t sizeOfPop) {

    std::vector<Individual> population;

    for (size_t i = 0; i < sizeOfPop; i++) {
      Individual individual;
      for (size_t j = 0; j < sizeOfIndividual; j++) {
        individual._genes.insert(getRandomItem(geneToAssTime).first);
      }
      population.push_back(individual);
    }
    return population;
  }

  //remove twins
  void removeDuplicates(std::vector<Individual> &pop) {

    std::unordered_set<std::string> uniqueStrings;
    for (auto &individual : pop) {
      std::string key = "";
      for (auto &gene : individual._genes) {
        key += gene;
      }
      if (uniqueStrings.count(key)) {
        //mark as deleted
        individual._genes.clear();
      } else {
        uniqueStrings.insert(key);
      }
    }

    //erase marked
    pop.erase(
        std::remove_if(pop.begin(), pop.end(),
                       [](const Individual &e) { return e._genes.empty(); }),
        pop.end());
  }

  void crowdSort(
      std::vector<Individual> &pop,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime) {

    size_t min[2] = {(size_t)-1, (size_t)-1};
    size_t max[2] = {0, 0};
    size_t diff[2] = {0, 0};

    // Evaluate all pop in the population
    for (size_t i = 0; i < pop.size(); i++) {
      evalIndividual(pop[i], geneToAssTime);
      min[0] =
          pop[i]._objective.first < min[0] ? pop[i]._objective.first : min[0];
      max[0] =
          pop[i]._objective.first > max[0] ? pop[i]._objective.first : max[0];
      min[1] =
          pop[i]._objective.second < min[1] ? pop[i]._objective.second : min[1];
      max[1] =
          pop[i]._objective.second > max[1] ? pop[i]._objective.second : max[1];
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
                    return pop[i]._objective.first < pop[j]._objective.first;
                  } else {
                    return pop[i]._objective.second < pop[j]._objective.second;
                  }
                });

      // Set the crowding distance of the boundary solutions to infinity
      crowdingDist[sortedIndividuals[0]] =
          crowdingDist[sortedIndividuals[pop.size() - 1]] = INFINITY;

      // Calculate the crowding distance of all other solutions in the current rank
      for (size_t i = 1; i < pop.size() - 1; i++) {
        if (k == 0) {
          crowdingDist[sortedIndividuals[i]] +=
              diff[k] > 0 ? (pop[sortedIndividuals[i + 1]]._objective.first -
                             pop[sortedIndividuals[i - 1]]._objective.first) /
                                (float)(diff[k])
                          : 0.f;
        } else {
          crowdingDist[sortedIndividuals[i]] +=
              diff[k] > 0 ? (pop[sortedIndividuals[i + 1]]._objective.second -
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

  void selectElites(
      std::vector<std::vector<Individual>> &fronts,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime,
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
  tournamentSelection(const std::vector<Individual> &pop) {

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

  Individual crossover(std::pair<Individual, Individual> &parents) {

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
  void mutateIndividual(
      Individual &child,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime) {}

  void mutatePop(
      std::vector<Individual> &pop,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime) {
    std::vector<Individual> mutatedPop = pop;
    for (auto &ind : pop) {
      if (getRandomBool()) {
        //add a random individual of the same size
        mutatedPop.push_back(
            samplePopulation(geneToAssTime, ind._genes.size(), 1).front());
      } else {
        //create a new individual with a single random element
        auto tmpInd = ind;
        tmpInd._genes.insert(getRandomItem(geneToAssTime).first);
        mutatedPop.push_back(tmpInd);
      }
    }
    pop = mutatedPop;
  }

  void addOffspring(
      std::vector<Individual> &pop,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime) {

    std::vector<Individual> offSpring;

    //we do not want to break pop
    std::vector<Individual> pop_copy = pop;

    generateDominanceRank(pop_copy, geneToAssTime);

    //each iteration generates and adds one child
    for (size_t i = 0; i < pop_copy.size() && pop_copy.size() > 1; i++) {
      auto parents = tournamentSelection(pop_copy);
      auto child = crossover(parents);
      mutateIndividual(child, geneToAssTime);
      offSpring.push_back(child);
    }
    //add the offpring to the elite population
    pop.insert(std::end(pop), std::begin(offSpring), std::end(offSpring));
  }

  double
  getDominatedSurface(const std::vector<std::pair<size_t, size_t>> &points,
                      const std::pair<size_t, size_t> &gridSize) {
    // Initialize a 2D grid with all elements set to false
    size_t gridX = (gridSize.first + 1);
    size_t maxYSize = 1000;
    size_t divider =
        (gridSize.second > maxYSize) ? (gridSize.second / maxYSize) : 1;
    size_t gridY = (gridSize.second + 1) / divider;

    std::vector<std::vector<bool>> grid(gridX, std::vector<bool>(gridY, false));

    for (size_t i = 0; i < points.size(); i++) {
      size_t x = points[i].first;
      size_t y = points[i].second / divider;

      for (size_t j = 0; j <= x; j++) {
        for (size_t k = y; k < gridY; k++) {
          grid[j][k] = true;
        }
      }
    }

    // Count the number of dominated cells
    size_t count = 0;
    for (size_t i = 0; i < gridX; i++) {
      for (size_t j = 0; j < gridY; j++) {
        if (grid[i][j]) {
          count++;
        }
      }
    }

    // Ensure that the returned value is not greater than the maximum surface
    return (double)count / (gridX * gridY);
  }

  void
  plotDominance(const std::vector<std::pair<size_t, double>> &data,
                const std::string &xlabel = "X",
                const std::string &ylabel = "Y",
                const std::string &title = "Data Plot",
                std::optional<std::pair<size_t, size_t>> xrange = std::nullopt,
                std::optional<std::pair<double, double>> yrange = std::nullopt,
                bool dontClose = true,
                const std::optional<std::string> &dumpFilePath = std::nullopt,
                const std::optional<std::string> &pngFilePath = std::nullopt) {

    static FILE *pipe = nullptr;

    if (!dontClose || pipe == nullptr) {
      //systemCustom("killall gnuplot");
      pipe = popen("gnuplot -persistent", "r");
      pipe = popen("gnuplot -persistent", "w");
      if (!pipe) {
        std::cerr << "Error opening gnuplot pipe" << std::endl;
        return;
      }
    }

    // Set up gnuplot settings
    fprintf(pipe, "set title '%s'\n", title.c_str());
    fprintf(pipe, "set xlabel '%s'\n", xlabel.c_str());
    fprintf(pipe, "set ylabel '%s'\n", ylabel.c_str());
    fprintf(pipe, "set grid\n");

    // Set up x and y ranges, if given
    if (xrange.has_value()) {
      fprintf(pipe, "set xrange [%lu:%lu]\n", xrange.value().first,
              xrange.value().second);
    }
    if (yrange.has_value()) {
      fprintf(pipe, "set yrange [%f:%f]\n", yrange.value().first,
              yrange.value().second);
    }

    fprintf(pipe, "set key below\n");

    // Dump data as CSV file, if requested
    if (dumpFilePath.has_value()) {
      std::ofstream outfile(dumpFilePath.value());
      if (!outfile.is_open()) {
        std::cerr << "Error opening dump file " << dumpFilePath.value()
                  << std::endl;
      } else {
        outfile << "x;y" << std::endl;
        for (const auto &p : data) {
          outfile << p.first << ";" << p.second << std::endl;
        }
        outfile.close();
      }
    }

    // Plot data using points
    fprintf(pipe,
            "plot '-' with points pointtype 7 pointsize 0.5 linecolor rgb "
            "'black' title "
            "'Dominance'\n");
    for (const auto &p : data) {
      fprintf(pipe, "%lu %f\n", p.first, p.second);
    }
    fprintf(pipe, "e\n");

    // Dump current plot as PNG file, if requested
    if (pngFilePath.has_value()) {
      std::string filePath = pngFilePath.value();
      std::string command =
          "set terminal pngcairo size 1920,1080 enhanced font "
          "'Verdana,27' linewidth 10 pointscale 10;"
          "set output '" +
          filePath + "';replot; set output";
      fprintf(pipe, "%s\n", command.c_str());
    }

    if (dontClose) {
      fflush(pipe);
    } else {
      pclose(pipe);
    }
  }

  void plotErrorDamage(
      const std::vector<std::pair<size_t, double>> &data,
      const std::string &xlabel = "X", const std::string &ylabel = "Y",
      const std::string &title = "Data Plot",
      std::optional<std::pair<size_t, size_t>> xrange = std::nullopt,
      std::optional<std::pair<double, double>> yrange = std::nullopt,
      bool dontClose = true,
      const std::optional<std::string> &dumpFilePath = std::nullopt,
      const std::optional<std::string> &pngFilePath = std::nullopt) {

    static FILE *pipe = nullptr;

    if (pngFilePath.has_value() || dumpFilePath.has_value() ||
        dirtyTimerSeconds("plotRate", 0) > plotRate) {
      dirtyTimerSeconds("plotRate", 1);
    } else {
      return;
    }

    if (!dontClose || pipe == nullptr) {
      //    systemCustom("killall gnuplot");
      pipe = popen("gnuplot -persistent", "r");
      pipe = popen("gnuplot -persistent", "w");
      if (!pipe) {
        std::cerr << "Error opening gnuplot pipe" << std::endl;
        return;
      }
    }

    // Set up gnuplot settings
    fprintf(pipe, "set title '%s'\n", title.c_str());
    fprintf(pipe, "set xlabel '%s'\n", xlabel.c_str());
    fprintf(pipe, "set ylabel '%s'\n", ylabel.c_str());
    fprintf(pipe, "set grid\n");

    // Set up x and y ranges, if given
    if (xrange.has_value()) {
      fprintf(pipe, "set xrange [%lu:%lu]\n", xrange.value().first,
              xrange.value().second);
    }
    if (yrange.has_value()) {
      fprintf(pipe, "set yrange [%f:%f]\n", yrange.value().first,
              yrange.value().second);
    }

    fprintf(pipe, "unset key\n");

    // Dump data as CSV file, if requested
    if (dumpFilePath.has_value()) {
      std::ofstream outfile(dumpFilePath.value());
      if (!outfile.is_open()) {
        std::cerr << "Error opening dump file " << dumpFilePath.value()
                  << std::endl;
      } else {
        outfile << "x;y" << std::endl;
        for (const auto &p : data) {
          outfile << p.first << ";" << p.second << std::endl;
        }
        outfile.close();
      }
    }

    // Plot data using points
    fprintf(pipe,
            "plot '-' with points pointtype 7 pointsize 0.5 linecolor rgb "
            "'dark-violet' \n");
    for (const auto &p : data) {
      fprintf(pipe, "%lu %f\n", p.first, p.second);
    }
    fprintf(pipe, "e\n");

    // Dump current plot as PNG file, if requested
    if (pngFilePath.has_value()) {
      std::string filePath = pngFilePath.value();
      std::string command =
          "set terminal pngcairo size 1920,1080 enhanced font "
          "'Verdana,27' linewidth 10 pointscale 10;"
          "set output '" +
          filePath + "';replot; set output";
      fprintf(pipe, "%s\n", command.c_str());
    }

    if (dontClose) {
      fflush(pipe);
    } else {
      pclose(pipe);
    }
  }

  void plotBeforeAfter(
      std::vector<std::pair<size_t, double>> data1,
      std::vector<std::pair<size_t, double>> data2,
      const std::string &xlabel = "X", std::string ylabel = "Y",
      const std::string &title = "Data Plot",
      const std::string &series1Title = "S1",
      const std::string &series2Title = "S2",
      std::optional<std::pair<size_t, size_t>> xrange = std::nullopt,
      std::optional<std::pair<double, double>> yrange = std::nullopt,
      bool dontClose = true,
      const std::optional<std::string> &dumpFilePath = std::nullopt,
      const std::optional<std::string> &pngFilePath = std::nullopt) {

    static FILE *pipe = nullptr;

    if (!dontClose || pipe == nullptr) {
      //    systemCustom("killall gnuplot");
      pipe = popen("gnuplot -persistent", "r");
      pipe = popen("gnuplot -persistent", "w");
      if (!pipe) {
        std::cerr << "Error opening gnuplot pipe" << std::endl;
        return;
      }
    }

    if (clc::ve_metricDirection) {
      for (auto &[n, e] : data1) {
        e = 1.f - e;
      }
      for (auto &[n, e] : data2) {
        e = 1.f - e;
      }
    }

    // Set up gnuplot settings
    fprintf(pipe, "set title '%s'\n", title.c_str());
    fprintf(pipe, "set xlabel '%s'\n", xlabel.c_str());
    fprintf(pipe, "set ylabel '%s'\n", ylabel.c_str());
    fprintf(pipe, "set grid\n");

    // Set up x and y ranges, if given
    if (xrange.has_value()) {
      fprintf(pipe, "set xrange [%lu:%lu]\n", xrange.value().first,
              xrange.value().second);
    }
    if (yrange.has_value()) {
      fprintf(pipe, "set yrange [%f:%f]\n", yrange.value().first,
              yrange.value().second);
    }

    fprintf(pipe, "set key below\n");

    // Dump data as CSV file, if requested
    if (dumpFilePath.has_value()) {
      std::ofstream outfile(dumpFilePath.value());
      if (!outfile.is_open()) {
        std::cerr << "Error opening dump file " << dumpFilePath.value()
                  << std::endl;
      } else {
        outfile << "x;y1;y2" << std::endl;
        for (size_t i = 0; i < data1.size(); i++) {
          outfile << data1[i].first << ";" << data1[i].second << ";"
                  << data2[i].second << std::endl;
        }
        outfile.close();
      }
    }

    // Plot data using points with colors
    fprintf(
        pipe,
        "plot '-' with points pointtype 7 pointsize 0.5 linecolor rgb 'blue' title '%s', \
                  '-' with points pointtype 7 pointsize 0.5 linecolor rgb 'dark-violet' title '%s'\n",
        series2Title.c_str(), series1Title.c_str());

    for (const auto &p : data2) {
      fprintf(pipe, "%lu %f\n", p.first, p.second);
    }
    fprintf(pipe, "e\n");
    for (const auto &p : data1) {
      fprintf(pipe, "%lu %f\n", p.first, p.second);
    }
    fprintf(pipe, "e\n");

    // Place the legend below the chart
    fprintf(pipe, "set key below\n");

    // Dump current plot as PNG file, if requested
    if (pngFilePath.has_value()) {
      std::string filePath = pngFilePath.value();
      std::string command =
          "set terminal pngcairo size 1920,1080 enhanced font "
          "'Verdana,27' linewidth 10 pointscale 10;"
          "set output '" +
          filePath + "';replot; set output";
      fprintf(pipe, "%s\n", command.c_str());
    }

    if (dontClose) {
      fflush(pipe);
    } else {
      pclose(pipe);
    }
  }

  void plotBeforeAfterRandom(
      std::vector<std::pair<size_t, double>> data1,
      std::vector<std::pair<size_t, double>> data2,
      std::vector<std::pair<size_t, double>> data3,
      const std::string &xlabel = "X", std::string ylabel = "Y",
      const std::string &title = "Data Plot",
      const std::string &series1Title = "S1",
      const std::string &series2Title = "S2",
      const std::string &series3Title = "S3",
      std::optional<std::pair<size_t, size_t>> xrange = std::nullopt,
      std::optional<std::pair<double, double>> yrange = std::nullopt,
      bool dontClose = true,
      const std::optional<std::string> &dumpFilePath = std::nullopt,
      const std::optional<std::string> &pngFilePath = std::nullopt) {

    static FILE *pipe = nullptr;

    if (!dontClose || pipe == nullptr) {
      //    systemCustom("killall gnuplot");
      pipe = popen("gnuplot -persistent", "r");
      pipe = popen("gnuplot -persistent", "w");
      if (!pipe) {
        std::cerr << "Error opening gnuplot pipe" << std::endl;
        return;
      }
    }

    if (clc::ve_metricDirection) {
      for (auto &[n, e] : data1) {
        e = 1.f - e;
      }
      for (auto &[n, e] : data2) {
        e = 1.f - e;
      }
      for (auto &[n, e] : data3) {
        e = 1.f - e;
      }
    }

    // Set up gnuplot settings
    fprintf(pipe, "set title '%s'\n", title.c_str());
    fprintf(pipe, "set xlabel '%s'\n", xlabel.c_str());
    fprintf(pipe, "set ylabel '%s'\n", ylabel.c_str());
    fprintf(pipe, "set grid\n");

    // Set up x and y ranges, if given
    if (xrange.has_value()) {
      fprintf(pipe, "set xrange [%lu:%lu]\n", xrange.value().first,
              xrange.value().second);
    }
    if (yrange.has_value()) {
      fprintf(pipe, "set yrange [%f:%f]\n", yrange.value().first,
              yrange.value().second);
    }

    fprintf(pipe, "set key above\n");

    // Dump data as CSV file, if requested
    if (dumpFilePath.has_value()) {
      std::ofstream outfile(dumpFilePath.value());
      if (!outfile.is_open()) {
        std::cerr << "Error opening dump file " << dumpFilePath.value()
                  << std::endl;
      } else {
        size_t longestSeriesSize =
            std::max(data1.size(), std::max(data2.size(), data3.size()));
        outfile << "x1;y1;x2;y2;x3;y3" << std::endl;
        for (size_t i = 0; i < longestSeriesSize; i++) {
          if (i < data1.size()) {
            outfile << data1[i].first << ";" << data1[i].second << ";";
          } else {
            outfile << ";;";
          }
          if (i < data2.size()) {
            outfile << data2[i].first << ";" << data2[i].second << ";";
          } else {
            outfile << ";;";
          }
          if (i < data3.size()) {
            outfile << data3[i].first << ";" << data3[i].second;
          } else {
            outfile << ";";
          }
          outfile << "\n";
        }
      }
      outfile.close();
    }

    // Plot data using points with colors
    fprintf(
        pipe,
        "plot '-' with points pointtype 7 pointsize 0.5 linecolor rgb 'blue' title '%s', \
                  '-' with points pointtype 7 pointsize 0.5 linecolor rgb 'dark-violet' title '%s', \
                  '-' with points pointtype 7 pointsize 0.5 linecolor rgb 'red' title '%s'\n",
        series2Title.c_str(), series1Title.c_str(), series3Title.c_str());

    for (const auto &p : data2) {
      fprintf(pipe, "%lu %f\n", p.first, p.second);
    }
    fprintf(pipe, "e\n");

    for (const auto &p : data1) {
      fprintf(pipe, "%lu %f\n", p.first, p.second);
    }
    fprintf(pipe, "e\n");

    for (const auto &p : data3) {
      fprintf(pipe, "%lu %f\n", p.first, p.second);
    }
    fprintf(pipe, "e\n");

    // Place the legend below the chart
    fprintf(pipe, "set key below\n");

    // Dump current plot as PNG file, if requested
    if (pngFilePath.has_value()) {
      std::string filePath = pngFilePath.value();
      std::string command =
          "set terminal pngcairo size 1920,1080 enhanced font "
          "'Verdana,27' linewidth 10 pointscale 10;"
          "set output '" +
          filePath + "';replot; set output";
      fprintf(pipe, "%s\n", command.c_str());
    }

    if (dontClose) {
      fflush(pipe);
    } else {
      pclose(pipe);
    }
  }

  std::pair<size_t, size_t> getMaxObjectivesValues(
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime) {

    std::unordered_set<std::string> uniqueInstances;
    for (auto &[id, instances] : geneToAssTime) {
      for (auto &i : instances) {
        uniqueInstances.insert(i);
      }
    }
    return std::make_pair(geneToAssTime.size(), uniqueInstances.size());
  }

  void genAndDumpRandomClusters(
      std::vector<Individual> paretoFront,
      const std::unordered_map<std::string, std::unordered_set<std::string>>
          &geneToAssTime,
      std::vector<std::pair<size_t, double>> &beforePushMetricFrontData,
      size_t reps = 10) {

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
        randomIndividuals.push_back(
            getRandomIndividual(geneToAssTime, individual._genes.size()));
      }

      double avgRandom = 0.f;

      std::vector<std::pair<double, Individual>> candidatesRand;

      std::cout << geObIndex++ << "/" << paretoFront.size() << "\n";

      //eval random pop
      evalIndividuals(randomIndividuals, geneToAssTime);

      for (auto &ind : randomIndividuals) {
        double rnd = (((double)ind._objective.second / _valuePrecision));
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
        std::make_pair(0.f, _maxObjs.first), std::make_pair(0.f, 1.f), 1,
        clc::ve_dumpTo + "/" + clc::ve_technique + "_" + "bar.csv",
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
  bool _pushing = 0;
  std::unordered_map<std::string, std::pair<size_t, size_t>> _cachedIndividual;
  std::mutex _cacheGuard;
  bool _simulate = false;
  std::pair<size_t, size_t> _maxObjs;
  size_t _valuePrecision = 10000;
  size_t plotRate = 1;
};
