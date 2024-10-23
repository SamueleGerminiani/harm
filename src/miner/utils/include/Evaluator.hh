#pragma once
#include "expUtils/expUtils.hh"
#include "formula/temporal/TemporalExpression.hh"
#include "globals.hh"
#include <mutex>

enum class Trinary;
namespace harm {

using namespace expression;

//forward declarations
class Automaton;
class Trace;

/** \class Evaluator
    \brief abstract class for the evaluation of temporal formulas
*/
class Evaluator {
public:
  /*! \structure Range
    \brief utility data structure for cuts and threads in the evaluation algorithm
*/
  struct Range {
    Range() {}
    Range(size_t start, size_t length)
        : _start(start), _length(length) {
      // not todo
    }
    size_t _start;
    size_t _length;
  };

  virtual ~Evaluator() = default;

  ///evaluates the formula at time 'time' and returns the truth value and the temporal shift
  virtual std::pair<Trinary, size_t> evaluate(size_t time) = 0;

  ///invalidates the cache, so that the next evaluation will be computed from scratch
  virtual void invalidateCache() { _inCache = false; }

  ///sets how many threads should be used for evaluating the formula
  void setL1Threads(size_t nThreads) {
    std::lock_guard<std::mutex> lock(_l1ThreadsGuard);
    _l1Threads = nThreads;
  }

  virtual void changeTrace(const harm::TracePtr &trace) = 0;

protected:
  Evaluator(const TemporalExpressionPtr &formula,
            const harm::TracePtr &trace);
  ///the formula to be evaluated
  TemporalExpressionPtr _formula;
  ///the trace on which the formula is evaluated
  harm::TracePtr _trace;

  ///mutex for level 1 changes of available threads (see setL1Threads)
  std::mutex _l1ThreadsGuard;
  /// available threads to implement level1 parallelism
  size_t _l1Threads = 1;

  ///indicates if the result of the last evaluation is in the cache
  bool _inCache = false;
};

///pointer to an Evaluator
using EvaluatorPtr = std::shared_ptr<Evaluator>;

EvaluatorPtr
generateEvaluator(const TemporalExpressionPtr &formula,
                  const TracePtr &trace,
                  const std::string &evaluatorType = "None");

} // namespace harm

