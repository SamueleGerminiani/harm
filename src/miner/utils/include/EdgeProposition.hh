#pragma once

#include "exp.hh"

class EdgeProposition {
public:
  virtual bool evaluate(size_t time) = 0;
  virtual std::string toString() = 0;
  virtual ~EdgeProposition() {}
  std::vector<EdgeProposition *> getOperands() { return _operands; }

protected:
  std::vector<EdgeProposition *> _operands;
};
class EdgeAnd : public EdgeProposition {
public:
  EdgeAnd(EdgeProposition *p1, EdgeProposition *p2);

  EdgeAnd(std::vector<EdgeProposition *> pp);
  ~EdgeAnd() override;
  bool evaluate(size_t time) override;
  std::string toString() override;
};

class EdgeOr : public EdgeProposition {
public:
  EdgeOr(EdgeProposition *p1, EdgeProposition *p2);
  EdgeOr(std::vector<EdgeProposition *> pp);
  ~EdgeOr() override;
  bool evaluate(size_t time) override;
  std::string toString() override;
};
class EdgeNot : public EdgeProposition {
public:
  EdgeNot(EdgeProposition *p);

  ~EdgeNot() override;

  bool evaluate(size_t time) override;

  std::string toString() override;
};
class EdgeTrue : public EdgeProposition {
public:
  EdgeTrue() : EdgeProposition() {}
  ~EdgeTrue() override {}
  bool evaluate(size_t time) override;
  std::string toString() override;
};
class EdgeFalse : public EdgeProposition {
public:
  EdgeFalse() : EdgeProposition() {}
  ~EdgeFalse() override {}
  bool evaluate(size_t time) override;
  std::string toString() override;
};
class EdgePlaceholder : public EdgeProposition {
public:
  EdgePlaceholder(expression::Proposition **toProp,
                  const std::string &phName = "");
  bool evaluate(size_t time);
  std::string toString();
  expression::Proposition **_toProp;
  std::string _phName = "";
};
