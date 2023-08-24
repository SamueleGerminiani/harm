#include "SpotParserHandler.hh"
#include "propositionParser.hh"
#include "propositionParsingUtils.hh"
#include <sstream>
#include <string>

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
    : _abort(false), _trace(trace) {}

std::string SpotParserHandler::handleNewPP(const std::string &ph) {
  if (!_phToProp.count(ph)) {
    _phToProp[ph] = new Proposition *(nullptr);
  }

  return ph;
}

std::string SpotParserHandler::handleNewInst(const std::string &prop) {
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

std::string SpotParserHandler::handleNewFunc(const std::string &funStr,
                                             const std::string &nonTemporalExp,
                                             bool containsPH) {

  if (_funStrToFunID.count(funStr)) {
    return _funStrToFunID.at(funStr);
  }

  std::string funID = nonTemporalExp + "fun_" + std::to_string(funCount++);
  _funStrToFunID[funStr] = funID;
  Proposition **pp = nullptr;

  if (containsPH) {
    std::string ph = handleNewPP(nonTemporalExp);
    pp = _phToProp.at(ph);
  } else {
    std::string inst = handleNewInst(nonTemporalExp);
    pp = _instToProp.at(inst);
  }
  _funIDtoFun[funStr] = new PropositionStable(pp, nonTemporalExp, VarType::Bool,
                                              1, _trace->getLength());

  return funID;
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

  if (ctx->tformula().size() == 2 && ctx->IMPLO() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = _subFormulas.top();
    _subFormulas.pop();
    _subFormulas.push(formulaAnt + Hstring(" => ", Hstring::Stype::Imp) +
                      formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LCURLY() != nullptr && ctx->RCURLY() != nullptr &&
      ctx->SEREIMPL() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("{", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(formulaAnt + Hstring(" "+ctx->SEREIMPL()->getText()+" ", Hstring::Stype::Imp) +
                      formulaCon);
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      ctx->LCURLY() != nullptr && ctx->RCURLY() != nullptr &&
      ctx->SEREIMPLO() != nullptr) {
    auto formulaCon = _subFormulas.top();
    _subFormulas.pop();
    auto formulaAnt = Hstring("{", Hstring::Stype::Temp) + _subFormulas.top() +
                      Hstring("}", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(formulaAnt + Hstring(" "+ctx->SEREIMPLO()->getText()+" ", Hstring::Stype::Imp) +
                      formulaCon);
    return;
  }
  messageError("Error in formula\n" + printErrorMessage());
}

void SpotParserHandler::exitTformula(spotParser::TformulaContext *ctx) {

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

  if (ctx->DT_AND() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" + printErrorMessage());
    std::string ph = "dtAnd" + std::to_string(dtCount++);
    _subFormulas.push(Hstring(ph, Hstring::Stype::DTAnd, nullptr));
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
    if (ctx->LSQUARED() != nullptr && ctx->RSQUARED() != nullptr) {
      newFormula = Hstring("X[", Hstring::Stype::Temp) +
                   Hstring(ctx->UINTEGER()->getText(), Hstring::Stype::Temp) +
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
      ctx->RCURLY() != nullptr && ctx->NOT() != nullptr) {
    Hstring newFormula = Hstring("{", Hstring::Stype::Temp) +
                         _subFormulas.top() +
                         Hstring("}!", Hstring::Stype::Temp);
    _subFormulas.pop();
    _subFormulas.push(newFormula);
    return;
  }
  if (ctx->sere() != nullptr && ctx->LCURLY() != nullptr &&
      ctx->RCURLY() != nullptr) {
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

static size_t retrieveNumberFromDTO(const std::string &input) {
  auto start = std::find_if(input.begin(), input.end(), ::isdigit);

  messageErrorIf(start == input.end(), "No number found in DTO: " + input);

  auto end = std::find_if_not(start, input.end(), ::isdigit);

  return std::stoull(std::string(start, end));
}
std::string retrieveColonOrSemicolonFromDTO(const std::string &input) {
  auto colonOrSemicolonPos = std::find_if(
      input.begin(), input.end(), [](char c) { return c == ':' || c == ';'; });

  messageErrorIf(colonOrSemicolonPos == input.end(),
                 "Colon ':' or semicolon ';' not found in DTO " + input);

  return std::string(1, *colonOrSemicolonPos);
}
void SpotParserHandler::exitSere(spotParser::SereContext *ctx) {
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

  if (ctx->FUNCTION() != nullptr) {

    messageErrorIf(ctx->nonTemporalExp() == nullptr,
                   "Function nonTemporalExp is not defined\n" +
                       printErrorMessage());

    std::string signature = ctx->FUNCTION()->getText() + "(" +
                            ctx->nonTemporalExp()->getText() + ")";
    std::string funStr = ctx->getText();
    if (ctx->nonTemporalExp()->PLACEHOLDER() != nullptr) {
      std::string funID =
          handleNewFunc(funStr, ctx->nonTemporalExp()->getText(), 1);
      Hstring s(_funStrToFunID.at(funStr), Hstring::Stype::Function);
      s[0]._f = _funIDtoFun.at(funID);
      _subFormulas.push(
          ctx->NOT() != nullptr ? Hstring("!", Hstring::Stype::Temp) + s : s);
    } else {
      messageErrorIf(ctx->nonTemporalExp()->boolean() == nullptr,
                     "Function boolean is not defined\n" + printErrorMessage());

      std::string funID =
          handleNewFunc(funStr, ctx->nonTemporalExp()->getText(), 0);
      Hstring s(_funStrToFunID.at(funStr), Hstring::Stype::Function);
      s[0]._f = _funIDtoFun.at(funID);
      _subFormulas.push(s);
    }

    return;
  }

  if (ctx->DT_NEXT() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" + printErrorMessage());
    std::string ph = "dtNext" + std::to_string(dtCount++);
    Hstring tmp = Hstring(ph, Hstring::Stype::DTNext, nullptr);
    tmp[0]._offset = retrieveNumberFromDTO(ctx->DT_NEXT()->getText());
    _subFormulas.push(tmp);

    return;
  }
  if (ctx->DT_NCREPS() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" + printErrorMessage());
    size_t number = retrieveNumberFromDTO(ctx->DT_NCREPS()->getText());
    std::string ph = "dtNCReps0[->" + std::to_string(number) + "]:dtMock";
    Hstring tmp = Hstring(ph, Hstring::Stype::DTNCReps, nullptr);
    tmp._offset = number;
    tmp[0]._offset = tmp._offset;
    tmp._sep = retrieveColonOrSemicolonFromDTO(ctx->DT_NCREPS()->getText());

    _subFormulas.push(tmp);

    return;
  }
  if (ctx->DT_NEXT_AND() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" + printErrorMessage());
    std::string ph = "dtNextAnd" + std::to_string(dtCount++);
    Hstring tmp = Hstring(ph, Hstring::Stype::DTNextAnd, nullptr);
    tmp._offset = retrieveNumberFromDTO(ctx->DT_NEXT_AND()->getText());
    tmp[0]._offset = tmp._offset;
    _subFormulas.push(tmp);

    return;
  }
  if (ctx->DT_AND() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" + printErrorMessage());
    std::string ph = "dtAnd" + std::to_string(dtCount++);
    _subFormulas.push(Hstring(ph, Hstring::Stype::DTAnd, nullptr));
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
          Hstring("..", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("] ", Hstring::Stype::Temp) + right;
      _subFormulas.push(newFormula);
    } else if (ctx->LSQUARED() != nullptr && ctx->RSQUARED() != nullptr &&
               ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 1) {
      newFormula =
          left + Hstring(" ##[", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
          Hstring("] ", Hstring::Stype::Temp) + right;
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
          Hstring("..", Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 2) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[=", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
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
          Hstring("..", Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 2) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[->", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
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
          Hstring("..", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[1]->getText(), Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
      _subFormulas.pop();
      _subFormulas.push(newFormula);
    } else if (ctx->DOTS() != nullptr && ctx->UINTEGER().size() == 1) {
      Hstring newFormula =
          _subFormulas.top() + Hstring("[*", Hstring::Stype::Temp) +
          Hstring(ctx->UINTEGER()[0]->getText(), Hstring::Stype::Temp) +
          Hstring("..", Hstring::Stype::Temp) +
          Hstring("]", Hstring::Stype::Temp);
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
  if (ctx->sere().size() == 1 && ctx->LCURLY() != nullptr &&
      ctx->RCURLY() != nullptr) {
    Hstring newFormula = Hstring("{", Hstring::Stype::Temp) +
                         _subFormulas.top() +
                         Hstring("}", Hstring::Stype::Temp);
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
