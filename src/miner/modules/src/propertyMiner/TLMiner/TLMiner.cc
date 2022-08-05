#include "TLMiner.hh"
#include "AntecedentGenerator.hh"
#include "Assertion.hh"
#include "Template.hh"
#include "globals.hh"
#include "minerUtils.hh"
#include "supportMethods.hh"

#include <algorithm>
#include <chrono>
#include <csignal>
#include <fstream>
#include <iostream>
#include <list>
#include <math.h>
#include <mutex>
#include <regex>
#include <spot/tl/print.hh>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace harm {

TLMiner::TLMiner() : PropertyMiner() {}

TLMiner::~TLMiner() {}

void TLMiner::mineProperties(Context &context, Trace *trace) {
#if dumpVacAss
  std::ofstream vacFile("vac.txt", ios_base::out);
  vacFile.close();
#endif

  _traceLength = trace->getLength();
  messageInfo("CONTEXT: " + context._name);

  // fill vector of ant, con, antcon
  for (auto pl : context._props) {
    messageInfo("PROP: " + prop2String(*pl.first));
    switch (pl.second) {
    case Location::Ant:
      _propsAnt.push_back(pl.first);
      break;
    case Location::Con:
      _propsCon.push_back(pl.first);
      break;
    case Location::AntCon:
      _propsAntCon.push_back(pl.first);
      break;
    case Location::DecTree:
      _propsDT.push_back(pl.first);
      break;
    case harm::Location::None:
      break;
    }
  }

  // fill numerics (clustering)
  for (CachedAllNumeric *ne : context._numerics) {
    _numerics.push_back(ne);
    messageInfo("NUMERIC: " + allNum2String(*ne));
  }

  l3Handler(context, clc::maxThreads);

  //store all the generated assertions into the context
  for (auto &pack : _collectedAssertions) {
    for (Assertion *ass : pack) {
      context._assertions.push_back(ass);
    }
  }

  //clear: necessary if TLMiner is reused (multiple contexts)
  clear();
}

void TLMiner::l3Handler(Context &context, size_t nThread) {

  //spot does not suppoty multithreading: need guard
  std::mutex spotStupidity;
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

    if (toBeServed < context._templates.size() &&
        l3Instances.size() < l3Constants::MAX_THREADS) {
      //mine a new template and give it the thread
      l3InstToNumThreads[toBeServed] = 1;
      l3Instances[toBeServed] = new Semaphore(1);
      Template *t = context._templates[toBeServed];
      //start a new l2Instance (new permutation of the current template)
      std::thread(&TLMiner::l2Handler, this, t, toBeServed,
                  std::ref(l3Instances), std::ref(l3avThreads),
                  std::ref(spotStupidity), std::ref(l3InstancesGuard),
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

#if enPB
  _progressBar.done();
#endif
  assert(l3avThreads.getAvailable() == nThread - 1);
}
void TLMiner::l2Handler(
    Template *t, size_t l3InstId,
    std::unordered_map<size_t, Semaphore *> &l3Instances,
    Semaphore &l3avThreads, std::mutex &spotStupidity,
    std::mutex &l3InstancesGuard,
    std::unordered_map<size_t, size_t> &l3InstToNumThreads) {
  //this function follows the same principles of l3Handler; however, we create a new Template instance for each permutation to avoid sharing memory

  Semaphore *l2avThreads = atGuard(l3Instances, l3InstId, l3InstancesGuard);
  std::unordered_map<size_t, size_t> l2Instances;
  size_t toBeServed = 0;
  size_t l2MaxThread = 2;
  std::vector<Template *> templs;
  std::vector<size_t> busyTemplates;
  std::vector<size_t> freeTemplates;
  std::unordered_map<size_t, size_t> templIndexTol2Inst;
  std::unordered_map<size_t, size_t> instToTemplIndex;
  std::mutex l2InstancesGuard;

  {
    std::lock_guard<std::mutex> lock{spotStupidity};
    t->genPermutations(_propsAnt, _propsCon, _propsAntCon);
#if enPB
    _progressBar.addInstance(l3InstId, t->getColoredTemplate(),
                             t->nPermsGenerated(), 70);
    _progressBar.enableCounter(l3InstId);
#endif
  }

  while (1) {
    l2avThreads->wait();
    std::lock_guard<std::mutex> lock{l2InstancesGuard};
    if (toBeServed < t->nPermsGenerated() &&
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
      Template *nextTemp = nullptr;
      if (freeTemplates.empty()) {
        // new copy
        std::lock_guard<std::mutex> lock{spotStupidity};
        busyTemplates.push_back(templs.size());
        templIndexTol2Inst[templs.size()] = toBeServed;
        instToTemplIndex[toBeServed] = templs.size();
        templs.push_back(new Template(*t));
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
      std::thread(&TLMiner::l1Handler, this, nextTemp, toBeServed, l3InstId,
                  std::ref(l2avThreads), std::ref(l2Instances),
                  std::ref(l2InstancesGuard))
          .detach();
      toBeServed++;
    } else if (!l2Instances.empty()) {
      for (auto &e : l2Instances) {
        if (e.second < l2MaxThread) {
          e.second++;
          templs[instToTemplIndex.at(e.first)]->setL1Threads(e.second);
          goto found;
        }
      }
      l2Instances.begin()->second++;
      templs[instToTemplIndex.at(l2Instances.begin()->first)]->setL1Threads(
          l2Instances.begin()->second);
      l2MaxThread++;
    found:;
    } else {
      break;
    }
    // Debug
    //    #if enPB
    //          _progressBar.changeMessage(
    //              l3InstId, std::to_string(l3InstToNumThreads.at(l3InstId)));
    //    #endif
  }

  for (size_t i = 0; i < templs.size(); i++) {
    delete templs[i];
  }

  //debug
  //#if enPB
  //    _progressBar.changeMessage(l3InstId, std::to_string(0));
  _progressBar.done(l3InstId);
  //#endif

  std::lock_guard<std::mutex> lock{l3InstancesGuard};
  size_t nThreads = l3Instances.at(l3InstId)->getAvailable() + 1;
  delete l3Instances.at(l3InstId);
  l3Instances.erase(l3InstId);

  l3avThreads.addNotifyOnce(nThreads);
}
void TLMiner::l1Handler(Template *t, size_t l2InstId, size_t l3InstId,
                        Semaphore *l2avThreads,
                        std::unordered_map<size_t, size_t> &l2Instances,
                        std::mutex &l2InstancesGuard) {

  std::vector<Assertion *> assp;
  t->loadPerm(l2InstId);

  if (t->getDT() != nullptr) {

    DecTreeVariables candidateVariables;
    for (size_t i = 0; i < _propsDT.size(); i++) {
      candidateVariables[i].first = _propsDT[i];
      candidateVariables[i].second =
          makeExpression<PropositionNot>(_propsDT[i]);
    }

    if (t->isVacuous(harm::Location::AntCon)) {
#if enPB
      _progressBar.increment(l3InstId);
      _progressBar.display();
#endif
      goto end;
    }

    AntecedentGenerator antGen;

    antGen.saveOffset = t->saveOffset();

    DecTreeVariables candidateVariables_copy;
    //creating a copy of candidateVariables to pass as parameter to decision tree algorithm
    candidateVariables_copy = candidateVariables;

    NumericDecTreeExp numericCandidates;
    for (size_t i = 0; i < _numerics.size(); i++) {
      numericCandidates[i] = _numerics[i];
    }

    std::vector<Proposition *> genProps;

    antGen.makeAntecedents(t, candidateVariables_copy, numericCandidates,
                           genProps);

    // Onset
    for (std::vector<Proposition *> &props : antGen.onSets) {

      //rebulding the assertion starting from a list propositions (the operands of a dt operator)
      if (t->getDT()->isMultiDimensional()) {
        for (size_t i = 0; i < props.size(); i++) {
          for (auto prop : t->getDT()->unpack(props[i])) {
            t->getDT()->addItem(prop, i);
          }
        }
      } else {
        for (auto prop : props) {
          t->getDT()->addItem(prop, -1);
        }
      }

      assert(!t->getDT()->getItems().empty());

      //check for vacuity
      if (!t->isVacuous(Location::Ant)) {

        //create a new assertion by making a snapshot of a template
        auto prettyAss = t->getDT()->prettyPrint(0);
        Assertion *ass = new Assertion();
        t->fillContingency(ass->_ct, 0);
        ass->_toString = prettyAss;
        auto loadedProps = t->getLoadedPropositions();
        ass->_complexity = getNumVariables(loadedProps);
        ass->_pRepetitions = getRepetitions(loadedProps);
        ass->fillValues(t);

        assp.push_back(ass);
        messageErrorIf(!t->assHoldsOnTrace(harm::Location::None),
                       "dt assertion is false: " + t->getColoredAssertion());
      }
#if dumpVacAss

      else {
        vacLock.lock();
        std::ofstream vacFile("vac.txt", ios_base::app);
        vacFile << t->getDT()->prettyPrint(0).first + "\n";
        vacFile.close();
        vacLock.unlock();
      }
#endif
      // clear the template of the current dt operands
      t->getDT()->removeItems();
      if (t->getDT()->isMultiDimensional()) {
        for (size_t i = 0; i < props.size(); i++) {
          t->getDT()->clearPack(props[i]);
          delete props[i];
        }
      }
    }

    // Offset, same as onset but the consequent is negated
    for (const std::vector<Proposition *> &props : antGen.offSets) {
      if (t->getDT()->isMultiDimensional()) {
        for (size_t i = 0; i < props.size(); i++) {
          for (auto prop : t->getDT()->unpack(props[i])) {
            t->getDT()->addItem(prop, i);
          }
        }

      } else {
        for (auto prop : props) {
          t->getDT()->addItem(prop, -1);
        }
      }

      assert(!t->getDT()->getItems().empty());

      if (!t->isVacuousOffset(Location::Ant)) {
        auto prettyAss = t->getDT()->prettyPrint(1);
        Assertion *ass = new Assertion();
        t->fillContingency(ass->_ct, 1);
        ass->_toString = prettyAss;
        auto loadedProps = t->getLoadedPropositions();
        ass->_complexity = getNumVariables(loadedProps);
        ass->_pRepetitions = getRepetitions(loadedProps);
        ass->fillValuesOffset(t);
        assp.push_back(ass);
      }
#if dumpVacAss

      else {
        vacLock.lock();
        std::ofstream vacFile("vac.txt", ios_base::app);
        vacFile << t->getDT()->prettyPrint(1).first + "\n";
        vacFile.close();
        vacLock.unlock();
      }
#endif

      t->getDT()->removeItems();
      if (t->getDT()->isMultiDimensional()) {
        for (size_t i = 0; i < props.size(); i++) {
          t->getDT()->clearPack(props[i]);
          delete props[i];
        }
      }
    }

#if enPB
    _progressBar.increment(l3InstId);
    _progressBar.display();
#endif

    //deallocate memory for negated candidate variables
    for (size_t i = 0; i < _propsDT.size(); i++) {
      dynamic_cast<PropositionNot *>(candidateVariables[i].second)->popItem();
      delete candidateVariables[i].second;
    }
    candidateVariables.clear();
    //delete all generated propositions from numeric expressions and clustering
    for (auto p : genProps) {
      delete p;
    }
    numericCandidates.clear();

  } // dt
  else {
    // If the template does not have a dt

    if (!t->isVacuous(harm::Location::AntCon) &&
        t->assHoldsOnTrace(harm::Location::None)) {

      //create a new assertion by making a snapshot of a template
      Assertion *ass = new Assertion();
      t->fillContingency(ass->_ct, 0);
      ass->_toString =
          std::make_pair(t->getAssertion(), t->getColoredAssertion());
      auto loadedProps = t->getLoadedPropositions();
      ass->_complexity = getNumVariables(loadedProps);
      ass->_pRepetitions = getRepetitions(loadedProps);
      ass->fillValues(t);
      assp.push_back(ass);
      messageErrorIf(ass->_ct[0][0] == 0, "!ATCT");
      messageErrorIf(ass->_ct[0][1] > 0, "ATCF");
    }
#if dumpVacAss
    else {
      if (t->isVacuous(harm::Location::AntCon)) {
        vacLock.lock();
        std::ofstream vacFile("vac.txt", ios_base::app);
        vacFile << t->getAssertion() + "\n";
        vacFile.close();
        vacLock.unlock();
      }
    }
#endif
#if enPB
    _progressBar.increment(l3InstId);
    _progressBar.display();
#endif
  } // else

end:;
  //store the assertions collected in the current permutation
  if (!assp.empty()) {
    std::lock_guard<std::mutex> lock{_collectedAssertionsGuard};
    _collectedAssertions.push_back(assp);
  }
#if enPB
  _progressBar.incrementCounter(l3InstId, assp.size());
#endif

  //delete this instance and notify the upper level
  std::lock_guard<std::mutex> lock{l2InstancesGuard};
  size_t nThreads = l2Instances.at(l2InstId);
  l2Instances.erase(l2InstId);
  l2avThreads->addNotifyOnce(nThreads);
}

void TLMiner::clear() {
  _propsAnt.clear();
  _propsCon.clear();
  _propsAntCon.clear();
  _propsDT.clear();
  _numerics.clear();
  _collectedAssertions.clear();
}
} // namespace harm
