#pragma once
#include "DTOperator.hh"

namespace harm {
/*! \class DTNext
    \brief Decision tree operator class for ..##N.., see base class for the description of the methods
*/
class DTNext : public DTOperator {
public:
  DTNext(BooleanConstant *p, size_t shift, Template *t, const DTLimits &limits);

  ~DTNext() override;
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

private:
  void generateFormulas();
  void handleParallelDepth();

  ///list of operands <id -> prop>
  std::unordered_map<size_t, Proposition *> _choices;
  ///order in which the operands were added
  std::vector<int> _order;

  ///list of tokens in the template representing each operand
  std::vector<std::string> _tokens;
  ///list of formulas: if _limits._maxDepth is equal to N, then _formulas contains N elements
  std::vector<Hstring> _formulas;
  ///max depth for each formula in _formulas
  std::vector<int> _assDepth;
  ///max depth for each formula's antecedent in _formulas
  std::vector<int> _antDepth;

  ///Pointer to the Template using this operator
  Template *_t;
  ///Contains the N of ..##N..
  size_t _shift;
  ///True if the dt operator can be constructed in an unordered fashion
  bool _randomConstruction;
  ///True if the templates contains a dynamic shift
  bool _applyDynamicShift = false;

  ///list of automaton representation of the antecedent of each formula in _formulas
  std::vector<Automaton *> _ant;

  ///max temporal depth of parallel operators in the template
  size_t _parallelDepth = 0;
  ///curr depth of the template
  size_t _currDepth = 0;

  BooleanConstant *_tc;
  std::vector<DecTreeVariables> _leaves;

};
} // namespace harm
