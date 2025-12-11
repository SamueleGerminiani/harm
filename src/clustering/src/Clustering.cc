
#include <algorithm>
#include <stddef.h>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClsOp.hh"
#include "Contiguous.hh" // IWYU pragma: keep
#include "Float.hh"
#include "Int.hh"
#include "Kmeans.hh" // IWYU pragma: keep
#include "Logic.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/expression/SetMembership.hh" // IWYU pragma: keep
#include "message.hh"

namespace harm {
using namespace expression;

template <typename ET>
using GetGreaterEqType = std::conditional_t<
    std::is_same_v<ET, FloatExpression>, FloatGreaterEq,
    std::conditional_t<std::is_same_v<ET, IntExpression>,
                       IntGreaterEq, LogicGreaterEq>>;
template <typename ET>
using GetLessEqType = std::conditional_t<
    std::is_same_v<ET, FloatExpression>, FloatLessEq,
    std::conditional_t<std::is_same_v<ET, IntExpression>, IntLessEq,
                       LogicLessEq>>;
template <typename ET>
using GetEqType = std::conditional_t<
    std::is_same_v<ET, FloatExpression>, FloatEq,
    std::conditional_t<std::is_same_v<ET, IntExpression>, IntEq,
                       LogicEq>>;

template <typename C>
std::vector<PropositionPtr>
makeRange(const std::vector<std::pair<GenericPtr<C>, GenericPtr<C>>>
              &constants,
          std::pair<ExpType, size_t> type, const GenericPtr<C> &n,
          const std::unordered_set<harm::ClsOp> &operators) {

  std::vector<PropositionPtr> ret;

  for (auto &[left, right] : constants) {
    if (left->evaluate(0) == right->evaluate(0)) {
      //eq
      if (operators.count(ClsOp::E)) {
        ret.push_back(
            makeGenericExpression<GetEqType<C>>(copy(n), copy(left)));
      }
    } else {
      if (operators.count(ClsOp::Range)) {
        //range, ge, le, eq
        ret.push_back(makeGenericExpression<PropositionAnd>(
            makeGenericExpression<GetGreaterEqType<C>>(copy(n),
                                                       copy(left)),
            makeGenericExpression<GetLessEqType<C>>(copy(n),
                                                    copy(right))));
      }
      if (operators.count(ClsOp::GE)) {
        ret.push_back(makeGenericExpression<GetGreaterEqType<C>>(
            copy(n), copy(left)));
      }
      if (operators.count(ClsOp::LE)) {
        ret.push_back(makeGenericExpression<GetLessEqType<C>>(
            copy(n), copy(right)));
      }
    }
  }

  return ret;
}

template <typename ET>
using GetSetMembershipType = std::conditional_t<
    std::is_same_v<ET, FloatExpression>, FloatSetMembership,
    std::conditional_t<std::is_same_v<ET, IntExpression>,
                       IntSetMembership, LogicSetMembership>>;
template <typename C>
std::vector<PropositionPtr>
makeInside(const std::vector<std::pair<GenericPtr<C>, GenericPtr<C>>>
               &constants,
           std::pair<ExpType, size_t> type, const GenericPtr<C> &n,
           const std::unordered_set<harm::ClsOp> &operators) {

  std::vector<PropositionPtr> ret;
  for (auto &[left, right] : constants) {
    if (left->evaluate(0) == right->evaluate(0)) {
      //set
      if (operators.count(ClsOp::E)) {
        ret.push_back(
            makeGenericExpression<GetEqType<C>>(copy(n), copy(left)));
      }
    } else {
      //range
      if (operators.count(ClsOp::Range)) {
        ret.push_back(generatePtr<GetSetMembershipType<C>>(
            copy(n), std::vector<GenericPtr<C>>{},
            std::vector<std::pair<GenericPtr<C>, GenericPtr<C>>>(
                {std::make_pair(copy(left), copy(right))})));
      }
      if (operators.count(ClsOp::GE)) {
        ret.push_back(generatePtr<GetSetMembershipType<C>>(
            copy(n), std::vector<GenericPtr<C>>{},
            std::vector<std::pair<GenericPtr<C>, GenericPtr<C>>>(
                {std::make_pair(
                    copy(right),
                    makeMaxConstant<C>(n->getType(),
                                       n->getMaxTime()))})));
      }
      if (operators.count(ClsOp::LE)) {
        ret.push_back(generatePtr<GetSetMembershipType<C>>(
            copy(n), std::vector<GenericPtr<C>>{},
            std::vector<std::pair<GenericPtr<C>, GenericPtr<C>>>(
                {std::make_pair(
                    makeMinConstant<C>(n->getType(), n->getMaxTime()),
                    copy(left))})));
      }
    }
  }

  return ret;
}

template <typename T>
std::vector<std::pair<GenericPtr<GetNumericExpType<T>>,
                      GenericPtr<GetNumericExpType<T>>>>
makeConstants(const std::vector<std::pair<T, T>> &clusters,
              std::pair<ExpType, size_t> type, size_t max_time) {

  std::vector<std::pair<GenericPtr<GetNumericExpType<T>>,
                        GenericPtr<GetNumericExpType<T>>>>
      ret;

  for (const auto &c : clusters) {
    if constexpr (std::is_same<T, expression::Float>::value) {
      FloatExpressionPtr lc = generatePtr<FloatConstant>(
          c.first, type.first, type.second, max_time);
      FloatExpressionPtr rc = generatePtr<FloatConstant>(
          c.second, type.first, type.second, max_time);
      ret.emplace_back(lc, rc);
    } else if constexpr (std::is_same<T, SInt>::value) {
      IntExpressionPtr lc = generatePtr<IntConstant>(
          (UInt)c.first, type.first, type.second, max_time);
      IntExpressionPtr rc = generatePtr<IntConstant>(
          (UInt)c.second, type.first, type.second, max_time);
      ret.emplace_back(lc, rc);
    } else if constexpr (std::is_same<T, SLogic>::value) {
      LogicExpressionPtr lc = generatePtr<LogicConstant>(
          Logic(type.second, isSigned(type.first), (ULogic)c.first, 0,
                0),
          type.first, type.second, max_time);

      LogicExpressionPtr rc = generatePtr<LogicConstant>(
          Logic(type.second, isSigned(type.first), (ULogic)c.second,
                0, 0),
          type.first, type.second, max_time);
      ret.emplace_back(lc, rc);
    } else {
      messageError("Unsupported type");
    }
  }
  return ret;
}

template <typename Original, typename Signed>
std::vector<Signed> gatherElements(const std::vector<size_t> &ivs,
                                   const NumericExpressionPtr &cn) {
  std::vector<Signed> elements;
  for (auto &iv : ivs) {
    if constexpr (std::is_same_v<Original, UInt> ||
                  std::is_same_v<Original, SInt>) {
      Signed val = (Signed)cn->evaluate<Original>(iv);
      if (!cn->_clsConfig._excluded.count(std::to_string(val))) {
        elements.push_back(val);
      }

    } else if constexpr (std::is_same_v<Original, ULogic> ||
                         std::is_same_v<Original, SLogic>) {
      Signed val = (Signed)cn->evaluate<Original>(iv);
      if (!cn->containsXZ(iv) &&
          !cn->_clsConfig._excluded.count(
              boost::multiprecision::to_string(val))) {
        elements.push_back(val);
      }
    } else {
      if (!cn->_clsConfig._excluded.count(std::to_string(iv))) {
        Signed val = (Signed)cn->evaluate<Signed>(iv);
        elements.push_back(val);
      }
    }
  }
  //debug
  //std::cout << num2String(cn) << "\n";
  //std::map<Signed, size_t> elementCount;
  //for (auto &e : elements) {
  //  elementCount[e]++;
  //}
  //for (auto &[k, v] : elementCount) {
  //  std::cout << k << "(#" << v << ") ";
  //}
  //std::cout << "\n";

  return elements;
}

template <typename T>
std::vector<PropositionPtr>
runClustering(const std::vector<size_t> &ivs,
              const NumericExpressionPtr &cn, bool inDTAlgo) {
  std::vector<PropositionPtr> ret;

  //cluster only signed types
  using SignedType = std::conditional_t<
      std::is_same_v<T, UInt>, SInt,
      std::conditional_t<std::is_same_v<T, ULogic>, SLogic, T>>;

  //gather signed elements
  std::vector<SignedType> elements =
      gatherElements<T, SignedType>(ivs, cn);

  if (elements.empty()) {
    return ret;
  }

  //get clustering parameters
  const std::unordered_set<ClsType> clsTypes =
      cn->_clsConfig._clusteringType;
  const std::unordered_set<ClsOp> clsOps = cn->_clsConfig._clsOps;
  size_t maxClusters = cn->_clsConfig._maxClusters;
  double minWCSS = cn->_clsConfig._minWCSS;
  auto type = cn->getType();

  for (const auto &ct : clsTypes) {
    std::vector<std::pair<GenericPtr<GetNumericExpType<SignedType>>,
                          GenericPtr<GetNumericExpType<SignedType>>>>
        constants;
    std::vector<std::pair<SignedType, SignedType>> clusters;
    std::vector<PropositionPtr> tmpProps;

    if (isKmeans(ct)) {
      if (inDTAlgo && ct == ClsType::Kmeans_UseAllIVsInDT) {
        //dont cluster, use all IVs
        clusters.emplace_back(
            *std::min_element(elements.begin(), elements.end()),
            *std::max_element(elements.begin(), elements.end()));
      } else {
        clusters = kmeansElbow<SignedType>(elements, maxClusters,
                                           minWCSS, 1);
      }
      //make range propositions
      constants =
          makeConstants<SignedType>(clusters, type, cn->getMaxTime());
      tmpProps = makeRange<GetNumericExpType<SignedType>>(
          constants, type, cn->get<GetNumericExpType<SignedType>>(),
          cn->_clsConfig._clsOps);

    } else if (isContiguous(ct)) {
      messageErrorIf(
          type.first == ExpType::Float,
          "Float type is not supported in sequenced clustering");
      if (inDTAlgo && ct == ClsType::Contiguous_UseAllIVsInDT) {
        //dont cluster, use all IVs
        clusters.emplace_back(
            *std::min_element(elements.begin(), elements.end()),
            *std::max_element(elements.begin(), elements.end()));
      } else {
        clusters = contiguousClustering<SignedType>(
            elements, maxClusters,
            clsOps.size() == 1 && clsOps.count(ClsOp::E));
      }

      //make inside propositions
      constants =
          makeConstants<SignedType>(clusters, type, cn->getMaxTime());
      tmpProps = makeInside<GetNumericExpType<SignedType>>(
          constants, type, cn->get<GetNumericExpType<SignedType>>(),
          cn->_clsConfig._clsOps);
    } else {
      messageError("Unsupported clustering type");
    }
    //debug
    //for (auto p : tmpProps) {
    //  std::cout << prop2String(p) << "\n";
    //}
    //std::cout << "------------------------"
    //          << "\n";

    //add propositions to result
    for (const PropositionPtr &p : tmpProps) {
      ret.push_back(p);
    }
  }
  return ret;
}

#define runClustering(type)                                          \
  template std::vector<PropositionPtr> runClustering<type>(          \
      const std::vector<size_t> &ivs,                                \
      const NumericExpressionPtr &cn, bool inDTAlgo);

// clang-format off
runClustering(UInt)
runClustering(SInt)
runClustering(ULogic)
runClustering(SLogic)
runClustering(Float)
// clang-format on
#define gatherElements(type)                                         \
  template std::vector<type> gatherElements<type>(                   \
      const std::vector<size_t> &ivs,                                \
      const NumericExpressionPtr &cn);

    // clang-format off
gatherElements(SInt)
gatherElements(SLogic)
gatherElements(Float)
// clang-format on

} // namespace harm
