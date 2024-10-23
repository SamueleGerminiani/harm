#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <string>
#include <utility>

#include "DTAnd.hh"
#include "DTNCReps.hh"
#include "DTNext.hh"
#include "DTNextAnd.hh"
#include "DTOperator.hh"
#include "EdgeProposition.hh"
#include "Location.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "Trinary.hh"
#include "expUtils/ExpType.hh"

#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/expression/GenericExpression.hh"
#include "fort.h"
#include "fort.hpp"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "misc.hh"

namespace harm {

TemplateImplication::TemplateImplication(
    const TemporalExpressionPtr &templateFormula,
    const TracePtr &trace, const DTLimits &limits)
    : _templateFormula(templateFormula), _limits(limits),
      _trace(trace) {

  build();
}

TemplateImplication::TemplateImplication(
    const TemplateImplication &original) {

  _templateFormula = copy(original._templateFormula);
  _trace = original._trace;
  _limits = original._limits;
  _check = original._check;

  ////rebuild the template
  build();

  ////copy the domains
  _phToIdsDomain = original._phToIdsDomain;
  _phToPropDomain = original._phToPropDomain;
  _numericsDT = original._numericsDT;
  _propsDT = original._propsDT;

  //copy the permutator
  _permutator = original._permutator;
  //reset the perm index
  _permIndex = 0;
}

TemplateImplication::~TemplateImplication() {}

size_t TemplateImplication::getNumberOfPermutations() const {
  return _permutator._permMatrix->_nRows;
}

std::string TemplateImplication::getAssertionStr(Language lang) {
  lang = (lang == Language::Unset) ? clc::outputLang : lang;
  return temp2String(_templateFormula, lang, PrintMode::ShowAll);
}
std::string
TemplateImplication::getColoredAssertionStr(Language lang) {
  lang = (lang == Language::Unset) ? clc::outputLang : lang;
  return temp2ColoredString(_templateFormula, lang,
                            PrintMode::ShowAll);
}
std::string TemplateImplication::getTemplateStr(Language lang) {
  lang = (lang == Language::Unset) ? clc::outputLang : lang;
  return temp2String(_templateFormula, lang,
                     PrintMode::ShowOnlyPermuationPlaceholders);
}
std::string
TemplateImplication::getColoredTemplateStr(Language lang) {
  lang = (lang == Language::Unset) ? clc::outputLang : lang;
  return temp2ColoredString(
      _templateFormula, lang,
      PrintMode::ShowOnlyPermuationPlaceholders);
}

DTOperatorPtr TemplateImplication::getDT() { return _dtOp; }
bool TemplateImplication::containsDT() { return _dtOp != nullptr; }

std::map<std::string, PropositionPtrPtr> &
TemplateImplication::get_aphToPP() {
  return _aphToPP;
}
std::map<std::string, PropositionPtrPtr> &
TemplateImplication::get_cphToPP() {
  return _cphToPP;
}
std::map<std::string, PropositionPtrPtr> &
TemplateImplication::get_acphToPP() {
  return _acphToPP;
}

std::string
TemplateImplication::getTemplateWithHiddenTokensStr(Language lang) {
  lang = (lang == Language::Unset) ? clc::outputLang : lang;
  return temp2String(_templateFormula, lang, PrintMode::Hide);
}

void TemplateImplication::nextPerm() {
  loadPerm(_permIndex);
  _permIndex++;
}

void TemplateImplication::loadPerm(size_t n) {

  if (getNumPlaceholders() == 0) {
    messageErrorIf(n != 0, "Perm not available!");
    //no permutations to load
    return;
  }

  messageErrorIf(
      _permIndex < 0,
      "No permutations available, did you forget to generate them?");

  if (n >= _permutator._permMatrix->_nRows) {
    messageError("Requested permutation index is out of range: " +
                 std::to_string(n) + " >= " +
                 std::to_string(_permutator._permMatrix->_nRows));
  }

  // load the nth permutation
  _antEvaluator->invalidateCache();
  _conEvaluator->invalidateCache();
  if (_contains_mma) {
    _impEvaluator->invalidateCache();
  }

  for (auto &[ph, index] : _permutator._phToIndex) {
    harm::Location where = getPlaceholderLocation(ph);
    //ph is the string representation of a placeholder index is the column of the permutation's table _permIndex is the row of the permutation's table

    if (where == harm::Location::Ant) {
      //feel the placeholder with the correct proposition _permutator._permMatrix->_matrix[_permIndex][e.second] contains the index of the proposition to be inserted
      (*_aphToPP.at(ph)) = _phToPropDomain.at(
          ph)[_permutator._permMatrix->_matrix[n][index]];
    } else if (where == harm::Location::Con) {
      (*_cphToPP.at(ph)) = _phToPropDomain.at(
          ph)[_permutator._permMatrix->_matrix[n][index]];
      (*_cphToPP.at(ph)) = _phToPropDomain.at(
          ph)[_permutator._permMatrix->_matrix[n][index]];
    } else if (where == harm::Location::AntCon) {
      (*_acphToPP.at(ph)) = _phToPropDomain.at(
          ph)[_permutator._permMatrix->_matrix[n][index]];
    } else {
      messageError("Unknown placeholder location");
    }
  }
  _permIndex = n;
}

size_t TemplateImplication::getNumPlaceholders(harm::Location where) {
  if (where == harm::Location::Ant) {
    return _aphToPP.size();
  } else if (where == harm::Location::Con) {
    return _cphToPP.size();
  } else {
    return _acphToPP.size();
  }
}

size_t TemplateImplication::getNumPlaceholders() {
  return _aphToPP.size() + _cphToPP.size() + _acphToPP.size();
}

void TemplateImplication::fillContingency(size_t (&ct)[3][3],
                                          bool offset) {
  //  //reset the contingency table
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      ct[i][j] = 0;
    }
  }

  // make sure the cached values are initialized
  evaluate(0);

  if (offset) {
    //ant -> !con

    for (size_t time = 0; time < _trace->getLength(); time++) {
      auto [ant, antShift] = _antEvaluator->evaluate(time);
      size_t shift =
          time + (_applyDynamicShift ? antShift : 0) + _constShift;
      auto [conValue, conShift] = _conEvaluator->evaluate(shift);
      auto con =
          (shift >= _trace->getLength()) ? Trinary::U : conValue;
      if (ant == Trinary::T && (!con) == Trinary::T) {
        if (!_contains_mma) {
          ct[0][0]++;
        } else {
          if (evaluateOffset(time) == Trinary::T ||
              evaluateOffset(time) == Trinary::U) {
            ct[0][0]++;
          } else if (evaluateOffset(time) == Trinary::F) {
            ct[0][1]++;
          }
        }
      } else if (ant == Trinary::T && (!con) == Trinary::F) {
        ct[0][1]++;
      } else if (ant == Trinary::T && (!con) == Trinary::U) {
        ct[0][2]++;
      } else if (ant == Trinary::F && (!con) == Trinary::T) {
        ct[1][0]++;
      } else if (ant == Trinary::F && (!con) == Trinary::F) {
        ct[1][1]++;
      } else if (ant == Trinary::F && (!con) == Trinary::U) {
        ct[1][2]++;
      } else if (ant == Trinary::U && (!con) == Trinary::T) {
        ct[2][0]++;
      } else if (ant == Trinary::U && (!con) == Trinary::F) {
        ct[2][1]++;
      } else if (ant == Trinary::U && (!con) == Trinary::U) {
        ct[2][2]++;
      }
    }
  } else {
    //ant -> con

    for (size_t time = 0; time < _trace->getLength(); time++) {
      auto [ant, antShift] = _antEvaluator->evaluate(time);
      size_t shift =
          time + (_applyDynamicShift ? antShift : 0) + _constShift;
      auto [conValue, conShift] = _conEvaluator->evaluate(shift);
      auto con =
          (shift >= _trace->getLength()) ? Trinary::U : conValue;
      if (ant == Trinary::T && con == Trinary::T) {
        if (!_contains_mma) {
          ct[0][0]++;
        } else {
          if (evaluate(time) == Trinary::T ||
              //this is to cover the case where the antecedent is true but the implication can't stronly hold
              evaluate(time) == Trinary::U) {
            ct[0][0]++;
          } else if (evaluate(time) == Trinary::F) {
            ct[0][1]++;
          }
        }
      } else if (ant == Trinary::T && con == Trinary::F) {
        ct[0][1]++;
      } else if (ant == Trinary::T && con == Trinary::U) {
        ct[0][2]++;
      } else if (ant == Trinary::F && con == Trinary::T) {
        ct[1][0]++;
      } else if (ant == Trinary::F && con == Trinary::F) {
        ct[1][1]++;
      } else if (ant == Trinary::F && con == Trinary::U) {
        ct[1][2]++;
      } else if (ant == Trinary::U && con == Trinary::T) {
        ct[2][0]++;
      } else if (ant == Trinary::U && con == Trinary::F) {
        ct[2][1]++;
      } else if (ant == Trinary::U && con == Trinary::U) {
        ct[2][2]++;
      }
    }
  }
}

void TemplateImplication::setCacheAntFalse() {
  _antEvaluator->invalidateCache();
  if (_contains_mma) {
    _impEvaluator->invalidateCache();
  }
}

void TemplateImplication::setCacheConFalse() {
  _conEvaluator->invalidateCache();
  if (_contains_mma) {
    _impEvaluator->invalidateCache();
  }
}

void TemplateImplication::build() {

  // clear utility variables
  _aphToPP.clear();
  _acphToPP.clear();
  _cphToPP.clear();
  _iToProp.clear();
  _tokenToFun.clear();
  _dtOp = nullptr;
  _constShift = 0;
  _applyDynamicShift = 0;
  _phToPropDomain.clear();
  _contains_mma = isMultipleMatch(_templateFormula);

  // retrieve the different parts of the assertion
  messageErrorIf(std::dynamic_pointer_cast<PropertyAlways>(
                     _templateFormula) == nullptr,
                 "The template must start with an always operator");
  const PropertyImplicationPtr fimpl =
      std::dynamic_pointer_cast<PropertyImplication>(
          _templateFormula->getItems()[0]);
  messageErrorIf(fimpl == nullptr,
                 "The template must contain an implication");
  const TemporalExpressionPtr fant = getAntecedent(fimpl);
  const TemporalExpressionPtr fcon = getConsequent(fimpl);

  _constShift =
      (size_t)(!fimpl->isOverlapping() && fimpl->isMMImplication());
  _applyDynamicShift = fimpl->isMMImplication();

  // fill utility variables for the antecedent
  traverse(fant, [&](const TemporalExpressionPtr &current) {
    if (isPermutationPlaceholder(current)) {
      BooleanLayerPermutationPlaceholderPtr p =
          std::dynamic_pointer_cast<
              BooleanLayerPermutationPlaceholder>(current);
      _aphToPP.insert({{p->getToken(), p->getPlaceholderPointer()}});
      _phToPropDomain[p->getToken()];
      return true;
    } else if (isInst(current)) {
      BooleanLayerInstPtr i =
          std::dynamic_pointer_cast<BooleanLayerInst>(current);
      _iToProp[i->getToken()] = i->getProposition();
      return true;
    }
    //visit the subexpressions
    return false;
  });

  // fill utility variables for the consequent
  traverse(fcon, [&](const TemporalExpressionPtr &current) {
    if (isPermutationPlaceholder(current)) {
      BooleanLayerPermutationPlaceholderPtr p =
          std::dynamic_pointer_cast<
              BooleanLayerPermutationPlaceholder>(current);
      if (_aphToPP.count(p->getToken())) {
        // if a placeholder is found in both the antecedent and consequent than it is of type 'ac'
        _aphToPP.erase(p->getToken());
        _acphToPP.insert(
            {{p->getToken(), p->getPlaceholderPointer()}});
      } else {
        //otherwise it is of type 'c'
        _cphToPP.insert(
            {{p->getToken(), p->getPlaceholderPointer()}});
      }
      //initialize the domain of the placeholder
      _phToPropDomain[p->getToken()];
      return true;
    } else if (isInst(current)) {
      BooleanLayerInstPtr i =
          std::dynamic_pointer_cast<BooleanLayerInst>(current);
      _iToProp[i->getToken()] = i->getProposition();
      return true;
    }
    //visit the subexpressions
    return false;
  });

  if (containsDTO(_templateFormula)) {
    //evaluators handled by the DTOperator
    switch (_limits._dto_param._type) {
    case harm::DTO_Type::Next:
      _dtOp = generatePtr<DTNext>(this);
      break;
    case harm::DTO_Type::NextAnd:
      _dtOp = generatePtr<DTNextAnd>(this);
      break;
    case harm::DTO_Type::NCReps:
      _dtOp = generatePtr<DTNCReps>(this);
      break;
    case harm::DTO_Type::GoTo:
      _dtOp = generatePtr<DTNCReps>(this);
      break;
    case harm::DTO_Type::And:
      _dtOp = generatePtr<DTAnd>(this);
      break;
    default:
      messageError("DTO_Type not supported");
    }
  } else {
    //evaluators handled by the TemplateImplication
    _antEvaluator = generateEvaluator(fant, _trace);
    if (_contains_mma) {
      _impEvaluator = generateEvaluator(fimpl, _trace);
    }
  }

  _conEvaluator = generateEvaluator(fcon, _trace);

  //retrieve the depth of the formulas
  _antDepth = getTemporalDepth(fant);
  _conDepth = getTemporalDepth(fcon);
}

void TemplateImplication::genPermutations(
    const std::unordered_map<int,
                             std::vector<expression::PropositionPtr>>
        &domainIdToProps,
    const std::unordered_map<
        int, std::vector<expression::NumericExpressionPtr>>
        &domainIdToNumerics) {
  //debug
  //print domainIdToProps
  //for (auto &[id, props] : domainIdToProps) {
  //  std::cout << "domainIdToProps[" << id << "] = ";
  //  for (auto &p : props) {
  //    std::cout << prop2String(p) << " ";
  //  }
  //  std::cout << std::endl;
  //}
  ////print domainIdToNumerics
  //for (auto &[id, numerics] : domainIdToNumerics) {
  //  std::cout << "domainIdToNumerics[" << id << "] = ";
  //  for (auto &n : numerics) {
  //    std::cout << num2String(n) << " ";
  //  }
  //  std::cout << std::endl;
  //}

  //clear the current domain
  for (auto &[ph, domain] : _phToPropDomain) {
    domain.clear();
  }

  // load the domains of the placeholders
  for (auto &[ph, ids] : _phToIdsDomain) {
    if (ph == "DT") {
      //DT is a special case handled later
      continue;
    }
    if (ids.empty()) {
      //global domain
      if (domainIdToProps.count((int)Location::Ant) &&
          _aphToPP.count(ph)) {
        _phToPropDomain.at(ph).insert(
            _phToPropDomain.at(ph).end(),
            domainIdToProps.at((int)Location::Ant).begin(),
            domainIdToProps.at((int)Location::Ant).end());
      } else if (domainIdToProps.count((int)Location::Con) &&
                 _cphToPP.count(ph)) {
        _phToPropDomain.at(ph).insert(
            _phToPropDomain.at(ph).end(),
            domainIdToProps.at((int)Location::Con).begin(),
            domainIdToProps.at((int)Location::Con).end());
      } else if (domainIdToProps.count((int)Location::AntCon) &&
                 _acphToPP.count(ph)) {
        _phToPropDomain.at(ph).insert(
            _phToPropDomain.at(ph).end(),
            domainIdToProps.at((int)Location::AntCon).begin(),
            domainIdToProps.at((int)Location::AntCon).end());
      } else if (domainIdToProps.count((int)Location::DecTree)) {
        _propsDT.insert(
            _propsDT.end(),
            domainIdToProps.at((int)Location::DecTree).begin(),
            domainIdToProps.at((int)Location::DecTree).end());
      }
    } else {
      //restricted domain
      for (auto id : ids) {
        messageErrorIf(!domainIdToProps.count(id) ||
                           domainIdToProps.at(id).empty(),
                       "Placeholder domain '" + std::to_string(id) +
                           "' is not defined!");
        messageErrorIf(!_phToPropDomain.count(ph),
                       "Placeholder '" + ph +
                           "' is not defined in the template!");
        for (auto p : domainIdToProps.at(id)) {
          _phToPropDomain.at(ph).push_back(p);
        }
      }
    }
  }

  //clear the current domain
  _numericsDT.clear();
  _propsDT.clear();

  if (_dtOp != nullptr) {
    messageErrorIf(!_phToIdsDomain.count("DT"),
                   "DT placeholder domain not set!");
    if (_phToIdsDomain.at("DT").empty()) {
      //propositions
      if (domainIdToProps.count((int)Location::DecTree)) {
        _propsDT.insert(
            _propsDT.end(),
            domainIdToProps.at((int)Location::DecTree).begin(),
            domainIdToProps.at((int)Location::DecTree).end());
      }

      //numerics
      if (domainIdToNumerics.count((int)Location::DecTree)) {
        _numericsDT.insert(
            _numericsDT.end(),
            domainIdToNumerics.at((int)Location::DecTree).begin(),
            domainIdToNumerics.at((int)Location::DecTree).end());
      }

    } else {
      //restricted domain

      //for now domains can only be of size 1
      auto &domains = _phToIdsDomain.at("DT");

      for (auto &id : domains) {
        messageErrorIf(!domainIdToNumerics.count(id) &&
                           !domainIdToProps.count(id),
                       "DT Placeholder domain '" +
                           std::to_string(id) + "' is not defined!");
        //propositions
        if (domainIdToProps.count(id)) {
          for (auto p : domainIdToProps.at(id)) {
            _propsDT.push_back(p);
          }
        }

        //numerics
        if (domainIdToNumerics.count(id)) {
          for (auto n : domainIdToNumerics.at(id)) {
            _numericsDT.push_back(n);
          }
        }
      }
    }

    messageErrorIf(_numericsDT.empty() && _propsDT.empty(),
                   "DT placeholder domain is empty!");
  }

  for (auto &[ph, props] : _phToPropDomain) {
    messageErrorIf(props.empty(),
                   "Not enough propositions for placeholder '" + ph +
                       "'");
  }

  //generate only if there are not any previously generated perms
  if (_permutator._permMatrix == nullptr &&
      (getNumPlaceholders() > 0 || containsDT())) {
    _permutator.genPermutations(_phToPropDomain, _templateFormula);
  }

  //set index to the first perm
  _permIndex = 0;
}

void TemplateImplication::printContingency() {
  size_t ct[3][3] = {{0}};
  fillContingency(ct, 0);
  fort::utf8_table table;
  table.set_border_style(FT_NICE_STYLE);
  ft_set_cell_span(table.getTablePointer(), 0, 0, 4);
  table.column(1).set_cell_text_align(fort::text_align::center);
  table.column(2).set_cell_text_align(fort::text_align::center);
  table.column(3).set_cell_text_align(fort::text_align::center);
  table.column(4).set_cell_text_align(fort::text_align::center);

  table << fort::header << "Contingency" << fort::endr;

  table << ""
        << "CT"
        << "CF"
        << "CU" << fort::endr;
  ft_add_separator(table.getTablePointer());
  table << "AT" << ct[0][0] << ct[0][1] << ct[0][2] << fort::endr;
  ft_add_separator(table.getTablePointer());
  table << "AF" << ct[1][0] << ct[1][1] << ct[1][2] << fort::endr;
  ft_add_separator(table.getTablePointer());
  table << "AU" << ct[2][0] << ct[2][1] << ct[2][2] << fort::endr;
  std::cout << table.to_string() << std::endl;
}
void TemplateImplication::check() {
  messageErrorIf(
      !isFullyInstantiated(),
      "Checking is available only for fully instantiated templates "
      "(assertions)");
  std::cout << "====================================================="
               "=========="
               "==========="
            << "\n";
  //evaluate the assertion
  setCacheAntFalse();
  setCacheConFalse();
  evaluate(0);

  //init the contingency table
  size_t ct[3][3] = {{0}};
  fillContingency(ct, 0);

  std::cout << getColoredAssertionStr() << "\n";

  if (!assHoldsOnTrace(harm::Location::AntCon)) {
    std::cout << GLOB("Assertion fails") << "\n";
    printContingency();
    std::vector<std::string> sorted;

    size_t maxSubtracesToPrint = 3;
    std::cout << "Failing sub-traces (top " +
                     std::to_string(maxSubtracesToPrint) + "):\n";

    for (size_t i = 0; i < _trace->getLength(); i++) {
      if (evaluate(i) == Trinary::F) {
        std::cout << "===================================="
                  << "\n";
        size_t counterExampleEnd = 0;
        if (!_contains_mma) {
          auto [antValue, antShift] = _antEvaluator->evaluate(i);
          auto [conValue, conShift] =
              _conEvaluator->evaluate(i + antShift + _constShift);
          counterExampleEnd = i + antShift + _constShift + conShift;
        } else {
          counterExampleEnd = i + _impEvaluator->evaluate(i).second;
        }

        std::cout << "[" << i << "," << counterExampleEnd << "]"
                  << "\n";
        std::cout << _trace->printTrace(i,
                                        (counterExampleEnd - i) + 1)
                  << "\n";
        std::cout << "===================================="
                  << "\n";
        if (--maxSubtracesToPrint == 0) {
          break;
        }
      }
    }
  } else {
    printContingency();
    char reasonVac[100];
    if (isVacuous(harm::Location::AntCon, reasonVac)) {
      std::cout << TIMPL("Assertion is vacuous: " +
                         std::string(reasonVac))
                << "\n";
    } else {
      std::cout << BOOL("Assertion holds") << "\n";
    }
  }

  {
    size_t maxPrintableTrace = 30;
    messageWarningIf(_trace->getLength() > maxPrintableTrace,
                     "Printing only the first " +
                         std::to_string(maxPrintableTrace) +
                         " elements");
    messageWarningIf(
        _contains_mma,
        "The assertion contains multiple matches operators in the "
        "antecedent, the shift refers only to the first match");
    std::cout << "Ant: ";
    for (size_t i = 0;
         i < std::min(maxPrintableTrace, _trace->getLength()); i++) {
      std::cout << evaluate_ant(i) << "(" << i << ")"
                << " ";
    }

    if (_applyDynamicShift || _constShift > 0) {
      std::cout << "\n";
      std::cout << "\n";
      std::cout << "Sft: ";
      for (size_t i = 0;
           i < std::min(maxPrintableTrace, _trace->getLength());
           i++) {
        auto [antValue, antShift] = _antEvaluator->evaluate(i);
        size_t shift = antShift + _constShift;
        std::cout << shift << "(" << i << ")"
                  << " ";
      }
    }
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "Con: ";
    for (size_t i = 0;
         i < std::min(maxPrintableTrace, _trace->getLength()); i++) {
      std::cout << evaluate_con(i) << "(" << i << ")"
                << " ";
    }
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Ass: ";
    for (size_t i = 0;
         i < std::min(maxPrintableTrace, _trace->getLength()); i++) {
      std::cout << evaluate(i) << "(" << i << ")"
                << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
  std::cout << "====================================================="
               "=========="
               "==========="
            << "\n";
}
const TemporalExpressionPtr &
TemplateImplication::getTemplateFormula() {
  return _templateFormula;
}

std::vector<std::pair<std::string, std::pair<ExpType, size_t>>>
TemplateImplication::getVars() {
  std::vector<std::pair<std::string, std::pair<ExpType, size_t>>>
      vars;
  std::vector<PropositionPtr> loadedProps = getLoadedPropositions();

  for (const PropositionPtr &p : loadedProps) {
    for (auto &var : expression::getVars(p)) {
      vars.push_back(var);
    }
  }

  return vars;
}

std::vector<PropositionPtr>
TemplateImplication::getLoadedPropositions() {
  std::vector<PropositionPtr> ret;
  auto antProps = getLoadedPropositionsAnt();
  ret.insert(ret.end(), antProps.begin(), antProps.end());
  auto conProps = getLoadedPropositionsCon();
  ret.insert(ret.end(), conProps.begin(), conProps.end());

  return ret;
}
std::vector<PropositionPtr>
TemplateImplication::getLoadedPropositionsAnt() {
  std::vector<PropositionPtr> ret;
  const TemporalExpressionPtr &ant =
      _templateFormula->getItems()[0]->getItems()[0];

  traverse(ant, [&](const TemporalExpressionPtr &current) {
    if (isPermutationPlaceholder(current)) {
      BooleanLayerPermutationPlaceholderPtr p =
          std::dynamic_pointer_cast<
              BooleanLayerPermutationPlaceholder>(current);

      assert(p->getPlaceholderPointer() != nullptr);
      ret.push_back(*p->getPlaceholderPointer());
      return true;
    } else if (isInst(current)) {
      BooleanLayerInstPtr i =
          std::dynamic_pointer_cast<BooleanLayerInst>(current);
      assert(i->getProposition() != nullptr);
      ret.push_back(i->getProposition());
      return true;
    }
    return false;
  });
  if (containsDT()) {
    auto dtProps = _dtOp->getItems();
    ret.insert(ret.end(), dtProps.begin(), dtProps.end());
  }
  return ret;
}
std::vector<PropositionPtr>
TemplateImplication::getLoadedPropositionsCon() {
  std::vector<PropositionPtr> ret;
  const TemporalExpressionPtr &con =
      _templateFormula->getItems()[0]->getItems()[1];
  traverse(con, [&](const TemporalExpressionPtr &current) {
    if (isPermutationPlaceholder(current)) {
      BooleanLayerPermutationPlaceholderPtr p =
          std::dynamic_pointer_cast<
              BooleanLayerPermutationPlaceholder>(current);

      assert(p->getPlaceholderPointer() != nullptr);
      ret.push_back(*p->getPlaceholderPointer());
      return true;
    } else if (isInst(current)) {
      BooleanLayerInstPtr i =
          std::dynamic_pointer_cast<BooleanLayerInst>(current);
      assert(i->getProposition() != nullptr);
      ret.push_back(i->getProposition());
      return true;
    }
    return false;
  });
  return ret;
}
void TemplateImplication::setL1Threads(size_t n) {
  _conEvaluator->setL1Threads(n);

  if (containsDT()) {
    _dtOp->setL1Threads(n);
  } else {
    _antEvaluator->setL1Threads(n);
    if (_contains_mma) {
      _impEvaluator->setL1Threads(n);
    }
  }
}

void TemplateImplication::setDTLimits(const DTLimits &l) {
  _limits = l;
}
bool TemplateImplication::isFullyInstantiated() {
  return getNumPlaceholders() == 0 && _dtOp == nullptr;
}

void TemplateImplication::changeTrace(const TracePtr &newTrace) {
  messageErrorIf(!isFullyInstantiated(),
                 "Trace can be changed only for fully instantiated "
                 "templates (assertions)");
  _trace = newTrace;

  _antEvaluator->changeTrace(newTrace);
  _conEvaluator->changeTrace(newTrace);
  if (_contains_mma) {
    _impEvaluator->changeTrace(newTrace);
  }
}

PropositionPtr TemplateImplication::getInst(const std::string &inst) {
  messageErrorIf(!_iToProp.count(inst),
                 "Unknown inst '" + inst + "'");
  return _iToProp.at(inst);
}

std::vector<PropositionPtr> TemplateImplication::getAllInst() {
  std::vector<PropositionPtr> res;
  for (auto &p : _iToProp) {
    res.push_back(p.second);
  }
  return res;
}
std::unordered_map<std::string, PropositionPtr>
TemplateImplication::getInstToProsition() {
  return _iToProp;
}

std::vector<expression::PropositionPtr>
TemplateImplication::getDTPropositions() {
  return _propsDT;
}

std::vector<expression::NumericExpressionPtr>
TemplateImplication::getDTNumerics() {
  return _numericsDT;
}
size_t TemplateImplication::getTraceLength() {
  return _trace->getLength();
}
bool TemplateImplication::getCheck() { return _check; }
void TemplateImplication::setCheck(bool check) { _check = check; }

void TemplateImplication::setPhIds(
    const std::unordered_map<std::string, std::unordered_set<int>>
        &phToIdsDomain) {
  _phToIdsDomain = phToIdsDomain;
}
std::unordered_map<std::string, std::unordered_set<int>>
TemplateImplication::getPhIds() {
  return _phToIdsDomain;
}

bool TemplateImplication::assHoldsOnTrace(harm::Location update) {
  switch (update) {
  case harm::Location::Ant:
    setCacheAntFalse();
    break;
  case harm::Location::Con:
    setCacheConFalse();
    break;
  case harm::Location::AntCon:
    setCacheAntFalse();
    setCacheConFalse();
    break;
  case harm::Location::None:
    break;
  default:
    messageError("Illegal use of Location operator");
    break;
  }

  for (size_t i = 0; i < _trace->getLength(); i++) {
    if (evaluate(i) == Trinary::F) {
      return false;
    }
  }
  return true;
}

bool TemplateImplication::assHoldsOnTraceOffset(
    harm::Location update) {
  switch (update) {
  case harm::Location::Ant:
    setCacheAntFalse();
    break;
  case harm::Location::Con:
    setCacheConFalse();
    break;
  case harm::Location::AntCon:
    setCacheAntFalse();
    setCacheConFalse();
    break;
  case harm::Location::None:
    break;
  default:
    messageError("Illegal use of Location operator");
    break;
  }

  for (size_t i = 0; i < _trace->getLength(); i++) {
    if (evaluateOffset(i) == Trinary::F) {
      return false;
    }
  }
  return true;
}

bool TemplateImplication::isVacuous(harm::Location update,
                                    char *cause) {
  switch (update) {
  case harm::Location::Ant:
    setCacheAntFalse();
    break;
  case harm::Location::Con:
    setCacheConFalse();
    break;
  case harm::Location::AntCon:
    setCacheAntFalse();
    setCacheConFalse();
    break;
  case harm::Location::None:
    break;
  default:
    messageError("Illegal use of Location operator");
    break;
  }

  //ATCT > 0
  for (size_t i = 0; i < _trace->getLength(); i++) {
    if (evaluate_ant(i) == Trinary::T && evaluate(i) == Trinary::T) {
      if (cause) {
        strcpy(cause, "ATCT == 0");
      }
      return false;
    }
  }
  return true;
}

bool TemplateImplication::isVacuousOffset(harm::Location update) {
  switch (update) {
  case harm::Location::Ant:
    setCacheAntFalse();
    break;
  case harm::Location::Con:
    setCacheConFalse();
    break;
  case harm::Location::AntCon:
    setCacheAntFalse();
    setCacheConFalse();
    break;
  case harm::Location::None:
    break;
  default:
    messageError("Illegal use of Location operator");
    break;
  }

  //ATCT > 0
  for (size_t i = 0; i < _trace->getLength(); i++) {
    if (evaluate_ant(i) == Trinary::T &&
        evaluateOffset(i) == Trinary::T) {
      return false;
    }
  }
  return true;
}

Trinary TemplateImplication::evaluate(size_t time) {
  if (!_contains_mma) {
    auto [antValue, antShift] = _antEvaluator->evaluate(time);
    size_t shift =
        time + (_applyDynamicShift ? antShift : 0) + _constShift;
    auto [conValue, conShift] = _conEvaluator->evaluate(shift);
    return !antValue ||
           (shift >= _trace->getLength() ? Trinary::U : conValue);
  } else {
    return _impEvaluator->evaluate(time).first;
  }
}
Trinary TemplateImplication::evaluate_ant(size_t time) {
  return _antEvaluator->evaluate(time).first;
}
Trinary TemplateImplication::evaluate_con(size_t time) {
  return _conEvaluator->evaluate(time).first;
}
Trinary TemplateImplication::evaluateOffset(size_t time) {
  if (!_contains_mma) {
    auto [antValue, antShift] = _antEvaluator->evaluate(time);
    size_t shift =
        time + (_applyDynamicShift ? antShift : 0) + _constShift;
    auto [conValue, conShift] = _conEvaluator->evaluate(shift);
    return !antValue ||
           (shift >= _trace->getLength() ? Trinary::U : !conValue);
  } else {
    return _impEvaluator->evaluate(time).first;
  }
}

Location
TemplateImplication::getPlaceholderLocation(const std::string &ph) {
  if (_aphToPP.count(ph)) {
    return harm::Location::Ant;
  } else if (_cphToPP.count(ph)) {
    return harm::Location::Con;
  } else if (_acphToPP.count(ph)) {
    return harm::Location::AntCon;
  } else if (ph == "DT") {
    return harm::Location::DecTree;
  } else {
    messageError("Unknown placeholder '" + ph + "'");
  }
  return harm::Location::None;
}

size_t TemplateImplication::getCT() {
  size_t CT = 0;
  for (size_t i = 0; i < _trace->getLength(); i++) {
    if (evaluate_con(i) == Trinary::T) {
      CT++;
    }
  }

  return CT;
}
size_t TemplateImplication::getCF() {
  size_t CF = 0;
  for (size_t i = 0; i < _trace->getLength(); i++) {
    if (evaluate_con(i) == Trinary::F) {
      CF++;
    }
  }

  return CF;
}
std::pair<size_t, size_t> TemplateImplication::getCT_CF() {
  size_t CT = 0;
  size_t CF = 0;
  for (size_t i = 0; i < _trace->getLength(); i++) {
    auto eval = evaluate_con(i);
    if (eval == Trinary::T) {
      CT++;
    } else if (eval == Trinary::F) {
      CF++;
    }
  }

  return std::make_pair(CT, CF);
}

size_t TemplateImplication::getCurrentPermIndex() {
  return _permIndex;
}
} // namespace harm
