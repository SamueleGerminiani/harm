#include "expUtils/smtEquivalence.hh"

#ifdef HARM_WITH_Z3
#include <z3++.h>

#include "visitors/ExpToZ3Visitor.hh"
#endif

namespace expression {
namespace smt {

#ifdef HARM_WITH_Z3

bool available() { return true; }

Equivalence checkEquivalence(const PropositionPtr &p1,
                             const PropositionPtr &p2, unsigned timeoutMs,
                             Counterexample *cex) {
  // logic values are encoded at one width U, at least the widest width in the query: start
  // with 64 and encode again with the width found, if wider
  unsigned U = 64;
  for (int attempt = 0; attempt < 2; attempt++) {
    try {
      z3::context ctx;
      ExpToZ3Visitor enc(ctx, U);
      z3::expr e1 = enc.encode(p1);
      z3::expr e2 = enc.encode(p2);
      if (enc.maxWidth() > U) {
        U = enc.maxWidth();
        continue;
      }
      z3::solver s(ctx);
      z3::params params(ctx);
      params.set("timeout", timeoutMs);
      s.set(params);
      for (const auto &a : enc.assumptions()) {
        s.add(a);
      }
      s.add(e1 != e2);
      switch (s.check()) {
      case z3::unsat:
        return Equivalence::Equivalent;
      case z3::sat:
        // with opaque atoms, a model may not correspond to real values
        if (enc.usedOpaque()) {
          return Equivalence::Unknown;
        }
        if (cex != nullptr) {
          *cex = enc.variableValues(s.get_model());
        }
        return Equivalence::NotEquivalent;
      default:
        return Equivalence::Unknown;
      }
    } catch (const z3::exception &) {
      return Equivalence::Unknown;
    }
  }
  return Equivalence::Unknown;
}

Entails checkImplication(const PropositionPtr &p, const PropositionPtr &q,
                         unsigned timeoutMs) {
  // as checkEquivalence: p implies q iff p && !q has no model (x/z encoded, D-011)
  unsigned U = 64;
  for (int attempt = 0; attempt < 2; attempt++) {
    try {
      z3::context ctx;
      ExpToZ3Visitor enc(ctx, U);
      z3::expr e1 = enc.encode(p);
      z3::expr e2 = enc.encode(q);
      if (enc.maxWidth() > U) {
        U = enc.maxWidth();
        continue;
      }
      z3::solver s(ctx);
      z3::params params(ctx);
      params.set("timeout", timeoutMs);
      s.set(params);
      for (const auto &a : enc.assumptions()) {
        s.add(a);
      }
      s.add(e1 && !e2);
      switch (s.check()) {
      case z3::unsat:
        return Entails::Yes;
      case z3::sat:
        return enc.usedOpaque() ? Entails::Unknown : Entails::No;
      default:
        return Entails::Unknown;
      }
    } catch (const z3::exception &) {
      return Entails::Unknown;
    }
  }
  return Entails::Unknown;
}

#else

bool available() { return false; }

Entails checkImplication(const PropositionPtr &, const PropositionPtr &, unsigned) {
  return Entails::Unknown;
}

Equivalence checkEquivalence(const PropositionPtr &, const PropositionPtr &,
                             unsigned, Counterexample *) {
  return Equivalence::Unknown;
}

#endif

} // namespace smt
} // namespace expression
