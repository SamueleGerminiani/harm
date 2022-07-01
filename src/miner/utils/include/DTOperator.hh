#pragma once

#include "DTLimits.hh"
#include "DTUtils.hh"
#include "Hstring.hh"
#include "exp.hh"
#include <map>
#include <pthread.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace harm {

class Template;
class Automaton;

using namespace expression;
using DecTreeVariables =
    std::map<size_t, std::pair<Proposition *, Proposition *>>;

class DTOperator {
public:
  virtual ~DTOperator() {}
  virtual void addItem(Proposition *p, int depth) = 0;
  virtual void popItem(int depth) = 0;
  virtual void removeItems() = 0;

  virtual std::vector<Proposition *> minimize(bool isOffset) = 0;
  virtual std::vector<Proposition *> unpack() = 0;
  virtual std::vector<Proposition *> unpack(Proposition *pack) = 0;
  virtual std::vector<Proposition *>
  unpack(std::vector<Proposition *> &pack) = 0;
  virtual void clearPack(Proposition *pack) = 0;

  virtual void addLeaf(Proposition *p, size_t id, bool second, int depth) = 0;
  virtual void removeLeaf(size_t id, bool second, int depth) = 0;
  virtual bool canInsertAtDepth(int depth) = 0;
  virtual void substitute(int depth, int width, Proposition*& sub) = 0;
  virtual bool isTaken(size_t id, bool second, int depth) = 0;

  virtual bool isRandomConstructed() = 0;
  virtual bool isMultiDimensional() = 0;
  virtual bool isSolutionInconsequential(std::vector<Proposition *> &sol) = 0;

  virtual std::vector<Proposition *> getItems() = 0;
  virtual size_t getNChoices() = 0;
  virtual size_t getCurrentDepth() = 0;
  virtual const DTLimits &getLimits() = 0;

  virtual std::pair<std::string, std::string> prettyPrint(bool offset) = 0;

protected:
  std::vector<Proposition *> _items;
  DTLimits _limits;
};

}
