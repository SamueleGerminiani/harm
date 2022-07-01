
#include "Hstring.hh"

Hstring::Hstring(std::string s, Stype t, expression::Proposition **pp)
    : _s(s), _t(t), _pp(pp), _offset(-1) {
  _append.push_back(*this);
}
Hstring::Hstring() : _s(""), _t(Stype::Temp), _pp(nullptr), _offset(-1) {
  _append.push_back(*this);
}
Hstring Hstring::operator+(const Hstring &right) {
  auto left = *this;
  for (const auto &i : right._append) {
    left._append.push_back(i);
  }
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
    case Stype::Inst:
      ret += prop2ColoredString(**e._pp);
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
    case Stype::Inst:
      ret += prop2String(**e._pp);
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
    case Stype::Imp:
      ret += e._s;
      break;
    default:;
    }
  }
  return ret;
}

Hstring Hstring::getAnt() {
  Hstring ret;
  size_t i = 1;
  while (_append[i]._t != Stype::Imp) {
    ret._append.push_back(_append[i++]);
  }
  return ret;
}
Hstring Hstring::getCon() {
  Hstring ret;
  size_t i = 1;
  while (_append[i++]._t != Stype::Imp)
    ;

  while (i < size() - 1) {
    ret._append.push_back(_append[i++]);
  }
  return ret;
}
Hstring Hstring::getImp() {
  size_t i = 0;
  while (_append[i++]._t != Stype::Imp)
    ;

  return _append[i - 1];
}
std::vector<Hstring>::iterator Hstring::begin() { return _append.begin(); }

std::vector<Hstring>::iterator Hstring::end() { return _append.end(); }

void Hstring::insert(std::vector<Hstring>::iterator where,
                     const Hstring &toInsert) {
  _append.insert(where, toInsert);
}
