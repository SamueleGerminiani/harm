

#pragma once

#include "DTLimits.hh"
#include "Evaluator.hh"
#include "Permutator.hh"
#include "formula/atom/Atom.hh"
#include "minerUtils.hh"
#include <map>
#include <mutex>
#include <optional>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

enum class Trinary;
namespace expression {
template <typename OT, typename ET> class Function;
using FunctionPropositionPtr =
    std::shared_ptr<Function<Proposition, Proposition>>;
} // namespace expression
template <typename T> class ProtectedQueueNotify;

namespace expression {
enum class ExpType;
}

namespace harm {
class DTAnd;
class DTNCReps;
class DTNext;
class DTNextAnd;
class DTOperator;
using DTOperatorPtr = std::shared_ptr<DTOperator>;
class Trace;
class EdgeProposition;
enum class Location;

/*! \class TemplateImplication
    \brief Class representing an assertion template of the form always(ant -> con), the template can be
   instantiated by loading boolean propositions
*/
class TemplateImplication {

public:
  /** \brief Constructor
   * \param templateFormula representation of a template as a PSL formula
   * \param trace pointer to the trace on which to evaluate the assertion
   * \param dtLimits configuration of the decision tree operator
     */
  TemplateImplication(const TemporalExpressionPtr &templateFormula,
                      const harm::TracePtr &trace,
                      const DTLimits &dtLimits);

  /** \brief Copy Constructor
   */
  TemplateImplication(const TemplateImplication &original);

  ~TemplateImplication();

  Location getPlaceholderLocation(const std::string &ph);

  /** \brief evaluates the assertion generated by loading the propositions in the template
   * \param time trace instant on which to evaluate the assertion
   */
  Trinary evaluate(size_t time);
  /** \brief evaluates the offset assertion (ant->!con) generated by loading the propositions in the template
   * \param time trace instant on which to evaluate the assertion
   */
  Trinary evaluateOffset(size_t time);
  /** \brief evaluates only the antecedent of the assertion
   * \param time trace instant on which to evaluate 
   */
  Trinary evaluate_ant(size_t time);
  /** \brief evaluates only the antecedent ignoring the chaded values
   * \param time trace instant on which to evaluate 
   */

  Trinary evaluate_con(size_t time);
  /** \brief return the length of the trace
   */
  size_t getTraceLength();
  /** \brief evaluates how many times the consequent is true on the trace
   */
  size_t getCT();
  /** \brief evaluates how many times the consequent is false on the trace
   */
  size_t getCF();
  /** \brief evaluates how many times the consequent is true and false on the trace
   */
  std::pair<size_t, size_t> getCT_CF();

  /** \brief force the next evaluation of the antecedent to ignore cached values (and store new ones)
   */
  void setCacheAntFalse();
  /** \brief force the next evaluation of the consequent to ignore cached values (and store new ones)
   */
  void setCacheConFalse();

  /** \brief returns the template insantiated with the propositions
   */
  std::string getAssertionStr(Language lang = Language::Unset);
  /** \brief returns the template insantiated with the propositions (colored)
   */
  std::string getColoredAssertionStr(Language lang = Language::Unset);

  /** \brief returns the string representation of the template
   */
  std::string getTemplateStr(Language lang = Language::Unset);
  /** \brief returns the string representation of the template (colored)
   */
  std::string getColoredTemplateStr(Language lang = Language::Unset);

  /** \brief returns the string representation of the template functions and placeholders hidden behind tokens
   */
  std::string
  getTemplateWithHiddenTokensStr(Language lang = Language::Unset);

  /** \brief returns a typed string representation of the template
   */
  const TemporalExpressionPtr &getTemplateFormula();

  /** \brief returns a pointer to the decision tree operator
   */
  DTOperatorPtr getDT();

  bool containsDT();

  ///get decition tree propositions
  std::vector<expression::PropositionPtr> getDTPropositions();

  ///get decition tree numerics
  std::vector<expression::NumericExpressionPtr> getDTNumerics();

  std::map<std::string, expression::PropositionPtrPtr> &get_aphToPP();
  std::map<std::string, expression::PropositionPtrPtr> &get_cphToPP();
  std::map<std::string, expression::PropositionPtrPtr> &
  get_acphToPP();

  /** \brief 
   * \param where ant or con
   */
  size_t getNumPlaceholders(harm::Location where);
  size_t getNumPlaceholders();

  /** \brief  generates a sequence of permutations for the current template,
   * each permutation is a set of propositions to be used to instantiate the
   * template
   * \param antP propositions for the antecedent
   * \param conP propositions for the consequent
   * \param antConP propositions for placeholders that are both in the antecedent and the consequent
   */

  void genPermutations(
      const std::unordered_map<
          int, std::vector<expression::PropositionPtr>>
          &domainIdToProps,
      const std::unordered_map<
          int, std::vector<expression::NumericExpressionPtr>>
          &_domainIdToNumerics);

  /** \brief loads the next permutation in the template. This method must be
   * called after genPermutations.
   */
  void nextPerm();
  /** \brief loads the n_th permutation in the template. This method must be
   * called after genPermutations.
   * \param the index of the permutation to load
   */
  void loadPerm(size_t n);

  size_t getCurrentPermIndex();

  std::vector<expression::PropositionPtr> getLoadedPropositions();

  /// \brief get the variables in the template
  std::vector<
      std::pair<std::string, std::pair<expression::ExpType, size_t>>>
  getVars();

  /** \brief get the depth of the propositions of the antecedent in the abtract syntax tree of the template formula
   */
  std::vector<expression::PropositionPtr> getLoadedPropositionsAnt();
  /** \brief get the depth of the propositions of the consequent in the abtract syntax tree of the template formula
   */
  std::vector<expression::PropositionPtr> getLoadedPropositionsCon();

  /** \brief get the number of permutations generated */
  size_t getNumberOfPermutations() const;

  /** \brief returns true if the assertion holds on the input trace, false otherwise */
  bool assHoldsOnTrace(harm::Location update);
  /** \brief returns true if the assertion (offset) holds on the input trace, false otherwise
   * \param update specifies if the template should be reevaluated and where */
  bool assHoldsOnTraceOffset(harm::Location update);
  /** \brief returns true if the assertion is vacuouse, false otherwise
   *\param update specifies if the template should be reevaluated and where 
   * \param cause if the assertion is vacuous, it will be filled with the cause of the vacuity, the function expects cause to be allocated and deallocated by the caller
   * */
  bool isVacuous(harm::Location update);
  /** \brief returns true if the assertion is vacuouse (offset), false otherwise 
   *\param update specifies if the template should be reevaluated and where 
    */
  bool isVacuousOffset(harm::Location update);

  /** \brief return the state of the "check" property
   * */
  bool getCheck();
  /** \brief set the state of the "check" property
   * */
  void setCheck(bool check);

private:
  //technical methods, they implement the generation and the evaluation of the template

  /** \brief initialises the template and builds all the necessary parts. To be
   * called only in the constructor!
   */
  void build();

  /** \brief returns the 'cause' of the failing assertions at time 'time'
   */
  std::string findCauseOfFailure(size_t time);
  /** \brief utility method to find the 'cause' of failure
   */
  std::string findCauseInEdgeProposition(EdgeProposition *ep,
                                         size_t time, bool goal,
                                         bool expPlaceholders);

public:
  /** \brief fill the contingency table with the cached values
   * \param ct is a pointer to a suitable matrix
   */
  void fillContingency(size_t (&ct)[3][3], bool offset);

  void setL1Threads(size_t n);

  void setDTLimits(const DTLimits &l);

  /** \brief returns true if the template is fully instantiated, false otherwise
   */
  bool isFullyInstantiated();

  void printContingency();

  /** \brief check if this (fully instantied) template holds on the input trace, it prints the reason if it does not hold
   */
  void check();

  /** \brief check if the instance at time 'timechoice is fundemental to make the ant true in the DTO
   * \param time is the time instant to check
   * \param depth is the depth in the DTO
   * \param width is the width in the DTO
   */
  std::pair<size_t, bool>
  gatherInterestingValue(size_t time, int depth, int width);

  void subPropInAssertion(expression::Proposition *original,
                          expression::Proposition *newProp);

  void setPhIds(
      const std::unordered_map<std::string, std::unordered_set<int>>
          &phToIdsDomain);
  std::unordered_map<std::string, std::unordered_set<int>> getPhIds();

  void changeTrace(const harm::TracePtr &newTrace);

  /** \brief returns the proposition corresponding to the given _inst_
   */
  expression::PropositionPtr getInst(const std::string &inst);
  /** \brief returns the pointer to proposition corresponding to the given _inst_
   */
  std::unordered_map<std::string, expression::PropositionPtr>
  getInstToProsition();
  /** \brief returns all the instantiated propositions
   */
  std::vector<expression::PropositionPtr> getAllInst();

  /// current employed templated
  TemporalExpressionPtr _templateFormula;

  /// used to generate the permutations
  Permutator _permutator;

  /*utility fields to link the placeholders with the instantiated propositions,
   * note that if the placeholder is not instantiated, then the proposition
   * points to a nullptr
   */
  /// link of all user instantiated placeholders to their respective
  /// propositions
  std::unordered_map<std::string, expression::PropositionPtr>
      _iToProp;
  /// link of all functions to their respective pointers
  std::unordered_map<std::string, expression::FunctionPropositionPtr>
      _tokenToFun;
  /// the pair of the dt operator and its string representation
  DTOperatorPtr _dtOp = nullptr;

  std::map<std::string, expression::PropositionPtrPtr> _aphToPP;
  std::map<std::string, expression::PropositionPtrPtr> _cphToPP;
  std::map<std::string, expression::PropositionPtrPtr> _acphToPP;

  /* current proposition domains:
    the generator of permutations will use the following propositions to
    generate the permutations
    */

  ///map ph to its domaion in terms of propositions (loaded by genPermutations)
  std::unordered_map<std::string,
                     std::vector<expression::PropositionPtr>>
      _phToPropDomain;
  ///map ph to the specified ids in the string representation of the template (loaded by the parser)
  std::unordered_map<std::string, std::unordered_set<int>>
      _phToIdsDomain;

  ///current decision tree proposition (loaded by genPermutations)
  std::vector<expression::PropositionPtr> _propsDT;
  ///current decision tree numerics (loaded by genPermutations)
  std::vector<expression::NumericExpressionPtr> _numericsDT;

  ///Evaluator for the antecedent
  EvaluatorPtr _antEvaluator = nullptr;
  ///Evaluator for the consequent
  EvaluatorPtr _conEvaluator = nullptr;
  ///Evaluator for the whole implication, used when _contains_mma is true
  EvaluatorPtr _impEvaluator = nullptr;

  /// dt operator configuration
  DTLimits _limits;

  /// pointer to the input traces
  harm::TracePtr _trace = nullptr;

  /// The constant temporal shift that must be applied to evaluate the consequent ex. If the template is Ant => Con the constant shift will be equal to 1. If the template is Ant -> Con the constant shift will be equal to 0
  size_t _constShift;

  /// if true, we must apply a dynamic shift before evaluating the consequent
  bool _applyDynamicShift;

  /// index to the current permutatian, -1 if no permutations are generated
  int _permIndex = -1;

  /// the template is an assertion that must be checked on the trace
  bool _check = 0;

  /// maximium temporal depth of the antecedent
  int _antDepth = 0;
  /// maximium temporal depth of the consequent
  int _conDepth = 0;

  /// if true, the template contains multi-match operators in the antecedent
  bool _contains_mma = 0;

  friend DTAnd;
  friend DTNext;
  friend DTNextAnd;
  friend DTNCReps;
};

//smart pointer to the TemplateImplication
using TemplateImplicationPtr = std::shared_ptr<TemplateImplication>;
} // namespace harm
