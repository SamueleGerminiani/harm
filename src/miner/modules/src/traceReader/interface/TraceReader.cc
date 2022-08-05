#include "TraceReader.hh"

#include <algorithm>
#include <string>

namespace l1Constants {
extern size_t MAX_THREADS;
}

namespace harm {

using namespace expression;

TraceReader::TraceReader(const std::vector<std::string> &files)
    : _files(files){
  // ntd
}

Trace *TraceReader::readTrace() {

   //avoid repeating the read
  if (_trace != nullptr) {
    return _trace;
  }

  //read all the single traces
  std::vector<Trace *> traces;
  for (auto &f : _files) {
    traces.push_back(readTrace(f));
  }

  if (traces.size() > 1) {
      //merge multiple traces into one
    _trace = mergeTrace(traces);
    //delete the sub-traces
    for (auto t : traces) {
      delete t;
    }
    //print some stats
    double avgLength =
        (double)_trace->getLength() / (double)_trace->getCuts().size();
    messageInfo("Final trace length: " + std::to_string(_trace->getLength()));
    messageInfo("N merged traces: " + std::to_string(_trace->getCuts().size()));
    messageInfo("AVG length: " + std::to_string(avgLength));
  } else {
      //only one trace
    _trace = traces[0];
    _trace->setCuts(std::vector<size_t>({_trace->getLength() - 1}));
    messageInfo("Trace length:" + std::to_string(_trace->getLength()));
  }
  //  debug
//  for (auto i : _trace->getCuts()) {
//      std::cout << i << " ";
//  }
//  std::cout <<  "\n";
  return _trace;
}
Trace *TraceReader::mergeTrace(const std::vector<Trace *> &traces) {

  std::vector<VarDeclaration> decs = traces[0]->getDeclarations();
  size_t mergedLength = traces[0]->getLength();
  //cuts are used to keep track of when the sub-traces (composing the merged trace) end
  std::vector<size_t> cuts;
  cuts.push_back(traces[0]->getLength() - 1);

  //  debug
  //  for (const auto &dec : decs) {
  //    std::cout << std::get<0>(dec) << "\n";
  //  }
  //  std::cout << "---------------------------"
  //            << "\n";

  // check that all traces have the same variables
  for (size_t i = 1; i < traces.size(); i++) {
    Trace *trace = traces[i];
    cuts.push_back(mergedLength + trace->getLength() - 1);
    std::vector<VarDeclaration> newDecs = trace->getDeclarations();
    messageErrorIf(newDecs.size() != decs.size(),
                   "The input traces do not have the same variables");
    for (const auto &dec : newDecs) {
      messageErrorIf(std::find_if(decs.begin(), decs.end(),
                                  [&dec](VarDeclaration &e) {
                                    return std::get<0>(dec) == std::get<0>(e) &&
                                           std::get<1>(dec) == std::get<1>(e) &&
                                           std::get<2>(dec) == std::get<2>(e);
                                  }) == decs.end(),
                     "The input traces do not have the same variables");
    }
    mergedLength += trace->getLength();
  }

  //create the base for the mergedTrace
  auto varsCopy = traces[0]->getVariables();
  Trace *mergedTrace = new Trace(varsCopy, mergedLength);
  mergedTrace->setCuts(cuts);

  std::vector<BooleanVariable *> boolVars;
  std::vector<NumericVariable *> numVars;
  std::vector<LogicVariable *> logVars;

  for (auto &var : varsCopy) {
    if (var.getType() == VarType::Bool) {
      boolVars.push_back(mergedTrace->getBooleanVariable(var.getName()));
    } else if (var.getType() == VarType::Numeric) {
      numVars.push_back(mergedTrace->getNumericVariable(var.getName()));
    } else {
      logVars.push_back(mergedTrace->getLogicVariable(var.getName()));
    }
  }

  //assign the merged trace with the values of the sub-traces
  size_t time = 0;

  for (auto t : traces) {
    for (size_t i = 0; i < t->getLength(); i++) {
      for (auto bv : boolVars) {
        auto currTracebv = t->getBooleanVariable(bv->getName());
        bv->assign(time + i, currTracebv->evaluate(i));
      }
      for (auto nv : numVars) {
        auto currTracenv = t->getNumericVariable(nv->getName());
        nv->assign(time + i, currTracenv->evaluate(i));
      }
      for (auto lv : logVars) {
        auto currTracelv = t->getLogicVariable(lv->getName());
        lv->assign(time + i, currTracelv->evaluate(i));
      }
    }
    time += t->getLength();
  }

  return mergedTrace;
}
} // namespace harm
