#pragma once
#include "message.hh"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
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

inline std::vector<int> generateDominanceRank(
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

template <typename T> void removeRandomElement(std::unordered_set<T> &set) {
  std::random_device rd;
  std::mt19937 gen(rd());

  // Get a random element from the set
  std::uniform_int_distribution<> dis(0, set.size() - 1);
  auto it = std::next(set.begin(), dis(gen));

  // Remove the random element from the set
  set.erase(it);
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

inline void
removeDuplicates(std::vector<std::unordered_set<std::string>> &vec) {
  std::unordered_set<std::string> uniqueStrings;
  for (auto &set : vec) {
    std::string key = "";
    for (auto &i : set) {
      key += i;
    }
    if (uniqueStrings.count(key)) {
      set.clear();
    } else {
      uniqueStrings.insert(key);
    }
  }
  vec.erase(std::remove_if(
                vec.begin(), vec.end(),
                [](std::unordered_set<std::string> &e) { return e.empty(); }),
            vec.end());
}

void inline crowdSort(
    std::vector<std::unordered_set<std::string>> &pop,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  // Evaluate all individuals in the population
  std::vector<std::pair<size_t, size_t>> objValues(pop.size());
  size_t min[2] = {(size_t)-1, (size_t)-1};
  size_t max[2] = {0, 0};
  size_t diff[2] = {0, 0};

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
void inline fillNewPopulation(
    std::vector<std::vector<std::unordered_set<std::string>>> &fronts,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes,
    std::vector<std::unordered_set<std::string>> &population,
    size_t originalPopSize) {

  population.clear();
  std::set<std::pair<size_t, size_t>> alreadyInUse;
  for (auto &front : fronts) {
    if (front.size() + population.size() <= originalPopSize) {
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
tournamentSelection(
    const std::vector<std::unordered_set<std::string>> &population,
    const std::vector<int> &rank) {

  std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>
      parents;

  //select first parent
  std::random_device rd1;
  std::mt19937 rng1(rd1());
  std::uniform_int_distribution<int> dist(0, population.size() - 1);

  int a1 = 0;
  int b1 = 0;

  while (a1 == b1) {
    a1 = dist(rng1);
    b1 = dist(rng1);
  }

  parents.first = rank[a1] > rank[b1] ? population[b1] : population[a1];

  //select second parent
  std::random_device rd2;
  std::mt19937 rng2(rd2());

  int a2 = 0;
  int b2 = 0;

  while (a2 == b2) {
    a2 = dist(rng2);
    b2 = dist(rng2);
  }
  parents.second = rank[a2] > rank[b2] ? population[b2] : population[a2];

  return parents;
}

inline std::unordered_set<std::string> crossover(
    std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>
        &parents) {
  std::unordered_set<std::string> kidGenes;

  for (auto &gene : parents.first) {
    kidGenes.insert(gene);
  }
  for (auto &gene : parents.second) {
    kidGenes.insert(gene);
  }

  return kidGenes;
}

inline void
mutate(std::unordered_set<std::string> &child,
       const std::unordered_map<std::string, std::unordered_set<std::string>>
           &allGenes) {}

inline std::vector<std::unordered_set<std::string>> produceOffspring(
    const std::vector<std::unordered_set<std::string>> &pop,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  std::vector<std::unordered_set<std::string>> newPop;

  auto rank = generateDominanceRank(pop, allGenes);
  for (size_t i = 0; i < pop.size(); i++) {
    auto parents = tournamentSelection(pop, rank);
    auto child = crossover(parents);
    mutate(child, allGenes);
    newPop.push_back(child);
  }
  newPop.insert(std::end(newPop), std::begin(pop), std::end(pop));
  return newPop;
}

inline std::vector<std::tuple<size_t, size_t, std::unordered_set<std::string>>>
nsga2(const std::unordered_map<std::string, std::unordered_set<std::string>>
          &allGenes,
      size_t iterations = 20,
      const std::vector<std::unordered_set<std::string>> &initialPop =
          std::vector<std::unordered_set<std::string>>()) {

  std::vector<std::unordered_set<std::string>> pop;

  if (initialPop.empty()) {
    pop = samplePopulation(allGenes, 20, 20);
  } else {
    pop = initialPop;
  }

  size_t originalPopSize = pop.size();
  //  debug
  std::cout << "Initial pop:"
            << "\n";
  for (auto &individual : pop) {
    auto score = evalIndividual(individual, allGenes);
    std::cout << "" << score.first << ";" << score.second << ""
              << "\n";
  }

  for (size_t i = 0; i < iterations; i++) {
    auto start = std::chrono::steady_clock::now();
    std::cout << "Iteration: " << i << "\n";

    size_t avgSize = 0;
    for (auto &i : pop) {
      avgSize += i.size();
    }
    avgSize = avgSize / pop.size();

    auto randPop = samplePopulation(allGenes, avgSize + 1, pop.size());
    for (auto &ind : randPop) {
      pop.push_back(ind);
    }

    pop = produceOffspring(pop, allGenes);

    removeDuplicates(pop);

    auto fronts = generateFronts(pop, allGenes);
    fillNewPopulation(fronts, allGenes, pop, originalPopSize);

    auto stop = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    for (auto &individual : pop) {
      auto score = evalIndividual(individual, allGenes);
      std::cout << "" << score.first << ";" << score.second << ""
                << "\n";
    }
    std::cout << "-----------------------> " << duration.count() << "s\n";
    std::cout << "Pop size:" << pop.size() << "\n";
  }

  std::vector<std::pair<size_t, size_t>> objectives(pop.size());
  for (int i = 0; i < pop.size(); i++) {
    objectives[i] = evalIndividual(pop[i], allGenes);
  }

  auto ranks = generateDominanceRank(pop, objectives);
  std::vector<std::tuple<size_t, size_t, std::unordered_set<std::string>>> ret;
  for (size_t i = 0; i < pop.size(); i++) {
    if (ranks[i] == 0) {
      auto score = objectives[i];

      ret.emplace_back(score.first, score.second, pop[i]);
    }
  }
  return ret;
}
