#include "PermGenerator.hh"
#include "colors.hh"
#include "message.hh"

#include <deque>
#include <spot/tl/print.hh>
#include <sstream>
#include <utility>

namespace harm {
Row operator*(const Row &r1, const Row &r2) {
  Row ret = r1;
  for (auto e : r2) {
    ret.push_back(e);
  }
  return ret;
}
Matrix operator*(const Matrix &m1, const Matrix &m2) {
  Matrix ret;
  for (auto &e1 : m1) {
    for (auto &e2 : m2) {
      ret.push_back(e1 * e2);
    }
  }
  return ret;
}
int binomialCoefficients(int n, int k) {

  if (k == 0 || k == n)
    return 1;
  return binomialCoefficients(n - 1, k - 1) + binomialCoefficients(n - 1, k);
}
bool operator==(const Row &r1, const Row &r2) {
  if (r1.size() != r2.size()) {
    return 0;
  }
  for (size_t i = 0; i < r1.size(); i++) {
    if (r1[i] != r2[i]) {
      return 0;
    }
  }
  return 1;
}
Matrix binCombinations(int N, int K) {
  Matrix ret;
  std::string bitmask(K, 1); // K leading 1's
  bitmask.resize(N, 0);      // N-K trailing 0's

  do {
    Row tmp;

    for (int i = 0; i < N; ++i) // [0..N-1] integers
    {
      if (bitmask[i])
        tmp.push_back(i);
    }
    ret.push_back(tmp);
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
  return ret;
}
Matrix genBinomial(Matrix in, size_t k) {
  Matrix ret;
  Matrix ens = binCombinations(in.size(), k);
  for (auto &en : ens) {
    Row finalRow;
    for (auto e : en) {
      for (auto f : in[e]) {
        finalRow.push_back(f);
      }
    }
    ret.push_back(finalRow);
  }
  return ret;
}
Matrix genCommutatives(Matrix in, size_t k) {
  Matrix ret;
  for (auto &r1 : in) {
    for (auto &r2 : in) {
      if (!(r1 == r2)) {
        ret.push_back(r1 * r2);
      }
    }
  }
  return ret;
}
PermGenerator::~PermGenerator() {
  if (_perms != nullptr) {
    for (size_t i = 0; i < _size.first; i++) {
      delete[] _perms[i];
    }
    delete[] _perms;
  }
}
PermGenerator::PermUnit *PermGenerator::generatePermUnit(spot::formula &templ) {
  std::unordered_set<std::string> foundPH;
  return generatePermUnit(templ, foundPH);
}
PermGenerator::PermUnit *
PermGenerator::generatePermUnit(spot::formula &templ,
                                std::unordered_set<std::string> &foundPH) {
  //   print_spin_ltl(std::cout, templ, false) << '\n';

  PermUnit *ret = new PermUnit();
  //  std::cout << __func__ << "\n";
  ret->_op = PermOperator::Mul;

  if (templ.is(spot::op::And) || templ.is(spot::op::Or)) {
    // retrieve equivalent operands
    std::map<size_t, std::vector<size_t>> equals;
    std::unordered_set<size_t> used;
    for (size_t i = 0; i < templ.size() && used.size() != templ.size(); i++) {
      if (!used.count(i)) {
        equals[i].push_back(i);
        used.insert(i);
        for (size_t j = 0; j < templ.size(); j++) {
          if (i == j) {
            continue;
          }
          if (!used.count(j)) {
            if (compare(templ[i], templ[j])) {
              equals.at(i).push_back(j);
              used.insert(j);
            }
          }
        }
      }
    }
    ret->_dim.first = 1;
    ret->_dim.second = 0;
    for (auto &i : equals) {
      if (i.second.size() > 1) {
        // cluster of equivalent operands
        auto ch = templ[i.first];
        auto *tmp = generatePermUnit(ch, foundPH);
        PermUnit *bin = new PermUnit();
        bin->_op = PermOperator::Bin;
        bin->_children.push_back(tmp);
        assert(tmp->_dim.first >= i.second.size());
        bin->_dim.first =
            binomialCoefficients(tmp->_dim.first, i.second.size());
        bin->_dim.second = tmp->_dim.second * i.second.size();
        ret->_children.push_back(bin);
      } else {
        // of size 1
        auto ch = templ[i.first];
        auto *tmp = generatePermUnit(ch, foundPH);
        for (auto &e : tmp->_children) {
          ret->_children.push_back(e);
        }
      }
    }
    // adjust the current dimension according to the operands
    for (auto &i : ret->_children) {
      ret->_dim.first *= i->_dim.first;
      ret->_dim.second += i->_dim.second;
    }

  } else if (templ.is(spot::op::ap) && templ.ap_name()[0] == 'P') {

    harm::Location loc = _phToLoc.at(templ.ap_name());
    PermUnit *ph = new PermUnit();
    ph->_op = PermOperator::Ph;
    if (foundPH.count(templ.ap_name())) {
      // this is a repeated placeholder
      ph->_dim.first = 1;
      ph->_dim.second = 1;
    } else {
      foundPH.insert(templ.ap_name());
      // set the correct domain
      if (loc == harm::Location::Ant) {
        ph->_dim.first = _aProps;
        ph->_dim.second = 1;
      } else if (loc == harm::Location::Con) {
        ph->_dim.first = _cProps;
        ph->_dim.second = 1;
      } else if (loc == harm::Location::AntCon) {
        ph->_dim.first = _acProps;
        ph->_dim.second = 1;
      }
    }
    ret->_children.push_back(ph);
    ret->_dim.first = ph->_dim.first;
    ret->_dim.second = ph->_dim.second;
  } else if ((templ.is(spot::op::U) || templ.is(spot::op::R)) &&
             (compare(templ[0], templ[1]))) {
    ret->_dim.first = 1;
    ret->_dim.second = 0;
    ret->_op = PermOperator::Mul;
    auto f = templ[0];
    auto *tmp = generatePermUnit(f, foundPH);
    PermUnit *com = new PermUnit();
    com->_op = PermOperator::Com;
    com->_children.push_back(tmp);
    com->_dim.first = (tmp->_dim.first * (tmp->_dim.first - 1));
    com->_dim.second = tmp->_dim.second * 2;

    ret->_children.push_back(com);
    for (auto &i : ret->_children) {
      ret->_dim.first *= i->_dim.first;
      ret->_dim.second += i->_dim.second;
    }

  } else if (!templ.is(spot::op::ap)) {
    ret->_op = PermOperator::Mul;
    ret->_dim.first = 1;
    for (size_t i = 0; i < templ.size(); i++) {
      auto ch = templ[i];
      auto *tmp = generatePermUnit(ch, foundPH);
      for (auto &e : tmp->_children) {
        ret->_children.push_back(e);
      }
      delete tmp;
    }
    for (auto &i : ret->_children) {
      ret->_dim.first *= i->_dim.first;
      ret->_dim.second += i->_dim.second;
    }
  }

  //    std::cout << ret->_dim.first << "x" << ret->_dim.second << "\n";
  return ret;
}
void PermGenerator::deletePermUnit(PermGenerator::PermUnit *pu) {

  for (auto &i : pu->_children) {
    deletePermUnit(i);
  }
  //  std::cout << __func__ << "\n";
  delete pu;
}
void PermGenerator::printPermUnit(PermGenerator::PermUnit *pu) {
  static std::string level = "";
  if (pu->_op == PermOperator::Ph) {
    std::cout << level << ">Ph"
              << "\n";
  } else if (pu->_op == PermOperator::Com) {
    std::cout << level << ">Com"
              << "\n";
  } else if (pu->_op == PermOperator::Bin) {
    std::cout << level << ">Bin"
              << "\n";
  } else if (pu->_op == PermOperator::Mul) {
    std::cout << level << ">Mul"
              << "\n";
  } else {
    messageError("");
  }
  level += "  ";

  for (auto i : pu->_children) {
    if (i->_op == PermOperator::Ph) {
      std::cout << level << "ph"
                << "\n";

    } else if (i->_op == PermOperator::Com) {
      std::cout << level << "c"
                << "\n";
      level += "  ";
      for (auto c : i->_children) {
        printPermUnit(c);
      }
      level.pop_back();
      level.pop_back();
    } else if (i->_op == PermOperator::Bin) {
      std::cout << level << "b"
                << "\n";
      level += "  ";
      for (auto c : i->_children) {
        printPermUnit(c);
      }
      level.pop_back();
      level.pop_back();
    } else if (i->_op == PermOperator::Mul) {
      std::cout << level << "m"
                << "\n";
      level += "  ";
      for (auto c : i->_children) {
        printPermUnit(c);
      }
      level.pop_back();
      level.pop_back();
    } else {
      messageError("unexpected case");
    }
  }
  level.pop_back();
  level.pop_back();
}
bool PermGenerator::compare(spot::formula f1, spot::formula f2) {

  if (f1.kind() != f2.kind()) {
    return false;
  }
  if (f1.size() != f2.size()) {
    return false;
  }
  if ((f1.is(spot::op::ap) && f1.ap_name()[0] != 'P') ||
      (f2.is(spot::op::ap) && f2.ap_name()[0] != 'P')) {

    return f1.ap_name() == f2.ap_name();
  }
  if ((f1.is(spot::op::ap) && (_mPhs.at(f1.ap_name()) > 1))) {
    return f1.ap_name() == f2.ap_name();
  }
  if ((f2.is(spot::op::ap) && (_mPhs.at(f2.ap_name()) > 1))) {
    return f1.ap_name() == f2.ap_name();
  }

  for (size_t i = 0; i < f1.size(); i++) {
    if (!compare(f1[i], f2[i])) {
      return false;
    }
  }
  return true;
}
void PermGenerator::genPermutations(size_t antP, size_t conP, size_t antConP,
                                    Hstring &templateFormula) {
  // set the domains
  _aProps = antP;
  _cProps = conP;
  _acProps = antConP;

  auto hcon = templateFormula.getCon();
  auto hant = templateFormula.getAnt();

  // retrieve placeholders to location
  std::unordered_set<std::string> antPhs;
  for (size_t i = 0; i < hant.size(); i++) {
    auto &e = hant[i];
    if (e._t == Hstring::Stype::Ph) {
      _phToLoc.insert({{e._s, harm::Location::Ant}});
      antPhs.insert(e._s);
    }
  }

  for (size_t i = 0; i < hcon.size(); i++) {
    auto &e = hcon[i];
    if (e._t == Hstring::Stype::Ph) {
      if (antPhs.count(e._s)) {
        _phToLoc.at(e._s) = harm::Location::AntCon;
      } else {
        _phToLoc.insert({{e._s, harm::Location::Con}});
      }
    }
  }

  spot::formula con = spot::parse_infix_psl(hcon.toSpotString()).f;
  spot::formula ant = spot::parse_infix_psl(hant.toSpotString()).f;

  // rebuild the formula
  spot::formula wholeForm =
      spot::parse_infix_psl(hant.toSpotString() + "->" + hcon.toSpotString()).f;

  // assign an index to each placeholders
  size_t index = 0;

  wholeForm.traverse([&index, this](spot::formula &templ) {
    if (templ.is(spot::op::ap) && templ.ap_name()[0] == 'P') {
      if (!_phToIndex.count(templ.ap_name())) {
        _phToIndex[templ.ap_name()] = index;
      } else {
        // repeated placeholders are stored elsewhere
        auto phName =
            templ.ap_name() + "_" + std::to_string(_mPhs.at(templ.ap_name()));
        _rphToIndex[phName] = index;
      }
      // count placeholders occurrences
      _mPhs[templ.ap_name()]++;
      index++;
    }
    return false;
  });

  //    debug
  // print_spin_ltl(std::cout, wholeForm, false) << '\n';
  messageErrorIf(wholeForm.is_constant(), "The template is a constant!");

  // find the dimensions and structure of the permutations
  PermUnit *pu = generatePermUnit(wholeForm);
  //    debug
  // printPermUnit(pu);

  // set the dimensions
  _size.first = pu->_dim.first;
  _size.second = pu->_dim.second;

  // allocate enough memory to store all permutations
  _perms = new int *[_size.first];
  for (size_t i = 0; i < _size.first; i++) {
    _perms[i] = new int[_size.second]{0};
  }

  // generate the permutations
  auto perms = visitPermUnit(pu);

  messageErrorIf(pu->_dim.first != perms.size() ||
                     pu->_dim.second != perms[0].size(),
                 "Perm dim does not match");

  // delete the dimensions and structure of the permutation
  deletePermUnit(pu);

  // copy the permutations in the class member field
  for (size_t i = 0; i < _size.first; i++) {
    std::copy(perms[i].begin(), perms[i].end(), _perms[i]);
  }

  // replace permutations of repeated placeholders
  for (auto &rph : _rphToIndex) {
    std::string ph = rph.first;
    size_t pos = ph.find('_');
    size_t srcIndex = _phToIndex.at(ph.substr(0, pos));
    for (size_t i = 0; i < _size.first; i++) {
      _perms[i][rph.second] = _perms[i][srcIndex];
    }
  }

  //  debug
  //  for (auto &e : _phToIndex) {
  //    std::cout << e.first << ":" << e.second << "\n";
  //  }
  //  for (auto &e : _rphToIndex) {
  //    std::cout << e.first << " r:" << e.second << "\n";
  //  }
  //  std::cout << _size.first << "\n";

  // replace perms of repeated placeholders

  // debug
  //      for (size_t i = 0; i < _size.first; i++) {
  //        for (size_t j = 0; j < _size.second; j++) {
  //          std::cout << _perms[i][j] << " ";
  //        }
  //        std::cout << "\n";
  //      }
}

void printMatrix(Matrix &m) {
  for (auto r : m) {
    for (auto c : r) {
      std::cout << c << " ";
    }
    std::cout << "\n";
  }
}
Matrix PermGenerator::visitPermUnit(PermGenerator::PermUnit *pu) {

  std::vector<Matrix> operands;

  if (pu->_op == PermOperator::Ph) {
    // create a Nx1 matrix
    Matrix op;
    for (size_t i = 0; i < pu->_dim.first; i++) {
      Row l;
      l.push_back(i);
      op.push_back(l);
    }
    operands.push_back(op);
  } else if (pu->_op == PermOperator::Com) {
    auto perms = visitPermUnit(pu->_children[0]);
    operands.push_back(
        genCommutatives(perms, pu->_dim.second / perms[0].size()));
  } else if (pu->_op == PermOperator::Bin) {
    auto perms = visitPermUnit(pu->_children[0]);
    operands.push_back(genBinomial(perms, pu->_dim.second / perms[0].size()));
  } else if (pu->_op == PermOperator::Mul) {
    for (auto c : pu->_children) {
      operands.push_back(visitPermUnit(c));
    }
  } else {
    messageError("");
  }

  Matrix ret = operands[0];
  // multiply
  for (size_t i = 1; i < operands.size(); i++) {
    ret = ret * operands[i];
  }

  return ret;
}
} // namespace harm
