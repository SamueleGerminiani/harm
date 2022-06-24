#include "minerUtils.hh"
#include "Hierarchical.hh"
#include "KDE.hh"
#include "Kmeans.hh"
#include "Template.hh"
#include "globals.hh"

namespace harm {

std::pair<VarType, uint8_t> variableTypeFromString(const std::string &type,
                                                   uint8_t size) {
  if (type == "bool") {
    return std::make_pair(VarType::Bool, 1);
  } else if (type == "char") {
    return std::make_pair(VarType::SLogic, 8);
  } else if (type == "short") {
    return std::make_pair(VarType::SLogic, 16);
  } else if (type == "int") {
    return std::make_pair(VarType::SLogic, 32);
  } else if (type == "long int") {
    return std::make_pair(VarType::SLogic, 64);
  } else if (type == "unsigned char") {
    return std::make_pair(VarType::ULogic, 8);
  } else if (type == "unsigned short") {
    return std::make_pair(VarType::ULogic, 16);
  } else if (type == "unsigned int") {
    return std::make_pair(VarType::ULogic, 32);
  } else if (type == "unsigned long int") {
    return std::make_pair(VarType::ULogic, 64);
  } else if (type == "float") {
    return std::make_pair(VarType::Numeric, 32);
  } else if (type == "double") {
    return std::make_pair(VarType::Numeric, 64);
  } else if (type == "integer") {
    return std::make_pair(VarType::SLogic, 32);

  } else if (type == "byte") {
    return std::make_pair(VarType::SLogic, 8);
  } else if (type == "shortint") {
    return std::make_pair(VarType::SLogic, 16);
  } else if (type == "longint") {
    return std::make_pair(VarType::SLogic, 64);
  } else if (type == "byte unsigned") {
    return std::make_pair(VarType::ULogic, 8);
  } else if (type == "shortint unsigned") {
    return std::make_pair(VarType::ULogic, 16);
  } else if (type == "longint unsigned") {
    return std::make_pair(VarType::ULogic, 64);
  } else if (type == "time") {
    return std::make_pair(VarType::ULogic, 64);
  } else if (type == "shortreal") {
    return std::make_pair(VarType::Numeric, 32);
  } else if (type == "real") {
    return std::make_pair(VarType::Numeric, 64);
  } else if (type == "reg") {
    return std::make_pair(VarType::ULogic, size);
  } else if (type == "wire") {
    return std::make_pair(VarType::ULogic, size);
  } else if (type == "logic") {
    return std::make_pair(VarType::ULogic, size);
  } else if (type == "bit") {
    return std::make_pair(VarType::ULogic, size);
  }

  messageError("Unknown type: " + type);

  return std::make_pair(VarType::Bool, 1);
}

template <typename T>
std::vector<Proposition *> inline makeLogicRange(
    std::vector<std::pair<T, T>> &clusters, std::pair<VarType, T> type,
    CachedAllNumeric *cn) {

  std::vector<Proposition *> ret;
  for (auto &c : clusters) {
    if (c.first != c.second) {
      LogicExpression *ll =
          new LogicConstant(c.first, type.first, type.second, cn->getMaxTime());
      LogicExpression *rl = new LogicConstant(c.second, type.first, type.second,
                                              cn->getMaxTime());
      LogicExpression *l1 = copy(*cn->get()._le);
      LogicExpression *l2 = copy(*cn->get()._le);
      ret.push_back(
          makeExpression<PropositionAnd>(makeExpression<LogicGreaterEq>(l1, ll),
                                         makeExpression<LogicLessEq>(l2, rl)));
      ret.push_back(makeExpression<LogicGreaterEq>(copy(*l1), copy(*ll)));
      ret.push_back(makeExpression<LogicLessEq>(copy(*l2), copy(*rl)));
    } else {
      LogicExpression *lc =
          new LogicConstant(c.first, type.first, type.second, cn->getMaxTime());
      LogicExpression *le = copy(*cn->get()._le);
      ret.push_back(makeExpression<LogicEq>(le, lc));
    }
  }
  return ret;
}

template <typename T>
std::vector<Proposition *> inline makeNumericRange(
    std::vector<std::pair<T, T>> &clusters, std::pair<VarType, T> type,
    CachedAllNumeric *cn) {

  std::vector<Proposition *> ret;
  for (auto &c : clusters) {
    if (c.first != c.second) {
      NumericExpression *ll = new NumericConstant(
          c.first, type.first, type.second, cn->getMaxTime());
      NumericExpression *rl = new NumericConstant(
          c.second, type.first, type.second, cn->getMaxTime());
      NumericExpression *l1 = copy(*cn->get()._ne);
      NumericExpression *l2 = copy(*cn->get()._ne);
      ret.push_back(makeExpression<PropositionAnd>(
          makeExpression<NumericGreaterEq>(l1, ll),
          makeExpression<NumericLessEq>(l2, rl)));
      ret.push_back(makeExpression<NumericGreaterEq>(copy(*l1), copy(*ll)));
      ret.push_back(makeExpression<NumericLessEq>(copy(*l2), copy(*rl)));
    } else {
      NumericExpression *lc = new NumericConstant(
          c.first, type.first, type.second, cn->getMaxTime());
      NumericExpression *le = copy(*cn->get()._ne);
      ret.push_back(makeExpression<NumericEq>(le, lc));
    }
  }
  return ret;
}

template <typename T>
std::vector<std::pair<T, T>> clsElbow(std::vector<T> &elements,
                                      double clsEffort) {
  std::vector<std::pair<T, T>> clusters;
  if (clc::clsAlg == "kmeans") {
    clusters = kmeansElbow<T>(elements, 20, clsEffort);
  } else if (clc::clsAlg == "kde") {
    clusters = kdeElbow<T>(elements, 20, clsEffort);
  } else if (clc::clsAlg == "hc") {
    clusters = hcElbow<T>(elements, 20, clsEffort);
  }
  return clusters;
}

std::vector<Proposition *> genPropsThroughClustering(std::vector<size_t> &ivs,
                                                     CachedAllNumeric *cn,
                                                     size_t max_length) {

  std::vector<Proposition *> ret;
  std::pair<VarType, uint8_t> type = cn->getType();

  if (cn->getType().first == VarType::Numeric) {
    if (cn->getType().second == 32) {
      std::vector<float> elements;
      for (auto &iv : ivs) {
        elements.push_back(cn->evaluate(iv)._f);
      }
      auto clusters = clsElbow<float>(elements, cn->_clsEffort);
      return makeNumericRange<float>(clusters, type, cn);
    } else {
      std::vector<double> elements;
      for (auto &iv : ivs) {
        elements.push_back(cn->evaluate(iv)._d);
      }
      auto clusters = clsElbow<double>(elements, cn->_clsEffort);
      return makeNumericRange<double>(clusters, type, cn);
    }
  } else if (cn->getType().first == VarType::SLogic) {
    std::vector<int64_t> elements;
    for (auto &iv : ivs) {
      elements.push_back(cn->evaluate(iv)._s);
    }
    auto clusters = clsElbow<int64_t>(elements, cn->_clsEffort);
    return makeLogicRange<int64_t>(clusters, type, cn);
  } else if (cn->getType().first == VarType::ULogic) {
    std::vector<int64_t> elements;
    for (auto &iv : ivs) {
      elements.push_back(cn->evaluate(iv)._u);
    }
    std::vector<std::pair<int64_t, int64_t>> clusters =
        clsElbow<int64_t>(elements, cn->_clsEffort);
    return makeLogicRange<int64_t>(clusters, type, cn);
  } else {
    messageError("Unknown type in CachedAllNumeric");
  }

  //  debug
  //  for (auto &p : ret) {
  //    std::cout << prop2String(*p)<< "\n";
  //  }
  return ret;
}

} // namespace harm
