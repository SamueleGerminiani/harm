
#include <utility>

#include "Assertion.hh"
#include "Float.hh"
#include "Metric.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"

using namespace expression;
namespace harm {
harm::MetricPtr Metric::parseMetric(const std::string &name,
                                    std::string formula) {

  std::vector<VarDeclaration> avF;
  for (const auto &af : Metric::availableFeatures) {
    avF.emplace_back(std::get<0>(af), std::get<1>(af),
                     std::get<2>(af));
  }

  harm::MetricPtr m = generatePtr<harm::Metric>();
  m->_oneValTrace = generatePtr<Trace>(avF, 1);

  m->_exp = hparser::parseFloatExpression(formula, m->_oneValTrace);
  auto vars = getVars(m->_exp);
  for (auto &v : vars) {
    m->_vars.push_back(v.first);
    m->_nameToFloatVarInMetric[v.first] =
        m->_oneValTrace->getFloatVariable(v.first);
  }

  m->_name = name;
  return m;
}

std::vector<std::tuple<std::string, expression::ExpType, size_t>>
    Metric::availableFeatures = {
        std::make_tuple("atct", ExpType::Float, 64),
        std::make_tuple("afct", ExpType::Float, 64),
        std::make_tuple("auct", ExpType::Float, 64),
        std::make_tuple("atcf", ExpType::Float, 64),
        std::make_tuple("afcf", ExpType::Float, 64),
        std::make_tuple("aucf", ExpType::Float, 64),
        std::make_tuple("atcu", ExpType::Float, 64),
        std::make_tuple("afcu", ExpType::Float, 64),
        std::make_tuple("aucu", ExpType::Float, 64),
        std::make_tuple("ct", ExpType::Float, 64),
        std::make_tuple("traceLength", ExpType::Float, 64),
        std::make_tuple("complexity", ExpType::Float, 64),
        std::make_tuple("faultCoverage", ExpType::Float, 64),
        std::make_tuple("nfCovered", ExpType::Float, 64),
        std::make_tuple("nFaults", ExpType::Float, 64),
        std::make_tuple("pRepetitions", ExpType::Float, 64)

};

std::unordered_map<size_t, Metric::FunctionParameter>
    Metric::functionParams = {
        {1, Metric::FunctionParameter(2.9937, 95.114)},
        {2, Metric::FunctionParameter(3.3212, 52.431)},
        {3, Metric::FunctionParameter(3.4217, 35.841)},
        {4, Metric::FunctionParameter(3.4191, 26.7)},
        {5, Metric::FunctionParameter(3.4217, 21.274)},
        {6, Metric::FunctionParameter(3.4163, 18.119)},
        {7, Metric::FunctionParameter(3.416, 15.523)},
        {8, Metric::FunctionParameter(3.4184, 13.609)},
        {9, Metric::FunctionParameter(3.3554, 11.83)},
        {0, Metric::FunctionParameter(3.3005, 10.623)},
        {12, Metric::FunctionParameter(12.713, 96.676)},
        {13, Metric::FunctionParameter(7.8153, 47.991)},
        {14, Metric::FunctionParameter(6.7778, 35.081)},
        {15, Metric::FunctionParameter(6.081, 26.593)},
        {16, Metric::FunctionParameter(5.1989, 20.435)},
        {17, Metric::FunctionParameter(4.9008, 17.058)},
        {18, Metric::FunctionParameter(4.9476, 15.385)},
        {19, Metric::FunctionParameter(4.7618, 13.595)},
        {10, Metric::FunctionParameter(4.536, 11.827)},
        {23, Metric::FunctionParameter(23.661, 102.23)},
        {24, Metric::FunctionParameter(12.689, 48.285)},
        {25, Metric::FunctionParameter(10.453, 35.329)},
        {26, Metric::FunctionParameter(8.538, 26.254)},
        {27, Metric::FunctionParameter(7.4046, 20.835)},
        {28, Metric::FunctionParameter(6.9327, 17.772)},
        {29, Metric::FunctionParameter(6.1655, 14.731)},
        {20, Metric::FunctionParameter(6.1083, 13.581)},
        {34, Metric::FunctionParameter(32.492, 98.036)},
        {35, Metric::FunctionParameter(17.829, 49.125)},
        {36, Metric::FunctionParameter(12.941, 32.887)},
        {37, Metric::FunctionParameter(10.718, 25.172)},
        {38, Metric::FunctionParameter(9.4645, 20.759)},
        {39, Metric::FunctionParameter(8.3259, 17.132)},
        {30, Metric::FunctionParameter(7.816, 15.239)},
        {45, Metric::FunctionParameter(39.517, 91.622)},
        {46, Metric::FunctionParameter(23.25, 50.304)},
        {47, Metric::FunctionParameter(16.46, 33.35)},
        {48, Metric::FunctionParameter(13.713, 26.097)},
        {49, Metric::FunctionParameter(11.944, 21.547)},
        {40, Metric::FunctionParameter(10.598, 18.145)},
        {56, Metric::FunctionParameter(53.453, 100.59)},
        {57, Metric::FunctionParameter(28.393, 50.449)},
        {58, Metric::FunctionParameter(19.486, 32.838)},
        {59, Metric::FunctionParameter(16.462, 26.324)},
        {50, Metric::FunctionParameter(14.146, 21.588)},
        {67, Metric::FunctionParameter(61.522, 97.435)},
        {68, Metric::FunctionParameter(32.798, 49.49)},
        {69, Metric::FunctionParameter(24.897, 36.015)},
        {60, Metric::FunctionParameter(18.216, 25.131)},
        {78, Metric::FunctionParameter(75.827, 103.61)},
        {79, Metric::FunctionParameter(37.637, 49.357)},
        {70, Metric::FunctionParameter(26.875, 33.86)},
        {89, Metric::FunctionParameter(78.201, 94.068)},
        {80, Metric::FunctionParameter(42.474, 49.253)},
        {90, Metric::FunctionParameter(92.567, 99.39)},

};

double Metric::evaluateMetric(Assertion &a, Metric &m) {

  messageErrorIf(m._vars.empty(), "No vars in metric ");
  for (auto &v : m._vars) {
    if (v == "atct") {
      m.assign(v, (double)a._ct[0][0]);
    } else if (v == "atcf") {
      m.assign(v, (double)a._ct[0][1]);
    } else if (v == "atcu") {
      m.assign(v, (double)a._ct[0][2]);
    } else if (v == "afct") {
      m.assign(v, (double)a._ct[1][0]);
    } else if (v == "afcf") {
      m.assign(v, (double)a._ct[1][1]);
    } else if (v == "afcu") {
      m.assign(v, (double)a._ct[1][2]);
    } else if (v == "auct") {
      m.assign(v, (double)a._ct[2][0]);
    } else if (v == "aucf") {
      m.assign(v, (double)a._ct[2][1]);
    } else if (v == "aucu") {
      m.assign(v, (double)a._ct[2][2]);
    } else if (v == "ct") {
      m.assign(v, (double)a._CT);
    } else if (v == "traceLength") {
      m.assign(v, (double)a._maxLength);
    } else if (v == "complexity") {
      m.assign(v, (double)a._complexity);
    } else if (v == "pRepetitions") {
      m.assign(v, (double)a._pRepetitions);
    } else if (v == "faultCoverage") {
      m.assign(v,
               (double)a._nfCovered / clc::faultyTraceFiles.size());
    } else if (v == "nFaults") {
      m.assign(v, (double)clc::faultyTraceFiles.size());
    } else if (v == "nfCovered") {
      m.assign(v, (double)a._nfCovered);
    } else {
      messageError("Unknown metric variable name '" + v + "'");
    }
  }
  return m.evaluate();
}

void Metric::assign(const std::string &name, double value) {
  _nameToFloatVarInMetric.at(name)->assign(0, value);
}

/** \brief Evaluate the metric with the current values of variables
   */
double Metric::evaluate() { return _exp->evaluate(0); }

Metric::~Metric() {}

bool Metric::contains(std::string assertionFeature) const {
  return std::find(_vars.begin(), _vars.end(), assertionFeature) !=
         _vars.end();
}

} // namespace harm
