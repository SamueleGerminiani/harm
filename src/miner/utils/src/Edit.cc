

#include <algorithm>
#include <boost/range/algorithm/count.hpp>
#include <boost/regex.hpp>
#include <boost/regex/v5/regex_match.hpp>
#include <ctype.h>
#include <istream>
#include <iterator>
#include <map>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Assertion.hh"
#include "Edit.hh"
#include "Location.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "message.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"

namespace harm {
using namespace expression;

bool toBeRemoved(const std::string assertionStr,
                 const std::vector<EditPtr> &remove,
                 const TracePtr &trace) {

  //t is the original template of the assertion being matched
  TemplateImplicationPtr t =
      hparser::parseTemplateImplication(assertionStr, trace);
  std::string hiddenAssertion = t->getTemplateWithHiddenTokensStr();
  //easier to match regexes if there are no spaces
  removeSpacesInPlace(hiddenAssertion);

  for (const auto &rule : remove) {
    if (rule->matchRemove(hiddenAssertion, t, trace)) {

      return true;
    }
  } //for remove

  //no rule matched
  return false;
}

bool rewriteAssertion(const AssertionPtr &ass,
                      const std::vector<EditPtr> &rewrite,
                      const TracePtr &trace) {

  //t is the original template of the assertion being matched
  TemplateImplicationPtr t =
      hparser::parseTemplateImplication(ass->toString(), trace);
  //strig representation of the template
  std::string hiddenAssertion = t->getTemplateWithHiddenTokensStr();
  //easier to match regexes if there are no spaces
  removeSpacesInPlace(hiddenAssertion);

  for (const auto &rule : rewrite) {
    if (rule->matchRewrite(hiddenAssertion, t, trace)) {

      //parse the rewritten assertion
      TemplateImplicationPtr newTemplate =
          hparser::parseTemplateImplication(hiddenAssertion, trace);
      messageWarningIf(
          !newTemplate->assHoldsOnTrace(harm::Location::AntCon),
          "Rewritten assertion does not hold on the trace:\n\t " +
              t->getAssertionStr() + "\nvs\n   \t" +
              newTemplate->getAssertionStr() + "\n\n");
      //update the the assertion
      fillAssertion(ass, newTemplate, 0);

      //rewrite using only the first matching rule
      return 1;
    }
  } //regex match

  return 0;
}

//Edit class----------------------------------------------

Edit::Edit(const std::string &rewrite, const std::string &to,
           const std::string &constraint)
    : _to(to) {
  build(rewrite, to, constraint);
}

Edit::Edit(const std::string &remove, const std::string &constraint) {
  build(remove, "", constraint);
}

Edit::~Edit() {}

void Edit::build(const std::string &rule, const std::string &to,
                 const std::string &constraint) {

  //handle regex
  _ruleRegex = buildRegex(rule, _varNameToType);

  std::vector<VarDeclaration> vars;
  for (auto &[var, val] : _varNameToType) {
    ExpType type = (val == "N" ? ExpType::UInt : ExpType::String);
    size_t size = (val == "N" ? 64 : 0);
    vars.emplace_back(var, type, size);
  }

  _trace = generatePtr<Trace>(vars, 1);

  if (constraint != "") {
    _constraint = hparser::parseProposition(constraint, _trace);
  }

  //only if we are in a rewrite rule
  if (_to != "") {
    _segmentedTo = segment(to);
    //check correctness of @ expressions
    for (auto &s : _segmentedTo) {
      if (s[0] == '@') {
        messageErrorIf(s.find_first_of(",") != std::string::npos,
                       "@(<type>,<var>) is not allowed in 'to': " +
                           s);
        //extract the value inside the @(<value>)
        auto value = s.substr(2, s.size() - 3);
        //check if value contains + * - or /, if so it is an arithmetic expression and will require special care
        if (value.find_first_of("+-*/") != std::string::npos) {
          //replace all numeric variables with N
          replace(_varNameToType, value);
          //check if value contains characters other than 'N' and '+-*/
          messageErrorIf(value.find_first_not_of("N+-*/0123456789") !=
                             std::string::npos,
                         "Invalid @ expression contains arithmetic "
                         "expression with non-numeric variables: " +
                             s);
        }
      }
    }
  }
}

bool Edit::matchRewrite(std::string &hiddenAssertion,
                        TemplateImplicationPtr t,
                        const TracePtr &trace) const {
  messageErrorIf(isRemove(),
                 "Trying to match a rewrite rule with a remove rule");

  std::string rewritten = "";
  //matches will contain the matches of the regex
  boost::match_results<std::string::const_iterator> matches;

  if (boost::regex_search(hiddenAssertion, matches,
                          boost::regex(_ruleRegex))) {
    messageErrorIf(matches.size() - 1 != _varNameToType.size(),
                   "Number of matches does not match number of "
                   "variables in the 'rewrite' rule: " +
                       std::to_string(matches.size()) + " vs " +
                       std::to_string(_varNameToType.size()));

    std::unordered_map<std::string, std::string> varNameToVal;

    //determine the value of the variables in the 'rewrite' part of the rule matched by the regex, store them in varNameToVal
    fillVarToVal(matches, t, varNameToVal);

    //eval the constraint with the values of the variables
    if (!evalConstraint(varNameToVal)) {
      return 0;
    }

    //eval the @(variable) in the 'to' part of the rule (if any)
    for (auto &s : _segmentedTo) {
      if (s[0] == '@') {
        auto value = s.substr(2, s.size() - 3);
        auto original = value;
        replace(varNameToVal, value);
        //check if value contains + * - /
        if (original.find_first_of("+-*/") != std::string::npos) {
          //expression must be evaluated semantically
          IntExpressionPtr le =
              hparser::parseIntExpression(value, trace);
          rewritten += std::to_string((int)le->evaluate(0));
        } else {
          //directly replace the variable
          rewritten += value;
        }
      } else {
        //non-@ part of the rule
        rewritten += s;
      }
    }

  } else {
    return 0;
  }

  //rewrite the input assertion
  hiddenAssertion = rewritten;
  return 1;
}

bool Edit::matchRemove(std::string &hiddenAssertion,
                       TemplateImplicationPtr t,
                       const TracePtr &trace) const {
  messageErrorIf(isRewrite(), "Trying to match a remove rule with a "
                              "rewrite rule, to rule is '" +
                                  _to + "'");

  //matches will contain the matches of the regex
  boost::match_results<std::string::const_iterator> matches;

  if (boost::regex_search(hiddenAssertion, matches,
                          boost::regex(_ruleRegex))) {
    messageErrorIf(matches.size() - 1 != _varNameToType.size(),
                   "Number of matches does not match number of "
                   "variables in the remove rule" +
                       std::to_string(matches.size()) + " vs " +
                       std::to_string(_varNameToType.size()));

    std::unordered_map<std::string, std::string> varToVal;
    //determine the value of the variables in the 'remove' part of the rule matched by the regex
    fillVarToVal(matches, t, varToVal);

    //eval the constraint with the values of the variables
    if (evalConstraint(varToVal)) {
      return true;
    }
  }

  return false;
}

bool Edit::evalConstraint(
    const std::unordered_map<std::string, std::string> &varToValue)
    const {
  //if there is no constraint, the constraint is assumed to be true
  if (_constraint == nullptr) {
    return true;
  }

  for (auto &[var, type] : _varNameToType) {
    if (type == "N") {
      //numeric variables are converted to uint64_t to allow arithmetic operations
      auto v = _trace->getIntVariable(var);
      v->assign(0, safeStoull(varToValue.at(var)));
    } else {
      //all other variables are converted to strings
      auto v = _trace->getStringVariable(var);
      v->assign(0, varToValue.at(var));
    }
  }

  return _constraint->evaluate(0);
}

std::pair<std::string, std::string>
Edit::splitStore(const std::string &content) {

  std::string part1, part2;

  // Split the content into two parts using a comma
  std::istringstream iss(content);
  if (std::getline(iss, part1, ',') && std::getline(iss, part2)) {
    return std::make_pair(part1, part2);
  } else {
    messageError(
        "Content inside @( ...) cannot be split into two parts.");
  }
  return std::make_pair("", "");
}

std::vector<std::string> Edit::segment(const std::string &input) {
  size_t startPos = 0;
  std::vector<std::string> contentVector;
  //remove all spaces and tabs
  auto copy = input;
  copy.erase(std::remove_if(copy.begin(), copy.end(), ::isspace),
             copy.end());

  while (1) {
    // Find the next occurrence of "@("
    size_t atIndex = copy.find("@(", startPos);
    if (atIndex == std::string::npos) {
      if (startPos + 1 <= copy.size()) {
        //add the last part of the string
        contentVector.push_back(copy.substr(startPos));
      }
      // No more occurrences found
      break;
    }

    //add to content vector the text before the @(
    contentVector.push_back(
        copy.substr(startPos, atIndex - startPos));

    // Find the matching closing ")"
    size_t closingIndex = copy.find(")", atIndex);
    messageErrorIf(closingIndex == std::string::npos,
                   "Error: Unmatched ') after '@('");

    // Extract the content "@(..)" and store it in the vector
    contentVector.push_back(
        copy.substr(atIndex, closingIndex - atIndex + 1));

    // Update the start position to the character after the closing ")"
    startPos = closingIndex + 1;
  }
  return contentVector;
}

std::string Edit::buildRegex(
    const std::string &rule,
    std::vector<std::pair<std::string, std::string>> &varName_type) {

  auto segments = Edit::segment(rule);

  std::string regex = "";
  const std::string nRegex = "(?:[0-9])+";
  const std::string propRegex = "(?:_inst(?:[0-9])+)";
  const std::string dtNext =
      "(?:" + propRegex + "##" + nRegex + ")*(?:" + propRegex + ")+";

  for (const auto &seg : segments) {
    std::pair<std::string, std::string> vv;
    //handle @ expressions
    if (seg[0] == '@') {
      if (std::find(seg.begin(), seg.end(), ',') == seg.end()) {
        //@(<var>)
        vv.first = seg.substr(2, seg.size() - 3);
        varName_type.emplace_back("", vv.first);

      } else {
        //@(<type>,<var>)
        vv = splitStore(seg.substr(2, seg.size() - 3));
        varName_type.emplace_back(vv.second, vv.first);
      }

      messageErrorIf(
          vv.first != "P" && vv.first != "N" && vv.first != "..##..",
          "Type of @(<type>,<var>) expression must be P or N or "
          "..##.., found '" +
              vv.first + "'");
      //build regex according to the type
      if (vv.first == "P") {
        regex += "(" + propRegex + ")";
      } else if (vv.first == "N") {
        regex += "(" + nRegex + ")";
      } else if (vv.first == "..##..") {
        regex += "(" + dtNext + ")";
      }

    } else {
      //escape special characters
      regex += escapeRegex(seg);
    }
  }

  return regex;
}

bool Edit::isRewrite() const { return _to != ""; }

bool Edit::isRemove() const { return _to == ""; }

std::vector<std::string> Edit::cutDTNext(const std::string &dtNext) {
  std::vector<std::string> cuts;
  std::string inputString = dtNext;
  replace(std::vector<std::pair<std::string, std::string>>(
              {{"_inst", " "}, {"##", " "}}),
          inputString);
  std::istringstream iss(inputString);

  size_t pos = 0;
  while (1) {
    std::string token;
    iss >> token;

    if (!iss)
      break;

    if (pos % 2 == 0) {
      cuts.push_back("_inst" + token);
    } else {
      cuts.push_back("##" + token);
    }
    pos++;
  }
  return cuts;
}

void Edit::fillVarToVal(
    const boost::match_results<std::string::const_iterator> &matches,
    TemplateImplicationPtr t,
    std::unordered_map<std::string, std::string> &varNameToVal)
    const {

  for (size_t i = 0; i < _varNameToType.size(); i++) {
    varNameToVal[_varNameToType[i].first] = matches[i + 1];
    if (_varNameToType[i].second == "N") {
      //unsigned int var number
      //store the value of the variable
      varNameToVal[_varNameToType[i].first] = matches[i + 1];
    } else if (_varNameToType[i].second == "P") {
      //proposition
      std::string prpStr = prop2String(t->getInst(matches[i + 1]));
      removeSpacesInPlace(prpStr);
      varNameToVal[_varNameToType[i].first] = prpStr;
    } else if (_varNameToType[i].second == "..##..") {
      //sequence of nexts
      //gather _insti to proposition
      std::unordered_map<std::string, std::string> iToProp;
      for (const auto &[token, pp] : t->getInstToProsition()) {
        std::string propStr = prop2String(pp);
        removeSpacesInPlace(propStr);
        iToProp[token] = propStr;
      }

      std::string finalStr = "";
      std::string instSequence = matches[i + 1];
      //returns a sequence of numbers
      auto sequence = Edit::cutDTNext(instSequence);

      for (size_t i = 0; i < sequence.size(); i++) {
        if (i % 2 == 0) {
          //even numbers are inst_i
          finalStr += iToProp[sequence[i]];
        } else {
          //odd numbers are ##
          finalStr += sequence[i];
        }
      }

      varNameToVal[_varNameToType[i].first] = finalStr;

    } else {
      messageError(
          "Variable type '" + _varNameToType[i].second +
          "' not supported, only N, P, ..##.. are supported");
    }
  }
}
} // namespace harm
