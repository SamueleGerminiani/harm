#pragma once
#include "message.hh"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

long long inline safeStoll(const std::string &str, int base = 10) {
  try {
    return std::stoll(str, nullptr, base);
  } catch (const std::invalid_argument &e) {
    messageWarning("Invalid argument: " + std::string(e.what()) +
                   " " + str + " base " + std::to_string(base));
  } catch (const std::out_of_range &e) {
    messageWarning("Out of range: " + std::string(e.what()) + " " +
                   str + " base " + std::to_string(base));
  } catch (const std::exception &e) {
    messageWarning("Warning: " + std::string(e.what()) + " " + str +
                   " base " + std::to_string(base));
  }

  // Return a default value or handle the error as needed
  return 0;
}

unsigned long long inline safeStoull(const std::string &str,
                                     int base = 10) {
  try {
    return std::stoull(str, nullptr, base);
  } catch (const std::invalid_argument &e) {
    messageWarning("Invalid argument: " + std::string(e.what()) +
                   " " + str + " base " + std::to_string(base));
  } catch (const std::out_of_range &e) {
    messageWarning("Out of range: " + std::string(e.what()) + " " +
                   str + " base " + std::to_string(base));
  } catch (const std::exception &e) {
    messageWarning("Warning: " + std::string(e.what()) + " " + str +
                   " base " + std::to_string(base));
  }

  // Return a default value or handle the error as needed
  return 0;
}

inline double safeStod(const std::string &str) {
  try {
    return std::stod(str);
  } catch (const std::invalid_argument &e) {
    messageWarning("Invalid argument: " + std::string(e.what()) +
                   " " + str);
  } catch (const std::out_of_range &e) {
    messageWarning("Out of range: " + std::string(e.what()) + " " +
                   str);
  } catch (const std::exception &e) {
    messageWarning("Warning: " + std::string(e.what()) + " " + str);
  }

  // Return a default value or handle the error as needed
  return 0.0;
}

template <typename T>
inline std::string to_string_with_precision(const T a_value,
                                            const int n = 6) {
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return out.str();
}

inline int **copy_matrix(int **mat, int size1, int size2) {
  int row;
  int **res = new int *[size1];
  for (row = 0; row < size1; row++) {
    res[row] = new int[size2];
    memcpy(res[row], mat[row], size2 * sizeof(int));
  }
  return res;
}

///call to system with error handling
void inline systemCustom(std::string command) {
  int status = system(command.c_str());
  if (status < 0) {
    std::cout << "System error: " << '\n';
  } else {
    if (!WIFEXITED(status)) {
      std::cout << "Program exited abnormaly\n";
    }
  }
}

///select the string after the input pattern
inline std::string selectStringAfter(std::string str,
                                     std::string pattern) {
  // Find the position of the pattern in the string
  size_t pos = str.find(pattern);

  // If the pattern is not found, return an empty string
  if (pos == std::string::npos) {
    return "";
  }

  // Return the substring after the pattern
  return str.substr(pos + pattern.length());
}

inline bool patternExists(std::string str, std::string pattern) {
  // Find the position of the pattern in the string
  size_t pos = str.find(pattern);

  // If the pattern is found, return true
  if (pos != std::string::npos) {
    return true;
  }

  // If the pattern is not found, return false
  return false;
}

///remove spaces from string
inline void removeSpacesInPlace(std::string &str) {
  str.erase(std::remove_if(str.begin(), str.end(), ::isspace),
            str.end());
}

///remove spaces from string without modifying the input
inline std::string removeSpaces(std::string str) {
  str.erase(std::remove_if(str.begin(), str.end(), ::isspace),
            str.end());
  return str;
}

///remove brackets from a string
inline void removeBracketsInPlace(std::string &str) {

  str.erase(std::remove_if(str.begin(), str.end(),
                           [](char ch) {
                             return ch == '[' || ch == ']' ||
                                    ch == '{' || ch == '}' ||
                                    ch == '(' || ch == ')';
                           }),
            str.end());
}

///replace all occurences of a string with a set of strings (tokens), the longest match always have higher priority
inline void
replace(const std::vector<std::pair<std::string, std::string>>
            &tokenAndSubstitution,
        std::string &inputString) {
  //token, substitution, current matcthing index, has matched
  std::vector<std::tuple<std::string, std::string, size_t, bool>>
      tokens;
  std::string outputString = "";
  //size of active tokens
  size_t size = tokenAndSubstitution.size();
  //current starting point of matching
  size_t start = 0;

  std::pair<std::string, std::string> lastMatch =
      std::make_pair("", "");

  //load tokens
  for (auto &tokenPair : tokenAndSubstitution) {
    tokens.emplace_back(tokenPair.first, tokenPair.second, 0, 0);
  }

  for (size_t i = 0; i <= inputString.size(); i++) {
    lastMatch = std::make_pair("", "");
    //for each token in the 'virtual' vector [active1, active2 ... activek | inactivek+1 ... inactiveN]
    for (size_t j = 0; j < size; j++) {
      auto &token = tokens[j];
      if (i < inputString.size() /*end of inputstring*/ &&
          std::get<2>(token) <
              std::get<0>(token).size() && /*end of token*/
          std::get<0>(token)[std::get<2>(token)] ==
              inputString[i] /*char matches*/) {
        //increase internal index of token
        std::get<2>(token)++;
        //if token is fully matched
        if (std::get<2>(token) == std::get<0>(token).size()) {
          std::get<3>(token) = 1;
        }
      } else {
        //the token does not match

        //if the token was fully matched
        if (std::get<3>(token)) {
          //save the last fully matched token
          lastMatch =
              std::make_pair(std::get<0>(token), std::get<1>(token));
        }
        //move unmatched token to the end of the vector
        std::swap(tokens[j], tokens[size - 1]);
        //decrease size of the 'virtual' vector
        size--;
        //decrease index to check the swapped token
        j--;
      }
    }

    //if all tokens did not match on this char
    if (size == 0) {
      if (lastMatch.first != "") {
        //one token fully matched
        //replace the token
        outputString += lastMatch.second;
        //move index back as the last matched token is observed after the last matched char
        i--;
      } else {
        //no tokens fully matched
        outputString += inputString.substr(start, i - start + 1);
      }

      //new start is set after the token that was replaced
      start = i + 1;

      //reset the list of tokens : all tokens become active
      for (auto &token : tokens) {
        std::get<2>(token) = 0;
        std::get<3>(token) = 0;
      }
      size = tokenAndSubstitution.size();
    }
  }

  //return
  inputString = outputString;
}

///replace all occurences of a string with a set of strings (tokens)
inline void replace(const std::string &from, const std::string &to,
                    std::string &inputString) {
  std::vector<std::pair<std::string, std::string>>
      tokenAndSubstitutionVec;
  tokenAndSubstitutionVec.emplace_back(from, to);
  replace(tokenAndSubstitutionVec, inputString);
}

///replace all occurences of a string with a set of strings (tokens)
inline void replace(const std::unordered_map<std::string, std::string>
                        &tokenAndSubstitutionMap,
                    std::string &inputString) {
  std::vector<std::pair<std::string, std::string>>
      tokenAndSubstitutionVec;
  for (auto &pair : tokenAndSubstitutionMap) {
    tokenAndSubstitutionVec.emplace_back(pair.first, pair.second);
  }
  replace(tokenAndSubstitutionVec, inputString);
}

// Function to escape reserved characters in a regex pattern
inline std::string escapeRegex(const std::string &pattern) {
  // Characters that need to be escaped in a regex pattern
  const std::string reservedChars = ".^$|()[]{}*+?\\";

  std::string escapedPattern;

  for (char ch : pattern) {
    if (reservedChars.find(ch) != std::string::npos) {
      // Escape the reserved character
      escapedPattern += "\\";
    }

    escapedPattern += ch;
  }

  return escapedPattern;
}

///count occurences of a substring in a string
size_t inline countOccurences(const std::string &str,
                              const std::string &sub) {
  if (sub.length() == 0)
    return 0;
  int count = 0;
  for (size_t offset = str.find(sub); offset != std::string::npos;
       offset = str.find(sub, offset + sub.length())) {
    ++count;
  }
  return count;
}

inline bool isInteger(const std::string &s) {
  char *p;
  strtol(s.c_str(), &p, 10);
  return *p == 0;
}

inline bool isPositiveInteger(const std::string &s) {
  char *p;
  auto res = strtol(s.c_str(), &p, 10);
  return *p == 0 && res >= 0;
}
inline bool isFloat(const std::string &s) {
  char *p;
  strtof(s.c_str(), &p);
  return *p == 0;
}
///dirty implementation of timer, can be used to measure time between two calls of the same timer
///id is the name of the timer
///start_stop is 1 if the timer should be started, 0 if the timer should be stopped
///if start_stop is 0, the function returns the time in seconds since the timer was started
inline size_t dirtyTimerSeconds(std::string id, bool start_stop) {
  static std::unordered_map<std::string,
                            std::chrono::steady_clock::time_point>
      idToStart;
  if (start_stop) {
    idToStart[id] = std::chrono::steady_clock::now();
    return -1;
  } else {
    messageErrorIf(!idToStart.count(id),
                   "Use of undefined timer '" + id + "'");
    return std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::steady_clock::now() - idToStart.at(id))
        .count();
  }
}
///check if the timer is timed out
inline bool isTimeOutSeconds(std::string id, size_t time) {
  return dirtyTimerSeconds(id, 0) >= time;
}

inline size_t dirtyTimerMilliseconds(std::string id,
                                     bool start_stop) {
  static std::unordered_map<std::string,
                            std::chrono::steady_clock::time_point>
      idToStart;
  if (start_stop) {
    idToStart[id] = std::chrono::steady_clock::now();
    return -1;
  } else {
    messageErrorIf(!idToStart.count(id),
                   "Use of undefined timer '" + id + "'");
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - idToStart.at(id))
        .count();
  }
}

inline bool isTimeOutMilliseconds(std::string id, size_t time) {
  return dirtyTimerMilliseconds(id, 0) >= time;
}

inline size_t dirtyTimerMicroseconds(std::string id,
                                     bool start_stop) {
  static std::unordered_map<std::string,
                            std::chrono::steady_clock::time_point>
      idToStart;
  if (start_stop) {
    idToStart[id] = std::chrono::steady_clock::now();
    return -1;
  } else {
    messageErrorIf(!idToStart.count(id),
                   "Use of undefined timer '" + id + "'");
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::steady_clock::now() - idToStart.at(id))
        .count();
  }
}

inline bool isTimeOutMicroseconds(std::string id, size_t time) {
  return dirtyTimerMicroseconds(id, 0) >= time;
}

///extract bits from an integer
template <typename T>
inline T extractBits(T num, size_t lower_bound, size_t upper_bound) {
  // Create a mask to clear all bits except those in the range [lower_bound:upper_bound]
  T mask = (T(1) << (upper_bound - lower_bound + 1)) - T(1);

  // Shift the mask to the lower_bound by 'lower_bound' positions to align it with the range
  mask <<= lower_bound;

  // Apply the mask to 'num' to extract the desired bits
  T result = (num & mask) >> lower_bound;

  return result;
}

inline std::vector<std::string>
extractSubStringsInsideQuotes(const std::string &input) {
  std::vector<std::string> substrings;
  size_t startPos = 0;

  while (startPos < input.length()) {
    // Find the next double quote.
    size_t openQuotePos = input.find('"', startPos);

    // If no double quote is found, break.
    if (openQuotePos == std::string::npos) {
      break;
    }

    // Find the closing double quote.
    size_t closeQuotePos = input.find('"', openQuotePos + 1);

    // If no closing double quote is found, break.
    if (closeQuotePos == std::string::npos) {
      break;
    }

    // Extract the substring between the quotes.
    std::string substring =
        "\"" +
        input.substr(openQuotePos + 1,
                     closeQuotePos - openQuotePos - 1) +
        "\"";

    // Add the substring to the vector.
    substrings.push_back(substring);

    // Move the starting position to after the closing double quote.
    startPos = closeQuotePos + 1;
  }

  return substrings;
}

//parse csv string
inline std::vector<std::string> parseCSV(const std::string &input) {
  std::vector<std::string> output;

  try {
    std::string token;
    std::istringstream tokenStream(input);
    while (std::getline(tokenStream, token, ',')) {
      removeSpacesInPlace(token);
      output.push_back(token);
    }
  } catch (std::exception &e) {
    messageError("Error while parsing comma separated string: " +
                 std::string(e.what()));
  }
  return output;
}

inline bool isBase2(std::string binary) {
  return binary.find_first_not_of("01xzXZ") == std::string::npos;
}

inline void removeDoubleQuotes(std::string &str) {
  str.erase(std::remove_if(str.begin(), str.end(),
                           [](char c) { return c == '"'; }),
            str.end());
}

inline bool isFileEmpty(const std::string &filename) {
  std::ifstream file(filename);
  return file.peek() == std::ifstream::traits_type::eof();
}

inline void deleteLastLine(const std::string &filename) {
  // Open the file for reading
  std::ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    messageError("Error opening file: " + filename);
    return;
  }

  // Read all lines into a vector
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inputFile, line)) {
    lines.push_back(line);
  }

  // Close the input file
  inputFile.close();

  // Open the file for writing
  std::ofstream outputFile(filename);
  if (!outputFile.is_open()) {
    messageError("Error opening file for writing: " + filename);
    return;
  }

  // Write all lines except the last one to the output file
  for (size_t i = 0; i < lines.size() - 1; ++i) {
    outputFile << lines[i] << std::endl;
  }

  // Close the output file
  outputFile.close();
}

inline std::vector<std::string>
splitString(const std::string &s, const std::string &delimiter) {
  std::vector<std::string> parts;
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;

  while ((pos_end = s.find(delimiter, pos_start)) !=
         std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    parts.push_back(token);
  }

  parts.push_back(s.substr(pos_start));
  return parts;
}

