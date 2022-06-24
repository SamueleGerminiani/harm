#include "SpotParserHandler.hh"
#include "propositionParser.hh"
#include "propositionParsingUtils.hh"
#include <sstream>

using namespace expression;

#define CHECK_ABORT                                                            \
  if (_abort)                                                                  \
    return;

namespace hparser {

void SpotParserHandler::enterFile(__attribute__((unused))
                                  spotParser::FileContext *ctx) {
  _abort = false;

}
SpotParserHandler::SpotParserHandler(harm::Trace *trace)
    : _abort(false), _trace(trace) {
}

void SpotParserHandler::exitFile(spotParser::FileContext *ctx) {
  auto formula = _subFormulas.top();
  _subFormulas.pop();
  _templateFormula = Hstring("G(", Hstring::Stype::G) + formula +
                     Hstring(")", Hstring::Stype::G);
  _errorMessages.clear();
}
void SpotParserHandler::exitFormula(spotParser::FormulaContext *ctx) {
  if (ctx->tformula().size() == 2 && ctx->IMPL() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = _subFormulas.top();
    _subFormulas.pop();
    _subFormulas.push(formulaAnt + Hstring(" -> ", Hstring::Stype::Imp) +
                      formulaCon);
    return;
  }

  if (ctx->tformula().size() == 2 && ctx->IMPL2() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = _subFormulas.top();
    _subFormulas.pop();
    _subFormulas.push(formulaAnt + Hstring(" => ", Hstring::Stype::Imp) +
                      formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->IMPL() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("{", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();

    _subFormulas.push(Hstring("{", Hstring::Stype::Temp) + formulaAnt +
                      Hstring("}", Hstring::Stype::Temp) +
                      Hstring(" -> ", Hstring::Stype::Imp) + formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->IMPL2() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("{", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(Hstring("{", Hstring::Stype::Temp) + formulaAnt +
                      Hstring("}", Hstring::Stype::Temp) +
                      Hstring(" => ", Hstring::Stype::Imp) + formulaCon);
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->BIND1() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("{", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(Hstring("{", Hstring::Stype::Temp) + formulaAnt +
                      Hstring("}", Hstring::Stype::Temp) +
                      Hstring(" []-> ", Hstring::Stype::Imp) + formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->BIND2() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("{", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(Hstring("{", Hstring::Stype::Temp) + formulaAnt +
                      Hstring("}", Hstring::Stype::Temp) +
                      Hstring(" []=> ", Hstring::Stype::Imp) + formulaCon);
    return;
  }
  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->SEREIMPL1() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("{", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(Hstring("{", Hstring::Stype::Temp) + formulaAnt +
                      Hstring("}", Hstring::Stype::Temp) +
                      Hstring(" |-> ", Hstring::Stype::Imp) + formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LGPAREN() != nullptr && ctx->RGPAREN() != nullptr &&
      ctx->SEREIMPL2() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("{", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(Hstring("{", Hstring::Stype::Temp) + formulaAnt +
                      Hstring("}", Hstring::Stype::Temp) +
                      Hstring(" |=> ", Hstring::Stype::Imp) + formulaCon);
    return;
  }
}

void SpotParserHandler::exitTformula(spotParser::TformulaContext *ctx) {

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
  if (ctx->placeholder() != nullptr) {
    std::string ph = "P" + ctx->placeholder()->NUMERIC()->getText();
    if (!_phToProp.count(ph)) {
      _phToProp[ph] = new Proposition *(nullptr);
    }
    _subFormulas.push(Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
    return;
  }
  if (ctx->BDT_AND() != nullptr) {
    messageErrorIf(bdtCount > 0, "More than one bdt operator defined\n" +
                                     printErrorMessage());
    std::string ph = "bdtAnd" + std::to_string(bdtCount++);
    _subFormulas.push(Hstring(ph, Hstring::Stype::BDTAnd, nullptr));
    return;
  }

  if (ctx->tformula().size() == 2 && ctx->AND() != nullptr) {
    Hstring newFormula =
        Hstring(" && ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->tformula().size() == 2 && ctx->OR() != nullptr) {
    Hstring newFormula =
        Hstring(" || ", Hstring::Stype::Temp) + _subFormulas.top();
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
      newFormula = Hstring("X[", Hstring::Stype::Temp) +
                   Hstring(ctx->NUMERIC()->getText(), Hstring::Stype::Temp) +
                   Hstring("]", Hstring::Stype::Temp) + _subFormulas.top();
    } else {
      newFormula = Hstring("X", Hstring::Stype::Temp) + _subFormulas.top();
    }
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->tformula().size() == 2 && ctx->UNTIL() != nullptr) {
    Hstring newFormula = _subFormulas.top();
    _subFormulas.pop();
    newFormula =
        _subFormulas.top() + Hstring(" U ", Hstring::Stype::Temp) + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->tformula().size() == 2 && ctx->RELEASE() != nullptr) {
    Hstring newFormula = _subFormulas.top();
    _subFormulas.pop();
    newFormula =
        _subFormulas.top() + Hstring(" R ", Hstring::Stype::Temp) + newFormula;
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
      ctx->RGPAREN() != nullptr && ctx->NOT() != nullptr) {
    Hstring newFormula = Hstring("{", Hstring::Stype::Temp) +
                         _subFormulas.top() +
                         Hstring("}!", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->sere() != nullptr && ctx->LGPAREN() != nullptr &&
      ctx->RGPAREN() != nullptr) {
    Hstring newFormula = Hstring("{", Hstring::Stype::Temp) +
                         _subFormulas.top() +
                         Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->tformula().size() == 1 && ctx->NOT() != nullptr) {
    Hstring newFormula =
        Hstring("!", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
}
void SpotParserHandler::exitSere(spotParser::SereContext *ctx) {
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
  if (ctx->placeholder() != nullptr) {
    std::string ph = "P" + ctx->placeholder()->NUMERIC()->getText();
    if (!_phToProp.count(ph)) {
      _phToProp[ph] = new Proposition *(nullptr);
    }
    if (ctx->NOT() == nullptr) {
      _subFormulas.push(Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
    } else {
      _subFormulas.push(Hstring("!", Hstring::Stype::Temp) +
                        Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
    }
    return;
  }
  if (ctx->bdt_next() != nullptr) {
    messageErrorIf(bdtCount > 0, "More than one bdt operator defined\n" +
                                     printErrorMessage());
    std::string ph = "bdtNext" + std::to_string(bdtCount++);
    Hstring tmp = Hstring(ph, Hstring::Stype::BDTNext, nullptr);
    tmp._offset =
        std::stoull(ctx->bdt_next()->NUMERIC()->getText(), nullptr, 10);
    tmp[0]._offset = tmp._offset;
    _subFormulas.push(tmp);

    return;
  }
  if (ctx->bdt_NCReps() != nullptr) {
    messageErrorIf(bdtCount > 0, "More than one bdt operator defined\n" +
                                     printErrorMessage());
    std::string ph =
        "bdtNCReps0[->" + ctx->bdt_NCReps()->NUMERIC()->getText() + "]:bdtMock";
    Hstring tmp = Hstring(ph, Hstring::Stype::BDTNCReps, nullptr);
    tmp._offset =
        std::stoull(ctx->bdt_NCReps()->NUMERIC()->getText(), nullptr, 10);
    tmp[0]._offset = tmp._offset;
    if (ctx->bdt_NCReps()->SEP()->getText() == "@;") {
      tmp._sep = ";";
    } else if (ctx->bdt_NCReps()->SEP()->getText() == "@:") {
      tmp._sep = ":";
    } else {
      messageError("Unknown separator: " + ctx->bdt_NCReps()->SEP()->getText()+printErrorMessage());
    }
    _subFormulas.push(tmp);

    return;
  }
  if (ctx->bdt_next_and() != nullptr) {
    messageErrorIf(bdtCount > 0, "More than one bdt operator defined\n" +
                                     printErrorMessage());
    std::string ph = "bdtNextAnd" + std::to_string(bdtCount++);
    Hstring tmp = Hstring(ph, Hstring::Stype::BDTNextAnd, nullptr);
    tmp._offset =
        std::stoull(ctx->bdt_next_and()->NUMERIC()->getText(), nullptr, 10);
    tmp[0]._offset = tmp._offset;
    _subFormulas.push(tmp);

    return;
  }
  if (ctx->BDT_AND() != nullptr) {
    messageErrorIf(bdtCount > 0, "More than one bdt operator defined\n" +
                                     printErrorMessage());
    std::string ph = "bdtAnd" + std::to_string(bdtCount++);
    _subFormulas.push(Hstring(ph, Hstring::Stype::BDTAnd, nullptr));
    return;
  }

  if (ctx->sere().size() == 2 && ctx->AND() != nullptr) {
    Hstring newFormula =
        Hstring(" && ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->sere().size() == 2 && ctx->BAND() != nullptr) {
    Hstring newFormula =
        Hstring(" & ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->sere().size() == 2 && ctx->BOR() != nullptr) {
    Hstring newFormula =
        Hstring(" | ", Hstring::Stype::Temp) + _subFormulas.top();
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

  if (ctx->DELAY() != nullptr) {
    Hstring newFormula;
    Hstring right = _subFormulas.top();
    _subFormulas.pop();
    ;
    Hstring left;
    if (ctx->sere().size() == 2) {
      left = _subFormulas.top();
      _subFormulas.pop();
    }

    if (ctx->LCPAREN() != nullptr && ctx->RCPAREN() != nullptr &&
        ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 2) {
      newFormula = left + Hstring(" ##[", Hstring::Stype::Temp) +
                   Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
                   Hstring("..", Hstring::Stype::Temp) +
                   Hstring(ctx->NUMERIC()[1]->getText(), Hstring::Stype::Temp) +
                   Hstring("] ", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    } else if (ctx->LCPAREN() != nullptr && ctx->RCPAREN() != nullptr &&
               ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 1) {
      newFormula = left + Hstring(" ##[", Hstring::Stype::Temp) +
                   Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
                   Hstring("..", Hstring::Stype::Temp) +
                   Hstring("] ", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    } else if (ctx->LCPAREN() != nullptr && ctx->RCPAREN() != nullptr &&
               ctx->NUMERIC().size() == 1) {
      newFormula = left + Hstring(" ##[", Hstring::Stype::Temp) +
                   Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
                   Hstring("] ", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    } else {
      newFormula = left + Hstring(" ##", Hstring::Stype::Temp) +
                   Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
                   Hstring(" ", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    }
    return;
  }

  if (ctx->sere().size() == 1 && ctx->LCPAREN() != nullptr &&
      ctx->ASS() != nullptr && !ctx->NUMERIC().empty() &&
      ctx->RCPAREN() != nullptr) {
    if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 2) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    }
    return;
  }

  if (ctx->sere().size() == 1 && ctx->LCPAREN() != nullptr &&
      ctx->IMPL() != nullptr && !ctx->NUMERIC().empty() &&
      ctx->RCPAREN() != nullptr) {
    if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 2) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    }
    return;
  }

  if (ctx->LCPAREN() != nullptr && ctx->TIMES() != nullptr &&
      ctx->RCPAREN() != nullptr) {
    if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 2) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->NUMERIC().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->NUMERIC().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
          Hstring(ctx->NUMERIC()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else {
      Hstring newFormula = _subFormulas.top() +
                           Hstring("[*", Hstring::Stype::Temp) +
                           Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    }
    return;
  }

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
        Hstring(" : ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->sere().size() == 2 && ctx->SCOL() != nullptr) {
    Hstring newFormula =
        Hstring(" ; ", Hstring::Stype::Temp) + _subFormulas.top();
    _subFormulas.pop();
    newFormula = _subFormulas.top() + newFormula;
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
}
std::string SpotParserHandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void SpotParserHandler::visitErrorNode(__attribute__((unused))
                                       antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}
void SpotParserHandler::addErrorMessage(const std::string &msg) {
  _errorMessages.push_back(msg);
}
Hstring &SpotParserHandler::getTemplateFormula() { return _templateFormula; }

} // namespace hparser
