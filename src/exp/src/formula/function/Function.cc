#include "formula/function/Function.hh"
#include "Logic.hh"
#include "formula/function/SVAfunction.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {
//Past------------------------------------------
//Must define these here because in Function.i.hh ExpVisitor is an incomplete type and cannot be included due to circular dependency between Function.hh and ExpVisitor.hh
template <> void PropositionPast::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void IntPast::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void LogicPast::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void FloatPast::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

//Stable------------------------------------------
template <> void PropositionStable::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void IntStable::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void LogicStable::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void FloatStable::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

//Rose------------------------------------------

template <> void PropositionRose::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void IntRose::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void LogicRose::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void PropositionRose::initEvaluate() {
  directEvaluate = [this](size_t time) {
    PropositionPtr &op = _isTemporal ? *_phPtr : _op;
    return time == 0 ? false
                     : !op->evaluate(time - 1) && op->evaluate(time);
  };
  disableCache();
}

//Rose------------------------------------------
template <> void IntRose::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return time == 0 ? false
                     : (_op->evaluate(time - 1) & 1) == 0 &&
                           (_op->evaluate(time) & 1) == 1;
  };
  disableCache();
}

template <> void LogicRose::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return time == 0 ? false
                     : (_op->evaluate(time - 1).getUnsignedValue() &
                        (ULogic)1) == 0 &&
                           (_op->evaluate(time).getUnsignedValue() &
                            (ULogic)1) == 1;
  };
  disableCache();
}

//Fell------------------------------------------

template <> void PropositionFell::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void IntFell::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void LogicFell::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void PropositionFell::initEvaluate() {
  directEvaluate = [this](size_t time) {
    PropositionPtr &op = _isTemporal ? *_phPtr : _op;
    return time == 0 ? false
                     : op->evaluate(time - 1) && !op->evaluate(time);
  };
  disableCache();
}

template <> void IntFell::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return time == 0 ? false
                     : (_op->evaluate(time - 1) & 1) == 1 &&
                           (_op->evaluate(time) & 1) == 0;
  };
  disableCache();
}

template <> void LogicFell::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return time == 0 ? false
                     : (_op->evaluate(time - 1).getUnsignedValue() &
                        (ULogic)1) == 1 &&
                           (_op->evaluate(time).getUnsignedValue() &
                            (ULogic)1) == 0;
  };
  disableCache();
}

} // namespace expression
