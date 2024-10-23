#include <algorithm>
#include <iterator>
#include <stack>
#include <unordered_set>
#include <vector>

#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/atom/Variable.hh"
#include "visitors/CopyVisitor.hh"
#include "visitors/PrinterVisitor.hh"
#include "visitors/TraceChangerVisitor.hh"
#include "visitors/VarExtractVisitor.hh"

namespace expression {
enum class ExpType;
} // namespace expression

namespace expression {
#define expToString(prefix, type)                                    \
  std::string prefix##2String(const type &o) {                       \
    PrinterVisitor printer(Language::SpotLTL, 0,                     \
                           PrintMode::ShowAll);                      \
    o->acceptVisitor(printer);                                       \
    return printer.get();                                            \
  }                                                                  \
  std::string prefix##2ColoredString(const type &exp) {              \
    PrinterVisitor printer(Language::SpotLTL, 1,                     \
                           PrintMode::ShowAll);                      \
    exp->acceptVisitor(printer);                                     \
    return printer.get();                                            \
  }

#define expOutOp(prefix, type)                                       \
  std::ostream &operator<<(std::ostream &os, const type &o) {        \
    PrinterVisitor printer(Language::SpotLTL, 0,                     \
                           PrintMode::ShowAll);                      \
    o->acceptVisitor(printer);                                       \
    os << printer.get();                                             \
    return os;                                                       \
  }

#define expStringStreamOp(prefix, type)                              \
  std::stringstream &operator<<(std::stringstream &os,               \
                                const type &o) {                     \
    PrinterVisitor printer(Language::SpotLTL, 0,                     \
                           PrintMode::ShowAll);                      \
    o->acceptVisitor(printer);                                       \
    os << printer.get();                                             \
    return os;                                                       \
  }

#define expCopyOp(suffix, type)                                      \
  type copy(const type &o) {                                         \
    CopyVisitor copier(false);                                       \
    o->acceptVisitor(copier);                                        \
    auto c = copier.get##suffix();                                   \
    if (o->isCacheEnabled()) {                                       \
      c->enableCache();                                              \
    }                                                                \
    return c;                                                        \
  }

#define expGetVars(suffix, type)                                     \
  std::vector<std::pair<std::string, std::pair<ExpType, size_t>>>    \
  getVars(const type &o) {                                           \
    VarExtractVisitor varext;                                        \
    o->acceptVisitor(varext);                                        \
    return varext.get_vars();                                        \
  }

// clang-format off
expToString(prop, PropositionPtr)

std::string temp2String(const TemporalExpressionPtr &exp, const Language lang, const PrintMode mode){
    PrinterVisitor printer(lang,false,mode);                                       
    exp->acceptVisitor(printer);                                        
    return printer.get();                                            
  }                                                                  
std::string temp2ColoredString(const TemporalExpressionPtr &exp, const Language lang, const PrintMode mode){
    PrinterVisitor printer(lang,true,mode);
    exp->acceptVisitor(printer);                                      
    return printer.get();                                            
  }
expToString(float, FloatExpressionPtr)
expToString(int, IntExpressionPtr)
expToString(num, NumericExpressionPtr)

expOutOp(prop, PropositionPtr)
expOutOp(temp, TemporalExpressionPtr)
expOutOp(float, FloatExpressionPtr)
expOutOp(int, IntExpressionPtr)
expOutOp(num, NumericExpressionPtr)


expCopyOp(Proposition, PropositionPtr)
  TemporalExpressionPtr copy(const TemporalExpressionPtr &o, bool removePlaceholders) {                                              
    CopyVisitor copier(removePlaceholders);                                              
    o->acceptVisitor(copier);                                         
    auto c = copier.getTemporal();                                   
    return c;                                                        
  }
expCopyOp(Float, FloatExpressionPtr)
expCopyOp(Int, IntExpressionPtr)
    // clang-format on
    NumericExpressionPtr copy(const NumericExpressionPtr &o) {
  CopyVisitor copier(false);
  o->acceptVisitor(copier);
  NumericExpressionPtr copy = copier.getNum();
  copy->_clsConfig = o->_clsConfig;
  return (copy);
}
// clang-format off

expGetVars(Proposition, PropositionPtr)
expGetVars(Temporal, TemporalExpressionPtr)
expGetVars(Float, FloatExpressionPtr)
expGetVars(Int, IntExpressionPtr)
    // clang-format on

    void sortPropositions(std::vector<PropositionPtr> &props) {
  std::sort(begin(props), end(props),
            [](PropositionPtr e1, PropositionPtr e2) {
              return prop2String(e1) < prop2String(e2);
            });
}

size_t getNumVariables(const std::vector<PropositionPtr> &props) {
  size_t ret = 0;
  for (const PropositionPtr &p : props) {
    ret += getVars(p).size();
  }
  return ret;
}

size_t getNumVariables(const PropositionPtr &p) {
  return getVars(p).size();
}

size_t getRepetitions(const std::vector<PropositionPtr> &props) {
  size_t ret = 0;
  std::unordered_set<std::string> propStr;

  for (const PropositionPtr &p : props) {
    auto ps = prop2String(p);
    if (propStr.count(ps)) {
      ret++;
    } else {
      propStr.insert(ps);
    }
  }

  return ret;
}

void changeTrace(const PropositionPtr &p,
                 const harm::TracePtr &newTrace) {
  TraceChangerVisitor tg(newTrace);
  p->acceptVisitor(tg);
}
void changeTrace(const TemporalExpressionPtr &te,
                 const harm::TracePtr &newTrace) {
  TraceChangerVisitor tg(newTrace);
  te->acceptVisitor(tg);
}
bool isConstantTrue(const PropositionPtr &p) {
  return dynamic_cast<expression::BooleanConstant *>(p.get()) !=
             nullptr &&
         dynamic_cast<expression::BooleanConstant *>(p.get())
             ->evaluate(0);
}

bool isSimple(const TemporalExpressionPtr &exp) {

  size_t phCount = 0;
  bool ret = true;
  traverse(exp, [&](const TemporalExpressionPtr &current) {
    if (isBooleanLayer(current)) {
      phCount++;
      if (phCount > 1) {
        ret = false;
      }
      return true;
    }
    if (!(isPropertyNot(current) || isPropertyNext(current) ||
          isSereDelay(current))) {
      ret = false;
    }
    return false;
  });

  return ret;
}

std::string printAST_terminal(const TemporalExpressionPtr &exp,
                              const Language lang,
                              const PrintMode mode) {
  // configurable parameters
  // Warning: the vertical connector must be a single character
  const char kVerticalConnector_ = '|';
  const std::string kHorizontalConnector_ = "`--> ";
  const size_t kVerticalSpaceBetweenNodes_ = 2;
  const std::string kHorizontalWhiteSpace_ = std::string(5, ' ');

  std::stringstream terminal_;
  // the edges string is used to keep track of the edges of the tree
  std::string edge_str_;
  std::stack<TemporalExpressionPtr> visitStack;

  std::function<void(const TemporalExpressionPtr &)> enter =
      [&](const TemporalExpressionPtr &current) {
        messageErrorIf(!visitStack.empty() &&
                           visitStack.top()->empty(),
                       "The parent does not have children?!?");
        if (!visitStack.empty() &&
            current == visitStack.top()->getItems().back()) {
          //  if this is the last child, we need to replace the last appended edge
          //  with white space
          edge_str_.replace(edge_str_.size() -
                                (kHorizontalWhiteSpace_.size() + 1),
                            kHorizontalWhiteSpace_.size() + 1,
                            kHorizontalWhiteSpace_.size() + 1, ' ');
        }

        visitStack.push(current);

        // print the node
        terminal_ << edge_str_ << kHorizontalConnector_
                  << temp2ColoredString(current, lang, mode)
                  << (!isBooleanLayer(current)
                          ? (" --> " +
                             opeToString(current->getOperator(),
                                         lang))
                          : "")
                  << "\n";

        if (current->empty()) {
          return;
        }

        // append a new vertical connector for the children of this node
        edge_str_ += kHorizontalWhiteSpace_ + kVerticalConnector_;

        // print the edges, the space between nodes is dictated by the
        // kVerticalSpaceBetweenNodes_ parameter
        for (size_t i = 0; i < kVerticalSpaceBetweenNodes_; i++) {
          terminal_ << edge_str_ << "\n";
        }
      };

  std::function<void(const TemporalExpressionPtr &)> exit =
      [&](const TemporalExpressionPtr &current) {
        // reduce the edges string to match the parent (only if not a leaf)
        if (!current->empty()) {
          edge_str_ = edge_str_.substr(
              0,
              edge_str_.size() - (kHorizontalWhiteSpace_.size() + 1));
        }

        visitStack.pop();
      };

  traverse(exp, enter, exit);

  return terminal_.str();
}

} // namespace expression
