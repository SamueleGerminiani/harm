#pragma once
#include "BDTOperator.hh"

namespace harm {
class BDTAnd : public BDTOperator {
public:
  BDTAnd(PropositionAnd *p, Template *t, const BDTLimits &limits);

  ~BDTAnd();
  bool isMultiDimensional() override;
  size_t getCurrentDepth() override;
  bool canInsertAtDepth(int depth) override;
  bool isRandomConstructed() override;
  size_t getNChoices() override;
  bool isTaken(size_t id, bool second, int depth) override;
  void removeLeaf(size_t id, bool second, int depth) override;
  void addLeaf(Proposition *p, size_t id, bool second, int depth) override;
  void removeItems() override;
  void addItem(Proposition *p, int depth) override;
  void popItem(int depth) override;
  std::vector<Proposition *> getItems() override;

  std::vector<Proposition *> minimize(bool isOffset) override;
  virtual std::vector<Proposition *> unpack() override;
  virtual std::vector<Proposition *> unpack(Proposition *pack) override;
  virtual std::vector<Proposition *>
  unpack(std::vector<Proposition *> &pack) override;

  void clearPack(Proposition *pack) override;
  virtual std::pair<std::string, std::string> prettyPrint(bool offset) override;
  bool isSolutionInconsequential(std::vector<Proposition *> &sol) override;
  void substitute(int depth, int width, Proposition *&sub) override {
    if (width == -1) {
      width = _choices->getItems().size() - 1;
    }
    Proposition *tmp = _choices->getItems()[width];
    _choices->getItems()[width] = sub;
    sub = tmp;
  }

  virtual const BDTLimits &getLimits() override;

private:
  PropositionAnd *_choices;
  Template *_t;
  DecTreeVariables _leaves;
};
}
