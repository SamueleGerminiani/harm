#include <algorithm>
#include <ctype.h>
#include <ostream>
#include <sstream>
#include <string>

#include "DTLimits.hh"
#include "DTUtils.hh"
#include "Float.hh"
#include "TemporalParserHandler.hh"
#include "Trace.hh"
#include "expUtils/ExpType.hh"

#include "formula/atom/Constant.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/temporal/temporal.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "tree/ErrorNode.h"
#include "tree/TerminalNode.h"

using namespace expression;

namespace hparser {

TemporalParserHandler::TemporalParserHandler(
    const harm::TracePtr &trace)
    : _trace(trace) {}

std::string
TemporalParserHandler::handleNewPP(const std::string &ph) {
  if (!_phToPP.count(ph)) {
    _phToPP[ph] = generatePtrPtr<Proposition>((Proposition *)nullptr);
  }

  return ph;
}

std::string
TemporalParserHandler::handleNewInst(const std::string &prop) {

  if (_propStrToInst.count(prop))
    return _propStrToInst.at(prop);

  PropositionPtr p = parsePropositionAlreadyTyped(prop, _trace);

  if (_useCache)
    p->enableCache();

  std::string inst = "_inst" + std::to_string(instCount++);
  _propStrToInst[prop] = inst;
  _instToPP[inst] = p;

  return inst;
}

void TemporalParserHandler::exitFormula(
    temporalParser::FormulaContext *ctx) {
  auto tformula = _tsubFormulas.top();
  _tsubFormulas.pop();
  _temporalExpression = generatePtr<PropertyAlways>(tformula);
  _errorMessages.clear();
}
void TemporalParserHandler::exitImplication(
    temporalParser::ImplicationContext *ctx) {

  TemporalExpressionPtr right = _tsubFormulas.top();
  _tsubFormulas.pop();
  TemporalExpressionPtr left = _tsubFormulas.top();
  _tsubFormulas.pop();

  messageErrorIf(
      clc::outputLang == Language::SVA &&
          (!isSere(left) && !isBooleanLayer(left)),
      "SystemVerilog requires the antecedent of an "
      "implication to be a "
      "SERE, '" +
          temp2String(left, clc::outputLang,
                      PrintMode::ShowOnlyPermuationPlaceholders) +
          "' is not a SERE.\n"
          "Change the output language to PSL or SpotLTL to "
          "allow this.\n" +
          printErrorMessage());

  messageErrorIf(
      clc::outputLang == Language::SVA &&
          (ctx->IMPL() != nullptr || ctx->IMPLO() != nullptr),
      "SystemVerilog implications requires to use |-> or |=>\n"
      "Change the output language to PSL or SpotLTL to "
      "allow the use of -> or =>\n" +
          printErrorMessage());

  //property
  if (ctx->tformula().size() == 2 &&
      (ctx->IMPL() != nullptr || ctx->IMPLO() != nullptr)) {
    _tsubFormulas.push(generatePtr<PropertyImplication>(
        left, right, false,
        (ctx->IMPLO() != nullptr) ? true : false));

    return;
  }

  //sere
  if (ctx->tformula().size() == 1 && ctx->sere() != nullptr &&
      (ctx->SEREIMPL() != nullptr || ctx->SEREIMPLO() != nullptr)) {
    _tsubFormulas.push(generatePtr<PropertyImplication>(
        left, right, true,
        (ctx->SEREIMPLO() != nullptr) ? true : false));

    return;
  }
  messageError("Error in formula\n" + printErrorMessage());
}

void TemporalParserHandler::exitTformula(
    temporalParser::TformulaContext *ctx) {

  if (ctx->DT_AND() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" +
                       printErrorMessage());
    std::string ph = "_dtAnd" + std::to_string(dtCount++);
    _dto_param._type = harm::DTO_Type::And;
    _tsubFormulas.push(generatePtr<BooleanLayerDTPlaceholder>(
        harm::DTO_Type::And,
        generatePtr<PropositionPtr>(
            makeGenericExpression<PropositionAnd>(
                _trace->getLength())),
        ph, 0));
    _phToIdsDomain["DT"];
    return;
  }

  if (ctx->tformula().size() == 2 &&
      (ctx->TAND() != nullptr || ctx->AND() != nullptr)) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<PropertyAnd>({left, right}));
    return;
  }

  if (ctx->tformula().size() == 2 &&
      (ctx->TOR() != nullptr || ctx->BOR() != nullptr ||
       ctx->OR() != nullptr)) {

    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<PropertyOr>({left, right}));
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->NEXT() != nullptr) {
    TemporalExpressionPtr exp = _tsubFormulas.top();
    _tsubFormulas.pop();
    size_t delay = ctx->UINTEGER() != nullptr
                       ? safeStoull(ctx->UINTEGER()->getText())
                       : 1;
    _tsubFormulas.push(generatePtr<PropertyNext>(exp, delay));

    return;
  }

  if (ctx->tformula().size() == 2 && ctx->UNTIL() != nullptr) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<PropertyUntil>({left, right}));
    return;
  }

  if (ctx->tformula().size() == 2 && ctx->RELEASE() != nullptr) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<PropertyRelease>({left, right}));
    return;
  }

  if (ctx->tformula().size() == 1 &&
      (ctx->TNOT() != nullptr || ctx->NOT() != nullptr)) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<PropertyNot>(right));
    return;
  }

  if (ctx->tformula().size() == 1 && ctx->EVENTUALLY() != nullptr) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<PropertyEventually>(right));
    return;
  }
}

void TemporalParserHandler::enterBooleanLayer(
    temporalParser::BooleanLayerContext *ctx) {

  if (ctx->PLACEHOLDER() != nullptr) {
    std::string ph = handleNewPP(ctx->PLACEHOLDER()->getText());
    _phToIdsDomain[ph];
    TemporalExpressionPtr bl_ph =
        generatePtr<BooleanLayerPermutationPlaceholder>(
            _phToPP.at(ph), ph);
    if (ctx->NOT() != nullptr) {
      bl_ph = generatePtr<BooleanLayerNot>(bl_ph);
    }
    _tsubFormulas.push(bl_ph);
    return;
  }

  if (ctx->boolean() != nullptr) {
    std::string inst = handleNewInst(ctx->boolean()->getText());
    _tsubFormulas.push(
        generatePtr<BooleanLayerInst>(_instToPP.at(inst), inst));
    return;
  }
}

void TemporalParserHandler::exitSere(
    temporalParser::SereContext *ctx) {

  if (ctx->FIRST_MATCH() != nullptr) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<SereFirstMatch>(right));
    return;
  }

  if (ctx->dt_next() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" +
                       printErrorMessage());
    std::string ph = "_dtNext" + std::to_string(dtCount++);
    _dto_param._step =
        safeStoull(ctx->dt_next()->UINTEGER()->getText());
    _dto_param._type = harm::DTO_Type::Next;

    _tsubFormulas.push(generatePtr<BooleanLayerDTPlaceholder>(
        harm::DTO_Type::Next,
        generatePtr<PropositionPtr>(generatePtr<BooleanConstant>(
            true, ExpType::Bool, 1, _trace->getLength())),
        ph, 0));
    _phToIdsDomain["DT"];

    return;
  }

  if (ctx->dt_ncreps() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" +
                       printErrorMessage());
    std::string ph = "_dtNCReps0";
    _dto_param._step =
        safeStoull(ctx->dt_ncreps()->UINTEGER()->getText());
    if (ctx->dt_ncreps()->COL() != nullptr) {
      _dto_param._separator = ":";
    } else if (ctx->dt_ncreps()->SCOL() != nullptr) {
      _dto_param._separator = ";";
    } else {
      messageError("Unknown NCReps separator");
    }
    if (ctx->dt_ncreps()->ASS() != nullptr) {
      _dto_param._type = harm::DTO_Type::NCReps;
    } else if (ctx->dt_ncreps()->IMPLO() != nullptr) {
      _dto_param._type = harm::DTO_Type::GoTo;
    } else {
      messageError("Unknown NCReps type");
    }

    _tsubFormulas.push(generatePtr<BooleanLayerDTPlaceholder>(
        _dto_param._type,
        generatePtr<PropositionPtr>(generatePtr<BooleanConstant>(
            true, ExpType::Bool, 1, _trace->getLength())),
        ph, 0));
    _phToIdsDomain["DT"];
    return;
  }

  if (ctx->dt_next_and() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" +
                       printErrorMessage());
    std::string ph = "_dtNextAnd" + std::to_string(dtCount++);
    _dto_param._step =
        safeStoull(ctx->dt_next_and()->UINTEGER()->getText());
    _dto_param._type = harm::DTO_Type::NextAnd;
    _tsubFormulas.push(generatePtr<BooleanLayerDTPlaceholder>(
        harm::DTO_Type::NextAnd,
        generatePtr<PropositionPtr>(
            makeGenericExpression<PropositionAnd>(
                _trace->getLength())),
        ph, 0));
    _phToIdsDomain["DT"];
    return;
  }

  if (ctx->DT_AND() != nullptr) {
    messageErrorIf(dtCount > 0,
                   "More than one dt operator defined\n" +
                       printErrorMessage());
    std::string ph = "_dtAnd" + std::to_string(dtCount++);
    _dto_param._type = harm::DTO_Type::And;
    _tsubFormulas.push(generatePtr<BooleanLayerDTPlaceholder>(
        harm::DTO_Type::And,
        generatePtr<PropositionPtr>(
            makeGenericExpression<PropositionAnd>(
                _trace->getLength())),
        ph, 0));
    _phToIdsDomain["DT"];
    return;
  }

  if (ctx->sere().size() == 2 &&
      (ctx->INTERSECT() != nullptr || ctx->AND() != nullptr)) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<SereIntersect>({left, right}));
    return;
  }

  if (ctx->sere().size() == 2 &&
      (ctx->BAND() != nullptr || ctx->TAND() != nullptr)) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<SereAnd>({left, right}));
    return;
  }

  if (ctx->sere().size() == 2 &&
      (ctx->TOR() != nullptr || ctx->BOR() != nullptr ||
       ctx->OR() != nullptr)) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<SereOr>({left, right}));
    return;
  }

  if (ctx->sere().size() == 1 && ctx->LSQUARED() != nullptr &&
      ctx->PLUS() != nullptr && ctx->RSQUARED() != nullptr) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<SerePlus>(right));
    return;
  }

  messageErrorIf(ctx->UINTEGER().empty() && ctx->DOLLAR() != nullptr,
                 "Invalid use of unbounded operator $\n" +
                     printErrorMessage());

  if (ctx->DELAY() != nullptr) {
    messageErrorIf(ctx->LSQUARED() != nullptr &&
                       ctx->RSQUARED() == nullptr,
                   "Missing right parenthesis in delay operator\n" +
                       printErrorMessage());
    messageErrorIf(ctx->LSQUARED() == nullptr &&
                       ctx->RSQUARED() != nullptr,
                   "Missing left parenthesis in delay operator\n" +
                       printErrorMessage());

    if (ctx->LSQUARED() != nullptr && ctx->RSQUARED() != nullptr &&
        (ctx->DOTS() != nullptr || ctx->COL() != nullptr) &&
        (ctx->UINTEGER().size() +
             (ctx->DOLLAR() != nullptr ? 1 : 0) ==
         2)) {
      //left ##[l:r] right or left ##[l:$] right or ##[l:r] right or ##[l:$] right

      std::string lw = ctx->UINTEGER()[0]->getText();
      std::string rw = ctx->DOLLAR() != nullptr
                           ? "$"
                           : ctx->UINTEGER()[1]->getText();

      TemporalExpressionPtr right = _tsubFormulas.top();
      _tsubFormulas.pop();
      int l = safeStoull(lw);
      int r = ctx->DOLLAR() != nullptr ? -1 : safeStoull(rw);
      messageErrorIf(r != -1 && l > r,
                     "Invalid use of delay operator: left bound must "
                     "be less than or equal to right bound\n" +
                         printErrorMessage());
      if (ctx->sere().size() == 2) {
        TemporalExpressionPtr left = _tsubFormulas.top();
        _tsubFormulas.pop();
        _tsubFormulas.push(generatePtr<SereDelay>(
            left, right, std::make_pair(l, r)));
      } else {
        _tsubFormulas.push(
            generatePtr<SereDelay>(right, std::make_pair(l, r)));
      }

    } else {
      //left ##[r] right or left ##r right or ##[r] right or ##r right
      messageErrorIf(ctx->DOLLAR() != nullptr,
                     "Invalid use of unbounded operator $\n" +
                         printErrorMessage());

      if (ctx->sere().size() == 2) {
        TemporalExpressionPtr right = _tsubFormulas.top();
        _tsubFormulas.pop();
        TemporalExpressionPtr left = _tsubFormulas.top();
        _tsubFormulas.pop();
        _tsubFormulas.push(generatePtr<SereDelay>(
            left, right,
            std::make_pair(
                safeStoull(ctx->UINTEGER()[0]->getText()),
                safeStoull(ctx->UINTEGER()[0]->getText()))));
      } else {
        TemporalExpressionPtr right = _tsubFormulas.top();
        _tsubFormulas.pop();
        _tsubFormulas.push(generatePtr<SereDelay>(
            right, std::make_pair(
                       safeStoull(ctx->UINTEGER()[0]->getText()),
                       safeStoull(ctx->UINTEGER()[0]->getText()))));
      }
    }
    return;
  }

  if (ctx->sere().empty() && ctx->booleanLayer() != nullptr &&
      ctx->LSQUARED() != nullptr && ctx->ASS() != nullptr &&
      ctx->RSQUARED() != nullptr) {

    if ((ctx->DOTS() != nullptr || ctx->COL() != nullptr) &&
        (ctx->UINTEGER().size() +
             (ctx->DOLLAR() != nullptr ? 1 : 0) ==
         2)) {
      //[=l:r] or [=l:$]

      int lw = safeStoull(ctx->UINTEGER()[0]->getText());
      int rw = ctx->DOLLAR() == nullptr
                   ? safeStoull(ctx->UINTEGER()[1]->getText())
                   : -1;
      messageErrorIf(rw != -1 && lw > rw,
                     "Invalid use of = operator: left bound must "
                     "be less than or equal to right bound\n" +
                         printErrorMessage());
      TemporalExpressionPtr right = _tsubFormulas.top();
      _tsubFormulas.pop();
      _tsubFormulas.push(generatePtr<SereNonConsecutiveRep>(
          right, std::make_pair(lw, rw)));

    } else {
      //[=r] or [=]
      messageErrorIf(ctx->DOLLAR() != nullptr,
                     "Invalid use of unbounded operator $\n" +
                         printErrorMessage());
      TemporalExpressionPtr right = _tsubFormulas.top();
      _tsubFormulas.pop();
      int rep = ctx->UINTEGER().size() == 1
                    ? safeStoull(ctx->UINTEGER()[0]->getText())
                    : 1;
      _tsubFormulas.push(generatePtr<SereNonConsecutiveRep>(
          right, std::make_pair(rep, rep)));
    }
    return;
  }

  if (ctx->sere().empty() && ctx->booleanLayer() != nullptr &&
      ctx->LSQUARED() != nullptr && ctx->IMPLO() != nullptr &&
      ctx->RSQUARED() != nullptr) {

    if ((ctx->DOTS() != nullptr || ctx->COL() != nullptr) &&
        (ctx->UINTEGER().size() +
             (ctx->DOLLAR() != nullptr ? 1 : 0) ==
         2)) {
      //[->l:r] or [->l:$]

      TemporalExpressionPtr right = _tsubFormulas.top();
      _tsubFormulas.pop();
      int lwi = safeStoull(ctx->UINTEGER()[0]->getText());
      int rwi = ctx->DOLLAR() != nullptr
                    ? -1
                    : safeStoull(ctx->UINTEGER()[1]->getText());
      messageErrorIf(rwi != -1 && lwi > rwi,
                     "Invalid use of -> operator: left bound must "
                     "be less than or equal to right bound\n" +
                         printErrorMessage());
      _tsubFormulas.push(
          generatePtr<SereGoto>(right, std::make_pair(lwi, rwi)));

    } else {
      //[->r] or [->]
      TemporalExpressionPtr right = _tsubFormulas.top();
      _tsubFormulas.pop();
      int rep = ctx->UINTEGER().size() == 1
                    ? safeStoull(ctx->UINTEGER()[0]->getText())
                    : 1;
      _tsubFormulas.push(
          generatePtr<SereGoto>(right, std::make_pair(rep, rep)));
    }
    return;
  }

  if (ctx->LSQUARED() != nullptr && ctx->TIMES() != nullptr &&
      ctx->RSQUARED() != nullptr) {

    if ((ctx->DOTS() != nullptr || ctx->COL() != nullptr) &&
        (ctx->UINTEGER().size() +
             (ctx->DOLLAR() != nullptr ? 1 : 0) ==
         2)) {
      //right [*l:r] or right [*l:$]

      TemporalExpressionPtr right = _tsubFormulas.top();
      _tsubFormulas.pop();

      int lwi = safeStoull(ctx->UINTEGER()[0]->getText());
      int rwi = ctx->DOLLAR() != nullptr
                    ? -1
                    : safeStoull(ctx->UINTEGER()[1]->getText());
      messageErrorIf(rwi != -1 && lwi > rwi,
                     "Invalid use of * operator: left bound must "
                     "be less than or equal to right bound\n" +
                         printErrorMessage());
      _tsubFormulas.push(generatePtr<SereConsecutiveRep>(
          right, std::make_pair(lwi, rwi)));
    } else {
      //right [*r] or right [*]
      messageErrorIf(ctx->DOLLAR() != nullptr,
                     "Invalid use of unbounded operator $\n" +
                         printErrorMessage());

      TemporalExpressionPtr right = _tsubFormulas.top();
      _tsubFormulas.pop();

      int lw;
      int rw;

      if (ctx->UINTEGER().empty()) {
        lw = 0;
        rw = -1;
      } else {
        lw = safeStoull(ctx->UINTEGER()[0]->getText());
        rw = lw;
      }

      _tsubFormulas.push(generatePtr<SereConsecutiveRep>(
          right, std::make_pair(lw, rw)));
    }
    return;
  }

  if (ctx->sere().size() == 2 && ctx->COL() != nullptr) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<SereConcat>(left, right, true));
    return;
  }

  if (ctx->sere().size() == 2 && ctx->SCOL() != nullptr) {
    TemporalExpressionPtr right = _tsubFormulas.top();
    _tsubFormulas.pop();
    TemporalExpressionPtr left = _tsubFormulas.top();
    _tsubFormulas.pop();
    _tsubFormulas.push(generatePtr<SereConcat>(left, right, false));
    return;
  }
}

std::string TemporalParserHandler::printErrorMessage() {
  std::stringstream ss;
  for (auto &msg : _errorMessages) {
    ss << msg << "\n";
  }
  return ss.str();
}

void TemporalParserHandler::visitErrorNode(
    __attribute__((unused)) antlr4::tree::ErrorNode *node) {
  messageError("Antlr parse error: " + node->getText() + "\n" +
               printErrorMessage());
}

void TemporalParserHandler::addErrorMessage(const std::string &msg) {
  _errorMessages.push_back(msg);
}

std::unordered_map<std::string, std::unordered_set<int>>
TemporalParserHandler::getPhToIdsDomain() {
  return _phToIdsDomain;
}
expression::TemporalExpressionPtr
TemporalParserHandler::getTemporalExpression() {
  messageErrorIf(
      !_tsubFormulas.empty(),
      "Error parsing formula, subformulas leftovers on "
      "the stack, the first one is '" +
          temp2String(_tsubFormulas.top(), Language::SpotLTL,
                      PrintMode::ShowOnlyPermuationPlaceholders) +
          "' " + printErrorMessage());
  return _temporalExpression;
}

harm::DTOParam TemporalParserHandler::getDTOParam() {
  return _dto_param;
}

} // namespace hparser
