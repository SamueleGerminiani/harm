#include "SpotToSVAhandler.hh"
#include "globals.hh"
#include "propositionParser.hh"
#include "propositionParsingUtils.hh"

#define CHECK_ABORT                                                            \
  if (_abort)                                                                  \
    return;

using namespace expression;
namespace hparser {

void SpotToSVAhandler::enterFile(__attribute__((unused))
                                 spotParser::FileContext *ctx) {
  _abort = false;
}
SpotToSVAhandler::SpotToSVAhandler(harm::Trace *trace)
    : _abort(false), _trace(trace) {}

void SpotToSVAhandler::exitFile(spotParser::FileContext *ctx) {
  auto formula = _subFormulas.top();
  _subFormulas.pop();
  _convertedFormula = Hstring("assert property(@(posedge " + clc::clk + ") ",
                              Hstring::Stype::G) +
                      formula + Hstring(");", Hstring::Stype::G);
  _errorMessages.clear();
}
void SpotToSVAhandler::exitFormula(spotParser::FormulaContext *ctx) {
  messageErrorIf(ctx->SEREIMPL1() == nullptr && ctx->SEREIMPL2() == nullptr &&
                     ctx->BIND1() == nullptr && ctx->BIND2() == nullptr,
                 " The antecedent of a SVA assertion must be a SERE!");

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->BIND1() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = _subFormulas.top();

    _subFormulas.pop();

    _subFormulas.push(Hstring("(", Hstring::Stype::Temp) + formulaAnt +
                      Hstring(")", Hstring::Stype::Temp) +
                      Hstring(" |-> ", Hstring::Stype::Imp) + formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->BIND2() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = _subFormulas.top();
    _subFormulas.pop();
    _subFormulas.push(Hstring("(", Hstring::Stype::Temp) + formulaAnt +
                      Hstring(")", Hstring::Stype::Temp) +
                      Hstring(" |=> ", Hstring::Stype::Imp) + formulaCon);
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->SEREIMPL1() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = _subFormulas.top();
    _subFormulas.pop();
    _subFormulas.push(Hstring("(", Hstring::Stype::Temp) + formulaAnt +
                      Hstring(")", Hstring::Stype::Temp) +
                      Hstring(" |-> ", Hstring::Stype::Imp) + formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->SEREIMPL2() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("(", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring(")", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(Hstring("(", Hstring::Stype::Temp) + formulaAnt +
                      Hstring(")", Hstring::Stype::Temp) +
                      Hstring(" |=> ", Hstring::Stype::Imp) + formulaCon);
    return;
  }
}

void SpotToSVAhandler::exitTformula(spotParser::TformulaContext *ctx) {

  if (ctx->boolean() != nullptr) {
    Proposition *p = parsePropositionAlreadyTyped(ctx->getText(), _trace);
    std::string pStr = prop2String(*p);
    if (!_propStrToInst.count(pStr)) {
      std::string ph = "_inst_" + std::to_string(instCount++);
      _propStrToInst[pStr] = ph;
    }
    if (_useCache) {
      _subFormulas.push(Hstring(_propStrToInst.at(pStr), Hstring::Stype::Inst,
                                new Proposition *(new CachedProposition(p))));
    } else {

      _subFormulas.push(Hstring(_propStrToInst.at(pStr), Hstring::Stype::Inst,
                                new Proposition *(p)));
    }
    return;
  }
  //  if (ctx->placeholder() != nullptr) {
  //    std::string ph = "P" + ctx->placeholder()->NUMERIC()->getText();
  //    if (!_phToProp.count(ph)) {
  //      _phToProp[ph] = new Proposition *(nullptr);
  //    }
  //    _subFormulas.push(Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
  //    return;
  //  }
  if (ctx->DT_AND() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" + printErrorMessage());
    std::string ph = "dtAnd" + std::to_string(dtCount++);
    _subFormulas.push(Hstring(ph, Hstring::Stype::DTAnd, nullptr));
    return;
  }

  if (ctx->DT_AND() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" + printErrorMessage());
    std::string ph = "dtAnd" + std::to_string(dtCount++);
    _subFormulas.push(Hstring(ph, Hstring::Stype::DTAnd, nullptr));
    return;
  }

  if (ctx->tformula().size() == 2 && ctx->AND() != nullptr) {
    Hstring newFormula =
        Hstring(" and ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->tformula().size() == 2 && ctx->OR() != nullptr) {
    Hstring newFormula =
        Hstring(" or ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->tformula().size() == 2 && ctx->XOR() != nullptr) {
    Hstring newFormula =
        Hstring(" xor ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->NEXT() != nullptr) {
    Hstring newFormula("", Hstring::Stype::Temp);
    if (ctx->LCPAREN() != nullptr && ctx->RCPAREN() != nullptr) {
      newFormula = Hstring("nexttime[", Hstring::Stype::Temp) +
                   Hstring(ctx->NUMERIC()->getText(), Hstring::Stype::Temp) +
                   Hstring("](", Hstring::Stype::Temp) + _subFormulas.top() +
                   Hstring(")", Hstring::Stype::Temp);
    } else {
      newFormula = Hstring("nexttime[1](", Hstring::Stype::Temp) +
                   _subFormulas.top() + Hstring(")", Hstring::Stype::Temp);
    }
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->tformula().size() == 2 && ctx->UNTIL() != nullptr) {
    Hstring newFormula = _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + Hstring(" until ", Hstring::Stype::Temp) +
                 newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->tformula().size() == 2 && ctx->RELEASE() != nullptr) {
    Hstring newFormula = _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() +
                 Hstring(" release ", Hstring::Stype::Temp) + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->LPAREN() != nullptr &&
      ctx->RPAREN() != nullptr) {
    Hstring newFormula = Hstring("(", Hstring::Stype::Temp) +
                         _subFormulas.top() +
                         Hstring(")", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->sere() != nullptr && ctx->LGPAREN() != nullptr &&
      ctx->RGPAREN() != nullptr) {
    Hstring newFormula = Hstring("(", Hstring::Stype::Temp) +
                         _subFormulas.top() +
                         Hstring(")", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->tformula().size() == 1 && ctx->NOT() != nullptr) {
    Hstring newFormula =
        Hstring("not", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
}
void SpotToSVAhandler::exitSere(spotParser::SereContext *ctx) {
  if (ctx->boolean() != nullptr) {
    Proposition *p = parsePropositionAlreadyTyped(ctx->getText(), _trace);
    std::string pStr = prop2String(*p);
    if (!_propStrToInst.count(pStr)) {
      std::string ph = "_inst_" + std::to_string(instCount++);
      _propStrToInst[pStr] = ph;
    }

    if (_useCache) {
      _subFormulas.push(Hstring(_propStrToInst.at(pStr), Hstring::Stype::Inst,
                                new Proposition *(new CachedProposition(p))));
    } else {

      _subFormulas.push(Hstring(_propStrToInst.at(pStr), Hstring::Stype::Inst,
                                new Proposition *(p)));
    }
    return;
  }
  //  if (ctx->placeholder() != nullptr) {
  //    std::string ph = "P" + ctx->placeholder()->NUMERIC()->getText();
  //    if (!_phToProp.count(ph)) {
  //      _phToProp[ph] = new Proposition *(nullptr);
  //    }
  //    if (ctx->NOT() == nullptr) {
  //      _subFormulas.push(Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
  //    } else {
  //      _subFormulas.push(Hstring("!", Hstring::Stype::Temp) +
  //                        Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
  //    }
  //    return;
  //  }
  //  if (ctx->dt_next() != nullptr) {
  //    messageErrorIf(dtCount > 0,
  //                   "More than one dt operator defined\n" + printErrorMessage());
  //    std::string ph = "dtNext" + std::to_string(dtCount++);
  //    Hstring tmp = Hstring(ph, Hstring::Stype::DTNext, nullptr);
  //    tmp._offset =
  //        std::stoull(ctx->dt_next()->NUMERIC()->getText(), nullptr, 10);
  //    tmp[0]._offset = tmp._offset;
  //    _subFormulas.push(tmp);
  //
  //    return;
  //  }
  //  if (ctx->dt_NCReps() != nullptr) {
  //    messageErrorIf(dtCount > 0,
  //                   "More than one dt operator defined\n" + printErrorMessage());
  //    std::string ph =
  //        "dtNCReps0[->" + ctx->dt_NCReps()->NUMERIC()->getText() + "]:dtMock";
  //    Hstring tmp = Hstring(ph, Hstring::Stype::DTNCReps, nullptr);
  //    tmp._offset =
  //        std::stoull(ctx->dt_NCReps()->NUMERIC()->getText(), nullptr, 10);
  //    tmp[0]._offset = tmp._offset;
  //    if (ctx->dt_NCReps()->SEP()->getText() == "@;") {
  //      tmp._sep = ";";
  //    } else if (ctx->dt_NCReps()->SEP()->getText() == "@:") {
  //      tmp._sep = ":";
  //    } else {
  //      messageError("Unknown separator: " + ctx->dt_NCReps()->SEP()->getText() +
  //                   printErrorMessage());
  //    }
  //    _subFormulas.push(tmp);
  //
  //    return;
  //  }
  //  if (ctx->dt_next_and() != nullptr) {
  //    messageErrorIf(dtCount > 0,
  //                   "More than one dt operator defined\n" + printErrorMessage());
  //    std::string ph = "dtNextAnd" + std::to_string(dtCount++);
  //    Hstring tmp = Hstring(ph, Hstring::Stype::DTNextAnd, nullptr);
  //    tmp._offset =
  //        std::stoull(ctx->dt_next_and()->NUMERIC()->getText(), nullptr, 10);
  //    tmp[0]._offset = tmp._offset;
  //    _subFormulas.push(tmp);
  //
  //    return;
  //  }
  //  if (ctx->DT_AND() != nullptr) {
  //    messageErrorIf(dtCount > 0,
  //                   "More than one dt operator defined\n" + printErrorMessage());
  //    std::string ph = "dtAnd" + std::to_string(dtCount++);
  //    _subFormulas.push(Hstring(ph, Hstring::Stype::DTAnd, nullptr));
  //    return;
  //  }

  if (ctx->sere().size() == 2 && ctx->AND() != nullptr) {
    Hstring newFormula =
        Hstring(" and ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->sere().size() == 2 && ctx->BAND() != nullptr) {
    Hstring newFormula =
        Hstring(" intersect ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->sere().size() == 2 && ctx->BOR() != nullptr) {
    Hstring newFormula =
        Hstring(" or ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->sere().size() == 1 && ctx->LCPAREN() != nullptr &&
      ctx->PLUS() != nullptr && ctx->RCPAREN() != nullptr) {
    Hstring newFormula =
        _subFormulas.top() + Hstring("[+]", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

//  if (ctx->DELAY() != nullptr) {
//    Hstring newFormula;
//    Hstring right = _subFormulas.top();
//    _subFormulas.pop();
//    ;
//    Hstring left;
//    if (ctx->sere().size() == 2) {
//      left = _subFormulas.top();
//      _subFormulas.pop();
//    }
//
//    if (ctx->LCPAREN() != nullptr && ctx->RCPAREN() != nullptr &&
//        ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 2) {
//      newFormula = left + Hstring(" ##[", Hstring::Stype::Temp) +
//                   Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//                   Hstring(":", Hstring::Stype::Temp) +
//                   Hstring(ctx->NUMERIC()[1]->getText(), Hstring::Stype::Temp) +
//                   Hstring("] ", Hstring::Stype::Temp) + right;
//      _subFormulas.push(newFormula);
//    } else if (ctx->LCPAREN() != nullptr && ctx->RCPAREN() != nullptr &&
//               ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 1) {
//      newFormula = left + Hstring(" ##[", Hstring::Stype::Temp) +
//                   Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//                   Hstring(":", Hstring::Stype::Temp) +
//                   Hstring("] ", Hstring::Stype::Temp) + right;
//      _subFormulas.push(newFormula);
//    } else if (ctx->LCPAREN() != nullptr && ctx->RCPAREN() != nullptr &&
//               ctx->NUMERIC().size() == 1) {
//      newFormula = left + Hstring(" ##[", Hstring::Stype::Temp) +
//                   Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//                   Hstring("] ", Hstring::Stype::Temp) + right;
//      _subFormulas.push(newFormula);
//    } else {
//      newFormula = left + Hstring(" ##", Hstring::Stype::Temp) +
//                   Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//                   Hstring(" ", Hstring::Stype::Temp) + right;
//      _subFormulas.push(newFormula);
//    }
//    return;
//  }
//
//  if (ctx->sere().size() == 1 && ctx->LCPAREN() != nullptr &&
//      ctx->ASS() != nullptr && !ctx->NUMERIC().empty() &&
//      ctx->RCPAREN() != nullptr) {
//    if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 1) {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring(":", Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    } else if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 2) {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring(":", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[1]->getText(), Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    } else {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    }
//    return;
//  }
//
//  if (ctx->sere().size() == 1 && ctx->LCPAREN() != nullptr &&
//      ctx->IMPL() != nullptr && !ctx->NUMERIC().empty() &&
//      ctx->RCPAREN() != nullptr) {
//    if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 1) {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring(":", Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    } else if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 2) {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring(":", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[1]->getText(), Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    } else {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    }
//    return;
//  }
//
//  if (ctx->LCPAREN() != nullptr && ctx->TIMES() != nullptr &&
//      ctx->RCPAREN() != nullptr) {
//    if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 2) {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring(":", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[1]->getText(), Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    } else if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 1) {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring(":", Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    } else if (ctx->NUMERIC().size() == 1) {
//      Hstring newFormula =
//          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
//          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
//          Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    } else {
//      Hstring newFormula = _subFormulas.top() +
//                           Hstring("[*", Hstring::Stype::Temp) +
//                           Hstring("]", Hstring::Stype::Temp);
//      _subFormulas.pop();
//      _subFormulas.push(newFormula);
//    }
//    return;
//  }

  if (ctx->sere().size() == 1 && ctx->LPAREN() != nullptr &&
      ctx->RPAREN() != nullptr) {
    Hstring newFormula = Hstring("(", Hstring::Stype::Temp) +
                         _subFormulas.top() +
                         Hstring(")", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->sere().size() == 2 && ctx->COL() != nullptr) {
    Hstring newFormula =
        Hstring(":", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->sere().size() == 2 && ctx->SCOL() != nullptr) {
    Hstring newFormula =
        Hstring(";", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
}
std::string SpotToSVAhandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void SpotToSVAhandler::visitErrorNode(__attribute__((unused))
                                      antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}
void SpotToSVAhandler::addErrorMessage(const std::string &msg) {
  _errorMessages.push_back(msg);
}
Hstring &SpotToSVAhandler::getConvertedFormula() { return _convertedFormula; }
} // namespace hparser
