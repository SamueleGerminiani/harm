#pragma once
#include "Atom.hh"

#include "ClsOp.hh"
namespace expression {
class CachedAllNumeric {
  union EvalRet {
    double _d;
    float _f;
    ULogic _u;
    SLogic _s;
  };
  union GetRet {
    NumericExpression *_ne;
    LogicExpression *_le;
  };

public:
  CachedAllNumeric(NumericExpression *nume, double clsEffort = 1.0f,
                   const std::unordered_set<harm::ClsOp> &clsOps =
                       std::unordered_set<harm::ClsOp>({harm::ClsOp::Range,
                                                        harm::ClsOp::E}));
  CachedAllNumeric(LogicExpression *loge, double clsEffort = 1.0f,
                   const std::unordered_set<harm::ClsOp> &clsOps =
                       std::unordered_set<harm::ClsOp>({harm::ClsOp::Range,
                                                        harm::ClsOp::E}));
  virtual ~CachedAllNumeric();
  EvalRet evaluate(size_t time);

  virtual void acceptVisitor(ExpVisitor &vis) ;

  virtual size_t getMaxTime();

  void setType(VarType type, size_t size);
  std::pair<VarType, size_t> getType();
  GetRet get();

private:
  NumericExpression *_nume = nullptr;
  LogicExpression *_loge = nullptr;
  double *_cachedd;
  float *_cachedf;
  ULogic *_cachedul;
  SLogic *_cachedsl;

public:
  double _clsEffort = 0.3f;
  std::unordered_set<harm::ClsOp> _clsOps;
};
} // namespace expression
