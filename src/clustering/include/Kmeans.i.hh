
#include "dkm.hpp"
#include "message.hh"
#include "misc.hh"
#include "utils.hh"
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

///Plot the variance for increasing K
template <typename T>
void inline plotVariance(const std::vector<size_t> &x,
                         const std::vector<T> &y,
                         const T &horizontalLineValue) {
  // Open a pipe to Gnuplot
  FILE *gnuplotPipe = popen("gnuplot -persist", "w");

  if (gnuplotPipe == nullptr) {
    std::cerr << "Error opening Gnuplot pipe." << std::endl;
    return;
  }

  // Send Gnuplot commands to plot the data and the horizontal line
  fprintf(gnuplotPipe, "set xlabel 'K'\n");
  fprintf(gnuplotPipe, "set ylabel 'V'\n");
  fprintf(gnuplotPipe, "set title 'Variance for increasing K'\n");
  fprintf(gnuplotPipe,
          "plot '-' with lines title 'Data', '-' with lines title "
          "'Horizontal Line'\n");

  for (size_t i = 0; i < x.size(); i++) {
    fprintf(gnuplotPipe, "%f %f\n", (double)x[i], (double)y[i]);
  }
  fprintf(gnuplotPipe, "e\n");

  // Define the horizontal line as a separate dataset
  fprintf(gnuplotPipe, "0 %f\n", (double)horizontalLineValue);
  fprintf(gnuplotPipe, "100 %f\n", (double)horizontalLineValue);
  fprintf(gnuplotPipe, "e\n");

  // Close the pipe
  pclose(gnuplotPipe);
}

template <typename T>
std::vector<std::pair<T, T>>
kmeansElbow(const std::vector<T> &elements, size_t max,
            double minWCSS, bool keepOnlyBest) {

  //this is to avoid truncating the decimals when T is integer, cant be avoided as long as we use boost::multiprecision
#define pump 10000
  double pumpDBL = pump;
  T pumpT = pump;
  T cutoff;

  std::vector<T> variances;

  // store data in the correct format
  std::vector<std::array<T, 1>> data;
  for (size_t i = 0; i < elements.size(); i++) {
    data.push_back(std::array<T, 1>({(T)(elements[i])}));
  }

  std::vector<std::tuple<T, T, size_t>> ranges;
  //set the initial variance to the maximum possible value
  T prevV = std::numeric_limits<T>::max() / pumpT;

  for (size_t clsSize = 1;
       clsSize <= max && clsSize <= elements.size(); clsSize++) {

    // generate the clusters
    auto cluster_data = dkm::kmeans_lloyd(data, clsSize, 100, (T)0);
    //std::get<0>(cluster_data) contains the means
    //std::get<1>(cluster_data) contains the elements in the cluster

    // group the clusters by label
    std::map<size_t, std::vector<T>> labelToValues;
    for (size_t j = 0; j < std::get<1>(cluster_data).size(); j++) {
      auto label = std::get<1>(cluster_data)[j];
      labelToValues[label].push_back(data[j][0]);
    }

    T totV = 0;
    auto means = std::get<0>(cluster_data);
    // compute the variance for each cluster
    for (size_t k = 0; k < means.size(); k++) {
      T mean = means[k][0];
      T currV = 0;
      for (auto &v : labelToValues[k]) {
        //need to pump the values to avoid truncating the decimals when T is integer
        T dist = (mean - v);
        //FIXME: this is not the traditional way to compute the variance but it should yield the same results if we take the absolute value
        currV += std::abs(dist);
      }
      totV += currV;
    }

    variances.push_back(totV);

    //debug
    //std::cout << "---------------------------"<< "\n";
    //std::cout << "K: " << clsSize << "\n";

    if (clsSize == 1) {
      cutoff = ((T)(minWCSS * pumpDBL) * variances[0]) / pumpT;
    } else {
      //debug
      //std::cout << "reduction: " << (prevV - totV) * pumpT << "\n";
      //std::cout << "minRed: " << (T)(0.5 * pumpDBL) * prevV << "\n";
      //std::cout << "cutoff: " << (T)cutoff << "\n";
      // continue only if the variance reduction is above the
      // defined threshold
      if ((((prevV - totV) * pumpT < (T)(0.5 * pumpDBL) * prevV) &&
           totV < (T)(cutoff))) {
        break;
      }
    }

    // translate the clusters into ranges [min, max]
    auto rr = toRanges<T>(labelToValues);

    if (keepOnlyBest) {
      //discard the ranges if this is not the best K
      ranges.clear();
    }

    // add the ranges to the final list
    ranges.insert(ranges.end(), rr.begin(), rr.end());

    prevV = totV;
  }

  //sort by frequency
  std::sort(ranges.begin(), ranges.end(),
            [](const std::tuple<T, T, size_t> &e1,
               const std::tuple<T, T, size_t> &e2) {
              return std::get<2>(e1) > std::get<2>(e2);
            });

  //keep only the first max ranges
  if (ranges.size() > max) {
    ranges.erase(ranges.begin() + max, ranges.end());
  }

  //translate the ranges into the output format
  std::set<std::pair<T, T>> foundRanges;
  std::vector<std::pair<T, T>> ret;
  for (auto &[l, r, f] : ranges) {
    if (!foundRanges.count({l, r})) {
      ret.push_back(std::pair<T, T>({l, r}));
      foundRanges.insert({l, r});
    }
  }

  //debug
  //print the ranges
  //for (auto &[l, r] : foundRanges) {
  //  std::cout << "[" << l << "," << r << "]\n ";
  //}

  //debug - print the variance for each K
  //std::vector<size_t> x(max);
  //std::iota(x.begin(), x.end(), 1);
  //plotVariance(x, variances, cutoff);
  //for (auto i : variances) {
  //  std::cout << i;
  //}
  //std::cout << "\n";

  return ret;
}

