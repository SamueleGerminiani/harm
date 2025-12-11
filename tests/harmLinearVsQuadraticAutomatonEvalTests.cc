#ifdef SPOTLTL

#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <iostream>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "AutomataBasedEvaluator.hh"
#include "Automaton.hh"
#include "CSVtraceReader.hh"
#include "EdgeProposition.hh"
#include "Evaluator.hh"
#include "Float.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "Trinary.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

namespace expression {
template <typename OT, typename ET> class Function;
} // namespace expression

using namespace harm;
using namespace expression;

class HarmLinearVsQuadraticAutomatonEvalTest
    : public ::testing::Test {

public:
  HarmLinearVsQuadraticAutomatonEvalTest() {
    l1Constants::MAX_THREADS = 10;
  }

  Trinary evaluateImplicationQuadratic(size_t time) {
    std::pair<Trinary, size_t> antRes;

    if (_implication->_applyDynamicShift) {
      antRes = _quadraticEvaluatorAnt->evaluateAutomaton<true>(time);
    } else {
      antRes = _quadraticEvaluatorAnt->evaluateAutomaton<false>(time);
    }

    size_t shift = _implication->_constShift + antRes.second;

    return !antRes.first ||
           ((shift >= _implication->getTraceLength())
                ? Trinary::U
                : _quadraticEvaluatorCon
                      ->evaluateAutomaton<false>(shift)
                      .first);
  }

  void check() {

    clc::reset = "";
    _tr = new CSVtraceReader("../tests/input/RandomTrace.csv");
    _trace = _tr->readTrace();

    std::string imp =
        "G(" + _strAnt + " " + _impSymbol + " " + _strCon + ")";
    _implication = hparser::parseTemplateImplication(imp, _trace);
    _implication->setL1Threads(5);
    _quadraticEvaluatorAnt = generatePtr<AutomataBasedEvaluator>(
        _implication->getTemplateFormula()
            ->getItems()[0]
            ->getItems()[0],
        _trace);
    _quadraticEvaluatorCon = generatePtr<AutomataBasedEvaluator>(
        _implication->getTemplateFormula()
            ->getItems()[0]
            ->getItems()[1],
        _trace);

    for (size_t i = 0; i < _trace->getLength(); i++) {
      ASSERT_EQ(_implication->evaluate(i),
                evaluateImplicationQuadratic(i));
    }
    delete _tr;
  }

  AutomataBasedEvaluatorPtr _quadraticEvaluatorAnt;
  AutomataBasedEvaluatorPtr _quadraticEvaluatorCon;
  TemplateImplicationPtr _implication;
  std::string _strAnt = "";
  std::string _strCon = "";
  std::string _impSymbol = "";
  TraceReader *_tr;
  TracePtr _trace;
};

TEST_F(HarmLinearVsQuadraticAutomatonEvalTest, equivalence1) {

  _strAnt = "{v1}";
  _strCon = "X(v2 W v3)";
  _impSymbol = "|->";
  check();
}

TEST_F(HarmLinearVsQuadraticAutomatonEvalTest, equivalence2) {

  _strAnt = "{v1 ##1 v2}";
  _strCon = "X(v3)";
  _impSymbol = "|->";
  check();
}

TEST_F(HarmLinearVsQuadraticAutomatonEvalTest, equivalence3) {

  _strAnt = "{v2}";
  _strCon = "X(v1 && v3)";
  _impSymbol = "|->";
  check();
}

TEST_F(HarmLinearVsQuadraticAutomatonEvalTest, equivalence4) {

  _strAnt = "{first_match(v1 ##[1..3] v2)}";
  _strCon = "X(v3 || v4)";
  _impSymbol = "|->";
  check();
}

TEST_F(HarmLinearVsQuadraticAutomatonEvalTest, equivalence5) {

  _strAnt = "{v1 [*2]: v2}";
  _strCon = "X(v3 || v4)";
  _impSymbol = "|->";
  check();
}

TEST_F(HarmLinearVsQuadraticAutomatonEvalTest, equivalence6) {

  _strAnt = "{first_match(v1 [*2..5]); v2}";
  _strCon = "X(v3)";
  _impSymbol = "|->";
  check();
}

TEST_F(HarmLinearVsQuadraticAutomatonEvalTest, equivalence7) {

  _strAnt = "{first_match(v1 ##[0..$] v2)}";
  _strCon = "X(v3)";
  _impSymbol = "|->";
  check();
}

TEST_F(HarmLinearVsQuadraticAutomatonEvalTest, equivalence8) {

  _strAnt = "{first_match(v1 [->2..$]); v2}";
  _strCon = "X(v3)";
  _impSymbol = "|->";
  check();
}

#endif
