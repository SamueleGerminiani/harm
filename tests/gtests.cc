#include "Assertion.hh"
#include "CSVtraceReader.hh"
#include "ManualDefinition.hh"
#include "Miner.hh"
#include "Qualifier.hh"
#include "TLMiner.hh"
#include "Trinary.hh"
#include "VCDtraceReader.hh"
#include "globals.hh"
#include "minerUtils.hh"
#include "propositionParser.hh"
#include "propositionParsingUtils.hh"
#include "templateParser.hh"
#include "templateParsingUtils.hh"
#include <bitset>
#include <filesystem>
#include <gtest/gtest.h>

using namespace harm;

class NextAndTest : public ::testing::Test {
protected:
  NextAndTest() {}

  ~NextAndTest() override {

    for (Context *context : _contexts)
      delete context;

    delete _contextMiner;
    delete _traceReader;
    delete _propertyMiner;
    delete _propertyQualifier;
    delete _trace;
  }

  void SetUp() override {
    clc::traceFiles.clear();
    clc::faultyTraceFiles.clear();
    clc::configFile = "";
    clc::parserType = "";
    clc::clk = "";
    clc::genTemp = 0;
    clc::maxThreads = 8;
  }

  void TearDown() override {}

  void mineProperties() {
    if (clc::parserType == "csv") {
      _traceReader = new CSVtraceReader(clc::traceFiles[0]);
    } else {
      _traceReader = new VCDtraceReader(clc::traceFiles[0], clc::clk);
    }
    _contextMiner = new ManualDefinition(clc::configFile);
    _propertyQualifier = new Qualifier();
    _trace = _traceReader->readTrace();
    _contextMiner->mineContexts(_trace, _contexts);
    messageErrorIf(_contexts.size() > 1, "Only 1 context supported!");
    _propertyMiner = new TLMiner();
    _propertyMiner->mineProperties(*_contexts[0], _trace);
  }
  Assertion *generateAssertion(Assertion *a, Trace *trace) {

    Assertion *ass = new Assertion();
    Template *t = hparser::parseTemplate(a->_toString.first, trace);
    t->nextPerm();
    t->evaluate(0);
    t->fillContingency(ass->_ct, 0);
    ass->_toString = a->_toString;
    auto loadedProps = t->getLoadedPropositions();
    ass->_complexity = getNumVariables(loadedProps);
    ass->_pRepetitions = getRepetitions(loadedProps);
    ass->fillValues(t);
    delete t;
    return ass;
  }

public:
  Trace *_trace = nullptr;
  TraceReader *_traceReader = nullptr;
  ContextMiner *_contextMiner = nullptr;
  PropertyMiner *_propertyMiner = nullptr;
  Qualifier *_propertyQualifier = nullptr;
  std::vector<Context *> _contexts;
};

TEST_F(NextAndTest, t1) {
  clc::configFile = "../tests/gTestsTB/nextAnd/nextAnd_t1.xml";
  clc::traceFiles.push_back("../tests/gTestsTB/nextAnd/nextAnd_t1.csv");
  clc::parserType = "csv";
  mineProperties();
  Context *c = _contexts[0];
  EXPECT_EQ(c->_assertions.size(), 2);
  EXPECT_EQ("G({{v1 ##1 v1 ##1 true}} |-> v4)",
            c->_assertions[0]->_toString.first);
}

TEST_F(NextAndTest, t2) {
  clc::configFile = "../tests/gTestsTB/nextAnd/nextAnd_t2.xml";
  clc::traceFiles.push_back("../tests/gTestsTB/nextAnd/nextAnd_t2.vcd");
  clc::parserType = "vcd";
  clc::clk = "wb_clk";
  mineProperties();
  Context *c = _contexts[0];
  EXPECT_EQ(c->_assertions.size(), 124);
}

TEST_F(NextAndTest, t3) {
  clc::configFile = "../tests/gTestsTB/nextAnd/nextAnd_t3.xml";
  clc::traceFiles.push_back("../tests/gTestsTB/nextAnd/nextAnd_t3.vcd");

  for (const auto &entry : std::filesystem::directory_iterator(
           "../tests/gTestsTB/nextAnd/nextAnd_t3_fd")) {
    if (entry.path().extension() == ".vcd") {
      clc::faultyTraceFiles.push_back(entry.path().u8string());
    }
  }
  clc::parserType = "vcd";
  clc::clk = "wb_clk";
  mineProperties();
  auto &assertions = _contexts[0]->_assertions;
  std::cout << assertions.size() << " assertions\n";
  for (auto &a : assertions) {
    Assertion *mock = generateAssertion(a, _trace);
    for (size_t i = 0; i < a->_max_length; i++) {
      EXPECT_EQ(a->evaluate(i), mock->evaluate(i));
    }
    delete mock;
  }
}

TEST_F(NextAndTest, t5) {
  clc::configFile = "../tests/gTestsTB/nextAnd/nextAnd_t5.xml";
  clc::traceFiles.push_back("../tests/gTestsTB/nextAnd/nextAnd_t5.vcd");

  clc::parserType = "vcd";
  clc::clk = "wb_clk";
  if (clc::parserType == "csv") {
    _traceReader = new CSVtraceReader(clc::traceFiles[0]);
  } else {
    _traceReader = new VCDtraceReader(clc::traceFiles[0], clc::clk);
  }
  _contextMiner = new ManualDefinition(clc::configFile);
  _propertyQualifier = new Qualifier();
  _trace = _traceReader->readTrace();
  _contextMiner->mineContexts(_trace, _contexts);
  for (auto &t : _contexts[0]->_templates) {
    auto formula = t->getTemplateFormula();
    PermGenerator pg;
    pg.genPermutations(3, 7, 0, formula);
    std::unordered_set<std::string> seen;
    std::cout << "Nperms: " << pg._size.first << "\n";
    for (size_t i = 0; i < pg._size.first; i++) {
      stringstream ss;
      for (size_t j = 0; j < pg._size.second; j++) {
        ss << pg._perms[i][j];
      }
      EXPECT_EQ(seen.count(ss.str()), false);
      seen.insert(ss.str());
    }
  }
}

class ParserTest : public ::testing::Test {
protected:
  ParserTest() {}

  ~ParserTest() override {

    delete _traceReader;
    delete _trace;
  }

  void SetUp() override {
    clc::traceFiles.clear();
    clc::faultyTraceFiles.clear();
    clc::configFile = "";
    clc::parserType = "";
    clc::clk = "";
    clc::genTemp = 0;
    clc::maxThreads = 8;
  }

  void TearDown() override {}

  void readTrace() {
    if (clc::parserType == "csv") {
      _traceReader = new CSVtraceReader(clc::traceFiles[0]);
    } else {
      _traceReader = new VCDtraceReader(clc::traceFiles[0], clc::clk);
    }
    _trace = _traceReader->readTrace();
  }

public:
  Trace *_trace = nullptr;
  TraceReader *_traceReader = nullptr;
};

TEST_F(ParserTest, t1) {
  clc::traceFiles.push_back("../tests/gTestsTB/parser/trace.csv");

  clc::parserType = "csv";
  if (clc::parserType == "csv") {
    _traceReader = new CSVtraceReader(clc::traceFiles[0]);
  } else {
    _traceReader = new VCDtraceReader(clc::traceFiles[0], clc::clk);
  }
  _trace = _traceReader->readTrace();

  Template *t = hparser::parseTemplate("G({v2}|->X[3](v1[0]))", _trace);
  // auto p=hparser::parseProposition("v1[5:0]==1",_trace);

  // std::cout << prop2String(*p) << "\n";
  std::cout << t->getColoredAssertion() << "\n";
  delete t;
}

class StuckAtTest : public ::testing::Test {
protected:
  StuckAtTest() {}

  ~StuckAtTest() override {

    delete _traceReader;
    delete _trace;
  }

  void SetUp() override {
    clc::traceFiles.clear();
    clc::faultyTraceFiles.clear();
    clc::configFile = "";
    clc::parserType = "";
    clc::clk = "";
    clc::genTemp = 0;
    clc::maxThreads = 8;
  }

  void TearDown() override {}

  void readTrace() {
    if (clc::parserType == "csv") {
      _traceReader = new CSVtraceReader(clc::traceFiles[0]);
    } else {
      _traceReader = new VCDtraceReader(clc::traceFiles[0], clc::clk);
    }
    _trace = _traceReader->readTrace();
  }

public:
  Trace *_trace = nullptr;
  TraceReader *_traceReader = nullptr;
};

TEST_F(StuckAtTest, t1) {
  clc::traceFiles.push_back("../tests/vendingMachine/vendingMachine.vcd");

  clc::parserType = "vcd";
  clc::clk = "clk";
  if (clc::parserType == "csv") {
    _traceReader = new CSVtraceReader(clc::traceFiles[0]);
  } else {
    _traceReader = new VCDtraceReader(clc::traceFiles[0], clc::clk);
  }
  _trace = _traceReader->readTrace();

  size_t sa = 1;
  size_t index = 0;
  bool con = 1;
  LogicExpression *wsa;
  LogicExpression *wsa2;
  LogicExpression *le = _trace->getLogicVariable("current_state");
  for (size_t i = 0; i < 10; i++) {
    std::cout << std::bitset<4>(le->evaluate(i)) << " ";
  }
  std::cout << "\n";
  if (sa == 0) {
    if (con) {
      ULogic value = ~(((1ULL << (index + 1)) - 1) << 1) >> 1;
      auto *c =
          new LogicConstant(value, VarType::SLogic, 64, _trace->getLength());
      wsa = makeExpression<LogicBAnd>(le, c);
      Proposition *p = hparser::parseProposition(
          std::string("(") + "current_state & " +
              (std::to_string((~((1ULL << (index + 1)) - 1) << 1) >> 1) + ")"),
          _trace);
      wsa2 = &dynamic_cast<LogicToBool *>(p)->getItem();

    } else {
      ULogic value = (~((uint64_t)(1ULL << index)) << 1) >> 1;
      auto *c =
          new LogicConstant(value, VarType::SLogic, 64, _trace->getLength());
      wsa = makeExpression<LogicBAnd>(le, c);
      Proposition *p = hparser::parseProposition(
          std::string("(") + "current_state & " +
              (std::to_string((~((uint64_t)(1ULL << index)) << 1) >> 1) + ")"),
          _trace);
      wsa2 = &dynamic_cast<LogicToBool *>(p)->getItem();
    }

  } else {
    if (con) {
      ULogic value = (1ULL << (index + 1)) - 1;
      auto *c =
          new LogicConstant(value, VarType::SLogic, 64, _trace->getLength());
      wsa = makeExpression<LogicBOr>(le, c);
      Proposition *p = hparser::parseProposition(
          std::string("(") + " current_state| " +
              (std::to_string((1ULL << (index + 1)) - 1)) + ")",
          _trace);
      wsa2 = &dynamic_cast<LogicToBool *>(p)->getItem();
    } else {
      ULogic value = 1ULL << index;
      auto *c =
          new LogicConstant(value, VarType::SLogic, 64, _trace->getLength());
      wsa = makeExpression<LogicBOr>(le, c);
      Proposition *p =
          hparser::parseProposition(std::string("(") + " current_state| " +
                                        (std::to_string(1ULL << index)) + ")",
                                    _trace);
      wsa2 = &dynamic_cast<LogicToBool *>(p)->getItem();
    }
  }
  for (size_t i = 0; i < 10; i++) {
    std::cout << std::bitset<4>(wsa->evaluate(i)) << " ";
  }
  std::cout << "\n";
  for (size_t i = 0; i < 10; i++) {
    std::cout << std::bitset<4>(wsa2->evaluate(i)) << " ";
  }
  std::cout << "\n";
}

class LatsTest : public ::testing::Test {
protected:
  LatsTest() {}

  ~LatsTest() override {

    for (Context *context : _contexts)
      delete context;

    delete _contextMiner;
    delete _traceReader;
    delete _propertyMiner;
    delete _propertyQualifier;
    delete _trace;
  }

  void SetUp() override {
    clc::traceFiles.clear();
    clc::faultyTraceFiles.clear();
    clc::configFile = "";
    clc::parserType = "";
    clc::clk = "";
    clc::genTemp = 0;
    clc::maxThreads = 8;
  }

  void TearDown() override {}

  void mineProperties() {
    if (clc::parserType == "csv") {
      _traceReader = new CSVtraceReader(clc::traceFiles[0]);
    } else {
      _traceReader = new VCDtraceReader(clc::traceFiles[0], clc::clk);
    }
    _contextMiner = new ManualDefinition(clc::configFile);
    _propertyQualifier = new Qualifier();
    _trace = _traceReader->readTrace();
    _contextMiner->mineContexts(_trace, _contexts);
    messageErrorIf(_contexts.size() > 1, "Only 1 context supported!");
    _propertyMiner = new TLMiner();
    _propertyMiner->mineProperties(*_contexts[0], _trace);
  }
  Assertion *generateAssertion(Assertion *a, Trace *trace) {

    Assertion *ass = new Assertion();
    Template *t = hparser::parseTemplate(a->_toString.first, trace);
    t->nextPerm();
    t->evaluate(0);
    t->fillContingency(ass->_ct, 0);
    ass->_toString = a->_toString;
    auto loadedProps = t->getLoadedPropositions();
    ass->_complexity = getNumVariables(loadedProps);
    ass->_pRepetitions = getRepetitions(loadedProps);
    ass->fillValues(t);
    delete t;
    return ass;
  }

public:
  Trace *_trace = nullptr;
  TraceReader *_traceReader = nullptr;
  ContextMiner *_contextMiner = nullptr;
  PropertyMiner *_propertyMiner = nullptr;
  Qualifier *_propertyQualifier = nullptr;
  std::vector<Context *> _contexts;
};

