#include "CSVtraceReader.hh"
#include "Template.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "globals.hh"
#include "templateParser.hh"
#include <gtest/gtest.h>

using namespace harm;
using namespace expression;

class EvalTest : public ::testing::Test {
protected:
  EvalTest() {}

  ~EvalTest() override {}

  void SetUp() override {}

  void TearDown() override {
    delete _tr;
    delete _trace;
    delete[] _cachedAnt;
    delete[] _cachedCon;
    delete[] _cachedDynShift;
    delete _t;
    for (auto &[t, pp] : _tokenToProp) {
      delete *pp;
      delete pp;
    }
  }

  Trinary evalAutomaton(size_t time, Automaton *root, size_t &dShift) const {
    Automaton::Node *cn = root->_root;
    /* visit the automaton by evaluating the edges (which are propositions)
   */
    while (time < _max_length) {
      for (const auto &edge : cn->_outEdges) {
        // if "the current cn->_outEdges[i] is true at instant 'time'"
        if (edge->_prop->evaluate(time)) {
          if (edge->_toNode->_type == 0) {
            dShift = time;
            return Trinary::F;
          } else if (edge->_toNode->_type == 1) {
            // store the dynamic shift for the current evaluation
            dShift = time;
            return Trinary::T;
          }

          // go to the next state
          cn = edge->_toNode;
          break;
        }
      }
      // each time we change state, time increases by 1
      time++;
    }
    dShift = time;
    return Trinary::U;
  }
  void build(std::string tempStrAnt, std::string tempStrCon) {
    spot::parsed_formula tempSpotAnt = spot::parse_infix_psl(tempStrAnt);
    messageErrorIf(tempSpotAnt.format_errors(std::cerr),
                   "SpotLTL: Syntax errors in antecedent of assertion:\n" +
                       tempStrAnt);
    spot::parsed_formula tempSpotCon = spot::parse_infix_psl(tempStrCon);
    messageErrorIf(tempSpotCon.format_errors(std::cerr),
                   "SpotLTL: Syntax errors in consequent of assertion:\n" +
                       tempStrCon);

    auto autAnt = generateDeterministicSpotAutomaton(tempSpotAnt.f);
    auto autCon = generateDeterministicSpotAutomaton(tempSpotCon.f);
    _hant = buildAutomaton(autAnt, _tokenToProp);
    _hcon = buildAutomaton(autCon, _tokenToProp);
  }
  void fill() {
    for (size_t i = 0; i < _max_length; i++) {
      size_t shiftAnt = 0;
      size_t shiftCon = 0;
      _cachedAnt[i] = evalAutomaton(i, _hant, shiftAnt);
      _cachedDynShift[i] = shiftAnt - i;
      _cachedCon[i] = evalAutomaton(i, _hcon, shiftCon);
    }
  }

  Trinary evaluate(size_t time) {
    size_t shift =
        time + (_applyDynamicShift ? _cachedDynShift[time] : 0) + _constShift;
    return !_cachedAnt[time] ||
           ((shift >= _max_length) ? Trinary::U : _cachedCon[shift]);
  }
  Trinary evaluate_ant(size_t time) { return _cachedAnt[time]; }
  Trinary evaluate_con(size_t time) { return _cachedCon[time]; }

  void check() {

    init();
    build(_tempStrAnt, _tempStrCon);
    fill();

    for (size_t i = 0; i < _trace->getLength(); i++) {
      EXPECT_EQ(_t->evaluate_ant(i), evaluate_ant(i));
      EXPECT_EQ(_t->evaluate_con(i), evaluate_con(i));
      EXPECT_EQ(_t->evaluate(i), evaluate(i));
    }
  }

  void init() {

    if (_imp == "|->") {
      _applyDynamicShift = 1;
    }

    _max_length = _trace->getLength();
    _cachedAnt = new Trinary[_max_length];
    _cachedCon = new Trinary[_max_length];
    _cachedDynShift = new size_t[_max_length];
    _t = hparser::parseTemplate("G(" + _tempStrAnt + _imp + _tempStrCon + ")",
                                _trace);
  }

public:
  TraceReader *_tr = nullptr;
  Trace *_trace = nullptr;
  size_t _max_length = 0;
  bool _applyDynamicShift = 0;
  size_t _constShift = 0;
  Trinary *_cachedAnt = nullptr;
  Trinary *_cachedCon = nullptr;
  Automaton *_hant = nullptr;
  Automaton *_hcon = nullptr;
  Template *_t = nullptr;
  size_t *_cachedDynShift = nullptr;
  std::unordered_map<std::string, expression::Proposition **> _tokenToProp;
  std::string _tempStrAnt = "";
  std::string _tempStrCon = "";
  std::string _imp = "";
};

TEST_F(EvalTest, t1) {
  _tr = new CSVtraceReader("../tests/input/EvalTest_RandomTrace.csv");
  _trace = _tr->readTrace();

  _tokenToProp["v1"] = new Proposition *(_trace->getBooleanVariable("v1"));
  _tokenToProp["v2"] = new Proposition *(_trace->getBooleanVariable("v2"));
  _tokenToProp["v3"] = new Proposition *(_trace->getBooleanVariable("v3"));

  _tempStrAnt = "{v1}";
  _tempStrCon = "X(v2 U v3)";
  _imp = "|->";

  check();
}

TEST_F(EvalTest, t2) {
  _tr = new CSVtraceReader("../tests/input/EvalTest_RandomTrace.csv");
  _trace = _tr->readTrace();

  _tokenToProp["v1"] = new Proposition *(_trace->getBooleanVariable("v1"));
  _tokenToProp["v2"] = new Proposition *(_trace->getBooleanVariable("v2"));
  _tokenToProp["v3"] = new Proposition *(_trace->getBooleanVariable("v3"));

  _tempStrAnt = "{v1 ##1 v2}";
  _tempStrCon = "X(v3)";
  _imp = "|->";

  check();
}

TEST_F(EvalTest, t3) {
  _tr = new CSVtraceReader("../tests/input/EvalTest_RandomTrace.csv");
  _trace = _tr->readTrace();

  _tokenToProp["v1"] = new Proposition *(_trace->getBooleanVariable("v1"));
  _tokenToProp["v2"] = new Proposition *(_trace->getBooleanVariable("v2"));
  _tokenToProp["v3"] = new Proposition *(_trace->getBooleanVariable("v3"));

  _tempStrAnt = "{v2}";
  _tempStrCon = "X(v1 && v3)";
  _imp = "|->";

  check();
}

TEST_F(EvalTest, t4) {
  _tr = new CSVtraceReader("../tests/input/EvalTest_RandomTrace.csv");
  _trace = _tr->readTrace();

  _tokenToProp["v1"] = new Proposition *(_trace->getBooleanVariable("v1"));
  _tokenToProp["v2"] = new Proposition *(_trace->getBooleanVariable("v2"));
  _tokenToProp["v3"] = new Proposition *(_trace->getBooleanVariable("v3"));
  _tokenToProp["v4"] = new Proposition *(_trace->getBooleanVariable("v4"));

  _tempStrAnt = "{v1 ##[1..3] v2}";
  _tempStrCon = "X(v3 || v4)";
  _imp = "|->";

  check();
}

TEST_F(EvalTest, t5) {
  _tr = new CSVtraceReader("../tests/input/EvalTest_RandomTrace.csv");
  _trace = _tr->readTrace();

  _tokenToProp["v1"] = new Proposition *(_trace->getBooleanVariable("v1"));
  _tokenToProp["v2"] = new Proposition *(_trace->getBooleanVariable("v2"));
  _tokenToProp["v3"] = new Proposition *(_trace->getBooleanVariable("v3"));
  _tokenToProp["v4"] = new Proposition *(_trace->getBooleanVariable("v4"));

  _tempStrAnt = "{v1 [*2]: v2}";
  _tempStrCon = "X(v3 || v4)";
  _imp = "|->";

  check();
}

TEST_F(EvalTest, t6) {
  _tr = new CSVtraceReader("../tests/input/EvalTest_RandomTrace.csv");
  _trace = _tr->readTrace();

  _tokenToProp["v1"] = new Proposition *(_trace->getBooleanVariable("v1"));
  _tokenToProp["v2"] = new Proposition *(_trace->getBooleanVariable("v2"));
  _tokenToProp["v3"] = new Proposition *(_trace->getBooleanVariable("v3"));

  _tempStrAnt = "{v1 [*2..$]; v2}";
  _tempStrCon = "X(v3)";
  _imp = "|->";

  check();
}

TEST_F(EvalTest, t7) {
  _tr = new CSVtraceReader("../tests/input/EvalTest_RandomTrace.csv");
  _trace = _tr->readTrace();

  _tokenToProp["v1"] = new Proposition *(_trace->getBooleanVariable("v1"));
  _tokenToProp["v2"] = new Proposition *(_trace->getBooleanVariable("v2"));
  _tokenToProp["v3"] = new Proposition *(_trace->getBooleanVariable("v3"));

  _tempStrAnt = "{v1 ##[0..$] v2}";
  _tempStrCon = "X(v3)";
  _imp = "|->";

  check();
}

TEST_F(EvalTest, t8) {
  _tr = new CSVtraceReader("../tests/input/EvalTest_RandomTrace.csv");
  _trace = _tr->readTrace();

  _tokenToProp["v1"] = new Proposition *(_trace->getBooleanVariable("v1"));
  _tokenToProp["v2"] = new Proposition *(_trace->getBooleanVariable("v2"));
  _tokenToProp["v3"] = new Proposition *(_trace->getBooleanVariable("v3"));

  _tempStrAnt = "{v1 [->2..$]; v2}";
  _tempStrCon = "X(v3)";
  _imp = "|->";

  check();
}
