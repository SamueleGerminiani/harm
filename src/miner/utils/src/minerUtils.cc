#include <algorithm>
#include <deque>
#include <ostream>
#include <sstream>
#include <unordered_map>

#include "Automaton.hh"
#include "ClsOp.hh"
#include "Clustering.hh"
#include "EdgeProposition.hh"
#include "Float.hh"
#include "Int.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/NumericExpression.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"
#include <mutex>

namespace harm {
using namespace expression;

std::ostream &operator<<(std::ostream &os, ClsOp op) {
  switch (op) {
  case ClsOp::Range:
    os << "r";
    break;
  case ClsOp::E:
    os << "e";
    break;
  case ClsOp::GE:
    os << "ge";
    break;
  case ClsOp::LE:
    os << "le";
    break;
  }
  return os;
}

std::pair<ExpType, size_t>
variableTypeFromString(const std::string &type, size_t size) {
  //2-value: increasing size
  if (type == "bool") {
    return std::make_pair(ExpType::Bool, 1);
  } else if (type == "char" || type == "byte") {
    return std::make_pair(ExpType::SInt, 8);
  } else if (type == "unsigned char" || type == "byte unsigned") {
    return std::make_pair(ExpType::UInt, 8);
  } else if (type == "short" || type == "shortint") {
    return std::make_pair(ExpType::SInt, 16);
  } else if (type == "unsigned short" ||
             type == "shortint unsigned") {
    return std::make_pair(ExpType::UInt, 16);
  } else if (type == "int") {
    return std::make_pair(ExpType::SInt, sizeof(int) * 8);
  } else if (type == "unsigned int") {
    return std::make_pair(ExpType::UInt, sizeof(int) * 8);
  } else if (type == "long int" || type == "int64_t" ||
             type == "longint") {
    return std::make_pair(ExpType::SInt, 64);
  } else if (type == "unsigned long int" ||
             type == "longint unsigned" || type == "uint64_t") {
    return std::make_pair(ExpType::UInt, 64);
  } else if (type == "bit") {
    return std::make_pair(ExpType::UInt, size);
  } else if (type == "bit signed") {
    return std::make_pair(ExpType::SInt, size);

    //machine dependent
  } else if (type == "size_t") {
    return std::make_pair(ExpType::UInt, sizeof(size_t) * 8);

    //4-value
  } else if (type == "integer") {
    return std::make_pair(ExpType::SInt, 32);
  } else if (type == "integer unsigned") {
    return std::make_pair(ExpType::UInt, 32);
  } else if (type == "time") {
    return std::make_pair(ExpType::UInt, 64);
  } else if (type == "time signed") {
    return std::make_pair(ExpType::SInt, 64);
  } else if (type == "reg" || type == "wire" || type == "logic") {
    return std::make_pair(ExpType::UInt, size);
  } else if (type == "reg signed" || type == "wire signed" ||
             type == "logic signed") {
    return std::make_pair(ExpType::SInt, size);

    //float
  } else if (type == "double" || type == "float" || type == "real" ||
             type == "realtime" || type == "shortreal") {
    return std::make_pair(ExpType::Float, 64);
  }

  messageError("Unknown type: " + type);
  return std::make_pair(ExpType::Bool, 1);
}

std::string varTypeToString(const ExpType &type, size_t size) {

  if (isInt(type)) {
    if (isSigned(type)) {
      if (size == 8) {
        return "char";
      } else if (size == 16) {
        return "short";
      } else if (size == 32) {
        return "int32_t";
      } else if (size == 64) {
        return "int64_t";
      } else {
        return "int64_t";
      }
    } else {
      if (size == 8) {
        return "unsigned char";
      } else if (size == 16) {
        return "unsigned short";
      } else if (size == 32) {
        return "uint32_t";
      } else if (size == 64) {
        return "uint64_t";
      } else {
        return "uint64_t";
      }
    }
  } else if (isFloat(type)) {
    return "double";
  } else if (isBool(type)) {
    return "bool";
  }

  messageError("Conversion error for : " + to_string(type) + " " +
               std::to_string(size));
  return "error";
}

size_t getTypeBase(const std::string &type) {

  if (type == "reg") {
    return 2;
  } else if (type == "wire") {
    return 2;
  } else if (type == "logic") {
    return 2;
  } else if (type == "integer") {
    return 2;
  } else if (type == "time") {
    return 2;
  } else if (type == "wire signed") {
    return 2;
  } else if (type == "logic signed") {
    return 2;
  } else if (type == "time signed") {
    return 2;
  } else if (type == "integer unsigned") {
    return 2;
  } else if (type == "bit") {
    return 2;
  }
  return 10;
}

std::vector<PropositionPtr>
genPropsThroughClustering(std::vector<size_t> &ivs,
                          const NumericExpressionPtr &cn,
                          bool inDTAlgo) {

  std::vector<PropositionPtr> ret;

  if (cn->getType().first == ExpType::Float) {
    ret = runClustering<Float>(ivs, cn, inDTAlgo);
  } else if (cn->getType().first == ExpType::SInt) {
    ret = runClustering<SInt>(ivs, cn, inDTAlgo);
  } else if (cn->getType().first == ExpType::UInt) {
    ret = runClustering<UInt>(ivs, cn, inDTAlgo);
  } else {
    messageError("gebPropsThroughClustering: unknown numeric type "
                 "for expression: '" +
                 num2String(cn) + "'");
  }

  //  debug
  //  for (auto &p : ret) {
  //    std::cout << prop2String(*p)<< "\n";
  //  }
  return ret;
}

///var declaration to cpp class
VarDeclaration toVarDeclaration(std::string name, std::string type,
                                size_t size) {

  VarDeclaration ret;
  auto [t, s] = variableTypeFromString(type, size);

  if (isInt(t) && s > 64) {
    messageWarning("Truncating '" + name + "' to 64 bits");
    s = 64;
  }

  //optimization: 1 bit logic to bool
  if (isInt(t) && s == 1) {
    t = ExpType::Bool;
  }

  ret.setName(name);
  ret.setType(t, s);

  return ret;
}

PlaceholderPack extractPlaceholders(
    const expression::TemporalExpressionPtr &formula) {
  PlaceholderPack ret;

  traverse(formula, [&ret](const TemporalExpressionPtr &current) {
    if (isPlaceholder(current)) {
      ret._tokenToPP[getBooleanLayerToken(current)] =
          getPlaceholderPointer(current);
      return true;
    } else if (isInst(current)) {
      BooleanLayerInstPtr i =
          std::dynamic_pointer_cast<BooleanLayerInst>(current);
      ret._tokenToInst[i->getToken()] = i->getProposition();
      return true;
    }
    //dont skip the children of this formula
    return false;
  });

  return ret;
}
#define UNKNOWN_DEPTH()                                              \
  max = -1;                                                          \
  return;
void maxTemporalDepth(int &max, const TemporalExpressionPtr &item) {
  //if the formula contains nonconsecutive operators, the depth is unknown (-1)

  messageErrorIf(isPropertyImplication(item),
                 "Unsupported operator in temporal depth "
                 "calculation: PropertyImplication");
  if (isPropertyAnd(item) || isPropertyOr(item) || isSereAnd(item) ||
      isSereOr(item) || isSereIntersect(item)) {
    //parallel operators: we keep the maximum depth of the children
    for (auto subItem : item->getItems()) {
      int childMaxDepth = 0;
      maxTemporalDepth(childMaxDepth, subItem);
      if (childMaxDepth == -1) {
        UNKNOWN_DEPTH();
      }
      max = std::max(max, childMaxDepth);
    }
  } else if (isPropertyNext(item) || isSereDelay(item) ||
             isSereConsecutiveRep(item) || isSereConcat(item)) {
    //sequential operators: increase the depth
    if (isPropertyNext(item)) {
      int childMaxDepth = 0;
      maxTemporalDepth(childMaxDepth, item->getItems()[0]);
      if (childMaxDepth == -1) {
        UNKNOWN_DEPTH();
      }
      max = childMaxDepth +
            (int)std::dynamic_pointer_cast<PropertyNext>(item)
                ->getDelay();
    } else if (isSereConsecutiveRep(item)) {
      auto window =
          std::dynamic_pointer_cast<SereConsecutiveRep>(item)
              ->getWindow();
      if (window.second == -1) {
        //unbounded repetition
        UNKNOWN_DEPTH();
      }
      int childMaxDepth = 0;
      maxTemporalDepth(childMaxDepth, item->getItems()[0]);
      if (window.second > 1 || childMaxDepth > 0) {
        childMaxDepth = childMaxDepth == 0 ? 1 : childMaxDepth;
        max = (childMaxDepth * window.second) - 1;
      } else {
        max = 0;
      }

    } else if (isSereDelay(item)) {
      auto window =
          std::dynamic_pointer_cast<SereDelay>(item)->getWindow();
      if (window.second == -1) {
        //unbounded delay
        UNKNOWN_DEPTH();
      }

      int leftChildMaxDepth = 0;
      if (item->size() > 1) {
        auto left = item->getItems()[0];
        maxTemporalDepth(leftChildMaxDepth, left);
        if (leftChildMaxDepth == -1) {
          UNKNOWN_DEPTH();
        }
      }

      auto right = item->getItems().size() == 1 ? item->getItems()[0]
                                                : item->getItems()[1];
      int rightChildMaxDepth = 0;
      maxTemporalDepth(rightChildMaxDepth, right);

      if (rightChildMaxDepth == -1) {
        UNKNOWN_DEPTH();
      }
      max = leftChildMaxDepth + window.second + rightChildMaxDepth;

    } else if (isSereConcat(item)) {
      auto left = item->getItems()[0];
      int leftChildMaxDepth = 0;
      maxTemporalDepth(leftChildMaxDepth, left);
      if (leftChildMaxDepth == -1) {
        UNKNOWN_DEPTH();
      }

      auto right = item->getItems().size() == 1 ? item->getItems()[0]
                                                : item->getItems()[1];
      int rightChildMaxDepth = 0;
      maxTemporalDepth(rightChildMaxDepth, right);
      if (rightChildMaxDepth == -1) {
        UNKNOWN_DEPTH();
      }
      max = leftChildMaxDepth + rightChildMaxDepth +
            (isOverlappingConcat(item) ? 0 : 1);
    }
  } else if (isPropertyEventually(item) || isPropertyAlways(item) ||
             isPropertyUntil(item) || isPropertyRelease(item) ||
             isSereNonConsecutiveRep(item) || isSereGoto(item) ||
             isSerePlus(item)) {
    //nonconsecutive operators
    UNKNOWN_DEPTH();
  } else if (isBooleanLayer(item)) {
    return;
  } else {
    //neutral operators: continue the search
    for (auto subItem : item->getItems()) {
      maxTemporalDepth(max, subItem);
    }
  }
}

int getTemporalDepth(const TemporalExpressionPtr &te) {
  int max = 0;
  maxTemporalDepth(max, te);
  return max;
}

void substitutePlaceholders(TemporalExpressionPtr &original,
                            const PlaceholderPack &pack) {

  traverse(original, [&](TemporalExpressionPtr &current) {
    if (isPlaceholder(current)) {
      if (pack._tokenToPP.count(getBooleanLayerToken(current))) {
        getPlaceholderPointer(current) =
            pack._tokenToPP.at(getBooleanLayerToken(current));
      }
    }

    return false;
  });
}

} // namespace harm
