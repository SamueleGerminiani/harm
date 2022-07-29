#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "DTUtils.hh"
#include "Hstring.hh"
#include <spot/tl/formula.hh>
#include <spot/twaalgos/postproc.hh>

namespace harm {
inline void comb(int N, int K, std::vector<std::vector<size_t>> &ret) {
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

inline spot::formula selectFirstEvent(spot::formula f) {
  //  print_spin_ltl(std::cout, f, false) << '\n';
  if (f.is(spot::op::And) || f.is(spot::op::AndRat) || f.is(spot::op::AndNLM) ||
      f.is(spot::op::Or) || f.is(spot::op::OrRat) || f.is(spot::op::ap)) {
    return f;
  } else {
    return selectFirstEvent(f[0]);
  }
}
inline bool onlyToken(const std::string &token, spot::formula f) {
  //  print_spin_ltl(std::cout, f, false) << '\n';
  if (f.is(spot::op::ap)) {
    return f.ap_name() == token;
  } else {
    for (size_t i = 0; i < f.size(); i++) {
      if (!onlyToken(token, f[i])) {
        return false;
      }
    }
    return true;
  }
}
inline bool nothingBefore(const std::string &token, spot::formula f) {
  //  print_spin_ltl(std::cout, f, false) << '\n';
  if (f.is(spot::op::And) || f.is(spot::op::AndRat) || f.is(spot::op::AndNLM) ||
      f.is(spot::op::Or) || f.is(spot::op::OrRat)) {
    for (size_t i = 0; i < f.size(); i++) {
      if (nothingBefore(token, f[i])) {
        return true;
      }
    }
    return false;

  } else if (f.is(spot::op::ap)) {
    return f.ap_name() == token;
  } else {
    return nothingBefore(token, f[0]);
  }
}
inline bool nothingAfter(const std::string &token, spot::formula f) {
  //  print_spin_ltl(std::cout, f, false) << '\n';
  if (f.is(spot::op::And) || f.is(spot::op::AndRat) || f.is(spot::op::AndNLM) ||
      f.is(spot::op::Or) || f.is(spot::op::OrRat)) {
    for (size_t i = 0; i < f.size(); i++) {
      if (nothingAfter(token, f[i])) {
        return true;
      }
    }
    return false;

  } else if (f.is(spot::op::ap)) {
    return f.ap_name() == token;
  } else {
    return nothingAfter(token, f[f.size() - 1]);
  }
}

} // namespace harm
