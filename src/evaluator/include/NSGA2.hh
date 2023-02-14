#pragma once
#include "message.hh"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
      if (a.first < b.first && a.second > b.second) {
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
      if (a.first < b.first && a.second > b.second) {
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

void inline fillNewPopulation(
    const std::vector<std::vector<std::unordered_set<std::string>>> &fronts,
    std::vector<std::unordered_set<std::string>> &population) {

  int popSize = population.size() / 2;
  population.clear();

  for (const auto &front : fronts) {
    for (const auto &individual : front) {
      population.push_back(individual);
      if (population.size() == popSize) {
        return;
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
  std::random_device rd;
  std::mt19937 rng1(rd());
  std::uniform_int_distribution<int> dist(0, population.size() - 1);

  int a1 = dist(rng1);
  int b1 = dist(rng1);
  auto individualA1 = population[a1];
  auto individualB1 = population[b1];
  auto scoreA1 = rank[a1];
  auto scoreB1 = rank[b1];
  parents.first = scoreA1 > scoreB1 ? individualB1 : individualA1;
  //  std::cout << a1 << "," << b1 << "\n";

  std::mt19937 rng2(rd());
  int a2 = dist(rng2);
  int b2 = dist(rng2);
  auto individualA2 = population[a2];
  auto individualB2 = population[b2];
  auto scoreA2 = rank[a2];
  auto scoreB2 = rank[b2];
  parents.second = scoreA2 > scoreB2 ? individualB2 : individualA2;
  // std::cout << a2 << "," << b2 << "\n";

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

  for (size_t i = 0; i < pop.size(); i++) {
    auto rank = generateDominanceRank(pop, allGenes);
    auto parents = tournamentSelection(pop, rank);
    auto child = crossover(parents);
    mutate(child, allGenes);
    newPop.push_back(child);
  }
  newPop.insert(std::end(newPop), std::begin(pop), std::end(pop));
  return newPop;
}

inline void
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

  std::vector<std::unordered_set<std::string>> allConf = pop;

  //  debug
  //  std::cout << "Initial pop:"
  //            << "\n";
  //  for (auto &individual : pop) {
  //    auto score = evalIndividual(individual, allGenes);
  //    std::cout << "" << score.first << "," << score.second << ""
  //              << "\n";
  //  }

  for (size_t i = 0; i < iterations; i++) {
    std::cout << "Iteration: " << i << "\n";

    std::cout << "Prod off"
              << "\n";
    pop = produceOffspring(pop, allGenes);
    std::cout << "fronts..."
              << "\n";
    auto fronts = generateFronts(pop, allGenes);
    fillNewPopulation(fronts, pop);
    std::cout << "fill new pop..."
              << "\n";
    std::cout << "Pop size:" << pop.size() << "\n";

    for (auto &individual : pop) {
      auto score = evalIndividual(individual, allGenes);
      //    std::cout << "" << score.first << "," << score.second << ""
      //              << "\n";
      allConf.push_back(individual);
    }
  }

  auto ranks = generateDominanceRank(allConf, allGenes);

  for (size_t i = 0; i < allConf.size(); i++) {
    if (ranks[i] == 0) {
      auto &individual = allConf[i];
      auto score = evalIndividual(individual, allGenes);
      std::cout << "" << score.first << ";" << score.second << ""
                << "\n";
    }
  }
}
