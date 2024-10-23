#pragma once

#include "TemporalExpression.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "globals.hh"
#include <memory>
#include <type_traits>

namespace harm {
enum class DTO_Type;
}

namespace expression {

/**
 * @class BooleanLayer
 * @brief A base class for different types of boolean layers in temporal expressions.
 */
class BooleanLayer : public TemporalExpression {
public:
  virtual ~BooleanLayer() {}

  /**
   * @brief Get the token of the boolean layer.
   * @return The token as a string.
   */
  virtual std::string getToken() { return _token; }

  /**
   * @brief Set the token for the boolean layer.
   * @param token The token to set.
   */
  void setToken(const std::string &token) { _token = token; }

protected:
  /**
   * @brief Accept a visitor for processing the expression.
   * @param vis The visitor to accept.
   */
  void acceptVisitor(ExpVisitor &vis) override {}

  /**
   * @brief Constructor for BooleanLayer.
   * @param token The token to set for the boolean layer.
   */
  BooleanLayer(const std::string &token) : _token(token) {}

  /// The token representing the boolean layer.
  std::string _token = "";
};

/**
 * @class BooleanLayerInst
 * @brief Represents an instance of a boolean layer.
 */
class BooleanLayerInst : public BooleanLayer {
public:
  /**
   * @brief Constructor for BooleanLayerInst.
   * @param p The proposition pointer.
   * @param token The token for the boolean layer instance.
   */
  BooleanLayerInst(const PropositionPtr &p, const std::string &token)
      : BooleanLayer(token), _p(p){};

  ~BooleanLayerInst() override {}

  void acceptVisitor(ExpVisitor &vis) override;

  /**
   * @brief Get the proposition of the boolean layer instance.
   * @return The proposition pointer.
   */
  PropositionPtr getProposition() { return _p; }

private:
  /// The proposition pointer.
  PropositionPtr _p = nullptr;
};

/**
 * @class BooleanLayerPlaceholder
 * @brief Represents a placeholder in a boolean layer.
 */
class BooleanLayerPlaceholder : public BooleanLayer {
public:
  /// Deleted copy constructor.
  BooleanLayerPlaceholder(const BooleanLayerPlaceholder &other) =
      delete;

  ~BooleanLayerPlaceholder() override {}

  void acceptVisitor(ExpVisitor &vis) override{};

  /**
   * @brief Get the placeholder pointer.
   * @return The placeholder pointer reference.
   */
  PropositionPtrPtr &getPlaceholderPointer() { return _pp; }

protected:
  /**
   * @brief Constructor for BooleanLayerPlaceholder.
   * @param pp The proposition pointer pointer.
   * @param token The token for the boolean layer placeholder.
   */
  explicit BooleanLayerPlaceholder(const PropositionPtrPtr &pp,
                                   const std::string &token)
      : BooleanLayer(token), _pp(pp){};

private:
  /// The placeholder pointer.
  PropositionPtrPtr _pp = nullptr;
};

using BooleanLayerPlaceholderPtr =
    std::shared_ptr<BooleanLayerPlaceholder>;

/**
 * @class BooleanLayerPermutationPlaceholder
 * @brief Represents a permutation placeholder in a boolean layer.
 */
class BooleanLayerPermutationPlaceholder
    : public BooleanLayerPlaceholder {
public:
  /**
   * @brief Constructor for BooleanLayerPermutationPlaceholder.
   * @param pp The proposition pointer pointer.
   * @param token The token for the boolean layer permutation placeholder.
   */
  explicit BooleanLayerPermutationPlaceholder(
      const PropositionPtrPtr &pp, const std::string &token)
      : BooleanLayerPlaceholder(pp, token){};

  ~BooleanLayerPermutationPlaceholder() override {}

  void acceptVisitor(ExpVisitor &vis) override;
};

using BooleanLayerPermutationPlaceholderPtr =
    std::shared_ptr<BooleanLayerPermutationPlaceholder>;

/**
 * @class BooleanLayerDTPlaceholder
 * @brief Represents a decision-tree placeholder in a boolean layer.
 */
class BooleanLayerDTPlaceholder : public BooleanLayerPlaceholder {
public:
  /**
   * @brief Constructor for BooleanLayerDTPlaceholder.
   * @param dtType The type of the decision-tree operator.
   * @param pp The proposition pointer pointer.
   * @param token The token for the boolean layer decision-tree placeholder.
   * @param dtID The ID for the decision-tree.
   */
  explicit BooleanLayerDTPlaceholder(const harm::DTO_Type dtType,
                                     const PropositionPtrPtr &pp,
                                     const std::string &token,
                                     int dtID)
      : BooleanLayerPlaceholder(pp, token), _dtType(dtType),
        _dtID(dtID){};

  ~BooleanLayerDTPlaceholder() override {}

  void acceptVisitor(ExpVisitor &vis) override;

  int getID() { return _dtID; }
  void setID(int dtID) { _dtID = dtID; }
  harm::DTO_Type getType() { return _dtType; }
  void setType(harm::DTO_Type dtType) { _dtType = dtType; }

private:
  /// The type of the decision-tree operator.
  harm::DTO_Type _dtType;
  /// The ID of the decision-tree placeholder. If 0, then this is the first placeholder of a decision-tree operator
  int _dtID = -1;
};

using BooleanLayerDTPlaceholderPtr =
    std::shared_ptr<BooleanLayerDTPlaceholder>;

/**
 * @class BooleanLayerNot
 * @brief Represents a negation in a boolean layer.
 */
class BooleanLayerNot : public BooleanLayer {
public:
  /**
   * @brief Constructor for BooleanLayerNot.
   * @param bl The temporal expression pointer.
   */
  explicit BooleanLayerNot(const TemporalExpressionPtr &bl)
      : BooleanLayer("bl_not") {
    _items.push_back(bl);
  };

  ~BooleanLayerNot() override {}

  void acceptVisitor(ExpVisitor &vis) override;
  TemporalExpressionPtr getBL() { return _items.back(); }
  virtual ope::temporalOpe getOperator() override {
    return ope::temporalOpe::BooleanLayerNot;
  }

private:
  using TemporalExpression::
      _items; // Inherited items from TemporalExpression.
};

using BooleanLayerNotPtr = std::shared_ptr<BooleanLayerNot>;

// Smart pointer aliases
using BooleanLayerPtr = std::shared_ptr<BooleanLayer>;
using BooleanLayerInstPtr = std::shared_ptr<BooleanLayerInst>;

inline bool isInst(const TemporalExpressionPtr &e) {
  return std::dynamic_pointer_cast<BooleanLayerInst>(e) != nullptr;
}

inline bool isPlaceholder(const TemporalExpressionPtr &e) {
  return std::dynamic_pointer_cast<BooleanLayerPlaceholder>(e) !=
         nullptr;
}

inline bool isBooleanLayerNot(const TemporalExpressionPtr &e) {
  return std::dynamic_pointer_cast<BooleanLayerNot>(e) != nullptr;
}

/**
 * @brief Check if the temporal expression is a boolean layer.
 * @param e The temporal expression pointer.
 * @return True if it is a boolean layer, false otherwise.
 */
inline bool isBooleanLayer(const TemporalExpressionPtr &e) {
  return isInst(e) || isPlaceholder(e);
}

/**
 * @brief Get the token of the boolean layer.
 * @param e The temporal expression pointer.
 * @return The token as a string.
 */
inline std::string
getBooleanLayerToken(const TemporalExpressionPtr &e) {
  messageErrorIf(!isBooleanLayer(e),
                 "getBooleanLayerToken, not a boolean layer temporal "
                 "expression");
  return std::dynamic_pointer_cast<BooleanLayer>(e)->getToken();
}

inline bool isPermutationPlaceholder(const TemporalExpressionPtr &e) {
  return std::dynamic_pointer_cast<
             BooleanLayerPermutationPlaceholder>(e) != nullptr;
}

inline bool isDTPlaceholder(const TemporalExpressionPtr &e) {
  return std::dynamic_pointer_cast<BooleanLayerDTPlaceholder>(e) !=
         nullptr;
}

/**
 * @brief Check if the temporal expression is a decision-tree placeholder with a specific ID.
 * @param e The temporal expression pointer.
 * @param id The ID to check.
 * @return True if it is a decision-tree placeholder with the given ID, false otherwise.
 */
inline bool isDTPlaceholder(const TemporalExpressionPtr &e, int id) {
  return isDTPlaceholder(e) &&
         std::dynamic_pointer_cast<BooleanLayerDTPlaceholder>(e)
                 ->getID() == id;
}

/**
 * @brief Check if two temporal expressions are of the same boolean layer type.
 * @param e1 The first temporal expression pointer.
 * @param e2 The second temporal expression pointer.
 * @return True if they are of the same boolean layer type, false otherwise.
 */
inline bool isSameBooleanLayerType(const TemporalExpressionPtr &e1,
                                   const TemporalExpressionPtr &e2) {
  return (isInst(e1) && isInst(e2)) ||
         (isDTPlaceholder(e1) && isDTPlaceholder(e2)) ||
         (isPermutationPlaceholder(e1) &&
          isPermutationPlaceholder(e2)) ||
         (isBooleanLayerNot(e1) && isBooleanLayerNot(e2));
}

/**
 * @brief Get the placeholder pointer of the temporal expression.
 * @param e The temporal expression pointer.
 * @return The placeholder pointer reference.
 */
inline PropositionPtrPtr &
getPlaceholderPointer(const TemporalExpressionPtr &e) {
  messageErrorIf(!isPlaceholder(e),
                 "getPlaceholderPointer, not a placeholder boolean "
                 "layer expression");
  return std::dynamic_pointer_cast<BooleanLayerPlaceholder>(e)
      ->getPlaceholderPointer();
}

/**
 * @brief Get the proposition (if present) of the temporal expression.
 * @param e The temporal expression pointer.
 * @return The proposition pointer.
 */
inline PropositionPtr getProposition(const TemporalExpressionPtr &e) {
  messageErrorIf(!isBooleanLayer(e),
                 "getProposition, not a boolean layer expression");

  if (isInst(e)) {
    return std::dynamic_pointer_cast<BooleanLayerInst>(e)
        ->getProposition();
  } else if (isPermutationPlaceholder(e)) {
    return *std::dynamic_pointer_cast<
                BooleanLayerPermutationPlaceholder>(e)
                ->getPlaceholderPointer();
  } else if (isDTPlaceholder(e)) {
    return *std::dynamic_pointer_cast<BooleanLayerDTPlaceholder>(e)
                ->getPlaceholderPointer();
  }

  messageError(
      "getProposition, not a proposition boolean layer expression");
  return nullptr;
}

/**
 * @brief Substitute all instances of a boolean layer formula with another formula using the token.
 * @param original The original temporal expression pointer.
 * @param sub The substitution temporal expression pointer.
 * @param token The token to match for substitution.
 */
inline void substituteByToken(TemporalExpressionPtr &original,
                              const TemporalExpressionPtr &sub,
                              const std::string &token) {
  bool atLeastOne = false;

  traverse(original, [&](TemporalExpressionPtr &f) {
    if (isBooleanLayer(f) &&
        std::dynamic_pointer_cast<BooleanLayer>(f)->getToken() ==
            token) {
      f = sub;
      atLeastOne = true;
      return true;
    }
    return false;
  });

  messageErrorIf(
      !atLeastOne,
      "substituteByToken failed, no boolean layer formula with token "
      "'" +
          token + "' found in formula'" +
          temp2String(original, clc::outputLang, PrintMode::Hide) +
          "'");
}

} // namespace expression

