#pragma once
#include "DTOperator.hh"

namespace harm {
/*! \class DTNextAnd
    \brief Decision tree operator class for ..#N&.., see base class for the description of the methods
*/
class DTNextAnd : public DTOperator {
public:
  DTNextAnd(size_t shift, Template *t, const DTLimits &limits);
  void generateFormulas();
void handleParallelDepth();

  ~DTNextAnd() override;
  bool isMultiDimensional() override;
  bool canInsertAtDepth(int depth) override;
  bool isRandomConstructed() override;
  bool isTaken(size_t id, bool second, int depth) override;

  size_t getNChoices() override;
  const DTLimits &getLimits() override;
  size_t getCurrentDepth() override;

  void addItem(Proposition *p, int depth) override;
  void popItem(int depth) override;
  void removeItems() override;
  std::vector<Proposition *> getItems() override;

  std::vector<Proposition *> minimize(bool isOffset) override;
  virtual std::vector<Proposition *> unpack() override;
  std::vector<Proposition *> unpack(Proposition *pack) override;
  virtual std::vector<Proposition *>
  unpack(std::vector<Proposition *> &pack) override;
  void clearPack(Proposition *pack) override;
  void removeLeaf(size_t id, bool second, int depth) override;
  void addLeaf(Proposition *p, size_t id, bool second, int depth) override;
  virtual std::pair<std::string, std::string> prettyPrint(bool offset) override;
  bool isSolutionInconsequential(std::vector<Proposition *> &sol) override {
    if (_applyDynamicShift) {
      return sol.empty() || dynamic_cast<PropositionAnd *>(sol.back())->empty();
    } else {
      return sol.empty() ||
             dynamic_cast<PropositionAnd *>(sol.front())->empty();
    }
  }
  void substitute(int depth, int width, Proposition *&sub) override;

private:
  std::unordered_map<size_t, std::vector<Proposition *>> _choices;
  std::vector<size_t> _order;
  std::vector<PropositionAnd *> _op;

  std::vector<std::string> _tokens;
  std::vector<Hstring> _formulas;
  std::vector<int> _assDepth;
  std::vector<int> _antDepth;

  Template *_t;
  size_t _shift;
  bool _randomConstruction;

  std::vector<Automaton *> _ant;

  size_t _parallelDepth = 0;
  size_t _currDepth = 0;
  bool _applyDynamicShift = false;

  std::vector<DecTreeVariables> _leaves;
  BooleanConstant *_tc;
};
} // namespace harm
