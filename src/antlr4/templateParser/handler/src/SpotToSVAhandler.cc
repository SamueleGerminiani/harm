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
  messageErrorIf(ctx->SEREIMPL() == nullptr && ctx->SEREIMPLO() == nullptr,
                 " The antecedent of a SVA assertion must be a SERE!");

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LCURLY() != nullptr && ctx->RCURLY() != nullptr &&
      ctx->SEREIMPL() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = _subFormulas.top();

    _subFormulas.pop();

    _subFormulas.push(
        Hstring("(", Hstring::Stype::Temp) + formulaAnt +
        Hstring(")", Hstring::Stype::Temp) +
        Hstring(" " + ctx->SEREIMPL()->getText() + " ", Hstring::Stype::Imp) +
        formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LCURLY() != nullptr && ctx->RCURLY() != nullptr &&
      ctx->SEREIMPLO() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = _subFormulas.top();
    _subFormulas.pop();
    _subFormulas.push(
        Hstring("(", Hstring::Stype::Temp) + formulaAnt +
        Hstring(")", Hstring::Stype::Temp) +
        Hstring(" " + ctx->SEREIMPLO()->getText() + " ", Hstring::Stype::Imp) +
        formulaCon);
  }
}

std::string SpotToSVAhandler::handleNewPP(const std::string &ph) {
  if (!_phToProp.count(ph)) {
    _phToProp[ph] = new Proposition *(nullptr);
  }

  return ph;
}

std::string SpotToSVAhandler::handleNewInst(const std::string &prop) {
  if (_propStrToInst.count(prop)) {
    return _propStrToInst.at(prop);
  }

  Proposition *p = parsePropositionAlreadyTyped(prop, _trace);
  std::string inst = "_inst_" + std::to_string(instCount++);
  _propStrToInst[prop] = inst;
  _instToProp[inst] = _useCache ? new Proposition *(new CachedProposition(p))
                                : new Proposition *(p);

  return inst;
}

void SpotToSVAhandler::exitTformula(spotParser::TformulaContext *ctx) {

  if (ctx->boolean() != nullptr) {
    std::string inst = handleNewInst(ctx->boolean()->getText());
    _subFormulas.push(
        Hstring(inst, Hstring::Stype::Inst, _instToProp.at(inst)));
    return;
  }

  if (ctx->PLACEHOLDER() != nullptr) {
    std::string ph = handleNewPP(ctx->PLACEHOLDER()->getText());
    _subFormulas.push(Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
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
    if (ctx->LSQUARED() != nullptr && ctx->RSQUARED() != nullptr) {
      newFormula = Hstring("nexttime[", Hstring::Stype::Temp) +
                   Hstring(ctx->UINTEGER()->getText(), Hstring::Stype::Temp) +
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

  if (ctx->tformula().size() == 1 && ctx->LROUND() != nullptr &&
      ctx->RROUND() != nullptr) {
    Hstring newFormula = Hstring("(", Hstring::Stype::Temp) +
                         _subFormulas.top() +
                         Hstring(")", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }

  if (ctx->sere() != nullptr && ctx->LCURLY() != nullptr &&
      ctx->RCURLY() != nullptr) {
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
    std::string inst = handleNewInst(ctx->boolean()->getText());
    _subFormulas.push(
        Hstring(inst, Hstring::Stype::Inst, _instToProp.at(inst)));
    return;
  }

  if (ctx->PLACEHOLDER() != nullptr) {
    std::string ph = handleNewPP(ctx->PLACEHOLDER()->getText());
    if (ctx->NOT() == nullptr) {
      _subFormulas.push(Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
    } else {
      _subFormulas.push(Hstring("!", Hstring::Stype::Temp) +
                        Hstring(ph, Hstring::Stype::Ph, _phToProp.at(ph)));
    }
    return;
  }

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

  if (ctx->sere().size() == 1 && ctx->LSQUARED() != nullptr &&
      ctx->PLUS() != nullptr && ctx->RSQUARED() != nullptr) {
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

    if (ctx->LSQUARED() != nullptr && ctx->RSQUARED() != nullptr &&
        ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 2) {
      newFormula =
          left + Hstring(" ##[", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(":", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("] ", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    } else if (ctx->LSQUARED() != nullptr && ctx->RSQUARED() != nullptr &&
               ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 1) {
      newFormula =
          left + Hstring(" ##[", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(":", Hstring::Stype::Temp) +
          Hstring("$]", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    } else if (ctx->LSQUARED() != nullptr && ctx->RSQUARED() != nullptr &&
               ctx->UINTEGER().size() == 1) {
      newFormula =
          left + Hstring(" ##[", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("] ", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    } else {
      newFormula =
          left + Hstring(" ##", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(" ", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    }
    return;
  }

  if (ctx->sere().size() == 1 && ctx->LSQUARED() != nullptr &&
      ctx->ASS() != nullptr && !ctx->UINTEGER().empty() &&
      ctx->RSQUARED() != nullptr) {
    if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(":", Hstring::Stype::Temp) +
          Hstring("$]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 2) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(":", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    }
    return;
  }

  if (ctx->sere().size() == 1 && ctx->LSQUARED() != nullptr &&
      ctx->IMPL() != nullptr && !ctx->UINTEGER().empty() &&
      ctx->RSQUARED() != nullptr) {
    if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(":", Hstring::Stype::Temp) +
          Hstring("$]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 2) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(":", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    }
    return;
  }

  if (ctx->LSQUARED() != nullptr && ctx->TIMES() != nullptr &&
      ctx->RSQUARED() != nullptr) {
    if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 2) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(":", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring(":", Hstring::Stype::Temp) +
          Hstring("$]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->UINTEGER().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
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

  if (ctx->sere().size() == 1 && ctx->LROUND() != nullptr &&
      ctx->RROUND() != nullptr) {
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
