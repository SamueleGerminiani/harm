#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "DTUtils.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/temporal/BooleanLayer.hh"
#include "formula/temporal/Property.hh"
#include "formula/temporal/Sere.hh"
#include "formula/temporal/TemporalExpression.hh"

namespace harm {
/** \brief returns a vector of combinations, k permutations of n elements 
   */
inline void comb(int N, int K,
                 std::vector<std::vector<size_t>> &ret) {
  std::string bitmask(K, 1); // K leading 1's
  bitmask.resize(N, 0);      // N-K trailing 0's

  do {
    std::vector<size_t> tmp;
    for (int i = 0; i < N; ++i) // [0..N-1] integers
    {
      if (bitmask[i])
        tmp.push_back(i);
    }
    ret.push_back(tmp);
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}

/** \brief returns the first temporal element in the formula
   */
inline expression::TemporalExpressionPtr
selectFirstEvent(const expression::TemporalExpressionPtr &f) {
  if (isSereAnd(f) || isSereOr(f) || isSereIntersect(f) ||
      isPropertyAnd(f) || isPropertyOr(f)) {
    return f;
  } else {
    if (f->size() > 0) {
      return selectFirstEvent((*f)[0]);
    } else {
      return f;
    }
  }
}
/** \brief returns true if token is the only element in formula f
   */
inline bool onlyToken(const std::string &token,
                      const expression::TemporalExpressionPtr &f) {
  messageErrorIf(f == nullptr, "onlyToken, formula is nullptr");
  if (isBooleanLayer(f)) {
    return getBooleanLayerToken(f) == token;
  } else {
    for (size_t i = 0; i < f->size(); i++) {
      if (!onlyToken(token, (*f)[i])) {
        return false;
      }
    }
    return true;
  }
}
/** \brief returns true if token f does not have any previouse elements in the sequence
   */
inline bool
nothingBefore(const std::string &token,
              const expression::TemporalExpressionPtr &f) {
  if (isSereAnd(f) || isSereOr(f) || isSereIntersect(f) ||
      isPropertyAnd(f) || isPropertyOr(f)) {
    for (size_t i = 0; i < f->size(); i++) {
      if (nothingBefore(token, (*f)[i])) {
        return true;
      }
    }
    return false;

  } else if (isBooleanLayer(f)) {
    return getBooleanLayerToken(f) == token;
  } else {
    return nothingBefore(token, (*f)[0]);
  }
}
/** \brief returns true if token f does not have any subsequent elements in the sequence
   */
inline bool nothingAfter(const std::string &token,
                         const expression::TemporalExpressionPtr &f) {
  if (isSereAnd(f) || isSereOr(f) || isSereIntersect(f) ||
      isPropertyAnd(f) || isPropertyOr(f)) {
    for (size_t i = 0; i < f->size(); i++) {
      if (nothingAfter(token, (*f)[i])) {
        return true;
      }
    }
    return false;
  } else if (isBooleanLayer(f)) {
    return getBooleanLayerToken(f) == token;
  } else {
    return nothingAfter(token, (*f)[f->size() - 1]);
  }
}

inline expression::TemporalExpressionPtr
getDTPlaceholder(const expression::TemporalExpressionPtr &f,
                 int DT_id) {

  expression::TemporalExpressionPtr ret = nullptr;
  traverse(f, [&](const expression::TemporalExpressionPtr &f) {
    if (isDTPlaceholder(f, DT_id)) {
      ret = f;
      return true;
    }
    return false;
  });
  return ret;
}
inline bool containsDTO(const expression::TemporalExpressionPtr &f) {
  return getDTPlaceholder(f, 0) != nullptr;
}
inline expression::TemporalExpressionPtr
getDTPlaceholderParent(const expression::TemporalExpressionPtr &f,
                       int DT_id) {
  expression::TemporalExpressionPtr ret = nullptr;
  traverse(f, [&](const expression::TemporalExpressionPtr &f) {
    for (const auto &child : f->getItems()) {
      if (isDTPlaceholder(child, DT_id)) {
        ret = f;
        return true;
      }
    }
    return false;
  });
  return ret;
}
} // namespace harm
