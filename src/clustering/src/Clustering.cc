
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
#include "expUtils/ExpType.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/expression/GenericExpression.hh"
#include "message.hh"

namespace harm {
using namespace expression;

template <typename ET>
using GetGreaterEqType =
    std::conditional_t<std::is_same_v<ET, FloatExpression>,
                       FloatGreaterEq, IntGreaterEq>;
template <typename ET>
using GetLessEqType =
    std::conditional_t<std::is_same_v<ET, FloatExpression>,
                       FloatLessEq, IntLessEq>;
template <typename ET>
using GetEqType =
    std::conditional_t<std::is_same_v<ET, FloatExpression>, FloatEq,
                       IntEq>;

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

    } else {
      if (!cn->_clsConfig._excluded.count(std::to_string(iv))) {
        Signed val = (Signed)cn->evaluate<Signed>(iv);
        elements.push_back(val);
      }
    }
  }
  //debug
  //  std::cout << num2String(*cn) << "\n";
  //  for (size_t i = 0; i < std::min(elements.size(), (size_t)50); i++) {
  //    std::cout << elements[i] << " ";
  //  }
  //  std::cout << "\n";

  return elements;
}

template <typename T>
std::vector<PropositionPtr>
runClustering(const std::vector<size_t> &ivs,
              const NumericExpressionPtr &cn, bool inDTAlgo) {
  std::vector<PropositionPtr> ret;

  //cluster only signed types
  using SignedType =
      std::conditional_t<std::is_same_v<T, UInt>, SInt, T>;

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
runClustering(Float)
// clang-format on
#define gatherElements(type)                                         \
  template std::vector<type> gatherElements<type>(                   \
      const std::vector<size_t> &ivs,                                \
      const NumericExpressionPtr &cn);

    // clang-format off
gatherElements(SInt)
gatherElements(Float)
// clang-format on

} // namespace harm
