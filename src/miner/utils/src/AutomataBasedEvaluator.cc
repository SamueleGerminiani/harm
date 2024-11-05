#include "AutomataBasedEvaluator.hh"
#include "Automaton.hh"
#include "EdgeProposition.hh"
#include "Semaphore.hh"
#include "globals.hh"
#include "minerUtils.hh"
#include <thread>
#include <unordered_map>

#ifdef SPOTLTL
#include "spot/twa/bddprint.hh"
#include "spot/twa/twa.hh"
#include "spot/twa/twagraph.hh"
#include "spot/twaalgos/translate.hh"
#include <spot/tl/formula.hh>
#include <spot/tl/parse.hh>
#include <spot/tl/print.hh>
#include <spot/twaalgos/isdet.hh>
#include <spot/twaalgos/postproc.hh>
#endif

namespace harm {

//static functions

#ifdef SPOTLTL
/** \brief generate a FSM from a spot formula
   */
static std::shared_ptr<spot::twa_graph>
generateDeterministicSpotAutomaton(const spot::formula &formula);

/** \brief builds a custom automaton (see class Automaton) from a spotLTL automaton
   */
static Automaton *
buildAutomatonFromSpot(spot::twa_graph_ptr &automata,
                       const PlaceholderPack &pack);

/** \brief converts a spot LTL formula to an edge custom proposition
   */
static EdgeProposition *
spotEdgeToProposition(const spot::formula &f,
                      const PlaceholderPack &pack);
/// @brief syntax sugar for printing a spot formula
static std::string to_string(const spot::formula &f);

///@brief returns tree if the string is a tokenplaceholder
static bool isPlaceholderStr(const std::string &s);
///@brief returns true if the string is an instance
static bool isInstStr(const std::string &s);
///@brief returns true if the string is a DTO placeholder
static bool isDTO_Str(const std::string &s);

#endif

//------------------------------AutomatataBased class-----------------------------------
//
AutomataBasedEvaluator::AutomataBasedEvaluator(
    const TemporalExpressionPtr &formula, const TracePtr &trace)
    : Evaluator(formula, trace) {
  generateAutomaton();
  initCache();
}

AutomataBasedEvaluator::~AutomataBasedEvaluator() {
  // Free _cacheParallel
  if (_cacheParallel) {
    for (size_t i = 0; i < l1Constants::MAX_THREADS; i++) {
      delete[] _cacheParallel[i]; // Delete each row
    }
    delete[] _cacheParallel;  // Delete the array of pointers
    _cacheParallel = nullptr; // Set to nullptr for safety
  }

  // Free _cache
  delete[] _cache;
  _cache = nullptr; // Set to nullptr for safety

  // Free _sereShiftCache
  delete[] _sereShiftCache;
  _sereShiftCache = nullptr; // Set to nullptr for safety

  // Free _sereShiftCacheParallel
  if (_sereShiftCacheParallel) {
    for (size_t i = 0; i < l1Constants::MAX_THREADS; i++) {
      delete[] _sereShiftCacheParallel[i]; // Delete each row
    }
    delete[] _sereShiftCacheParallel;  // Delete the array of pointers
    _sereShiftCacheParallel = nullptr; // Set to nullptr for safety
  }
}

void AutomataBasedEvaluator::changeTrace(
    const harm::TracePtr &trace) {
  expression::changeTrace(_formula, trace);
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
void printList(size_t n_size, size_t c_size,
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
void AutomataBasedEvaluator::joinData(Range traceRange,
                                      const Range &threadsRange) {
  size_t threadIndex = threadsRange._start;
  size_t pad = traceRange._length / threadsRange._length;
  for (size_t timeIndex = traceRange._start;
       timeIndex < traceRange._start + traceRange._length;
       timeIndex++) {

    // increment index unless it is already the last thread
    threadIndex =
        timeIndex == (traceRange._start +
                      ((threadIndex - threadsRange._start + 1) *
                       pad)) &&
                (threadIndex !=
                 threadsRange._start + threadsRange._length - 1)
            ? threadIndex + 1
            : threadIndex;

    _cache[timeIndex] = _cacheParallel[threadIndex][timeIndex];
    if constexpr (Dynamic) {
      _sereShiftCache[timeIndex] =
          _sereShiftCacheParallel[threadIndex][timeIndex];
    }
  }
}
template <bool Dynamic>
void AutomataBasedEvaluator::linearEval(
    Range traceRange, Range threadsRange,
    ProtectedQueueNotify<Range> &threadsPool) {

  if (threadsRange._length > 1 &&
      threadsRange._length <= traceRange._length) {

    std::thread threadArray[threadsRange._length];

    for (size_t nThread = 0; nThread < threadsRange._length;
         ++nThread) {
      threadArray[nThread] =
          std::thread([this, nThread, &threadsRange, &traceRange]() {
            runLinearEval<Dynamic>(traceRange, threadsRange, nThread);
          });
    }

    // join threads
    for (size_t i = 0; i < threadsRange._length; ++i)
      threadArray[i].join();

    joinData<Dynamic>(traceRange, threadsRange);
  } else {
    // only 1 thread
    runLinearEval<Dynamic>(traceRange, Range(threadsRange._start, 1));
    joinData<Dynamic>(traceRange, Range(threadsRange._start, 1));
  }

  // notify the end and free the threads
  threadsPool.push(threadsRange);
}

template <bool Dynamic>
void AutomataBasedEvaluator::runLinearEval(Range &traceRange,
                                           const Range &threadsRange,
                                           size_t nThread) {
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

  size_t nStates = _automaton->_idToNode.size();
  std::vector<std::pair<size_t, LinkedInterface>> curr;
  std::vector<std::pair<size_t, LinkedInterface>> next;
  for (size_t i = 0; i < nStates; i++) {
    curr.emplace_back(i, LinkedInterface());
    next.emplace_back(i, LinkedInterface());
  }

  for (size_t time = sp;
       time < traceRange._start + traceRange._length; time++) {
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
    printList(next.size(), curr.size(), curr, next,
              "After: next->curr");
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
      for (const auto &edge :
           _automaton->_idToNode.at(c.first)->_outEdges) {
        if (edge->_prop->evaluate(time)) {
          // pass the tokens
          if (edge->_toNode->_type ==
              Automaton::Node::Type::Rejecting) {
            LinkedEntry *it = c.second._head;
            assert(it != nullptr);
            while (it != nullptr) {
              this->_cacheParallel[threadsRange._start + nThread]
                                  [it->_id] = Trinary::F;
              if constexpr (Dynamic) {
                this->_sereShiftCacheParallel[threadsRange._start +
                                              nThread][it->_id] =
                    time - it->_id;
              }
              LinkedEntry *toDelete = it;
              it = it->_nextEntry;
              delete toDelete;
            }
          } else if (edge->_toNode->_type ==
                     Automaton::Node::Type::Accepting) {
            LinkedEntry *it = c.second._head;
            assert(it != nullptr);
            while (it != nullptr) {
              this->_cacheParallel[threadsRange._start + nThread]
                                  [it->_id] = Trinary::T;
              if constexpr (Dynamic) {
                this->_sereShiftCacheParallel[threadsRange._start +
                                              nThread][it->_id] =
                    time - it->_id;
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
      printList(next.size(), curr.size(), curr, next,
                "After: curr->next");
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
      this->_cacheParallel[threadsRange._start + nThread][it->_id] =
          Trinary::U;
      if constexpr (Dynamic) {
        this->_sereShiftCacheParallel[threadsRange._start + nThread]
                                     [it->_id] =
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

template <bool Dynamic> void AutomataBasedEvaluator::evalWithCut() {
  _l1ThreadsGuard.lock();
  size_t avThreads = std::min(_l1Threads, l1Constants::MAX_THREADS);
  _l1ThreadsGuard.unlock();
  size_t start = 0;
  ProtectedQueueNotify<AutomataBasedEvaluator::Range> threadsPool;
  auto &cuts = _trace->getCuts();
  if (cuts.size() > 1) {
    size_t toWaitFor = 0;
    for (size_t i = 0; i < cuts.size() && avThreads > 0; i++) {
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
      linearEval<Dynamic>(traceRange, threadsRange, threadsPool);
      prevCut = cut + 1;
    }

    for (size_t i = 0; i < toWaitFor; i++) {
      threadsPool.pop();
    }
  } else {
    linearEval<Dynamic>(
        Range(0, _trace->getLength()),
        Range(0, _trace->getLength() < 5000 /*heuristic optimization*/
                     ? 1
                     : avThreads),
        threadsPool);

    //linearEval<Dynamic>(Range(0, _trace->getLength()), Range(0, avThreads), threadsPool);
  }
}

void AutomataBasedEvaluator::linearEval(harm::Location what) {
  if (_inCache) {
    return;
  }
  evalWithCut<true>();
  _inCache = true;
}

std::pair<Trinary, size_t>
AutomataBasedEvaluator::evaluate(size_t time) {
  linearEval(harm::Location::AntCon);
  return std::make_pair(_cache[time], _sereShiftCache[time]);
}

template <bool Dynamic>
std::pair<Trinary, size_t>
AutomataBasedEvaluator::evaluateAutomaton(size_t time) {
  size_t dShift = 0;
  Automaton::Node *cn = _automaton->_root;
  /* visit the automaton by evaluating the edges (which are propositions)
   */
  while (time < _trace->getLength()) {
    for (const auto &edge : cn->_outEdges) {
      // if "the current cn->_outEdges[i] is true at instant 'time'"
      if (edge->_prop->evaluate(time)) {
        if (edge->_toNode->_type ==
            Automaton::Node::Type::Rejecting) {
          if constexpr (Dynamic) {
            // store the dynamic shift for the current evaluation
            dShift = time;
          }
          return {Trinary::F, dShift};
        } else if (edge->_toNode->_type ==
                   Automaton::Node::Type::Accepting) {
          if constexpr (Dynamic) {
            // store the dynamic shift for the current evaluation
            dShift = time;
          }
          return {Trinary::T, dShift};
        }

        // go to the next state
        cn = edge->_toNode;
        break;
      }
    }
    // each time we change state, time increases by 1
    time++;
  }
  if constexpr (Dynamic) {
    // store the dynamic shift for the current evaluation
    dShift = time;
  }
  return {Trinary::U, dShift};
}

void AutomataBasedEvaluator::generateAutomaton() {

#ifdef SPOTLTL
  {
    static std::mutex spotGuard;
    std::lock_guard<std::mutex> lock{spotGuard};
    //retrieve the string representation of temporal formula
    std::string spotFormulaStr =
        temp2String(_formula, Language::SpotLTL, PrintMode::Hide);
    //retrieve the spot formula
    spot::formula spotFormula =
        spot::parse_infix_psl(spotFormulaStr).f;
    //generate the spot automaton
    std::shared_ptr<spot::twa_graph> spotAutomaton =
        generateDeterministicSpotAutomaton(spotFormula);
    //extract the placeholders
    auto placeholderPack = extractPlaceholders(_formula);
    //build the harm automaton
    _automaton =
        buildAutomatonFromSpot(spotAutomaton, placeholderPack);
    //std::cout << printAutomaton(_automaton) << "\n";
  }
#else
  messageError("No automata generator library provided");
  //other automata-based libraries
#endif
}

void AutomataBasedEvaluator::initCache() {
  _cacheParallel = new Trinary *[l1Constants::MAX_THREADS];
  for (size_t i = 0; i < l1Constants::MAX_THREADS; i++) {
    _cacheParallel[i] = new Trinary[_trace->getLength()];
    //init
    std::fill_n(_cacheParallel[i], _trace->getLength(), Trinary::U);
  }

  //final truth values memory: final result of linearEval
  _cache = new Trinary[_trace->getLength()];
  std::fill_n(_cache, _trace->getLength(), Trinary::U);

  //allocate more memory to keep track of sere shifts
  _sereShiftCache = new size_t[_trace->getLength()];
  std::fill_n(_sereShiftCache, _trace->getLength(), 0);
  _sereShiftCacheParallel = new size_t *[l1Constants::MAX_THREADS];

  for (size_t i = 0; i < l1Constants::MAX_THREADS; i++) {
    _sereShiftCacheParallel[i] = new size_t[_trace->getLength()];
    std::fill_n(_sereShiftCacheParallel[i], _trace->getLength(), 0);
  }
}

///explicit template instantiations
template std::pair<Trinary, size_t>
AutomataBasedEvaluator::evaluateAutomaton<true>(size_t time);
template std::pair<Trinary, size_t>
AutomataBasedEvaluator::evaluateAutomaton<false>(size_t time);

//--------------------------------------------------------------------------------------

///spot related functions
#ifdef SPOTLTL

std::string to_string(const spot::formula &f) {
  std::stringstream ss;
  ss << f;
  return ss.str();
}

std::shared_ptr<spot::twa_graph>
generateDeterministicSpotAutomaton(const spot::formula &formula) {
  static std::unordered_map<std::string,
                            std::shared_ptr<spot::twa_graph>>
      cache;
  std::string formulaStr = to_string(formula);
  if (cache.count(formulaStr)) {
    return cache.at(formulaStr);
  }

  spot::formula formula_to_use = formula;

  if (formula_to_use.kind() == spot::op::Closure) {
    //adding the EConcat forbids weakly accepting states
    formula_to_use =
        spot::formula::EConcat(formula[0], spot::formula::tt());
    //debug
    //std::cout << to_string(formula_to_use) << "\n";
  }

  spot::translator trans;
  trans.set_pref(spot::postprocessor::Deterministic);
  auto aut = trans.run(formula_to_use);

  spot::postprocessor post;
  post.set_pref(spot::postprocessor::Complete);
  aut = post.run(aut);

  messageErrorIf(!spot::is_deterministic(aut),
                 "The formula_to_use '" + to_string(formula_to_use) +
                     "' generates a non-deterministic automaton");
  messageErrorIf(!spot::is_complete(aut),
                 "The formula_to_use '" + to_string(formula_to_use) +
                     "' generates an incomplete automaton");
  messageWarningIf(
      aut->num_states() == 1,
      "The formula '" + to_string(formula_to_use) +
          "' generates a trivial automaton with only one state");

  //add to cache
  cache.insert({formulaStr, aut});

  return aut;
}

Automaton *buildAutomatonFromSpot(spot::twa_graph_ptr &automata,
                                  const PlaceholderPack &pack) {
  size_t stateCount = 0;
  std::unordered_map<size_t, size_t> hashToId;
  auto initState = automata->get_init_state();
  Automaton *retA = new Automaton();

  // dictionary to extract edge propositions
  auto bddDict = automata->get_dict();
  // keep track of visited states
  std::unordered_map<size_t, const spot::state *> visited;
  // queue
  std::deque<const spot::state *> fringe;

  // visit the automata starting from the initial state(BFS)
  fringe.push_front(initState);
  // mark the first state as visited
  visited.insert({initState->hash(), initState});

  while (!fringe.empty()) {
    const spot::state *currState = fringe.back();
    fringe.pop_back();

    if (hashToId.count(currState->hash()) == 0) {
      //create a link to retrieve the Node (only if it doesn't already exist)
      hashToId[currState->hash()] = stateCount++;
      retA->_idToNode[hashToId.at(currState->hash())] =
          new Automaton::Node(hashToId.at(currState->hash()),
                              Automaton::Node::Type::Pending);
    }

    // identify if the current state is a terminal state
    auto it = automata->succ_iter(currState);
    if (it->first() && (it->dst()->hash() == currState->hash()) &&
        !it->next()) {
      if (automata->state_is_accepting(currState)) {
        // acceptance state: the evaluation returns true
        retA->_idToNode.at(hashToId.at(currState->hash()))->_type =
            Automaton::Node::Type::Accepting;
        retA->_accepting =
            retA->_idToNode.at(hashToId.at(currState->hash()));
      } else {
        // rejecting state: the evaluation returns false
        retA->_idToNode.at(hashToId.at(currState->hash()))->_type =
            Automaton::Node::Type::Rejecting;
        retA->_rejecting =
            retA->_idToNode.at(hashToId.at(currState->hash()));
      }
    }
    delete it;

    // for each out edge
    for (auto s : automata->succ(currState)) {
      if (visited.count(s->dst()->hash()) == 0) {
        // mark as visited
        visited.insert({s->dst()->hash(), s->dst()});
        // put on the queue
        fringe.push_back(s->dst());
      }

      // retrieve the spotLTL representation of an edge
      spot::formula edge = spot::parse_formula(
          spot::bdd_format_formula(bddDict, s->cond()));

      if (hashToId.count(s->dst()->hash()) == 0) {
        //Again: create a link to retrieve the Node (only if it doesn't exist already)
        hashToId[s->dst()->hash()] = stateCount++;
        retA->_idToNode[hashToId.at(s->dst()->hash())] =
            new Automaton::Node(hashToId.at(s->dst()->hash()),
                                Automaton::Node::Type::Pending);
      }
      // add the custom edge to the custom node
      EdgeProposition *newEdgeProp =
          spotEdgeToProposition(edge, pack);
      Automaton::Edge *newEdge = new Automaton::Edge(
          newEdgeProp,
          retA->_idToNode.at(hashToId.at(s->dst()->hash())),
          retA->_idToNode.at(hashToId.at(currState->hash())));

      retA->_idToNode.at(hashToId.at(currState->hash()))
          ->_outEdges.push_back(newEdge);
      retA->_idToNode.at(hashToId.at(s->dst()->hash()))
          ->_inEdges.push_back(newEdge);
    }
  }

  // set the initial state of the automaton
  retA->_root = retA->_idToNode.at(0);

  //FIXME: do we still need this?
  //messageErrorIf(retA->_rejecting == nullptr, "Automaton misses the rejecting state");
  //messageErrorIf(retA->_accepting == nullptr, "Automaton misses the accepting state");

  return retA;
}

EdgeProposition *spotEdgeToProposition(const spot::formula &f,
                                       const PlaceholderPack &pack) {
  //visit the expression depending on the type of operator

  // And
  if (f.is(spot::op::And)) {
    std::vector<EdgeProposition *> operands;
    for (size_t i = 0; i < f.size(); i++) {
      operands.push_back(spotEdgeToProposition(f[i], pack));
    }

    return new EdgeAnd(operands);
  }

  // Or
  if (f.is(spot::op::Or)) {
    std::vector<EdgeProposition *> operands;
    for (size_t i = 0; i < f.size(); i++) {
      operands.push_back(spotEdgeToProposition(f[i], pack));
    }

    return new EdgeOr(operands);
  }

  // Not
  if (f.is(spot::op::Not)) {
    return new EdgeNot(spotEdgeToProposition(f[0], pack));
  }

  // Atomic proposition
  if (f.is(spot::op::ap)) {
    if (isPlaceholderStr(f.ap_name())) {
      messageErrorIf(!pack._tokenToPP.count(f.ap_name()),
                     "Placeholder not found: " + f.ap_name());
      return new EdgePlaceholder(pack._tokenToPP.at(f.ap_name()),
                                 f.ap_name());
    } else if (isInstStr(f.ap_name())) {
      messageErrorIf(!pack._tokenToInst.count(f.ap_name()),
                     "Inst not found: " + f.ap_name());
      return new EdgeInst(pack._tokenToInst.at(f.ap_name()),
                          f.ap_name());
    } else if (isDTO_Str(f.ap_name())) {
      messageErrorIf(!pack._tokenToPP.count(f.ap_name()),
                     "DTO Placeholder not found: " + f.ap_name());
      return new EdgePlaceholder(pack._tokenToPP.at(f.ap_name()),
                                 f.ap_name());
    } else {
      messageError("Unknown atomic proposition: " + f.ap_name());
    }
  }

  // Constants
  if (f.is_tt()) {
    return new EdgeTrue();
  }

  if (f.is_ff()) {
    return new EdgeFalse();
  }

  messageError("Error in spot edge formula");
  return nullptr;
}

bool isPlaceholderStr(const std::string &s) { return s[0] == 'P'; }
bool isInstStr(const std::string &s) {
  return s.size() > 5 && s.substr(0, 5) == "_inst";
}
bool isDTO_Str(const std::string &s) {
  return s.size() > 2 && s.substr(0, 3) == "_dt";
}

#endif

} // namespace harm
