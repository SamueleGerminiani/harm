#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <z3++.h>

#include "visitors/ExpVisitor.hh"
#include "visitors/visitorExpList.hh"

namespace expression {

/// @brief Encodes HARM propositions as Z3 formulas with HARM's exact semantics (H2, D-003).
///
/// Logic values are encoded as HARM's Logic class stores them: a value, an x-mask and a z-mask,
/// all as bit-vectors of one uniform width U (the widest width in the query). HARM keeps "hidden"
/// value bits above a value's width (the carry of a sum, the ones of a negation) and every
/// operator masks or sign-extends its operands at its own width: the encoding does the same.
///
/// Every construct that is not encoded exactly becomes an opaque atom: a free variable keyed by
/// the construct's text (the same text gives the same atom). This is sound (a property proved
/// for every value of the atom holds for its real values) but incomplete.
class ExpToZ3Visitor : public ExpVisitor {
public:
  /// @param U width of the logic bit-vectors, at least the widest width in the query
  ExpToZ3Visitor(z3::context &ctx, unsigned U);
  ~ExpToZ3Visitor() override = default;

  /// @brief the encoding of a proposition
  z3::expr encode(const PropositionPtr &p);

  /// @brief constraints that hold for every variable value (e.g. a bit is never both x and z)
  const std::vector<z3::expr> &assumptions() const { return _assumptions; }

  /// @brief true if an opaque atom was used (a satisfiable query is then not a counterexample)
  bool usedOpaque() const { return _usedOpaque; }

  /// @brief the widest logic width seen; U must be at least this
  unsigned maxWidth() const { return _maxWidth; }

  /// @brief the values of the variables (not of the opaque atoms) in a model
  std::map<std::string, std::string> variableValues(const z3::model &m);

  VISITOR_EXP_LIST(visitor_virtual, override)

private:
  /// a logic value: raw value bits, x-mask and z-mask (all U bits wide), its static type, and
  /// whether its width may change at run time (arithmetic collapses to a 1-bit x)
  struct LTerm {
    z3::expr v, x, z;
    unsigned w;
    bool sgn;
    bool mayCollapse;
  };

  z3::context &_ctx;
  unsigned _U;
  unsigned _maxWidth = 0;
  bool _usedOpaque = false;

  std::vector<z3::expr> _bools;
  std::vector<z3::expr> _ints; // 64-bit bit-vectors
  std::vector<z3::expr> _floats;
  std::vector<LTerm> _logics;

  std::vector<z3::expr> _assumptions;
  /// variables and opaque atoms by name/text
  std::map<std::string, z3::expr> _boolAtoms, _intAtoms, _floatAtoms;
  std::map<std::string, LTerm> _logicAtoms;

  // ---- helpers
  z3::expr bv(uint64_t value) { return _ctx.bv_val(value, _U); }
  z3::expr zero() { return _ctx.bv_val(0, _U); }
  z3::expr mask(unsigned width);
  /// operand value as HARM's unsignedToSLogic/signedToSLogic sees it at width R
  z3::expr ext(const z3::expr &v, unsigned R, bool sgn);
  z3::expr anyXZ(const LTerm &t);
  void see(unsigned width);

  z3::expr popBool();
  z3::expr popInt();
  z3::expr popFloat();
  LTerm popLogic();

  template <typename Node> std::string text(Node &o);
  void opaqueBool(const std::string &key);
  void opaqueInt(const std::string &key);
  void opaqueFloat(const std::string &key);
  void opaqueLogic(const std::string &key, unsigned w, bool sgn);

  void logicCompare(const std::pair<ExpType, size_t> &a,
                    const std::pair<ExpType, size_t> &b, int op);
  void logicBitwise(const std::pair<ExpType, size_t> &type, int op);
  void logicArith(const std::pair<ExpType, size_t> &type, int op);
  void intCompare(const std::pair<ExpType, size_t> &a,
                  const std::pair<ExpType, size_t> &b, int op);
  /// HARM's extendTo: masked to the width, sign-extended (x/z included) if 'sgn'
  LTerm extendTo(const LTerm &t, unsigned width, bool sgn);
};

} // namespace expression
