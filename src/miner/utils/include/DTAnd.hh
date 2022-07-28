#pragma once
#include "DTOperator.hh"

namespace harm {
/*! \class DTAnd
    \brief Decision tree operator class for ..&&.., see base class for the description of the methods
*/
class DTAnd : public DTOperator {
public:
  DTAnd(PropositionAnd *p, Template *t, const DTLimits &limits);

  virtual ~DTAnd();
  virtual bool isMultiDimensional() override;
  virtual size_t getCurrentDepth() override;
  virtual bool canInsertAtDepth(int depth) override;
  virtual bool isRandomConstructed() override;
  virtual size_t getNChoices() override;
  virtual bool isTaken(size_t id, bool second, int depth) override;
  virtual void removeLeaf(size_t id, bool second, int depth) override;
  virtual void addLeaf(Proposition *p, size_t id, bool second, int depth) override;
  virtual void removeItems() override;
  virtual void addItem(Proposition *p, int depth) override;
  virtual void popItem(int depth) override;
  virtual std::vector<Proposition *> getItems() override;

  virtual std::vector<Proposition *> minimize(bool isOffset) override;
  virtual std::vector<Proposition *> unpack() override;
  virtual std::vector<Proposition *> unpack(Proposition *pack) override;
  virtual std::vector<Proposition *> unpack(std::vector<Proposition *> &pack) override;

  virtual void clearPack(Proposition *pack) override;
  virtual std::pair<std::string, std::string> prettyPrint(bool offset) override;
  virtual bool isSolutionInconsequential(std::vector<Proposition *> &sol) override;
  virtual void substitute(int depth, int width, Proposition *&sub);
  virtual const DTLimits &getLimits() override;

private:
  ///List of operands
  PropositionAnd *_choices;
  ///Pointer to the Template using this operator
  Template *_t;
  DecTreeVariables _leaves;
};
}
