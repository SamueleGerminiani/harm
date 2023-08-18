
#include "Hstring.hh"

Hstring::Hstring(
    std::string s, Stype t, expression::Proposition **pp, int offset,
    expression::Function<expression::Proposition, expression::Proposition> *f,
    const std::string &sep) {
  Hstring hs;
  hs._s = s;
  hs._t = t;
  hs._pp = pp;
  hs._offset = offset;
  hs._f = f;
  hs._sep = sep;
  _append.push_back(hs);
}
Hstring Hstring::operator+(const Hstring &right) {
  Hstring left = *this;
  left._append.insert(left._append.end(), right._append.begin(),
                      right._append.end());

  return left;
}
size_t Hstring::size() { return _append.size(); }

Hstring &Hstring::operator[](size_t i) { return _append[i]; }
bool Hstring::exists(std::string toFind) {
  for (auto &i : _append) {

    if (i._s == toFind) {
      return true;
    }
  }
  return false;
}

std::string Hstring::toColoredString(bool sub) {
  messageErrorIf(_append.empty(), "Attempted to print an empty Hstring");

  std::string ret = "";
  for (auto &e : _append) {
    switch (e._t) {
    case Stype::G:
      ret += GLOB(e._s);
      break;
    case Stype::Temp:
      ret += TEMP(e._s);
      break;
    case Stype::Ph:
      ret += VAR((sub ? prop2ColoredString(**e._pp) : e._s));
      break;
    case Stype::Inst:
      ret += prop2ColoredString(**e._pp);
      break;
    case Stype::Function:
      ret += e._f->toColoredString(sub);
      break;
    case Stype::DTAnd:
      if (!sub || dynamic_cast<expression::PropositionAnd *>(*e._pp)->empty()) {
        ret += BOOL("..&&..");
      } else {
        ret += prop2ColoredString(**e._pp);
      }
      break;
    case Stype::DTNext:
      if (sub) {
        if (e._offset > 0) {
          ret += TEMP(" ##" + std::to_string(e._offset) + " ");
          ret += prop2ColoredString(**e._pp);
        } else {
          ret += prop2ColoredString(**e._pp);
        }
      } else {
        ret += TEMP("..##..");
      }
      break;
    case Stype::DTNCReps:
      if (sub) {
        ret += prop2ColoredString(**e._pp);
        if (e._offset > 0) {
          ret += TEMP(" [->" + std::to_string(e._offset) + "]; ");
        } else {
          ret +=
              TEMP(" [->" + std::to_string(e._offset * (-1)) + "]:") + VAR("1");
        }
      } else {
        ret += TEMP("..[->]" + e._sep + "..");
      }
      break;
    case Stype::DTNextAnd:
      if (sub) {
        if (e._offset > 0) {
          ret += TEMP(" ##" + std::to_string(e._offset) + " ");
          ret += prop2ColoredString(**e._pp);
        } else {
          ret += prop2ColoredString(**e._pp);
        }
      } else {
        ret += TEMP("..#&..");
      }
      break;
    case Stype::Imp:
      ret += TIMPL(e._s);
      break;
    default:;
    }
  }
  return ret;
}
std::string Hstring::toString(bool sub) {
  messageErrorIf(_append.empty(), "Attempted to print an empty Hstring");

  std::string ret = "";
  for (auto &e : _append) {
    switch (e._t) {
    case Stype::G:
      ret += e._s;
      break;
    case Stype::Temp:
      ret += e._s;
      break;
    case Stype::Ph:
      ret += (sub ? prop2String(**e._pp) : e._s);
      break;
    case Stype::Inst:
      ret += prop2String(**e._pp);
      break;
    case Stype::Function:
      ret += e._f->toString(sub);
      break;
    case Stype::DTAnd:
      if (!sub || dynamic_cast<expression::PropositionAnd *>(*e._pp)->empty()) {
        ret += "..&&..";
      } else {
        ret += prop2String(**e._pp);
      }
      break;
    case Stype::DTNext:
      if (sub) {
        if (e._offset > 0) {
          ret += (" ##" + std::to_string(e._offset) + " ");
          ret += prop2String(**e._pp);
        } else {
          ret += prop2String(**e._pp);
        }
      } else {
        ret += ("..##..");
      }
      break;
    case Stype::DTNCReps:
      if (sub) {
        ret += prop2String(**e._pp);
        if (e._offset > 0) {
          ret += " [->" + std::to_string(e._offset) + "]; ";
        } else {
          ret += (" [->" + std::to_string(e._offset * (-1)) + "]:1");
        }
      } else {
        ret += ("..[->]" + e._sep + "..");
      }
      break;
    case Stype::DTNextAnd:
      if (sub) {
        if (e._offset > 0) {
          ret += (" ##" + std::to_string(e._offset) + " ");
          ret += prop2String(**e._pp);
        } else {
          ret += prop2String(**e._pp);
        }
      } else {
        ret += ("..#&..");
      }
      break;
    case Stype::Imp:
      ret += e._s;
      break;

    default:;
    }
  }
  return ret;
}

std::string Hstring::toSpotString() {

  std::string ret = "";
  for (auto &e : _append) {
    switch (e._t) {
    case Stype::G:
      ret += e._s;
      break;
    case Stype::Temp:
      ret += e._s;
      break;
    case Stype::Ph:
      ret += e._s;
      break;
    case Stype::Imp:
      ret += e._s;
      break;
    case Stype::DTAnd:
      ret += e._s;
      break;
    case Stype::DTNext:
      if (e._offset > 0) {
        ret += " ##" + std::to_string(e._offset) + " ";
      }
      ret += e._s;
      break;
    case Stype::DTNCReps:
      ret += e._s;
      if (e._offset > 0) {
        ret += " [->" + std::to_string(e._offset) + "]; ";
      }
      break;
    case Stype::DTNextAnd:
      if (e._offset > 0) {
        ret += " ##" + std::to_string(e._offset) + " ";
      }
      ret += e._s;
      break;
    case Stype::Inst:
      ret += e._s;
      break;
    case Stype::Function:
      ret += e._s;
      break;
    default:;
    }
  }
  return ret;
}

Hstring Hstring::getAnt() {
  auto imp_it = std::find_if(_append.begin(), _append.end(),
                             [](Hstring &e) { return e._t == Stype::Imp; });

  messageErrorIf(imp_it == _append.end(),
                 "No implication found in Hstring: " + this->toSpotString());

  Hstring ret;
  ret._append.insert(ret._append.end(), _append.begin() + 1, imp_it);

  return ret;
}
Hstring Hstring::getCon() {

  auto imp_it = std::find_if(_append.begin(), _append.end(),
                             [](Hstring &e) { return e._t == Stype::Imp; });

  messageErrorIf(imp_it == _append.end(),
                 "No implication found in Hstring: " + this->toSpotString());

  Hstring ret;
  ret._append.insert(ret._append.end(), imp_it+1, _append.end()-1);

  return ret;
}
Hstring Hstring::getImp() {
  auto imp_it = std::find_if(_append.begin(), _append.end(),
                             [](Hstring &e) { return e._t == Stype::Imp; });

  messageErrorIf(imp_it == _append.end(),
                 "No implication found in Hstring: " + this->toSpotString());

  Hstring hs;
  hs._append.push_back(*imp_it);
  
  return hs;
}
std::vector<Hstring>::iterator Hstring::begin() { return _append.begin(); }

std::vector<Hstring>::iterator Hstring::end() { return _append.end(); }

std::vector<Hstring>::reverse_iterator Hstring::rbegin() {
  return _append.rbegin();
}

std::vector<Hstring>::reverse_iterator Hstring::rend() {
  return _append.rend();
}
bool Hstring::isDT(const Hstring &e) {
  switch (e._t) {
  case Stype::DTAnd:
    return 1;
    break;
  case Stype::DTNext:
    return 1;
    break;
  case Stype::DTNCReps:
    return 1;
    break;
  case Stype::DTNextAnd:
    return 1;
    break;
  default:
    return 0;
  }
}

std::vector<Hstring> Hstring::getDTOperands() {
  std::vector<Hstring> ret;
  for (auto &e : _append) {
    if (isDT(e)) {
      ret.push_back(e);
    }
  }
  return ret;
}

void Hstring::insert(std::vector<Hstring>::iterator where,
                     const Hstring &toInsert) {
  _append.insert(where, toInsert._append.begin(),
                      toInsert._append.end());
}
std::ostream &operator<<(std::ostream &os, const Hstring::Stype &t) {

  switch (t) {
  case Hstring::Stype::DTAnd:
    os << "DTAnd";
    break;
  case Hstring::Stype::DTNext:
    os << "DTNext";
    break;
  case Hstring::Stype::DTNCReps:
    os << "DTNCReps";
    break;
  case Hstring::Stype::DTNextAnd:
    os << "DTNextAnd";
    break;
  case Hstring::Stype::G:
    os << "G";
    break;
  case Hstring::Stype::Temp:
    os << "Temp";
    break;
  case Hstring::Stype::Imp:
    os << "Imp";
    break;
  case Hstring::Stype::Inst:
    os << "Inst";
    break;
  case Hstring::Stype::Ph:
    os << "Ph";
    break;
  case Hstring::Stype::Function:
    os << "Function";
    break;
  }
  return os;
}
