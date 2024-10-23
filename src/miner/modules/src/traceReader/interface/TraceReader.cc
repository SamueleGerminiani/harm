#include <algorithm>
#include <stddef.h>
#include <string>

#include "PointerUtils.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"

namespace harm {

using namespace expression;

TraceReader::TraceReader(const std::vector<std::string> &traceFiles)
    : _traceFiles(traceFiles) {
  // ntd
}

TracePtr TraceReader::readTrace() {

  //avoid repeating the read
  if (_trace != nullptr) {
    return _trace;
  }

  //read all the single traces
  std::vector<TracePtr> traces;
  for (auto &f : _traceFiles) {
    //call the protected method
    auto trace = readTrace(f);
    if (trace != nullptr) {
      traces.push_back(trace);
    }
  }
  messageErrorIf(traces.empty(), "All traces are empty or could not be processed");

  if (traces.size() > 1) {
    //merge multiple traces into one
    _trace = mergeTrace(traces);
    //print some stats
    double avgLength = (double)_trace->getLength() /
                       (double)_trace->getCuts().size();
    messageInfo("Final trace length: " +
                std::to_string(_trace->getLength()));
    messageInfo("N merged traces: " +
                std::to_string(_trace->getCuts().size()));
    messageInfo("AVG length: " + std::to_string(avgLength));
  } else {
    //only one trace
    _trace = traces[0];
    _trace->setCuts(std::vector<size_t>({_trace->getLength() - 1}));
    messageInfo("Trace length:" +
                std::to_string(_trace->getLength()));
  }

  //  debug
  //for (auto i : _trace->getCuts()) {
  //  std::cout << i << " ";
  //}
  //std::cout << "\n";

  return _trace;
}

TracePtr
TraceReader::mergeTrace(const std::vector<TracePtr> &traces) {

  //get declarations from the first trace
  std::vector<VarDeclaration> decs = traces[0]->getDeclarations();
  //starting merged length
  size_t mergedLength = traces[0]->getLength();
  //cuts are used to keep track of when the sub-traces (composing the merged trace) end
  std::vector<size_t> cuts;
  cuts.push_back(traces[0]->getLength() - 1);

  //  debug
  //  for (const auto &dec : decs) {
  //    std::cout << dec.getName() << "\n";
  //  }
  //  std::cout << "---------------------------"
  //            << "\n";

  // check that all traces have the same variables and record the cuts
  for (size_t i = 1; i < traces.size(); i++) {
    const TracePtr &trace = traces[i];
    cuts.push_back(mergedLength + trace->getLength() - 1);
    std::vector<VarDeclaration> newDecs = trace->getDeclarations();
    messageErrorIf(newDecs.size() != decs.size(),
                   "Not all input traces share the same variables");
    for (const auto &dec : newDecs) {
      messageErrorIf(
          std::find_if(decs.begin(), decs.end(),
                       [&dec](VarDeclaration &e) {
                         return dec.getName() == e.getName() &&
                                dec.getSize() == e.getSize() &&
                                dec.getType() == e.getType();
                       }) == decs.end(),
          "Not all input traces share the same variables");
    }
    mergedLength += trace->getLength();
  }

  //create the base for the mergedTrace
  auto varsCopy = traces[0]->getVariables();
  //create the final merged trace
  TracePtr mergedTrace = generatePtr<Trace>(varsCopy, mergedLength);
  mergedTrace->setCuts(cuts);

  //collect the variables of the traces
  std::vector<BooleanVariablePtr> boolVars;
  std::vector<FloatVariablePtr> numVars;
  std::vector<IntVariablePtr> intVars;

  for (auto &var : varsCopy) {
    if (var.getType() == ExpType::Bool) {
      boolVars.push_back(
          mergedTrace->getBooleanVariable(var.getName()));
    } else if (var.getType() == ExpType::Float) {
      numVars.push_back(mergedTrace->getFloatVariable(var.getName()));
    } else if (isInt(var.getType())) {
      intVars.push_back(mergedTrace->getIntVariable(var.getName()));
    } else {
      messageError("Unsupported variable type");
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
        auto currTracenv = t->getFloatVariable(nv->getName());
        nv->assign(time + i, currTracenv->evaluate(i));
      }
      for (auto lv : intVars) {
        auto currTraceiv = t->getIntVariable(lv->getName());
        lv->assign(time + i, currTraceiv->evaluate(i));
      }
    }
    time += t->getLength();
  }

  return mergedTrace;
}

} // namespace harm
