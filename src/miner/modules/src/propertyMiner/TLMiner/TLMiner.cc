#include <algorithm>
#include <assert.h>
#include <fstream>
#include <functional>
#include <iterator>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

#include "AntecedentGenerator.hh"
#include "Assertion.hh"
#include "Context.hh"
#include "DTOperator.hh"
#include "Location.hh"
#include "TLMiner.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "formula/expression/GenericExpression.hh"
#include "globals.hh"
#include "message.hh"

namespace expression {
class NumericExpression;
} // namespace expression

namespace harm {

TLMiner::TLMiner() : PropertyMiner() {}

TLMiner::~TLMiner() {}

void TLMiner::mineProperties(const ContextPtr &context,
                             const TracePtr &trace) {

  _vacFile.open(clc::dumpVacAss, std::ios_base::out);
  _vacFile.close();

  messageInfo("CONTEXT: " + context->_name);

#ifdef DEBUG
  for (auto &[id, props] : context->_domainIdToProps) {
    for (auto &prop : props) {
      messageInfo("PROP (" + domainIdToString(id) +
                  "): " + prop2String(prop));
    }
  }
  for (auto &[id, props] : context->_domainIdToNumerics) {
    for (auto &prop : props) {
      messageInfo("NUMERIC (" + domainIdToString(id) +
                  "): " + num2String(prop));
    }
  }
#endif

  _context = context;

  l3Handler(clc::maxThreads);

  //store all the generated assertions into the context
  for (auto &pack : _collectedAssertions) {
    for (const AssertionPtr &ass : pack) {
      context->_assertions.push_back(ass);
    }
  }

  messageWarningIf(
      _nVacAss > 0,
      "Number of vacuous assertions found for context '" +
          context->_name + "': " + std::to_string(_nVacAss));

  //clear: necessary if TLMiner is reused (multiple contexts)
  clear();
}

void TLMiner::l3Handler(size_t nThread) {

  //threads for l3
  Semaphore l3avThreads(nThread);
  //active l3 instances (template being mined)
  std::unordered_map<size_t, Semaphore *> l3Instances;
  std::mutex l3InstancesGuard;

  size_t toBeServed = 0;
  //keep track of how many threads are currently allocated for each active template
  size_t l3MaxThread = 2;
  //simple mapping  Instance -> Number of threads
  std::unordered_map<size_t, size_t> l3InstToNumThreads;
  while (1) {
    //consume a thread
    l3avThreads.wait();
    //allocate the thread
    std::lock_guard<std::mutex> lock{l3InstancesGuard};

    if (toBeServed < _context->_templates.size() &&
        l3Instances.size() < l3Constants::MAX_THREADS) {
      //mine a new template and give it to the thread
      l3InstToNumThreads[toBeServed] = 1;
      l3Instances[toBeServed] = new Semaphore(1);
      TemplateImplicationPtr t = _context->_templates[toBeServed];
      //start a new l2Instance (new permutation of the current template)
      std::thread(&TLMiner::l2Handler, this, t, toBeServed,
                  std::ref(l3Instances), std::ref(l3avThreads),
                  std::ref(l3InstancesGuard),
                  std::ref(l3InstToNumThreads))
          .detach();
      toBeServed++;
    } else if (!l3Instances.empty()) {
      //all templates are being mined: give the thread to an active template
      //this code is to balance the number of threads among the active templates, it searches for an l3Instance that is using less threads than the current max
      for (auto &e : l3Instances) {
        if (l3InstToNumThreads.at(e.first) < l3MaxThread) {
          e.second->notify();
          l3InstToNumThreads.at(e.first)++;
          goto found;
        }
      }
      //all l3Instance are using the same number of threads
      l3Instances.begin()->second->notify();
      l3MaxThread++;
      l3InstToNumThreads.at(l3Instances.begin()->first)++;
    found:;
    } else {
      break;
    }
  }

  _progressBar.done();

  messageErrorIf(l3avThreads.getAvailable() != nThread - 1,
                 "l3avThreads.getAvailable() != nThread - 1");
}
void TLMiner::l2Handler(
    const TemplateImplicationPtr &t, size_t l3InstId,
    std::unordered_map<size_t, Semaphore *> &l3Instances,
    Semaphore &l3avThreads, std::mutex &l3InstancesGuard,
    std::unordered_map<size_t, size_t> &l3InstToNumThreads) {
  //this function follows the same principles of l3Handler; however, we create a new Template instance for each permutation to avoid sharing memory

  Semaphore *l2avThreads =
      atGuard(l3Instances, l3InstId, l3InstancesGuard);
  std::unordered_map<size_t, size_t> l2Instances;
  size_t toBeServed = 0;
  size_t l2MaxThread = 2;
  std::vector<TemplateImplicationPtr> templs;
  std::vector<size_t> busyTemplates;
  std::vector<size_t> freeTemplates;
  std::unordered_map<size_t, size_t> templIndexTol2Inst;
  std::unordered_map<size_t, size_t> instToTemplIndex;
  std::mutex l2InstancesGuard;

  {
    t->genPermutations(_context->_domainIdToProps,
                       _context->_domainIdToNumerics);

    _progressBar.addInstance(l3InstId, t->getColoredTemplateStr(),
                             t->getNumberOfPermutations(), 70);
    _progressBar.enableCounter(l3InstId);
  }

  while (1) {
    l2avThreads->wait();
    std::lock_guard<std::mutex> lock{l2InstancesGuard};
    if (toBeServed < t->getNumberOfPermutations() &&
        l2Instances.size() < l2Constants::MAX_THREADS) {

      l2Instances[toBeServed] = 1;

      // update bt
      for (auto &i : busyTemplates) {
        if (!l2Instances.count(templIndexTol2Inst.at(i))) {
          freeTemplates.push_back(i);
          i = -1;
        }
      }
      busyTemplates.erase(
          std::remove(begin(busyTemplates), end(busyTemplates), -1),
          end(busyTemplates));
      TemplateImplicationPtr nextTemp = nullptr;
      if (freeTemplates.empty()) {
        // new copy
        busyTemplates.push_back(templs.size());
        templIndexTol2Inst[templs.size()] = toBeServed;
        instToTemplIndex[toBeServed] = templs.size();
        templs.push_back(generatePtr<TemplateImplication>(*t));
        nextTemp = templs.back();
      } else {
        // reuse old copy
        nextTemp = templs[freeTemplates.back()];
        busyTemplates.push_back(freeTemplates.back());
        templIndexTol2Inst.at(freeTemplates.back()) = toBeServed;
        instToTemplIndex[toBeServed] = freeTemplates.back();
        freeTemplates.pop_back();
      }

      assert(nextTemp != nullptr);
      //elaborate the permutation
      std::thread(&TLMiner::l1Handler, this, nextTemp, toBeServed,
                  l3InstId, std::ref(l2avThreads),
                  std::ref(l2Instances), std::ref(l2InstancesGuard))
          .detach();
      toBeServed++;
    } else if (!l2Instances.empty()) {
      for (auto &e : l2Instances) {
        if (e.second < l2MaxThread) {
          e.second++;
          templs[instToTemplIndex.at(e.first)]->setL1Threads(
              e.second);
          goto found;
        }
      }
      l2Instances.begin()->second++;
      templs[instToTemplIndex.at(l2Instances.begin()->first)]
          ->setL1Threads(l2Instances.begin()->second);
      l2MaxThread++;
    found:;
    } else {
      break;
    }
    // Debug the threads allocation
    //
    //          _progressBar.changeMessage(
    //              l3InstId, std::to_string(l3InstToNumThreads.at(l3InstId)));
    //
  }

  // Debug the threads allocation
  //
  //    _progressBar.changeMessage(l3InstId, std::to_string(0));
  _progressBar.done(l3InstId);

  std::lock_guard<std::mutex> lock{l3InstancesGuard};
  size_t nThreads = l3Instances.at(l3InstId)->getAvailable() + 1;
  delete l3Instances.at(l3InstId);
  l3Instances.erase(l3InstId);

  l3avThreads.addNotifyOnce(nThreads);
}

void TLMiner::l1Handler(
    const TemplateImplicationPtr &t, size_t l2InstId, size_t l3InstId,
    Semaphore *l2avThreads,
    std::unordered_map<size_t, size_t> &l2Instances,
    std::mutex &l2InstancesGuard) {

  //load the permutation in the template
  t->loadPerm(l2InstId);

  std::vector<AssertionPtr> assp;

  if (t->getDT() != nullptr) {
    //the template contains a dt operator

    if (t->isVacuous(harm::Location::AntCon)) {
      if (!clc::keepVacAss) {
        goto end;
      }
    }

    //generate the decision tree variables

    DecTreeVariables candidateVariables;
    auto propsDT = t->getDTPropositions();
    for (size_t i = 0; i < t->getDTPropositions().size(); i++) {
      candidateVariables[i].first = propsDT[i];
      candidateVariables[i].second =
          makeGenericExpression<PropositionNot>(propsDT[i]);
    }

    NumericDecTreeExp numericCandidates;
    auto numericsDT = t->getDTNumerics();
    for (size_t i = 0; i < numericsDT.size(); i++) {
      numericCandidates[i] = numericsDT[i];
    }

    AntecedentGenerator antGen;
    antGen._saveOffset = t->getDT()->getLimits()._saveOffset;
    antGen.makeAntecedents(t, candidateVariables, numericCandidates);

    //onset
    handleDTSolutions(t, antGen._onSets, assp, false);
    //offset
    handleDTSolutions(t, antGen._offSets, assp, true);

    candidateVariables.clear();

    numericCandidates.clear();

  } else {
    // If the template does not have a dt

    if (t->assHoldsOnTrace(harm::Location::None)) {
      bool isVacuous = t->isVacuous(Location::AntCon);

      if (!isVacuous || clc::keepVacAss) {
        AssertionPtr ass = generatePtr<Assertion>();
        fillAssertion(ass, t, false);
        assp.push_back(ass);

        if (isVacuous) {
          dumpVac(ass->toString());
        }
      }
    }
  }

end:;
  //store the assertions collected in the current permutation
  if (!assp.empty()) {
    std::lock_guard<std::mutex> lock{_collectedAssertionsGuard};
    _collectedAssertions.push_back(assp);
  }

  _progressBar.incrementCounter(l3InstId, assp.size());
  _progressBar.increment(l3InstId);
  _progressBar.display();

  //delete this instance and notify the upper level
  std::lock_guard<std::mutex> lock{l2InstancesGuard};
  size_t nThreads = l2Instances.at(l2InstId);
  l2Instances.erase(l2InstId);
  l2avThreads->addNotifyOnce(nThreads);
}

void TLMiner::handleDTSolutions(const TemplateImplicationPtr &t,
                                std::vector<DTSolution> &solutions,
                                std::vector<AssertionPtr> &assp,
                                bool isOffset) {

  for (auto &dtSol : solutions) {
    dtSol.sortByWidth(true);
    //rebulding the assertion starting from a list of propositions (the operands of a dt operator)
    if (t->getDT()->isMultiDimensional()) {
      auto multiSol = dtSol.getMultidimensionalSolution();
      for (size_t i = 0; i < multiSol.size(); i++) {
        for (auto prop : multiSol[i]) {
          t->getDT()->addItem(prop, i);
        }
      }
    } else {
      for (auto prop : dtSol.getUnidimensionalSolution()) {
        t->getDT()->addItem(prop, -1);
      }
    }

    //antecedent is invalidated by the modification to the template
    t->setCacheAntFalse();

#if DEBUG
    messageErrorIf(
        isOffset ? !t->assHoldsOnTraceOffset(harm::Location::AntCon)
                 : !t->assHoldsOnTrace(harm::Location::AntCon),
        "dt assertion (" +
            (isOffset ? std::string("Offset")
                      : std::string("Onset")) +
            ") is false: " + t->getColoredAssertionStr());
    messageErrorIf(t->getDT()->getItems().empty(),
                   "dt items is empty");
#endif

    //check for vacuity
    bool isVacuous;
    if (isOffset) {
      isVacuous = t->isVacuousOffset(Location::Ant);
    } else {
      isVacuous = t->isVacuous(Location::Ant);
    }

    if (!isVacuous || clc::keepVacAss) {

      //create a new assertion by making a snapshot of a template

      AssertionPtr ass = generatePtr<Assertion>();
      fillAssertion(ass, t, isOffset);
      assp.push_back(ass);
      if (isVacuous) {
        dumpVac(ass->toString());
      }
    }
    // clear the template of the current dt operands
    t->getDT()->removeItems();
  }
}

void TLMiner::dumpVac(const std::string &assStr) {

  _vacLock.lock();
  _nVacAss++;
  if (clc::dumpVacAss != "") {
    std::ofstream _vacFile(clc::dumpVacAss, std::ios_base::app);
    _vacFile << assStr + "\n";
    _vacFile.close();
  }
  _vacLock.unlock();
}
void TLMiner::clear() {
  _collectedAssertions.clear();
  _nVacAss = 0;
}
} // namespace harm
