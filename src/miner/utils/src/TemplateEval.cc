#include "Semaphore.hh"
#include "Template.hh"
#include "colors.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"

#include <algorithm>
#include <math.h>
#include <mutex>
#include <sstream>
#include <sys/wait.h>
#include <thread>
#include <utility>

#define enableQuadraticEval 0

namespace harm {

size_t lf = 0;
size_t te = 0;
double getQuadFasterScore() { return (double)lf / (double)te; }
bool Template::quadFaster() {
  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;

  auto t1 = high_resolution_clock::now();
  auto t2 = high_resolution_clock::now();

  setCacheConFalse();
  setCacheAntFalse();
  quadraticEval(harm::Location::Ant);
  quadraticEval(harm::Location::Con);
  evaluate_ant(0);
  evaluate_con(0);
  t2 = high_resolution_clock::now();

  duration<double, std::milli> quadTime = t2 - t1;

  setCacheConFalse();
  setCacheAntFalse();
  t1 = high_resolution_clock::now();
  linearEval(harm::Location::Ant);
  linearEval(harm::Location::Con);
  t2 = high_resolution_clock::now();
  duration<double, std::milli> linearTime = t2 - t1;

  if ((double)quadTime.count() > ((double)linearTime.count())) {
    std::cout << "!QuadTime:" << quadTime.count() << "\n";
    std::cout << "LinearTime:" << linearTime.count() << "\n";
    std::cout << "--------------------"
              << "\n";
  }
  if (quadTime > linearTime) {
    lf++;
  }
  te++;
  return 0;
}

struct LinkedEntry {
  LinkedEntry(size_t id) : _id(id), _nextEntry(nullptr) {
    // not todo
  }
  LinkedEntry() : _id(-1), _nextEntry(nullptr) {}
  size_t _id;
  LinkedEntry *_nextEntry;
};
struct LinkedInterface {
  LinkedInterface() : _head(nullptr), _tail(nullptr) {}

public:
  LinkedEntry *_head;
  LinkedEntry *_tail;
};

#define printl 0
inline void printList(size_t n_size, size_t c_size,
                      std::vector<std::pair<size_t, LinkedInterface>> &curr,
                      std::vector<std::pair<size_t, LinkedInterface>> &next,
                      const std::string msg) {
  std::cout << msg << "\n";
  std::cout << "Next:"
            << "\n";
  for (size_t i = 0; i < n_size; i++) {
    if (next[i].second._head == nullptr) {
      continue;
    }
    LinkedEntry *it = next[i].second._head;
    std::cout << "State " << next[i].first << "\n\t";
    while (it != nullptr) {
      std::cout << it->_id << " ";
      it = it->_nextEntry;
    }
    std::cout << "\n";
  }
  std::cout << "\n";
  std::cout << "Curr:"
            << "\n";
  for (size_t i = 0; i < c_size; i++) {
    if (curr[i].second._head == nullptr) {
      continue;
    }
    LinkedEntry *it = curr[i].second._head;
    std::cout << "State " << curr[i].first << "\n\t";
    while (it != nullptr) {
      std::cout << it->_id << " ";
      it = it->_nextEntry;
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
template <bool Dynamic>
void Template::joinData(Trinary *cachedValues, Range traceRange,
                        const Range &threadsRange) {
  size_t threadIndex = threadsRange._start;
  size_t pad = traceRange._length / threadsRange._length;
  for (size_t timeIndex = traceRange._start;
       timeIndex < traceRange._start + traceRange._length; timeIndex++) {

    // increment index unless it is already the last thread
    threadIndex =
        timeIndex == (traceRange._start +
                      ((threadIndex - threadsRange._start + 1) * pad)) &&
                (threadIndex != threadsRange._start + threadsRange._length - 1)
            ? threadIndex + 1
            : threadIndex;

    cachedValues[timeIndex] = _cachedValuesP[threadIndex][timeIndex];
    if constexpr (Dynamic) {
      _dynamicShiftCachedValues[timeIndex] =
          _cachedDynShiftsP[threadIndex][timeIndex];
    }
  }
}
template <bool Dynamic>
void Template::linearEval(Automaton *aut, Trinary *cachedValues,
                          Range traceRange, Range threadsRange,
                          ProtectedQueueNotify<Range> &threadsPool) {

  if (threadsRange._length > 1 && threadsRange._length <= traceRange._length) {

    std::thread threadArray[threadsRange._length];

    for (size_t nThread = 0; nThread < threadsRange._length; ++nThread) {
      threadArray[nThread] = std::thread(
          [this, aut, cachedValues, nThread, &threadsRange, &traceRange]() {
            runLinearEval<Dynamic>(aut, cachedValues, traceRange, threadsRange,
                                   nThread);
          });
    }

    // join threads
    for (size_t i = 0; i < threadsRange._length; ++i)
      threadArray[i].join();

    joinData<Dynamic>(cachedValues, traceRange, threadsRange);
  } else {
    // only 1 thread
    runLinearEval<Dynamic>(aut, cachedValues, traceRange,
                           Range(threadsRange._start, 1));
    joinData<Dynamic>(cachedValues, traceRange, Range(threadsRange._start, 1));
  }

  // notify the end and free the threads
  threadsPool.push(threadsRange);
}

template <bool Dynamic>
inline void Template::runLinearEval(Automaton *aut, Trinary *cachedValues,
                                    Range &traceRange,
                                    const Range &threadsRange, size_t nThread) {
  size_t pad = traceRange._length / threadsRange._length;
  // sp is exacly the first eval unit
  size_t sp = traceRange._start + nThread * pad;
  // ep is 1 unit after the last eval unit
  size_t ep = (nThread == (threadsRange._length - 1))
                  ? (traceRange._start + traceRange._length)
                  : (sp + pad);
  // debug
  // std::cout << "sp: "<<sp<<" ep: "<<ep << "\n";

  // to handle the case in which time >= ep but there are still unresolved
  // units in the states (due to parallelism)
  bool noActiveInstances = true;

  size_t nStates = aut->_idToNode.size();
  std::vector<std::pair<size_t, LinkedInterface>> curr;
  std::vector<std::pair<size_t, LinkedInterface>> next;
  for (size_t i = 0; i < nStates; i++) {
    curr.emplace_back(i, LinkedInterface());
    next.emplace_back(i, LinkedInterface());
  }

  for (size_t time = sp; time < traceRange._start + traceRange._length;
       time++) {
    // next -> curr
#if printl
    printList(next.size(), curr.size(), curr, next, "next->curr");
#endif

    for (auto &n : next) {
      if (n.second._head == nullptr) {
        continue;
      }
      if (curr[n.first].second._head == nullptr) {
        curr[n.first].second._head = n.second._head;
        curr[n.first].second._tail = n.second._tail;
      } else {
        curr[n.first].second._tail->_nextEntry = n.second._head;
        curr[n.first].second._tail = n.second._tail;
      }
      n.second._head = nullptr;
      n.second._tail = nullptr;
      // we still have work to do
      noActiveInstances = false;
    }

    // next empty (all to nullptr)
#if printl
    printList(next.size(), curr.size(), curr, next, "After: next->curr");
#endif
    // increment root state
    if (time < ep) {
      if (curr[0].second._head == nullptr) {
        curr[0].second._head = new LinkedEntry(time);
        curr[0].second._tail = curr[0].second._head;
      } else {
        curr[0].second._tail->_nextEntry = new LinkedEntry(time);
        curr[0].second._tail = curr[0].second._tail->_nextEntry;
      }
    } else if (noActiveInstances) {
      break;
    }
    // curr -> next

#if printl
    printList(next.size(), curr.size(), curr, next, "curr->next");
#endif
    for (auto &c : curr) {
      if (c.second._head == nullptr) {
        continue;
      }
      for (const auto &edge : aut->_idToNode.at(c.first)->_outEdges) {
        if (edge->_prop->evaluate(time)) {
          // pass the tokens
          if (edge->_toNode->_type == 0) {
            LinkedEntry *it = c.second._head;
            assert(it != nullptr);
            while (it != nullptr) {
              this->_cachedValuesP[threadsRange._start + nThread][it->_id] =
                  Trinary::F;
              if constexpr (Dynamic) {
                this->_cachedDynShiftsP[threadsRange._start + nThread]
                                       [it->_id] = time - it->_id;
              }
              LinkedEntry *toDelete = it;
              it = it->_nextEntry;
              delete toDelete;
            }
          } else if (edge->_toNode->_type == 1) {
            LinkedEntry *it = c.second._head;
            assert(it != nullptr);
            while (it != nullptr) {
              this->_cachedValuesP[threadsRange._start + nThread][it->_id] =
                  Trinary::T;
              if constexpr (Dynamic) {
                this->_cachedDynShiftsP[threadsRange._start + nThread]
                                       [it->_id] = time - it->_id;
              }
              LinkedEntry *toDelete = it;
              it = it->_nextEntry;
              delete toDelete;
            }
          } else {
            if (next[edge->_toNode->_id].second._head == nullptr) {
              next[edge->_toNode->_id].second._head = c.second._head;
              next[edge->_toNode->_id].second._tail = c.second._tail;
            } else {
              next[edge->_toNode->_id].second._tail->_nextEntry =
                  c.second._head;
              next[edge->_toNode->_id].second._tail = c.second._tail;
            }
          }
          c.second._head = nullptr;
          c.second._tail = nullptr;
          break;
        }
      }

#if printl
      printList(next.size(), curr.size(), curr, next, "After: curr->next");
      std::cout << "--------------------------"
                << "\n";
#endif
    }
    noActiveInstances = true;
  }
  // Unknown instances
  for (auto &n : next) {
    if (n.second._head == nullptr) {
      continue;
    }
    LinkedEntry *it = n.second._head;
    assert(it != nullptr);
    while (it != nullptr) {
      this->_cachedValuesP[threadsRange._start + nThread][it->_id] = Trinary::U;
      if constexpr (Dynamic) {
        this->_cachedDynShiftsP[threadsRange._start + nThread][it->_id] =
            (traceRange._start + traceRange._length - 1) - it->_id;
      }
      LinkedEntry *toDelete = it;
      it = it->_nextEntry;
      delete toDelete;
    }

    n.second._head = nullptr;
    n.second._tail = nullptr;
  }
}

template <bool Dynamic>
inline void Template::evalWithCut(Automaton *aut, Trinary *cachedValues) {
  _l1Guard.lock();
  size_t avThreads = std::min(_availThreads, l1Constants::MAX_THREADS);
  _l1Guard.unlock();
  size_t start = 0;
  ProtectedQueueNotify<Template::Range> threadsPool;
  auto &cuts = _trace->getCuts();
  if (cuts.size() > 1) {
    size_t toWaitFor = 0;
    for (size_t i = 0; i < cuts.size() && avThreads > 0; i++) {
      //      FIXME
      //      size_t nThreads = cuts[i] < 5000 /*heuristic optimization*/
      //                            ? 1
      //                            : std::ceil((double)avThreads /
      //                                        (double)(_trace->getCuts().size()
      //                                        - i));
      size_t nThreads = 1;
      threadsPool.push(Range(start, nThreads));
      avThreads -= nThreads;
      start += nThreads;
      toWaitFor++;
    }
    size_t prevCut = 0;
    for (size_t i = 0; i < cuts.size(); i++) {
      auto &cut = cuts[i];
      auto threadsRange = threadsPool.pop();
      auto traceRange = Range(prevCut, (cut - prevCut) + 1);
      // debug
      // std::cout << "["<<traceRange._start<<", "<<traceRange._length <<"] | ";
      // std::cout << "["<<threadsRange._start<<", "<<threadsRange._length
      // <<"]\n";
      std::thread t(&Template::linearEval<Dynamic>, this, aut, cachedValues,
                    traceRange, threadsRange, std::ref(threadsPool));
      t.detach();

      //t.join();
      //          
      prevCut = cut + 1;
    }

    for (size_t i = 0; i < toWaitFor; i++) {
      threadsPool.pop();
    }
  } else {
    linearEval<Dynamic>(aut, cachedValues, Range(0, _trace->getLength()),
                        Range(0, _max_length < 5000 /*heuristic optimization*/ ? 1
                                     : avThreads),
                        threadsPool);
  }
}

void Template::linearEval(harm::Location what) {

  switch (what) {
  case harm::Location::Ant:
#if printl
    std::cout << "ANTECEDENT"
              << "\n";
#endif
    if (!_antInCache) {
      if (_applyDynamicShift) {
        evalWithCut<1>(_ant, _antCachedValues);
      } else {
        evalWithCut<0>(_ant, _antCachedValues);
      }
      _antInCache = true;
    }
    break;
  case harm::Location::Con:
#if printl
    std::cout << "CONSEQUENT"
              << "\n";
#endif
    if (!_conInCache) {
      evalWithCut<0>(_con, _conCachedValues);
      _conInCache = true;
    }
    break;
  case harm::Location::AntCon:
    if (!_antInCache) {
      if (_applyDynamicShift) {
        evalWithCut<1>(_ant, _antCachedValues);
      } else {
        evalWithCut<0>(_ant, _antCachedValues);
      }
      _antInCache = true;
    }
    if (!_conInCache) {
      evalWithCut<0>(_con, _conCachedValues);
      _conInCache = true;
    }
    break;
  case harm::Location::None:
    break;
  }
}
void Template::quadraticEval(harm::Location what) {
  switch (what) {
  case harm::Location::Ant:
#if printl
    std::cout << "ANTECEDENT"
              << "\n";
#endif
    if (!_antInCache) {
      if (_applyDynamicShift) {
        quadraticEvalDynamic(_ant, _antCachedValues);
      } else {
        quadraticEval(_ant, _antCachedValues);
      }
      _antInCache = true;
    }
    break;
  case harm::Location::Con:
#if printl
    std::cout << "CONSEQUENT"
              << "\n";
#endif
    if (!_conInCache) {
      quadraticEval(_con, _conCachedValues);
      _conInCache = true;
    }
    break;
  case harm::Location::AntCon:
    if (!_antInCache) {
      if (_applyDynamicShift) {
        quadraticEvalDynamic(_ant, _antCachedValues);
      } else {
        quadraticEval(_ant, _antCachedValues);
      }
      _antInCache = true;
    }
    if (!_conInCache) {
      quadraticEval(_con, _conCachedValues);
      _conInCache = true;
    }
    break;
  case harm::Location::None:
    break;
  }
}
void Template::quadraticEvalDynamic(Automaton *aut, Trinary *cachedValues) {

  _l1Guard.lock();
  size_t feasThreads = std::min(_availThreads, l1Constants::MAX_THREADS);
  _l1Guard.unlock();

  std::thread threadArray[feasThreads];

  size_t length = _max_length;

  for (size_t nThread = 0; nThread < feasThreads; ++nThread) {
    threadArray[nThread] =
        std::thread([this, nThread, length, aut, feasThreads]() {
          size_t j = 0;
          size_t dShift;
          for (size_t i = nThread; i < length; i += feasThreads) {
            _cachedValuesP[nThread][j] = evalAutomatonDyShift(i, aut, dShift);
            _cachedDynShiftsP[nThread][j] = dShift - i;
            j++;
          }
        });
  }
  // join threads
  for (size_t i = 0; i < feasThreads; ++i)
    threadArray[i].join();

  size_t j = 0;
  for (size_t i = 0; i < _max_length; i += feasThreads) {
    for (size_t ti = 0; ti < feasThreads && (i + ti) < _max_length; ti++) {
      cachedValues[i + ti] = _cachedValuesP[ti][j];
      _dynamicShiftCachedValues[i + ti] = _cachedDynShiftsP[ti][j];
    }
    j++;
  }
}
void Template::quadraticEval(Automaton *aut, Trinary *cachedValues) {

  _l1Guard.lock();
  size_t feasThreads = std::min(_availThreads, l1Constants::MAX_THREADS);
  _l1Guard.unlock();
  std::thread threadArray[feasThreads];

  size_t length = _max_length;

  for (size_t nThread = 0; nThread < feasThreads; ++nThread) {
    threadArray[nThread] =
        std::thread([this, nThread, length, aut, feasThreads]() {
          size_t j = 0;
          for (size_t i = nThread; i < length; i += feasThreads) {
            _cachedValuesP[nThread][j] = evalAutomaton(i, aut);
            j++;
          }
        });
  }
  // join threads
  for (size_t i = 0; i < feasThreads; ++i)
    threadArray[i].join();

  size_t j = 0;
  for (size_t i = 0; i < _max_length; i += feasThreads) {
    for (size_t ti = 0; ti < feasThreads && (i + ti) < _max_length; ti++) {
      cachedValues[i + ti] = _cachedValuesP[ti][j];
    }
    j++;
  }
}
Trinary Template::evaluateOffset(size_t time) {

#if enableQuadraticEval
  quadraticEval(harm::Location::AntCon);
#else
  linearEval(harm::Location::AntCon);
#endif
  size_t shift = time +
                 (_applyDynamicShift ? _dynamicShiftCachedValues[time] : 0) +
                 _constShift;
  return !_antCachedValues[time] ||
         ((shift >= _max_length) ? Trinary::U : !_conCachedValues[(shift)]);
}

Trinary Template::evaluate(size_t time) {

#if enableQuadraticEval
  quadraticEval(harm::Location::AntCon);
#else
  linearEval(harm::Location::AntCon);
#endif
  size_t shift = time +
                 (_applyDynamicShift ? _dynamicShiftCachedValues[time] : 0) +
                 _constShift;
  return !_antCachedValues[time] ||
         ((shift >= _max_length) ? Trinary::U : _conCachedValues[(shift)]);
}
Trinary Template::evaluateAntNoChache(size_t time) {
  return evalAutomaton(time, _ant);
}
Trinary Template::evaluate_ant(size_t time) {
#if enableQuadraticEval
  quadraticEval(harm::Location::Ant);
#else
  linearEval(harm::Location::Ant);
#endif

  return _antCachedValues[time];
}
Trinary Template::evaluate_con(size_t time) {
#if enableQuadraticEval
  quadraticEval(harm::Location::Con);
#else
  linearEval(harm::Location::Con);
#endif

  return _conCachedValues[time];
}

Trinary Template::evalAutomaton(size_t time, Automaton *root) const {
  Automaton::Node *cn = root->_root;
  /* visit the automaton by evaluating the edges (which are propositions)
   */
  while (time < _max_length) {
    for (const auto &edge : cn->_outEdges) {
      // if "the current cn->_outEdges[i] is true at instant 'time'"
      if (edge->_prop->evaluate(time)) {
        if (edge->_toNode->_type == 0)
          return Trinary::F;
        else if (edge->_toNode->_type == 1) {
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
  return Trinary::U;
}
Trinary Template::evalAutomatonDyShift(size_t time, Automaton *root,
                                       size_t &dShift) {
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
bool Template::assHoldsOnTrace(harm::Location update) {

  switch (update) {
  case harm::Location::None:
    break;
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
  }

  for (size_t i = 0; i < _max_length; i++) {
    if (evaluate(i) == Trinary::F) {
      return false;
    }
  }
  return true;
}
bool Template::assHoldsOnTraceOffset(harm::Location update) {

  switch (update) {
  case harm::Location::None:
    break;
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
  }

  for (size_t i = 0; i < _max_length; i++) {
    if (evaluateOffset(i) == Trinary::F) {
      return false;
    }
  }
  return true;
}
bool Template::isVacuous(harm::Location update) {
  switch (update) {
  case harm::Location::None:
    break;
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
  }

  for (size_t i = 0; i < _max_length; i++) {
    if (evaluate_ant(i) == Trinary::T && evaluate(i) == Trinary::T) {
      goto nextCondition;
    }
  }
  return true;

nextCondition:;
  for (size_t i = 0; i < _max_length; i++) {
    if (evaluate_con(i) == Trinary::F) {
      return false;
    }
  }
  return true;
}
bool Template::isVacuousOffset(harm::Location update) {
  switch (update) {
  case harm::Location::None:
    break;
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
  }

  for (size_t i = 0; i < _max_length; i++) {
    if (evaluate_ant(i) == Trinary::T && evaluate(i) == Trinary::F) {
      goto nextCondition;
    }
  }
  return true;

nextCondition:;
  for (size_t i = 0; i < _max_length; i++) {
    if (evaluate_con(i) == Trinary::T) {
      return false;
    }
  }
  return true;
}
} // namespace harm
