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

inline std::string
serializeIndividual(const std::unordered_set<std::string> &individual) {
  std::set<std::string> sorted_individual(individual.begin(), individual.end());
  std::stringstream ss;
  for (const auto &token : sorted_individual) {
    ss << token << ",";
  }
  return ss.str();
}
inline std::string toDefineBR(const std::unordered_set<std::string> &individual,
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
inline std::string
toDefineSR(const std::unordered_set<std::string> &individual) {
  std::string define = "";
  std::unordered_map<std::string, std::string> idToMask;
  std::unordered_map<std::string, size_t> idToSize;
  for (auto &token : individual) {
    define += " +define+" + token;
  }

  return define;
}

inline std::pair<size_t, size_t> evalIndividual(
    const std::unordered_set<std::string> &individual,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes,
    size_t t_id = 0, bool switchEval = false) {

  static std::unordered_map<std::string, std::pair<size_t, size_t>>
      cachedIndividual;
  static std::mutex cacheGuard;
  static bool simulate = false;

  if (switchEval) {
    std::unique_lock<std::mutex> lock{cacheGuard};
    simulate = !simulate;
    cachedIndividual.clear();
    return std::pair<size_t, size_t>();
  }

  std::string si = serializeIndividual(individual);

  if (countGuard(cachedIndividual, si, cacheGuard)) {
    return atGuard(cachedIndividual, si, cacheGuard);
  }

  if (!simulate) {

    std::unordered_set<std::string> uniqueFeatures;
    for (const auto &gene : individual) {
      for (const auto &feature : allGenes.at(gene)) {
        uniqueFeatures.insert(feature);
      }
    }

    auto ret = std::make_pair<size_t, size_t>(individual.size(),
                                              uniqueFeatures.size());

    messageErrorIf(ret.first == 0, "?");
    std::string si = serializeIndividual(individual);
    cacheGuard.lock();
    cachedIndividual[si] = ret;
    cacheGuard.unlock();

    return ret;

  } else {

    bool printOut = 0;

    if (clc::ve_pushp_design == "sobelBR") {

      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineBR(individual);
      systemCustom(
          ("$MODELSIM_BIN/vlog -work " + work + " " + define +
           " +define+OUT_PATH=\"" + work +
           "/\""
           " +define+IN_PATH=\"" +
           "../simulator/IO/in/" +
           "\" -sv ../simulator/rtl/br_cluster/* ../simulator/rtl/tb/*" +
           (printOut ? "" : "> /dev/null"))
              .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".sobel_tb -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("python3 ../simulator/scripts/sobel_IO_to_jpeg.py " + work +
                    "/512x512sobel_out_nbits.txt  " + work + "/img.jpeg" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("python3 -W ignore ../simulator/scripts/calc_SSIM_WP.py "
                    "../simulator/imgs/BR_cluster/golden.jpeg " +
                    work + "/img.jpeg " + work + "/out.txt" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      std::ifstream inputFile(work + "/out.txt");
      double ssim;
      inputFile >> ssim;
      inputFile.close();
      ssim = ssim < 0.f ? 0.f : ssim;
      systemCustom(
          ("rm -rf " + work + (printOut ? "" : "> /dev/null")).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(),
                                                (1.f - ssim) * 10000);
      //debug
      //std::cout <<ssim<< "------------------->"<<ret.second << "\n";
      //messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else if (clc::ve_pushp_design == "sobelSR") {
      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineSR(individual);
      systemCustom(("$MODELSIM_BIN/vlog -work " + work + " " + define +
                    " +define+OUT_PATH=\"" + work +
                    "/\""
                    " +define+IN_PATH=\"" +
                    "../simulator/IO/in/" +
                    "\" -sv ../simulator/rtl/sr/* ../simulator/rtl/tb/*" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".sobel_tb -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("python3 ../simulator/scripts/sobel_IO_to_jpeg.py " + work +
                    "/512x512sobel_out_nbits.txt  " + work + "/img.jpeg" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("python3 -W ignore ../simulator/scripts/calc_SSIM_WP.py "
                    "../simulator/imgs/SR_cluster/golden.jpeg " +
                    work + "/img.jpeg " + work + "/out.txt" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      std::ifstream inputFile(work + "/out.txt");
      double ssim;
      inputFile >> ssim;
      inputFile.close();
      ssim = ssim < 0.f ? 0.f : ssim;
      systemCustom(("rm -rf " + work).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(),
                                                (1.f - ssim) * 10000);
      //std::cout <<ssim<< "------------------->"<<ret.second << "\n";
      //    messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else if (clc::ve_pushp_design == "invkBR") {
      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineBR(individual);
      systemCustom(("$MODELSIM_BIN/vlog -work " + work + " " + define +
                    " +define+OUT_PATH=\"" + work + "/\"" +
                    " -sv ../simulator/rtl/br_cluster/* ../simulator/rtl/tb/*" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".inv_kin_tb -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("./../simulator/scripts/getError/getError.x "
                    "../simulator/theta/BR_cluster/golden.csv " +
                    work + "/output.csv \"2,3\" " + ("> " + work + "/err.csv"))
                       .c_str());

      std::ifstream inputFile(work + "/err.csv");
      double err;
      inputFile >> err;
      inputFile.close();
      err = err < 0.f ? 0.f : err;
      //    systemCustom(("cat " + work + "/err.csv").c_str());
      systemCustom(
          ("rm -rf " + work + (printOut ? "" : "> /dev/null")).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(), err * 10000);
      //std::cout <<err<< "------------------->"<<ret.second << "\n";
      //    messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else if (clc::ve_pushp_design == "invkSR") {
      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineSR(individual);
      systemCustom(("$MODELSIM_BIN/vlog -work " + work + " " + define +
                    " +define+OUT_PATH=\"" + work + "/\"" +
                    " -sv ../simulator/rtl/sr/* ../simulator/rtl/tb/*" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".inv_kin_tb -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("./../simulator/scripts/getError/getError.x "
                    "../simulator/theta/SR_cluster/golden.csv " +
                    work + "/output.csv \"2,3\" " + ("> " + work + "/err.csv"))
                       .c_str());

      std::ifstream inputFile(work + "/err.csv");
      double err;
      inputFile >> err;
      inputFile.close();
      err = err < 0.f ? 0.f : err;
      //    systemCustom(("cat " + work + "/err.csv").c_str());
      systemCustom(
          ("rm -rf " + work + (printOut ? "" : "> /dev/null")).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(), err * 10000);
      //std::cout <<err<< "------------------->"<<ret.second << "\n";
      //    messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else if (clc::ve_pushp_design == "firBR") {
      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineBR(individual);
      systemCustom(("$MODELSIM_BIN/vlog -work " + work + " " + define +
                    " +define+OUT_PATH=\"" + work + "/\"" +
                    " -sv ../simulator/rtl/br_cluster/* ../simulator/rtl/tb/*" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".tb_FIR -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("./../simulator/scripts/getError/getError.x "
                    "../simulator/filtered/BR_cluster/golden.csv " +
                    work + "/output.csv \"0\" " + ("> " + work + "/err.csv"))
                       .c_str());

      std::ifstream inputFile(work + "/err.csv");
      double err;
      inputFile >> err;
      inputFile.close();
      err = err < 0.f ? 0.f : err;
      //    systemCustom(("cat " + work + "/err.csv").c_str());
      systemCustom(
          ("rm -rf " + work + (printOut ? "" : "> /dev/null")).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(), err * 10000);
      //std::cout <<err<< "------------------->"<<ret.second << "\n";
      //    messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else if (clc::ve_pushp_design == "firSR") {
      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineSR(individual);
      systemCustom(("$MODELSIM_BIN/vlog -work " + work + " " + define +
                    " +define+OUT_PATH=\"" + work + "/\"" +
                    " -sv ../simulator/rtl/sr/* ../simulator/rtl/tb/*" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".tb_FIR -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("./../simulator/scripts/getError/getError.x "
                    "../simulator/filtered/SR_cluster/golden.csv " +
                    work + "/output.csv \"0\" " + ("> " + work + "/err.csv"))
                       .c_str());

      std::ifstream inputFile(work + "/err.csv");
      double err;
      inputFile >> err;
      inputFile.close();
      err = err < 0.f ? 0.f : err;
      //systemCustom(("cat " + work + "/err.csv").c_str());
      systemCustom(
          ("rm -rf " + work + (printOut ? "" : "> /dev/null")).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(), err * 10000);
      //std::cout <<err<< "------------------->"<<ret.second << "\n";
      //    messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else if (clc::ve_pushp_design == "brentkBR") {
      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineBR(individual);
      systemCustom(("$MODELSIM_BIN/vlog -work " + work + " " + define +
                    " +define+OUT_PATH=\"" + work + "/\"" +
                    " -sv ../simulator/rtl/br_cluster/* ../simulator/rtl/tb/*" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".UBBKA_31_0_31_0_tb -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("./../simulator/scripts/getError/getError.x "
                    "../simulator/sum/BR_cluster/golden.csv " +
                    work + "/output.csv \"0\" " + ("> " + work + "/err.csv"))
                       .c_str());

      std::ifstream inputFile(work + "/err.csv");
      double err;
      inputFile >> err;
      inputFile.close();
      err = err < 0.f ? 0.f : err;
      //    systemCustom(("cat " + work + "/err.csv").c_str());
      systemCustom(
          ("rm -rf " + work + (printOut ? "" : "> /dev/null")).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(), err * 10000);
      //std::cout <<err<< "------------------->"<<ret.second << "\n";
      //    messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else if (clc::ve_pushp_design == "brentkSR") {

      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineSR(individual);
      systemCustom(("$MODELSIM_BIN/vlog -work " + work + " " + define +
                    " +define+OUT_PATH=\"" + work + "/\"" +
                    " -sv ../simulator/rtl/sr/* ../simulator/rtl/tb/*" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".UBBKA_31_0_31_0_tb -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("./../simulator/scripts/getError/getError.x "
                    "../simulator/sum/SR_cluster/golden.csv " +
                    work + "/output.csv \"0\" " + ("> " + work + "/err.csv"))
                       .c_str());

      std::ifstream inputFile(work + "/err.csv");
      double err;
      inputFile >> err;
      inputFile.close();
      err = err < 0.f ? 0.f : err;
      //systemCustom(("cat " + work + "/err.csv").c_str());
      systemCustom(
          ("rm -rf " + work + (printOut ? "" : "> /dev/null")).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(), err * 10000);
      //std::cout <<err<< "------------------->"<<ret.second << "\n";
      //    messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else if (clc::ve_pushp_design == "reBR") {
      std::string work = "work" + std::to_string(t_id);
      systemCustom(("$MODELSIM_BIN/vlib " + work).c_str());
      auto define = toDefineBR(individual);
      systemCustom(("$MODELSIM_BIN/vlog -work " + work + " " + define +
                    " +define+OUT_PATH=\"" + work + "/\"" +
                    " -sv ../simulator/rtl/br_cluster/* ../simulator/rtl/tb/*" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());
      systemCustom(("$MODELSIM_BIN/vsim -L " + work + " " + work +
                    ".adder_tb -c -voptargs=\"+acc\" -do \"run "
                    "-all; quit\"" +
                    (printOut ? "" : "> /dev/null"))
                       .c_str());

      systemCustom(("./../simulator/scripts/getError/getError.x "
                    "../simulator/sum/BR_cluster/golden.csv " +
                    work + "/output.csv \"0\" " + ("> " + work + "/err.csv"))
                       .c_str());

      std::ifstream inputFile(work + "/err.csv");
      double err;
      inputFile >> err;
      inputFile.close();
      err = err < 0.f ? 0.f : err;
      //    systemCustom(("cat " + work + "/err.csv").c_str());
      systemCustom(
          ("rm -rf " + work + (printOut ? "" : "> /dev/null")).c_str());
      auto ret = std::make_pair<size_t, size_t>(individual.size(), err * 10000);
      //std::cout <<err<< "------------------->"<<ret.second << "\n";
      //    messageErrorIf(ret.first==0,"?");
      cacheGuard.lock();
      cachedIndividual[serializeIndividual(individual)] = ret;
      cacheGuard.unlock();

      return ret;

    } else {
      messageError("Uknown pushp design");
      return std::make_pair<size_t, size_t>(0, 0);
    }
  }
}

inline std::vector<std::pair<size_t, size_t>> getObjectives(
    const std::vector<std::unordered_set<std::string>> &pop,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {
  std::vector<std::pair<size_t, size_t>> objectives(pop.size());

  Semaphore maxThreads(clc::maxThreads);
  Semaphore completed(0);
  //FIXME: unexplainable race condition
  progresscpp::ParallelProgressBar pb;
  //  pb.addInstance(0, "Calculating objectives...", pop.size(), 70);
  std::cout << "Calculating objectives..." << "\n";

  for (size_t toBeServed = 0; toBeServed < pop.size(); toBeServed++) {

    maxThreads.wait();

    std::thread([&objectives, toBeServed, &maxThreads, &pop, &allGenes,
                 &completed, &pb]() {
      objectives[toBeServed] =
          evalIndividual(pop.at(toBeServed), allGenes, toBeServed);
      maxThreads.addNotifyOnce(1);
      completed.addNotifyOnce(1);
      //    pb.increment(0);
      //    pb.display();
    }).detach();
  }
  completed.wait(pop.size());
  //pb.done(0);

  return objectives;
}

inline std::vector<size_t> generateDominanceRank(
    const std::vector<std::unordered_set<std::string>> &individuals,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes) {

  int n = individuals.size();

  // Store the objective values for each individual
  std::vector<std::pair<size_t, size_t>> objectives =
      getObjectives(individuals, allGenes);

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
inline bool getRandomBool() {
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
inline std::unordered_set<std::string> getRandomIndividual(
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes,
    size_t sizeOfIndividual) {

  std::unordered_set<std::string> individual;
  while (individual.size() < sizeOfIndividual) {
    individual.insert(getRandomItem(allGenes).first);
  }
  return individual;
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
    size_t allowedPopSize) {

  population.clear();

  //used to avoid repetitions of individuals with the same score
  std::set<std::pair<size_t, size_t>> alreadyInUse;

  for (auto &front : fronts) {
    if (front.size() + population.size() <= allowedPopSize) {
      //front fits entirely
      for (const auto &individual : front) {
        auto score = evalIndividual(individual, allGenes);
        if (!alreadyInUse.count(score)) {
          alreadyInUse.insert(score);
          population.push_back(individual);
        }
      }
    } else if (population.size() < allowedPopSize) {
      //front does not fit, need crowd sorting
      crowdSort(front, allGenes);
      for (const auto &individual : front) {
        auto score = evalIndividual(individual, allGenes);
        if (!alreadyInUse.count(score)) {
          alreadyInUse.insert(score);
          population.push_back(individual);
        }
        if (population.size() == allowedPopSize) {
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
  std::vector<std::unordered_set<std::string>> mutatedPop = pop;
  for (auto &ind : pop) {
    if (getRandomBool()) {
      //add a random individual of the same size
      mutatedPop.push_back(samplePopulation(allGenes, ind.size(), 1).front());
    } else {
      //create a new individual with a single random element
      auto tmpInd = ind;
      tmpInd.insert(getRandomItem(allGenes).first);
      mutatedPop.push_back(tmpInd);
    }
  }
  pop = mutatedPop;
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

//size_t inline getDominatedSurface(
//    const std::vector<std::pair<size_t, size_t>> &points,
//    const std::pair<size_t, size_t> &gridSize) {
//  // Initialize a 2D grid with all elements set to false
//  std::vector<std::vector<bool>> grid(
//      gridSize.first + 1, std::vector<bool>(gridSize.second + 1, false));
//
//  // Mark all the dominated cells as true
//  for (size_t i = 0; i < points.size(); i++) {
//    size_t x = points[i].first;
//    size_t y = points[i].second;
//
//    for (size_t j = 0; j <= x; j++) {
//      for (size_t k = y; k < gridSize.second; k++) {
//        grid[j][k] = true;
//      }
//    }
//  }
//
//  // Count the number of dominated cells
//  size_t count = 0;
//  for (size_t i = 0; i < gridSize.first; i++) {
//    for (size_t j = 0; j < gridSize.second; j++) {
//      if (grid[i][j]) {
//        count++;
//      }
//    }
//  }
//
//  // Ensure that the returned value is not greater than the maximum surface
//  return std::min(count, gridSize.first * gridSize.second);
//}

double inline getDominatedSurface(
    const std::vector<std::pair<size_t, size_t>> &points,
    const std::pair<size_t, size_t> &gridSize) {
  // Initialize a 2D grid with all elements set to false
  size_t gridX = (gridSize.first + 1);
  size_t maxYSize = 10000;
  size_t divider =
      (gridSize.second > maxYSize) ? (gridSize.second / maxYSize) : 1;
  size_t gridY = (gridSize.second + 1) / divider;

  std::vector<std::vector<bool>> grid(gridX, std::vector<bool>(gridY, false));

  // Mark all the dominated cells as true
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

void inline plotDominance(
    const std::vector<std::pair<size_t, double>> &data,
    const std::string &xlabel = "X", const std::string &ylabel = "Y",
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
  fprintf(pipe, "plot '-' with points pointtype 7 pointsize 0.5 linecolor rgb "
                "'black' title "
                "'Dominance'\n");
  for (const auto &p : data) {
    fprintf(pipe, "%lu %f\n", p.first, p.second);
  }
  fprintf(pipe, "e\n");

  // Dump current plot as PNG file, if requested
  if (pngFilePath.has_value()) {
    std::string filePath = pngFilePath.value();
    std::string command = "set terminal pngcairo size 1920,1080 enhanced font "
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

void inline plotErrorDamage(
    const std::vector<std::pair<size_t, double>> &data,
    const std::string &xlabel = "X", const std::string &ylabel = "Y",
    const std::string &title = "Data Plot",
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
  fprintf(pipe, "plot '-' with points pointtype 7 pointsize 0.5 linecolor rgb "
                "'dark-violet' \n");
  for (const auto &p : data) {
    fprintf(pipe, "%lu %f\n", p.first, p.second);
  }
  fprintf(pipe, "e\n");

  // Dump current plot as PNG file, if requested
  if (pngFilePath.has_value()) {
    std::string filePath = pngFilePath.value();
    std::string command = "set terminal pngcairo size 1920,1080 enhanced font "
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

void inline plotBeforeAfter(
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

  if (clc::ve_pushp_design == "sobelBR" || clc::ve_pushp_design == "sobelSR") {
    for (auto &[n, e] : data1) {
      e = 1.f - e;
    }
    for (auto &[n, e] : data2) {
      e = 1.f - e;
    }
    ylabel = "SSIM";
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
    std::string command = "set terminal pngcairo size 1920,1080 enhanced font "
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

void inline plotBeforeAfterRandom(
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

  if (clc::ve_pushp_design == "sobelBR" || clc::ve_pushp_design == "sobelSR") {
    for (auto &[n, e] : data1) {
      e = 1.f - e;
    }
    for (auto &[n, e] : data2) {
      e = 1.f - e;
    }
    for (auto &[n, e] : data3) {
      e = 1.f - e;
    }
    ylabel = "SSIM";
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
    std::string command = "set terminal pngcairo size 1920,1080 enhanced font "
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

inline void genAndDumpRandomClusters(
    const std::vector<std::unordered_set<std::string>> &paretoFront,
    const std::unordered_map<std::string, std::unordered_set<std::string>>
        &allGenes,
    std::vector<std::pair<size_t, double>> &beforePushMetricFrontData,
    bool pushing = 0, size_t reps = 10) {

  auto maxObjs = pushing
                     ? std::make_pair<size_t, size_t>(allGenes.size(), 10000)
                     : getMaxObjectivesValues(allGenes);

  std::vector<std::pair<size_t, size_t>> originalObjectives;
  std::vector<std::pair<size_t, double>> originalData;
  std::vector<std::pair<size_t, double>> randomData;
  std::vector<std::unordered_set<std::string>> randomRepresentatives;

  //keep track the elaborated individuals
  size_t geObIndex = 0;

  for (auto &individual : paretoFront) {
    originalObjectives.push_back(evalIndividual(individual, allGenes));

    //gather random individuals
    std::vector<std::unordered_set<std::string>> randomIndividuals;
    for (size_t i = 0; i < reps; i++) {
      randomIndividuals.push_back(
          getRandomIndividual(allGenes, individual.size()));
    }

    double avgRandom = 0.f;

    std::vector<std::pair<double, std::unordered_set<std::string>>>
        candidatesRand;

    std::cout << geObIndex++ << "/" << paretoFront.size() << "\n";
    //eval random individuals
    std::vector<std::pair<size_t, size_t>> objectives =
        getObjectives(randomIndividuals, allGenes);

    for (size_t i = 0; i < objectives.size(); i++) {
      double rnd = (((double)objectives[i].second / (double)maxObjs.second));
      avgRandom += rnd;
      candidatesRand.emplace_back(rnd, randomIndividuals[i]);
    }

    avgRandom /= objectives.size();

    //sort by distance from the avg
    std::sort(
        begin(candidatesRand), end(candidatesRand),
        [&avgRandom](std::pair<double, std::unordered_set<std::string>> &e1,
                     std::pair<double, std::unordered_set<std::string>> &e2) {
          return std::abs(e1.first - avgRandom) <
                 std::abs(e2.first - avgRandom);
        });

    //store a good rand candidate (close to the average)
    randomRepresentatives.push_back(candidatesRand.front().second);

    randomData.emplace_back(individual.size(), avgRandom);
  }

  for (const auto &[x, y] : originalObjectives) {
    originalData.emplace_back(x, (((double)y / (double)maxObjs.second)));
  }

  plotBeforeAfterRandom(
      beforePushMetricFrontData, originalData, randomData, "Number of tokens",
      (pushing ? std::string("Error") : std::string("Damage")), "",
      "Before push", "After push", "Random", std::make_pair(0.f, maxObjs.first),
      std::make_pair(0.f, 1.f), 1,
      clc::ve_dumpTo + "/" + clc::ve_technique + "_" + "bar.csv",
      clc::ve_dumpTo + "/" + clc::ve_technique + "_bar.png");

  std::ofstream out(clc::ve_dumpTo + "/" + clc::ve_technique +
                    "_randCandidates.csv");

  std::sort(randomRepresentatives.begin(), randomRepresentatives.end(),
            [](std::unordered_set<std::string> &e1,
               std::unordered_set<std::string> &e2) {
              return e1.size() < e2.size();
            });

  //dump verilog defines
  out << "size,define\n";
  for (auto &rp : randomRepresentatives) {
    out << rp.size() << ","
        << (clc::ve_technique == "br" ? toDefineBR(rp, 0) : toDefineSR(rp))
        << "\n";
  }
  out.close();
}
inline std::vector<std::tuple<size_t, double, std::unordered_set<std::string>>>
nsga2(const std::unordered_map<std::string, std::unordered_set<std::string>>
          &allGenes,
      size_t maxIterations = 100, double minIncrement = 1.f,
      const std::vector<std::unordered_set<std::string>> &initialPop =
          std::vector<std::unordered_set<std::string>>()) {

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
  auto maxObjs = getMaxObjectivesValues(allGenes);
  bool saveParetoMetricBeforePush = 0;
  std::vector<std::pair<size_t, double>> beforePushMetricFrontData;
  std::vector<std::unordered_set<std::string>> pop;

  if (initialPop.empty()) {
    pop = samplePopulation(allGenes, 1, allGenes.size());
  } else {
    pop = initialPop;
  }

  size_t allowedPopSize = pop.size();

  //used for the halting criteria
  double prevDominance = 0;
  double dominance = DBL_MAX;
  bool pushing = 0;
  dirtyTimerSeconds("startNSGA2", 1);

  if (clc::ve_only_sim) {
    dirtyTimerSeconds("startPush", 1);
    pushing = 1;
    evalIndividual(std::unordered_set<std::string>(), allGenes, 0, 1);
    maxObjs.second = 10000;
  }

  for (size_t i = 0; i < maxIterations; i++) {
    std::cout << "Population size " << allowedPopSize << "\n";
    //keep track how long each iteratin takes
    dirtyTimerSeconds("startIteration", 1);

    //skip the first iteration
    if (i > 0) {
      //mutation on the entire population
      mutatePop(pop, allGenes);
      addOffspring(pop, allGenes);
      removeDuplicates(pop);
    }

    auto fronts = generateFronts(pop, allGenes);

    selectElites(fronts, allGenes, pop, allowedPopSize);

    std::vector<std::pair<size_t, size_t>> chart_data;
    bool confWithAllTokensExists = 0;
    for (auto &individual : generateParetoFront(pop, allGenes)) {
      auto score = evalIndividual(individual, allGenes);
      chart_data.push_back(score);
      confWithAllTokensExists =
          confWithAllTokensExists || score.first == maxObjs.first;
    }

    dominance = getDominatedSurface(chart_data, maxObjs);
    double increment = ((dominance - prevDominance) / dominance) * 100.f;

    //convert damage to double, and normalize it
    std::vector<std::pair<size_t, double>> front_plot_data;
    for (const auto &[x, y] : chart_data) {
      front_plot_data.emplace_back(x, (((double)y / (double)maxObjs.second)));
    }

    if (saveParetoMetricBeforePush) {
      saveParetoMetricBeforePush = 0;
      dominancePhase1 = dominance;
      beforePushMetricFrontData = front_plot_data;
    }

    if (pushing) {
      plotBeforeAfter(
          beforePushMetricFrontData, front_plot_data, "Number of tokens",
          (pushing ? std::string("Error") : std::string("Damage")),
          "Dominance: " + std::to_string(dominance * 100) + "%", "Before push",
          "After push", std::make_pair(0.f, maxObjs.first),
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
      plotErrorDamage(front_plot_data, "Number of tokens",
                      (pushing ? std::string("Error") : std::string("Damage")),
                      "Dominance: " + std::to_string(dominance * 100) + "%",
                      std::make_pair(0.f, maxObjs.first),
                      std::make_pair(0.f, 1.f), 1);
    }

    auto duration = dirtyTimerSeconds("startIteration", 0);

    std::cout << "Iteration: " << i << "th\n";
    std::cout << "Duration: " << duration << "s\n";
    std::cout << "PrevDominance:" << prevDominance << "\n";
    std::cout << "Dominance:" << dominance << "\n";
    std::cout << "Dominance increment :" << increment << "%\n";

    //terminal condition
    if (increment <= minIncrement) {
      if (!clc::ve_only_sim && !isTimeOut("startNSGA2", clc::ve_minTime)) {
        goto continueUpdate;
      }

      if (pushing) {
        if (!isTimeOut("startPush", clc::ve_minPushTime)) {
          goto continueUpdate;
        }

      } else {
        secondsPhase1 = dirtyTimerSeconds("startNSGA2", 0);
        plotErrorDamage(
            front_plot_data, "Number of tokens", std::string("Damage"),
            "Dominance " + std::to_string(dominance * 100) + "%",
            std::make_pair(0.f, maxObjs.first), std::make_pair(0.f, 1.f), 1,
            clc::ve_dumpTo + "/" + clc::ve_technique + "_" + "damage.cvs",
            clc::ve_dumpTo + "/" + clc::ve_technique + "_damage.png");

        if (clc::ve_pushp) {
            std::cout<<"######  #     #  #####  #     # ### #     #  #####\n";
            std::cout<<"#     # #     # #     # #     #  #  ##    # #     #\n";
            std::cout<<"#     # #     # #       #     #  #  # #   # #\n";
            std::cout<<"######  #     #  #####  #######  #  #  #  # #  ####\n";
            std::cout<<"#       #     #       # #     #  #  #   # # #     #\n";
            std::cout<<"#       #     # #     # #     #  #  #    ## #     #\n";
            std::cout<<"#        #####   #####  #     # ### #     #  #####\n";


          //dump frontier before push
          dirtyTimerSeconds("startPush", 1);
          pushing = 1;
          evalIndividual(std::unordered_set<std::string>(), allGenes, 0, 1);
          maxObjs.second = 10000;
          prevDominance = 0;
          dominance = DBL_MAX;
          saveParetoMetricBeforePush = 1;
          continue;
        }
      }

      break;

    } else {
      if (pushing) {
        if (isTimeOut("startPush", clc::ve_maxPushTime)) {
          break;
        }
      }
    }

  continueUpdate:;
    prevDominance = dominance;
    allowedPopSize = allowedPopSize <= 100 ? std::min(100ul, initialPop.size())
                                           : allowedPopSize * 0.9;
  }

  if (clc::ve_pushp) {
    secondsPhase2 = dirtyTimerSeconds("startPush", 0);
    dominancePhase2 = dominance;
  }
  if (clc::ve_only_sim) {
    dominancePhase1 = dominance;
  }

  std::cout << "NSGA2 has finished!"
            << "\n";

  //dump temporal statistics
  fileAppendContent(clc::ve_dumpTo + "/" + clc::ve_technique + "_" + "time.csv",
                    std::to_string(secondsPhase1) + ";" +
                        std::to_string(secondsPhase2) + "\n");
  //dump dominance stat
  fileDumpContent(clc::ve_dumpTo + "/" + clc::ve_technique + "_" +
                      "dominance.csv",
                  "dominancePhase1;dominancePhase2;increment\n");
  fileAppendContent(
      clc::ve_dumpTo + "/" + clc::ve_technique + "_" + "dominance.csv",
      std::to_string(dominancePhase1) + ";" + std::to_string(dominancePhase2) +
          ";" + std::to_string(dominancePhase2 - dominancePhase1) + "\n");

  //organize the return structure
  std::vector<std::tuple<size_t, double, std::unordered_set<std::string>>> ret;

  for (auto &individual : generateParetoFront(pop, allGenes)) {
    auto score = evalIndividual(individual, allGenes);
    ret.emplace_back(score.first, score.second / maxObjs.second, individual);
  }

  if (clc::ve_genRand) {
    genAndDumpRandomClusters(generateParetoFront(pop, allGenes), allGenes,
                             beforePushMetricFrontData, pushing, 50);
  }

  return ret;
}
