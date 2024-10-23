#pragma once
#include <map>
#include <mutex>
#include <optional>
#include <set>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "DTOperator.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class NumericExpression;
using NumericExpressionPtr = std::shared_ptr<NumericExpression>;
} // namespace expression
namespace harm {
class DTOperator;
using DTOperatorPtr = std::shared_ptr<DTOperator>;
class TemplateImplication;
using TemplateImplicationPtr = std::shared_ptr<TemplateImplication>;
class OCCS;
struct DTSolution;
} // namespace harm

#define printTree 0

namespace harm {

// For the decision tree algorithm variables are enumerated. Each variable is a proposition splitting the search space.
using DecTreeVariables =
    std::map<size_t, std::pair<expression::PropositionPtr,
                               expression::PropositionPtr>>;
using NumericDecTreeExp =
    std::map<size_t, expression::NumericExpressionPtr>;

/*! \struct DiscoveredLeaf
    \brief utility structure to store a leaf of a decision tree
*/
struct DiscoveredLeaf {
  explicit DiscoveredLeaf(size_t id, int depth, bool negated)
      : _id(id), _depth(depth), _negated(negated) {
    // not todo
  }

  size_t _id;
  int _depth;
  bool _negated;

  // Define equality operator
  bool operator==(const DiscoveredLeaf &other) const {
    return _id == other._id && _depth == other._depth &&
           _negated == other._negated;
  }
};

// Define hash function
struct DiscoveredLeafHash {
  std::size_t operator()(const DiscoveredLeaf &leaf) const {
    std::size_t h1 = std::hash<size_t>()(leaf._id);
    std::size_t h2 = std::hash<int>()(leaf._depth);
    std::size_t h3 = std::hash<bool>()(leaf._negated);
    return h1 ^ (h2 << 1) ^ (h3 << 2); // Combine the hashes
  }
};
/*! \struct CandidateDec
    \brief utility structure to store a candidate
*/
struct CandidateDec {

  explicit CandidateDec(size_t id, int depth, bool negated,
                        expression::PropositionPtr p, double gain,
                        double score, bool ofNumericOrigin)
      : _id(id), _depth(depth), _negated(negated), _prop(p),
        _gain(gain), _score(score),
        _ofNumericOrigin(ofNumericOrigin) {}

  ///id of the candidate in the vector of decision variables
  size_t _id;
  ///depth in the DT operator
  int _depth;
  ///if true, this is the negated version of the candidate
  bool _negated;
  ///the proposition corresponding to this candidate
  expression::PropositionPtr _prop;
  /// the score gained obtained by splitting on this candidate
  double _gain;
  ///the score value after splitting on this candidate
  double _score;
  ///if true, this candidate was generated from a numeric expression
  bool _ofNumericOrigin = false;
};

/*! \class AntecedentGenerator
    \brief This class implements a search algorithm based on a decision tree
*/
class AntecedentGenerator {
public:
  /// @brief Constructor.
  AntecedentGenerator();

  /// @brief Destructor.
  ~AntecedentGenerator() = default;

  /// @brief Copy constructor.
  /// @param other The other variable to be copied.
  AntecedentGenerator(const AntecedentGenerator &other) = delete;

  /// @brief Assignment operator
  /// @param other The other variable to be copied.
  AntecedentGenerator &
  operator=(const AntecedentGenerator &other) = delete;

  /// @brief fill onSets and offSets with solutions
  void makeAntecedents(const TemplateImplicationPtr &t,
                       const DecTreeVariables &dcVariables,
                       const NumericDecTreeExp &numericCandidates);

  /// the algorithm's result (onset, ant -> con):
  std::vector<DTSolution> _onSets;
  /// the algorithm's result (offset, ant -> !con):
  std::vector<DTSolution> _offSets;

  ///if true, it prompts the algo to save the offset
  bool _saveOffset;

private:
  ///number of times the consequent is true
  size_t _CT = 0;
  ///number of times the consequent is false
  size_t _CF = 0;

  ///previously found solutions in string representation
  std::unordered_set<std::string> _knownSolutions;

private:
  /// @brief implements the actual dt algo
  void runDecisionTree(std::set<size_t> &unusedVars,
                       const DecTreeVariables &dcVariables,
                       std::set<size_t> &unusedNumerics,
                       const NumericDecTreeExp &numericCandidates,
                       const TemplateImplicationPtr &t,

                       double currEntropy);

  /// @brief find choices to split the search space
  void findCandidates(
      size_t candidate, const DecTreeVariables &dcVariables,
      const TemplateImplicationPtr &t,
      std::unordered_set<DiscoveredLeaf, DiscoveredLeafHash>
          &discSolutions,
      std::vector<CandidateDec> &igs, int depth, double currEntropy);

  /// @brief find choices to split the search space, use numerics instead of props, uses gatherPropositionsFromNumerics
  void findCandidatesNumeric(
      size_t candidate, const NumericDecTreeExp &dcVariables,
      const TemplateImplicationPtr &t,
      std::unordered_set<DiscoveredLeaf, DiscoveredLeafHash>
          &discSolutions,
      std::vector<CandidateDec> &igs, int depth,

      double currEntropy);

  /// @brief find choices through clustering, uses gatherPropositionsFromNumerics
  std::vector<expression::PropositionPtr>
  gatherPropositionsFromNumerics(expression::NumericExpressionPtr cn,
                                 const TemplateImplicationPtr &t,
                                 int depth);

  bool
  isKnownSolution(const DTOperatorPtr &dto, bool checkOnly = false,
                  const std::optional<DTSolution> &ovveridenSolution =
                      std::nullopt);

  void storeSolution(const TemplateImplicationPtr &t, bool isOffset);

  /// @brief checks the fitness antecedent with respect to the consequent
  /// returns true if the antecedent is a good fit, false otherwise
  bool checkFitness(const TemplateImplicationPtr &t,
                    const OCCS &occs);

  //------------ For printing the decision tree -----------------------
  //keeps track of the tree being printed
  std::stringstream ss_tree;
  //keeps track of the list of assertions found
  std::stringstream foundAss;
  ///keeps track of the number of states
  size_t nStates = 0;
  std::unordered_map<size_t, std::string> nStateToClsProps;
  ///keeps track of which assertions are found in which state
  std::unordered_map<size_t, std::string> nStateToAss;

  ///to protect the output file
  static std::mutex dtDumpMutex;
  //-----------------------------------------------------------------
};

} // namespace harm
