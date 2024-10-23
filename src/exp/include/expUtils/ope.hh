#pragma once

#include "Language.hh"
#include "globals.hh"
#include "message.hh"
#include <string>

namespace expression {
namespace ope {
enum temporalOpe : int {
  PropertyAlways = 0,
  PropertyEventually,
  PropertyNext,
  PropertyUntil,
  PropertyRelease,
  PropertyAnd,
  PropertyOr,
  PropertyNot,
  PropertyImplication,
  SereConcat,
  SereDelay,
  SereConsecutiveRep,
  SerePlus,
  SereGoto,
  SereNonConsecutiveRep,
  SereAnd,
  SereOr,
  SereIntersect,
  SereFirstMatch,
  BooleanLayerNot,
  TemporalNoOp
};

enum ope : int {
  PropositionNot = 0,
  PropositionAnd,
  PropositionOr,
  PropositionXor,
  PropositionEq,
  PropositionNeq,

  FloatSum,
  FloatSub,
  FloatMul,
  FloatDiv,
  FloatEq,
  FloatNeq,
  FloatGreater,
  FloatGreaterEq,
  FloatLess,
  FloatLessEq,
  FloatSetMembership,

  IntSum,
  IntSub,
  IntMul,
  IntDiv,
  IntBAnd,
  IntBOr,
  IntBXor,
  IntNot,
  IntEq,
  IntNeq,
  IntGreater,
  IntGreaterEq,
  IntLess,
  IntLessEq,
  IntLShift,
  IntRShift,
  IntSetMembership,

  Function,

  NoOp

};

inline std::string opeToString(temporalOpe o,
                               Language lang = Language::Unset) {
  lang = (lang == Language::Unset) ? clc::outputLang : lang;
  switch (o) {
  case PropertyAlways:

    switch (lang) {
    case Language::SpotLTL:
      return "G";
    case Language::PSL:
      return "always";
    case Language::SVA:
      return "always";
    default:
      messageError("Unset language");
    }

  case PropertyEventually:
    switch (lang) {
    case Language::SpotLTL:
      return "F";
    case Language::PSL:
      return "eventually";
    case Language::SVA:
      return "eventually";
    default:
      messageError("Unset language");
    }

  case PropertyNext:
    switch (lang) {
    case Language::SpotLTL:
      return "X";
    case Language::PSL:
      return "next";
    case Language::SVA:
      return "nexttime";
    default:
      messageError("Unset language");
    }

  case PropertyUntil:
    switch (lang) {
    case Language::SpotLTL:
      return "W";
    case Language::PSL:
      return "until";
    case Language::SVA:
      return "until";
    default:
      messageError("Unset language");
    }

  case PropertyRelease:
    switch (lang) {
    case Language::SpotLTL:
      return "R";
    case Language::PSL:
      messageError("Release operator not supported in PSL");
    case Language::SVA:
      messageError("Release operator not supported in SVA");
    default:
      messageError("Unset language");
    }

  case PropertyAnd:
    switch (lang) {
    case Language::SpotLTL:
      return "&&";
    case Language::PSL:
      return "&&";
    case Language::SVA:
      return "and";
    default:
      messageError("Unset language");
    }

  case PropertyOr:
    switch (lang) {
    case Language::SpotLTL:
      return "|";
    case Language::PSL:
      return "|";
    case Language::SVA:
      return "or";
    default:
      messageError("Unset language");
    }
  case PropertyNot:
    switch (lang) {
    case Language::SpotLTL:
      return "!";
    case Language::PSL:
      return "!";
    case Language::SVA:
      return "not";
    default:
      messageError("Unset language");
    }
  case PropertyImplication:
    return "Implication";
  case SereConcat:
    return "SereConcat";
    switch (lang) {
    case Language::SpotLTL:
      return "SereConcat";
    case Language::PSL:
      messageError("SereConcat not supported in PSL");
    case Language::SVA:
      return "SereConcat";
    default:
      messageError("Unset language");
    }
  case SereDelay:
    return "##";
  case SereConsecutiveRep:
    return "*";
  case SerePlus:
    return "+";
  case SereGoto:
    return "->";
  case SereNonConsecutiveRep:
    return "=";
  case SereAnd:
    switch (lang) {
    case Language::SpotLTL:
      return "&";
    case Language::PSL:
      return "&";
    case Language::SVA:
      return "and";
    default:
      messageError("Unknown language");
    }
  case SereOr:
    switch (lang) {
    case Language::SpotLTL:
      return "|";
    case Language::PSL:
      return "|";
    case Language::SVA:
      return "or";
    default:
      messageError("Unknown language");
    }
  case SereIntersect:
    switch (lang) {
    case Language::SpotLTL:
      return "&&";
    case Language::PSL:
      return "&&";
    case Language::SVA:
      return "intersect";
    default:
      messageError("Unknown language");
    }
  case SereFirstMatch:
    switch (lang) {
    case Language::SpotLTL:
      return "first_match";
    case Language::PSL:
      messageError("First match operator not supported in PSL");
    case Language::SVA:
      return "first_match";
    default:
      messageError("Unknown language");
    }
  case BooleanLayerNot:
    return "!";
  case TemporalNoOp:
    return "TemporalNoOp";
  }

  messageError("Unknown temporal ope type");
  return "";
}

inline std::string opeToString(ope o) {
  switch (o) {
  case PropositionNot:
    return "!";
  case PropositionAnd:
    return "&&";
  case PropositionOr:
    return "||";
  case PropositionXor:
    return "^";
  case PropositionEq:
    return "==";
  case PropositionNeq:
    return "!=";

  case FloatSum:
    return "+";
  case FloatSub:
    return "-";
  case FloatMul:
    return "*";
  case FloatDiv:
    return "/";
  case FloatEq:
    return "==";
  case FloatNeq:
    return "!=";
  case FloatGreater:
    return ">";
  case FloatGreaterEq:
    return ">=";
  case FloatLess:
    return "<";
  case FloatLessEq:
    return "<=";
  case FloatSetMembership:
    return "inside";

  case IntSum:
    return "+";
  case IntSub:
    return "-";
  case IntMul:
    return "*";
  case IntDiv:
    return "/";
  case IntBAnd:
    return "&";
  case IntBOr:
    return "|";
  case IntBXor:
    return "^";
  case IntNot:
    return "~";
  case IntEq:
    return "==";
  case IntNeq:
    return "!=";
  case IntGreater:
    return ">";
  case IntGreaterEq:
    return ">=";
  case IntLess:
    return "<";
  case IntLessEq:
    return "<=";
  case IntLShift:
    return "<<";
  case IntRShift:
    return ">>";
  case IntSetMembership:
    return "inside";

  case NoOp:
    return "NoOp";

  case Function:
    return "$function";
  }

  messageError("Unknown ope type");
  return "";
}
inline int opeToPrecedenceClass(temporalOpe o) {

  switch (o) {
  case PropertyAlways:
    return -1;

  case SereConsecutiveRep:
    return 0;
  case SerePlus:
    return 0;
  case SereGoto:
    return 0;
  case SereNonConsecutiveRep:
    return 0;
  case SereFirstMatch:
    return 0;

  case PropertyEventually:
    return 0;
  case PropertyNot:
    return 0;
  case BooleanLayerNot:
    return 0;
  case PropertyNext:
    return 0;

  case PropertyUntil:
    return 1;
  case PropertyRelease:
    return 1;

  case PropertyAnd:
    return 2;
  case SereAnd:
    return 2;
  case SereIntersect:
    return 2;

  case PropertyOr:
    return 3;
  case SereOr:
    return 3;

  case SereDelay:
    return 4;
  case SereConcat:
    return 5;
  case PropertyImplication:
    return 6;

  case TemporalNoOp:
    return 7;
  }

  messageError("Unknown temporal ope type");
  return 7;
}

inline int opeToPrecedenceClass(ope o) {
  switch (o) {

  case Function:
    return 0;
  case IntNot:
    return 0;
  case IntSetMembership:
    return 0;
  case FloatSetMembership:
    return 0;
  case PropositionNot:
    return 0;

  case FloatMul:
    return 1;
  case FloatDiv:
    return 1;
  case IntMul:
    return 1;
  case IntDiv:
    return 1;

  case FloatSum:
    return 2;
  case FloatSub:
    return 2;
  case IntSum:
    return 2;
  case IntSub:
    return 2;

  case IntLShift:
    return 3;
  case IntRShift:
    return 3;

  case FloatLess:
    return 4;
  case IntLess:
    return 4;
  case FloatLessEq:
    return 4;
  case IntLessEq:
    return 4;
    return 4;
  case FloatGreater:
    return 4;
  case FloatGreaterEq:
    return 4;
  case IntGreater:
    return 4;
  case IntGreaterEq:
    return 4;

  case PropositionEq:
    return 5;
  case PropositionNeq:
    return 5;
  case IntEq:
    return 5;
  case IntNeq:
    return 5;
  case FloatNeq:
    return 5;
  case FloatEq:
    return 5;

  case IntBAnd:
    return 6;

  case IntBXor:
    return 7;

  case IntBOr:
    return 8;

  case PropositionAnd:
    return 9;

  case PropositionXor:
    return 10;

  case PropositionOr:
    return 11;

  case NoOp:
    return 12;
  }

  messageError("Unknown ope type");

  return 12;
}

//return true if o1 has a higher precedence than o2
inline bool hasHigherPrecedence(const ope &o1, const ope &o2) {
  return opeToPrecedenceClass(o1) < opeToPrecedenceClass(o2);
}
inline bool isSamePrecedence(const temporalOpe &o1,
                             const temporalOpe &o2) {
  return opeToPrecedenceClass(o1) == opeToPrecedenceClass(o2);
}
inline bool hasHigherPrecedence(const temporalOpe &o1,
                                const temporalOpe &o2) {
  return opeToPrecedenceClass(o1) < opeToPrecedenceClass(o2);
}
inline bool isPropertyOpe(const temporalOpe &o) {
  return o == PropertyAlways || o == PropertyEventually ||
         o == PropertyNext || o == PropertyUntil ||
         o == PropertyRelease || o == PropertyAnd ||
         o == PropertyOr || o == PropertyNot ||
         o == PropertyImplication;
}
inline bool isSereOpe(const temporalOpe &o) {
  return o == SereConcat || o == SereDelay ||
         o == SereConsecutiveRep || o == SerePlus || o == SereGoto ||
         o == SereNonConsecutiveRep || o == SereAnd || o == SereOr ||
         o == SereIntersect || o == SereFirstMatch;
}

} // namespace ope

} // namespace expression
