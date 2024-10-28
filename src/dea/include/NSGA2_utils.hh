#include "Individual.hh"
#include "dea.hh"
#include "misc.hh"
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

namespace dea {
inline std::string serializeIndividual(const Individual &individual) {
  std::set<std::string> sorted_individual(individual._genes.begin(),
                                          individual._genes.end());
  std::stringstream ss;
  for (const auto &token : sorted_individual) {
    ss << token << ",";
  }
  return ss.str();
}
inline std::string
toDefineBR(const std::unordered_set<std::string> &individual,
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

inline std::string
toScriptList(const std::unordered_set<std::string> &individual) {
  std::string list = "";
  std::unordered_map<std::string, std::string> idToMask;
  std::unordered_map<std::string, size_t> idToSize;
  for (auto &token : individual) {
    list += token + ";";
  }

  list.pop_back();

  return list;
}

inline void plotDominance(
    const std::vector<std::pair<size_t, double>> &data,
    const std::string &xlabel = "X", const std::string &ylabel = "Y",
    const std::string &title = "Data Plot",
    std::optional<std::pair<size_t, size_t>> xrange = std::nullopt,
    std::optional<std::pair<double, double>> yrange = std::nullopt,
    bool dontClose = true,
    const std::optional<std::string> &dumpFilePath = std::nullopt,
    const std::optional<std::string> &pngFilePath = std::nullopt) {

  static FILE *pipe = nullptr;

  if (!clc::ve_dont_plot) {
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

    // Plot data using points
    fprintf(pipe, "plot '-' with points pointtype 7 pointsize 0.5 "
                  "linecolor rgb "
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
  }

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

  if (!clc::ve_dont_plot) {
    if (dontClose) {
      fflush(pipe);
    } else {
      pclose(pipe);
    }
  }
}

inline void plotErrorDamage(
    const std::vector<std::pair<size_t, double>> &data,
    const std::string &xlabel = "X", const std::string &ylabel = "Y",
    const std::string &title = "Data Plot",
    std::optional<std::pair<size_t, size_t>> xrange = std::nullopt,
    std::optional<std::pair<double, double>> yrange = std::nullopt,
    bool dontClose = true,
    const std::optional<std::string> &dumpFilePath = std::nullopt,
    const std::optional<std::string> &pngFilePath = std::nullopt) {

  static FILE *pipe = nullptr;

  if (!clc::ve_dont_plot) {

    if (pngFilePath.has_value() || dumpFilePath.has_value() ||
        dirtyTimerSeconds("plotRate", 0) > clc::ve_plotRate) {
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

    // Plot data using points
    fprintf(pipe, "plot '-' with points pointtype 7 pointsize 0.5 "
                  "linecolor rgb "
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
  }

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

  if (!clc::ve_dont_plot) {
    if (dontClose) {
      fflush(pipe);
    } else {
      pclose(pipe);
    }
  }
}

inline void plotBeforeAfter(
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

  if (!clc::ve_dont_plot) {
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
  }

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

  if (!clc::ve_dont_plot) {
    if (dontClose) {
      fflush(pipe);
    } else {
      pclose(pipe);
    }
  }
}

inline void plotBeforeAfterRandom(
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

  if (!clc::ve_dont_plot) {
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

    // Plot data using points with colors
    fprintf(
        pipe,
        "plot '-' with points pointtype 7 pointsize 0.5 linecolor rgb 'blue' title '%s', \
                  '-' with points pointtype 7 pointsize 0.5 linecolor rgb 'dark-violet' title '%s', \
                  '-' with points pointtype 7 pointsize 0.5 linecolor rgb 'red' title '%s'\n",
        series2Title.c_str(), series1Title.c_str(),
        series3Title.c_str());

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
  }

  if (!clc::ve_dont_plot) {
    // Dump data as CSV file, if requested
    if (dumpFilePath.has_value()) {
      std::ofstream outfile(dumpFilePath.value());
      if (!outfile.is_open()) {
        std::cerr << "Error opening dump file "
                  << dumpFilePath.value() << std::endl;
      } else {
        size_t longestSeriesSize = std::max(
            data1.size(), std::max(data2.size(), data3.size()));
        outfile << "x1;y1;x2;y2;x3;y3" << std::endl;
        for (size_t i = 0; i < longestSeriesSize; i++) {
          if (i < data1.size()) {
            outfile << data1[i].first << ";" << data1[i].second
                    << ";";
          } else {
            outfile << ";;";
          }
          if (i < data2.size()) {
            outfile << data2[i].first << ";" << data2[i].second
                    << ";";
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
  }

  if (!clc::ve_dont_plot) {
    if (dontClose) {
      fflush(pipe);
    } else {
      pclose(pipe);
    }
  }
}

inline bool getRandomBool() {
  std::time_t seed = std::time(nullptr) + getpid();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, 1);
  return distribution(generator);
}

template <typename T, typename U>
inline std::pair<T, U>
getRandomItem(const std::unordered_map<T, U> &map) {
  auto seed =
      std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, map.size() - 1);
  int randomIndex = distribution(generator);

  auto it = map.begin();
  std::advance(it, randomIndex);
  return *it;
}
inline Individual getRandomIndividual(
    const std::unordered_map<
        std::string, std::unordered_set<std::string>> &geneToAssTime,
    size_t numberOfGenes) {

  messageErrorIf(numberOfGenes == 0,
                 "requested number of genes is 0");
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

inline std::vector<Individual> samplePopulation(
    const std::unordered_map<
        std::string, std::unordered_set<std::string>> &geneToAssTime,
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
inline void removeDuplicates(std::vector<Individual> &pop) {

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
  pop.erase(std::remove_if(
                pop.begin(), pop.end(),
                [](const Individual &e) { return e._genes.empty(); }),
            pop.end());
}

inline double getDominatedSurface(
    const std::vector<std::pair<size_t, size_t>> &points,
    const std::pair<size_t, size_t> &gridSize) {
  // Initialize a 2D grid with all elements set to false
  size_t gridX = (gridSize.first + 1);
  size_t maxYSize = 1000;
  size_t divider =
      (gridSize.second > maxYSize) ? (gridSize.second / maxYSize) : 1;
  size_t gridY = (gridSize.second + 1) / divider;

  std::vector<std::vector<bool>> grid(
      gridX, std::vector<bool>(gridY, false));

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

inline std::pair<size_t, size_t> getMaxObjectivesValues(
    const std::unordered_map<std::string,
                             std::unordered_set<std::string>>
        &geneToAssTime) {

  std::unordered_set<std::string> uniqueInstances;
  for (auto &[id, instances] : geneToAssTime) {
    for (auto &i : instances) {
      uniqueInstances.insert(i);
    }
  }
  return std::make_pair(geneToAssTime.size(), uniqueInstances.size());
}

inline void printPushing() {

  std::cout << "######  #     #  #####  #     # ### #     "
               "#  #####\n";
  std::cout << "#     # #     # #     # #     #  #  ##    "
               "# #     #\n";
  std::cout << "#     # #     # #       #     #  #  # #  "
               " # #\n";
  std::cout << "######  #     #  #####  #######  #  #  #  "
               "# #  ####\n";
  std::cout << "#       #     #       # #     #  #  #   # "
               "# #     #\n";
  std::cout << "#       #     # #     # #     #  #  #    "
               "## #     #\n";
  std::cout << "#        #####   #####  #     # ### #     "
               "#  #####\n";
}

} // namespace dea
