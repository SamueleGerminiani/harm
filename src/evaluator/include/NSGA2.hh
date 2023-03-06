#pragma once
#include "message.hh"
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <iostream>
#include <optional>
#include <random>
#include <ratio>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

inline std::pair<size_t, size_t> evalIndividual(
    const std::unordered_set<std::string> &individual,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  std::unordered_set<std::string> uniqueFeatures;

  for (const auto &gene : individual) {
    for (auto &feature : allGenes.at(gene)) {
      uniqueFeatures.insert(feature);
    }
  }

  return std::make_pair<size_t, size_t>(individual.size(),
                                        uniqueFeatures.size());
}

inline std::vector<size_t> generateDominanceRank(
    const std::vector<std::unordered_set<std::string>> &individuals,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  int n = individuals.size();

  // Store the objective values for each individual
  std::vector<std::pair<size_t, size_t>> objectives(n);
  for (int i = 0; i < n; i++) {
    objectives[i] = evalIndividual(individuals[i], allGenes);
  }

  // Store the dominance rank for each individual
  std::vector<size_t> rank(n, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j)
        continue;
      auto &a = objectives[i];
      auto &b = objectives[j];
      if ((a.first <= b.first && a.second >= b.second) &&
          (a.first < b.first || a.second > b.second)) {
        rank[i]++;
      }
    }
  }

  return rank;
}
inline std::vector<int> generateDominanceRank(
    const std::vector<std::unordered_set<std::string>> &individuals,
    std::vector<std::pair<size_t, size_t>> &objectives) {

  int n = individuals.size();
  messageErrorIf(objectives.size() != n,
                 "Objectives size (" + std::to_string(objectives.size()) +
                     ") != individuals size (" + std::to_string(n) + ")");

  // Store the dominance rank for each individual
  std::vector<int> rank(n, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j)
        continue;
      auto &a = objectives[i];
      auto &b = objectives[j];
      if ((a.first <= b.first && a.second >= b.second) &&
          (a.first < b.first || a.second > b.second)) {
        rank[i]++;
        //std::cout << a.first << "," << a.second << " dominated by " << b.first << "," << b.second << "\n";
      }
    }
  }

  return rank;
}

inline std::vector<std::vector<std::unordered_set<std::string>>> generateFronts(
    const std::vector<std::unordered_set<std::string>> &individuals,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  int n = individuals.size();

  auto rank = generateDominanceRank(individuals, allGenes);

  // Store the list of individuals in each front
  std::vector<std::vector<std::unordered_set<std::string>>> fronts(n);
  for (int i = 0; i < n; i++) {
    fronts[rank[i]].push_back(individuals[i]);
  }

  // Remove empty fronts
  fronts.erase(
      std::remove_if(
          fronts.begin(), fronts.end(),
          [](const std::vector<std::unordered_set<std::string>> &front) {
            return front.empty();
          }),
      fronts.end());

  return fronts;
}
inline std::vector<std::unordered_set<std::string>> generateParetoFront(
    const std::vector<std::unordered_set<std::string>> &individuals,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  int n = individuals.size();
  auto rank = generateDominanceRank(individuals, allGenes);
  std::vector<std::unordered_set<std::string>> topFront;

  for (int i = 0; i < n; i++) {
    if (rank[i] == 0) {
      topFront.push_back(individuals[i]);
    }
  }

  return topFront;
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

inline std::vector<std::unordered_set<std::string>> samplePopulation(
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes,
    size_t sizeOfIndividual, size_t sizeOfPop) {
  std::vector<std::unordered_set<std::string>> population;

  for (size_t i = 0; i < sizeOfPop; i++) {
    std::unordered_set<std::string> individual;
    for (size_t j = 0; j < sizeOfIndividual; j++) {
      individual.insert(getRandomItem(allGenes).first);
    }
    population.push_back(individual);
  }
  return population;
}

//remove twins
inline void
removeDuplicates(std::vector<std::unordered_set<std::string>> &pop) {

  std::unordered_set<std::string> uniqueStrings;
  for (auto &individual : pop) {
    std::string key = "";
    for (auto &gene : individual) {
      key += gene;
    }
    if (uniqueStrings.count(key)) {
      //mark as deleted
      individual.clear();
    } else {
      uniqueStrings.insert(key);
    }
  }

  //erase marked
  pop.erase(std::remove_if(pop.begin(), pop.end(),
                           [](const std::unordered_set<std::string> &e) {
                             return e.empty();
                           }),
            pop.end());
}

void inline crowdSort(
    std::vector<std::unordered_set<std::string>> &pop,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  std::vector<std::pair<size_t, size_t>> objValues(pop.size());
  size_t min[2] = {(size_t)-1, (size_t)-1};
  size_t max[2] = {0, 0};
  size_t diff[2] = {0, 0};

  // Evaluate all individuals in the population
  for (size_t i = 0; i < pop.size(); i++) {
    objValues[i] = evalIndividual(pop[i], allGenes);
    min[0] = objValues[i].first < min[0] ? objValues[i].first : min[0];
    max[0] = objValues[i].first > max[0] ? objValues[i].first : max[0];
    min[1] = objValues[i].second < min[1] ? objValues[i].second : min[1];
    max[1] = objValues[i].second > max[1] ? objValues[i].second : max[1];
  }
  diff[0] = max[0] - min[0];
  diff[1] = max[1] - min[1];

  // Initialize the crowding distance of all individuals to zero
  std::vector<double> crowdingDist(pop.size(), 0.0);

  // Sort the individuals in each rank based on objective function values
  for (size_t k = 0; k < 2; k++) {
    //init
    std::vector<size_t> sortedIndividuals(pop.size());
    std::iota(sortedIndividuals.begin(), sortedIndividuals.end(), 0);

    std::sort(sortedIndividuals.begin(), sortedIndividuals.end(),
              [&k, &objValues](const size_t &i, const size_t &j) {
                if (k == 0) {
                  return objValues[i].first < objValues[j].first;
                } else {
                  return objValues[i].second < objValues[j].second;
                }
              });

    // Set the crowding distance of the boundary solutions to infinity
    crowdingDist[sortedIndividuals[0]] =
        crowdingDist[sortedIndividuals[pop.size() - 1]] = INFINITY;

    // Calculate the crowding distance of all other solutions in the current rank
    for (size_t i = 1; i < pop.size() - 1; i++) {
      if (k == 0) {
        crowdingDist[sortedIndividuals[i]] +=
            diff[k] > 0 ? (objValues[sortedIndividuals[i + 1]].first -
                           objValues[sortedIndividuals[i - 1]].first) /
                              (float)(diff[k])
                        : 0.f;
      } else {
        crowdingDist[sortedIndividuals[i]] +=
            diff[k] > 0 ? (objValues[sortedIndividuals[i + 1]].second -
                           objValues[sortedIndividuals[i - 1]].second) /
                              (float)(diff[k])
                        : 0.f;
      }
    }
  }

  //need to associate the individual with a score for sorting
  std::vector<std::pair<std::unordered_set<std::string>, double>> popWithCD;
  for (size_t i = 0; i < pop.size(); i++) {
    popWithCD.emplace_back(pop[i], crowdingDist[i]);
  }
  std::sort(popWithCD.begin(), popWithCD.end(),
            [](std::pair<std::unordered_set<std::string>, double> &e1,
               std::pair<std::unordered_set<std::string>, double> &e2) {
              return e1.second > e2.second;
            });

  pop.clear();

  for (auto &e : popWithCD) {
    pop.push_back(e.first);
  }
}

void inline selectElites(
    std::vector<std::vector<std::unordered_set<std::string>>> &fronts,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes,
    std::vector<std::unordered_set<std::string>> &population,
    size_t originalPopSize) {

  population.clear();

  //used to avoid repetitions of individuals with the same score
  std::set<std::pair<size_t, size_t>> alreadyInUse;

  for (auto &front : fronts) {
    if (front.size() + population.size() <= originalPopSize) {
      //front fits entirely
      for (const auto &individual : front) {
        auto score = evalIndividual(individual, allGenes);
        if (!alreadyInUse.count(score)) {
          alreadyInUse.insert(score);
          population.push_back(individual);
        }
      }
    } else if (population.size() < originalPopSize) {
      //front does not fit, need crowd sorting
      crowdSort(front, allGenes);
      for (const auto &individual : front) {
        auto score = evalIndividual(individual, allGenes);
        if (!alreadyInUse.count(score)) {
          alreadyInUse.insert(score);
          population.push_back(individual);
        }
        if (population.size() == originalPopSize) {
          return;
        }
      }
    }
  }
}

inline std::pair<std::unordered_set<std::string>,
                 std::unordered_set<std::string>>
tournamentSelection(const std::vector<std::unordered_set<std::string>> &pop,
                    const std::vector<size_t> &rank) {

  std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>
      parents;

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

  parents.first = rank[a1] > rank[b1] ? pop[b1] : pop[a1];

  //select second parent
  std::random_device rd2;
  std::mt19937 rng2(rd2());

  int a2 = 0;
  int b2 = 0;

  while (a2 == b2) {
    a2 = dist(rng2);
    b2 = dist(rng2);
  }
  parents.second = rank[a2] > rank[b2] ? pop[b2] : pop[a2];

  return parents;
}

inline std::unordered_set<std::string> crossover(
    std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>
        &parents) {

  std::unordered_set<std::string> kidGenes;

  //merge the genes

  for (auto &gene : parents.first) {
    kidGenes.insert(gene);
  }
  for (auto &gene : parents.second) {
    kidGenes.insert(gene);
  }

  return kidGenes;
}

inline void mutateIndividual(
    std::unordered_set<std::string> &child,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {}

inline void
mutatePop(std::vector<std::unordered_set<std::string>> &pop,
          const std::unordered_map<std::string, std::unordered_set<std::string>>
              &allGenes) {
  for (auto &ind : pop) {
    //add a random individual of the same size
    pop.push_back(samplePopulation(allGenes, ind.size(), 1).front());
  }
}

inline void addOffspring(
    std::vector<std::unordered_set<std::string>> &pop,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  std::vector<std::unordered_set<std::string>> offSpring;

  auto rank = generateDominanceRank(pop, allGenes);
  //each iteration generates and adds one child
  for (size_t i = 0; i < pop.size(); i++) {
    auto parents = tournamentSelection(pop, rank);
    auto child = crossover(parents);
    mutateIndividual(child, allGenes);
    offSpring.push_back(child);
  }
  //add the offpring to the elite population
  pop.insert(std::end(pop), std::begin(offSpring), std::end(offSpring));
}

size_t inline getDominatedSurface(
    const std::vector<std::pair<size_t, size_t>> &points,
    const std::pair<size_t, size_t> &gridSize) {
  // Initialize a 2D grid with all elements set to false
  std::vector<std::vector<bool>> grid(
      gridSize.first, std::vector<bool>(gridSize.second, false));

  // Mark all the dominated cells as true
  for (size_t i = 0; i < points.size(); i++) {
    size_t x = points[i].first;
    size_t y = points[i].second;

    for (size_t j = 0; j <= x; j++) {
      for (size_t k = y; k < gridSize.second; k++) {
        grid[j][k] = true;
      }
    }
  }

  // Count the number of dominated cells
  size_t count = 0;
  for (size_t i = 0; i < gridSize.first; i++) {
    for (size_t j = 0; j < gridSize.second; j++) {
      if (grid[i][j]) {
        count++;
      }
    }
  }

  // Ensure that the returned value is not greater than the maximum surface
  return std::min(count, gridSize.first * gridSize.second);
}

void inline plotGNU(
    const std::vector<std::pair<size_t, size_t>> &data,
    const std::string &xlabel = "X", const std::string &ylabel = "Y",
    const std::string &title = "Data Plot",
    std::optional<std::pair<size_t, size_t>> xrange = std::nullopt,
    std::optional<std::pair<size_t, size_t>> yrange = std::nullopt,
    bool dontClose = true) {

  static FILE *pipe = nullptr;

  if (!dontClose || pipe == nullptr) {
    system("killall gnuplot");
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
    fprintf(pipe, "set yrange [%lu:%lu]\n", yrange.value().first,
            yrange.value().second);
  }

  fprintf(pipe, "set key below\n");

  // Plot data using points
  fprintf(
      pipe,
      "plot '-' with points pointtype 7 pointsize 0.5 title 'Configuration'\n");
  for (const auto &p : data) {
    fprintf(pipe, "%lu %lu\n", p.first, p.second);
  }
  fprintf(pipe, "e\n");

  // Place the legend below the chart

  if (dontClose) {
    fflush(pipe);
  } else {
    pclose(pipe);
  }
}
inline std::pair<size_t, size_t> getMaxObjectivesValues(
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  std::unordered_set<std::string> uniqueInstances;
  for (auto &[id, instances] : allGenes) {
    for (auto &i : instances) {
      uniqueInstances.insert(i);
    }
  }
  return std::make_pair(allGenes.size(), uniqueInstances.size());
}
inline std::vector<std::tuple<size_t, size_t, std::unordered_set<std::string>>>
nsga2(const std::unordered_map<std::string, std::unordered_set<std::string>>
          &allGenes,
      size_t maxIterations = 20, double minIncrement = 1.f,
      const std::vector<std::unordered_set<std::string>> &initialPop =
          std::vector<std::unordered_set<std::string>>()) {

  auto maxObjs = getMaxObjectivesValues(allGenes);

  //debug
  //std::cout << "Grid size:" << maxObjs.first << "," << maxObjs.second << "\n";

  std::vector<std::unordered_set<std::string>> pop;

  if (initialPop.empty()) {
    pop = samplePopulation(allGenes, 1, allGenes.size());
  } else {
    pop = initialPop;
  }

  size_t originalPopSize = pop.size()>200?200:pop.size();
  std::cout << "Pop size:" << originalPopSize << "\n";

  //  debug
  //  std::cout << "Initial pop:"
  //            << "\n";
  //  for (auto &individual : pop) {
  //    auto score = evalIndividual(individual, allGenes);
  //    std::cout << "" << score.first << ";" << score.second << ""
  //              << "\n";
  //  }

  //used for the halting criteria
  double prevDominance = 0;
  double dominance = DBL_MAX;

  for (size_t i = 0; i < maxIterations; i++) {
    //keep track how long each iteratin takes
    auto start = std::chrono::steady_clock::now();

    //mutation on the entire population
    mutatePop(pop, allGenes);

    addOffspring(pop, allGenes);

    removeDuplicates(pop);

    auto fronts = generateFronts(pop, allGenes);

    selectElites(fronts, allGenes, pop, originalPopSize);

    auto stop = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::vector<std::pair<size_t, size_t>> front_plot_data;
    for (auto &individual : generateParetoFront(pop, allGenes)) {
      auto score = evalIndividual(individual, allGenes);
      front_plot_data.push_back(score);
    }

    dominance = getDominatedSurface(front_plot_data, maxObjs) /
                ((double)maxObjs.first * maxObjs.second);

    //plot the pareto frontier - debug
    plotGNU(front_plot_data, "Ntokens", "Damage",
            "Surface dominance: " + std::to_string(dominance * 100) + "%",
            std::make_pair(0, maxObjs.first),
            std::make_pair(0, maxObjs.second),1);

    std::cout << "Iteration: " << i << "th\n";
    std::cout << "Duration: " << duration.count() << "s\n";
    std::cout << "PrevDominance:" << prevDominance << "\n";
    std::cout << "Dominance:" << dominance << "\n";
    double increment = ((dominance - prevDominance) / dominance) * 100.f;
    std::cout << "Dominance increment :" << increment << "%\n";

    //terminal condition
    if (increment <= minIncrement) {
      break;
    }

    prevDominance = dominance;
  }

  std::vector<std::pair<size_t, size_t>> objectives(pop.size());
  for (int i = 0; i < pop.size(); i++) {
    objectives[i] = evalIndividual(pop[i], allGenes);
  }

  //<x,y,individual>
  std::vector<std::tuple<size_t, size_t, std::unordered_set<std::string>>> ret;
  for (auto &individual : generateParetoFront(pop, allGenes)) {
    auto score = evalIndividual(individual, allGenes);
    ret.emplace_back(score.first, score.second, individual);
  }

  return ret;
}
