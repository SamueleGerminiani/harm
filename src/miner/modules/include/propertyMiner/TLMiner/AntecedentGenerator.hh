#pragma once
#include "PropertyMiner.hh"

#include <list>
#include <set>
#include <vector>

#define printTree 0

namespace harm {

// For the decision tree algorithm variables are enumerated. Each variable is a proposition splitting the search space.
using DecTreeVariables = std::map<size_t, std::pair<Proposition *, Proposition *>>;
using NumericDecTreeExp = std::map<size_t, CachedAllNumeric *>;

/*! \struct DiscoveredLeaf
    \brief utility structure to store a leaf of a decision tree
*/
struct DiscoveredLeaf {
  DiscoveredLeaf(size_t id, bool second, int depth)
      : _id(id), _second(second), _depth(depth) {
    // not todo
  }
  size_t _id;
  bool _second;
  int _depth;
};
/*! \struct CandidateDec
    \brief utility structure to store a candidate
*/
struct CandidateDec {

  CandidateDec() {}
  CandidateDec(size_t id, double ig, int depth, Proposition *p, bool offSet,
               double entropy = 1.f)
      : _id(id), _ig(ig), _depth(depth), _entropy(entropy) {
    _props.emplace_back(p, offSet);
  }
  CandidateDec(size_t id, double ig, int depth, Proposition *p1, bool offSet1,
               Proposition *p2, bool offSet2, double entropy = 1.f)
      : _id(id), _ig(ig), _depth(depth), _entropy(entropy) {
    _props.emplace_back(p1, offSet1);
    _props.emplace_back(p2, offSet2);
  }
  size_t _id;
  double _ig;
  int _depth;
  double _entropy;
  std::vector<std::pair<Proposition *, size_t>> _props;
};

/*! \class AntecedentGenerator
    \brief This class implements a search algorithm based on a decision tree with an entropy based heuristic.
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
  AntecedentGenerator &operator=(const AntecedentGenerator &other) = delete;

  /// @brief maxPropositions defines the maximum number of propositions in a
  /// generated antecedent
  size_t maxPropositions;

  /// the algorithm's result (onset, ant -> con):
  std::vector<std::vector<Proposition *>> onSets;
  /// the algorithm's result (offset, ant -> !con):
  std::vector<std::vector<Proposition *>> offSets;

  ///if true, it prompts the algo to save the offset
  bool saveOffset;

  ///previously found solutions in a string representation
  std::unordered_set<std::string> knownSolutions;

  /// @brief fill onSets and offSets with solutions
  void makeAntecedents(Template *t, DecTreeVariables &dcVariables,
                       NumericDecTreeExp &numericCandidates,
                       std::vector<Proposition *> &genProps);

private:
  /// @brief implements the actual dt algo
  void _runDecisionTree(std::set<size_t> &unusedVars,
                        DecTreeVariables &dcVariables,
                        std::set<size_t> &unusedNumerics,
                        NumericDecTreeExp &numericCandidates, Template *t,
                        std::vector<Proposition *> &genProps,
                        double currEntropy);

  /// @brief find choices to split the search space
  inline void findCandidates(size_t candidate, DecTreeVariables &dcVariables,
                             Template *t,
                             std::vector<DiscoveredLeaf> &discLeaves,
                             std::vector<CandidateDec> &igs, int depth,
                             double currEntropy);

  /// @brief find choices to split the search space, use numerics instead of props, uses gatherPropositionsFromNumerics
  inline void findCandidatesNumeric(size_t candidate,
                                    NumericDecTreeExp &dcVariables, Template *t,
                                    std::vector<DiscoveredLeaf> &discLeaves,
                                    std::vector<CandidateDec> &igs, int depth,
                                    std::vector<Proposition *> &genProps,
                                    double currEntropy);

  /// @brief find choices through clustering, uses gatherPropositionsFromNumerics
  inline std::vector<Proposition *>
  gatherPropositionsFromNumerics(CachedAllNumeric *cn, Template *t, int depth,
                                 std::vector<Proposition *> &genProps);

  /// @brief analyse the trace to find a set of values on which to perform the clustering
  inline std::vector<size_t>
  gatherInterestingValues(Template *t, int depth);

  bool isKnownSolution(const std::vector<Proposition *> &items,
                       DTOperator *template_dt, bool checkOnly = false);

  void storeSolution(Template *t, bool isOffset);


  //debug
#if printTree
  std::stringstream tree;
  std::stringstream foundAss;
  size_t nStates = 0;
  std::unordered_map<size_t, std::string> nStateToAss;
#endif
};

} // namespace harm
