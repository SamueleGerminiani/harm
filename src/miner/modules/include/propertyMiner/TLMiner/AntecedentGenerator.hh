#pragma once
#include "PropertyMiner.hh"

#include <list>
#include <set>
#include <vector>

#define printTree 0
using namespace std;

extern size_t countA;

namespace harm {

// for the decision tree algorithm variables are numerated.
// Each variable is a proposition splitting the research space.
using DecTreeVariables = map<size_t, std::pair<Proposition *, Proposition *>>;
using NumericDecTreeExp = map<size_t, CachedAllNumeric *>;

/// @brief AntecedentGenerator
///
/// This class implements a search algorithm based on a decision tree.
/// Given a goal, which is represented by a proposition, the algorihtm generates
/// sets of constraints. When a constraint is satisfied, then the goal has
/// value 1.
///

struct DiscoveredLeaf {
  DiscoveredLeaf(size_t id, bool second, int depth)
      : _id(id), _second(second), _depth(depth) {
    // not todo
  }
  size_t _id;
  bool _second;
  int _depth;
};
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
  double _entropy;
  int _depth;
  std::vector<std::pair<Proposition *, size_t>> _props;
};
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

  /// @brief saveOffset defines if
  bool saveOffset;

  /// the algorithm's result:
  ////set<set<Proposition *>> onSets;
  ////set<set<Proposition *>> offSets;
  vector<vector<Proposition *>> onSets;
  vector<vector<Proposition *>> offSets;
  unordered_set<std::string> knownSolutions;

  /// @brief makeAntecedents
  /// @param dcVariables a set of Variables
  /// @paran posAndNeg a flag ...
  /// @return ....
  void makeAntecedents(Template *t, DecTreeVariables &dcVariables,
                       NumericDecTreeExp &numericCandidates,
                       std::vector<Proposition *> &genProps);

private:
  void _runDecisionTree(std::set<size_t> &unusedVars,
                        DecTreeVariables &dcVariables,
                        std::set<size_t> &unusedNumerics,
                        NumericDecTreeExp &numericCandidates, Template *t,
                        std::vector<Proposition *> &genProps,
                        double currEntropy);
  inline void findCandidates(size_t candidate, DecTreeVariables &dcVariables,
                             Template *t,
                             std::vector<DiscoveredLeaf> &discLeaves,
                             std::vector<CandidateDec> &igs, int depth,
                             double currEntropy);
  template <typename T>
  std::vector<Proposition *>
  getPropsThroughClustering(CachedAllNumeric *cn, std::vector<size_t> &sVals,
                            Template *t, int depth,
                            std::vector<Proposition *> &genProps);

  inline std::vector<Proposition *>
  gatherPropositions(CachedAllNumeric *cn, Template *t, int depth,
                     std::vector<Proposition *> &genProps);

  inline std::vector<Proposition *>
  gatherPropositionsFromNumerics(CachedAllNumeric *cn, Template *t, int depth,
                                 std::vector<Proposition *> &genProps);
  inline std::vector<Proposition *>
  generatePropositionsFromIV(std::vector<size_t> &ivs, CachedAllNumeric *cn,
                             Template *t);

  inline std::vector<size_t>
  gatherInterestingValues(Template *t, CachedAllNumeric *cn, int depth);

  inline void findCandidatesNumeric(size_t candidate,
                                    NumericDecTreeExp &dcVariables, Template *t,
                                    std::vector<DiscoveredLeaf> &discLeaves,
                                    std::vector<CandidateDec> &igs, int depth,
                                    std::vector<Proposition *> &genProps,
                                    double currEntropy);

  bool isKnownSolution(const std::vector<Proposition *> &items, DTOperator *template_dt, bool checkOnly=false);
  void _store(Template *t, bool value);

  void _getCoverage(Template *t, bool value);

  size_t addL = 0;
  size_t removeL = 0;
#if printTree
  std::stringstream tree;
  std::stringstream foundAss;
  size_t nStates = 0;
  std::unordered_map<size_t, std::string> nStateToAss;
#endif
};

} // namespace harm
