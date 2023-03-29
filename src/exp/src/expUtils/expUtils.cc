#include "expUtils/expUtils.hh"
#include "classes/atom/Atom.hh"
#include "classes/atom/Variable.hh"
#include "visitors/ColoredPrinterVisitor.hh"
#include "visitors/CopyVisitor.hh"
#include "visitors/CounterVisitor.hh"
#include "visitors/PrinterVisitor.hh"
#include "visitors/TraceChangerVisitor.hh"
#include "visitors/VarExtractVisitor.hh"

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::ostream &operator<<(std::ostream &os, expression::Proposition &p) {

  expression::PrinterVisitor printer;
  p.acceptVisitor(printer);
  os << printer.get();
  return os;
}
std::string prop2String(expression::Proposition &p) {
  expression::PrinterVisitor printer;
  p.acceptVisitor(printer);
  return printer.get();
}
std::string num2String(expression::NumericExpression &n) {
  expression::PrinterVisitor printer;
  n.acceptVisitor(printer);
  return printer.get();
}
std::string log2String(expression::LogicExpression &l) {
  expression::PrinterVisitor printer;
  l.acceptVisitor(printer);
  return printer.get();
}
std::string prop2ColoredString(expression::Proposition &p) {
  expression::ColoredPrinterVisitor printer;
  p.acceptVisitor(printer);
  return printer.get();
}
std::string allNum2String(expression::CachedAllNumeric &all) {
  expression::PrinterVisitor printer;
  all.acceptVisitor(printer);
  return printer.get();
}
expression::Proposition *copy(expression::Proposition &p) {
  expression::CopyVisitor copier;
  p.acceptVisitor(copier);
  return copier.get();
}
expression::LogicExpression *copy(expression::LogicExpression &le) {
  expression::CopyVisitor copier;
  le.acceptVisitor(copier);
  return copier.getLogic();
}
expression::NumericExpression *copy(expression::NumericExpression &ne) {
  expression::CopyVisitor copier;
  ne.acceptVisitor(copier);
  return copier.getNumeric();
}
void sortPropositions(std::vector<expression::Proposition *> &props) {
  std::sort(begin(props), end(props),
            [](expression::Proposition *e1, expression::Proposition *e2) {
              return prop2String(*e1) < prop2String(*e2);
            });
}

size_t prop2NumVars(expression::Proposition &p) {
  expression::CounterVisitor counter;
  p.acceptVisitor(counter);
  return counter.get_count();
}
size_t getNumVariables(const std::vector<expression::Proposition *> &props) {
  size_t ret = 0;

  for (expression::Proposition *p : props) {
    ret += prop2NumVars(*p);
  }

  return ret;
}
size_t getRepetitions(const std::vector<expression::Proposition *> &props) {
  size_t ret = 0;
  std::unordered_set<std::string> propStr;

  for (expression::Proposition *p : props) {
    auto ps = prop2ColoredString(*p);
    if (propStr.count(ps)) {
      ret++;
    } else {
      propStr.insert(ps);
    }
  }

  return ret;
}
std::vector<std::pair<std::string, size_t>> getVars(expression::Proposition &p,
                                                    bool keepIndex) {
  expression::VarExtractVisitor varext(keepIndex);
  p.acceptVisitor(varext);
  return varext.get_vars();
}

void changeTrace(expression::Proposition &p, harm::Trace *newTrace) {
  expression::TraceChangerVisitor tg(newTrace);
  p.acceptVisitor(tg);
}
