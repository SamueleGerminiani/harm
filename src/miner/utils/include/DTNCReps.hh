#pragma once

#include "DTOperator.hh"

namespace harm {
class DTNCReps : public DTOperator {
public:
  DTNCReps(BooleanConstant *p, size_t shift, Template *t,
           const DTLimits &limits);

  ~DTNCReps() override;
  bool isMultiDimensional() override;
  bool canInsertAtDepth(int depth) override;
  bool isRandomConstructed() override;
  bool isTaken(size_t id, bool second, int depth) override;

  size_t getNChoices() override;
  size_t getCurrentDepth() override;
  const DTLimits &getLimits() override;

  void addItem(Proposition *p, int depth) override;
  void popItem(int depth) override;
  void removeItems() override;
  std::vector<Proposition *> getItems() override;

  std::vector<Proposition *> minimize(bool isOffset) override;
  virtual std::vector<Proposition *> unpack() override;
  virtual std::vector<Proposition *> unpack(Proposition *pack) override;
  virtual std::vector<Proposition *>
  unpack(std::vector<Proposition *> &pack) override;

  void clearPack(Proposition *pack) override;
  bool isSolutionInconsequential(std::vector<Proposition *> &sol) override;

  void removeLeaf(size_t id, bool second, int depth) override;
  void addLeaf(Proposition *p, size_t id, bool second, int depth) override;

  virtual std::pair<std::string, std::string> prettyPrint(bool offset) override;
  void substitute(int depth, int width, Proposition *&sub) override;
  void generateFormulas();
  void handleParallelDepth();

private:
  std::unordered_map<size_t, Proposition *> _choices;
  std::vector<int> _order;

  std::vector<std::string> _tokens;
  std::vector<Hstring> _formulas;
  std::vector<int> _assDepth;
  std::vector<int> _antDepth;

  Template *_t;
  size_t _shift;
  bool _randomConstruction;
  bool _applyDynamicShift = false;

  std::vector<Automaton *> _ant;

  size_t _parallelDepth = 0;
  size_t _currDepth = 0;

  BooleanConstant *_tc;
  std::vector<DecTreeVariables> _leaves;
};
} // namespace harm
