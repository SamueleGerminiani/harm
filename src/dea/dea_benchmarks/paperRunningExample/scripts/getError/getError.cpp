

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::vector<unsigned int>>
getValues(const std::string &csvFile, const std::string &fields) {
  std::vector<std::vector<unsigned int>> ret;
  std::unordered_set<size_t> indexes;
  // parse fields
  {
    std::string word;
    std::stringstream str(fields);

    while (getline(str, word, ',')) {
      indexes.insert(std::stoul(word));
    }
  }
  for (auto i : indexes) {
    ret.emplace_back();
  }

  std::ifstream in(csvFile);
  if (!in.is_open()) {
    std::cout << "Error in file: " << csvFile << std::endl;
    exit(1);
  }

  std::string line, word;
  // parse csv file

  // remove header
  getline(in, line);

  while (getline(in, line)) {
    std::stringstream str(line);

    // real index
    size_t i = 0;
    // compressed index
    size_t j = 0;

    // parse row
    while (getline(str, word, ',')) {
      if (indexes.count(i)) {
        ret[j].push_back(std::stoull(word));
        j++;
      }
      i++;
    }
  }

  in.close();

  return ret;
}

unsigned int getMax(std::vector<unsigned int> &v) {
  unsigned int max = std::numeric_limits<unsigned int>::lowest();
  for (auto i : v) {
    max = std::max(i, max);
  }
  return max;
}
unsigned int getMaxDiff(std::vector<unsigned int> &g_field,
                        std::vector<unsigned int> &f_field) {
  unsigned int max = std::numeric_limits<unsigned int>::lowest();
  for (size_t i = 0; i < g_field.size(); i++) {
    max = std::max(
        (unsigned int)std::abs((int)(g_field[i] - f_field[i])), max);
  }

  return max;
}

double getError(std::vector<std::vector<unsigned int>> &g,
                std::vector<std::vector<unsigned int>> &f) {
  size_t nFields = g.size();
  size_t nValues = g.back().size();

  //    debug
  //    std::cout << "nFields: "<<nFields << std::endl;
  //    std::cout << "nValues: "<<nValues << std::endl;

  // retrieve the max value for each field
  std::vector<double> maxes;
  for (size_t i = 0; i < g.size(); i++) {
    maxes.push_back(getMaxDiff(g[i], f[i]));
  }

  double ret = 0.f;
  for (int i = 0; i < nFields; ++i) {
    double errField = 0.f;
    // process field
    for (int j = 0; j < nValues; ++j) {
      errField +=
          (g[i][j] == 0.f && f[i][j] == 0.f
               ? 0.f
               : (double)(std::abs(((long long int)g[i][j] -
                                    (long long int)f[i][j]))) /
                     (double)std::max(g[i][j], f[i][j]));
      //            std::stringstream ss;
      //              ss << g[i][j]<<","<<f[i][j]<<"="<<(double)(std::abs(((long long int)g[i][j] - (long long int)f[i][j]))) / (double)std::max(g[i][j],f[i][j])<<"\n";
      //              system(("echo " + ss.str()+" >> log.txt").c_str());
      // errField += (maxes[i]==0.f?0.f:std::abs(g[i][j] - f[i][j]) /
      // maxes[i]);
      //  debug
      //  std::cout << "["<<i<<"]"<<"["<<j<<"]" << std::endl;
      //  maxes[i]
      //  << std::endl;
    }
    // store result of current field
    ret += errField / nValues;
  }
  // make avg of all fields
  ret /= nFields;
  //    system(("\""+std::to_string(ret)+"\"").c_str());
  return ret;
}

int main(int argc, char *argv[]) {
  // get input
  std::string golden = argv[1];
  std::string faulty = argv[2];
  std::string fields = argv[3];

  // parse traces
  auto gValues = getValues(golden, fields);
  auto fValues = getValues(faulty, fields);
  double err = getError(gValues, fValues);

  // print error
  std::cout << std::fixed << std::setprecision(8) << err << std::endl;

  return 0;
}
