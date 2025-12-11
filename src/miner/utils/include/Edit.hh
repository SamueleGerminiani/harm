#pragma once

#include <boost/regex.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace expression {
template <typename T> class Atom;

using Proposition = Atom<bool>;
using PropositionPtr = std::shared_ptr<Proposition>;
} // namespace expression

namespace harm {
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;
class Trace;
using TracePtr = std::shared_ptr<Trace>;
class TemplateImplication;
using TemplateImplicationPtr = std::shared_ptr<TemplateImplication>;

/*! \class Edit
    \brief class for assertion edits
*/
class Edit {

public:
  //delete all other constructors
  Edit() = delete;
  Edit(const Edit &) = delete;
  Edit &operator=(const Edit &) = delete;

  ~Edit();

  /** \brief constructor for rewrite edits
   */
  Edit(const std::string &rewrite, const std::string &to,
       const std::string &constraint);

  /** \brief constructor for remove edits
   */
  Edit(const std::string &remove, const std::string &constraint);

  /** \brief check if the given assertion matches the 'rewrite' rule
   */
  bool matchRewrite(std::string &spotAssertion,
                    TemplateImplicationPtr t,
                    const harm::TracePtr &trace) const;

  /** \brief check if the given assertion matches the 'remove' rule
   */
  bool matchRemove(std::string &spotAssertion,
                   TemplateImplicationPtr t,
                   const harm::TracePtr &trace) const;

  /** \brief returns true if the rule is a 'rewrite' rule
   */
  bool isRewrite() const;

  /** \brief returns true if the rule is a 'remove' rule
   */
  bool isRemove() const;

private:
  /** \brief builds the rule
   */
  void build(const std::string &rule, const std::string &to,
             const std::string &cond);

  /** \brief builds a regex for 'remove' or 'rewrite' edits
   */
  static std::string buildRegex(
      const std::string &rule,
      std::vector<std::pair<std::string, std::string>> &varVal);

  /// Function to handle the content inside @( ... )
  static std::pair<std::string, std::string>
  splitStore(const std::string &content);

  /** \brief parse rule and divide it into segments @( ... )
   */
  static std::vector<std::string> segment(const std::string &input);

  /** \brief parse expressions of the form _inst_0 ##k0 _inst_1 ##k1 ... ##kn _inst_n
   */
  static std::vector<std::string>
  cutDTNext(const std::string &dtNext);

  /** \brief retrieve the variable values from the matches on a given assertion
   */
  void
  fillVarToVal(const boost::match_results<std::string::const_iterator>
                   &matches,
               TemplateImplicationPtr t,
               std::unordered_map<std::string, std::string>
                   &varNameToVal) const;

  /** \brief evaluates the constraint of this rule with the given variable values
   */
  bool evalConstraint(
      const std::unordered_map<std::string, std::string> &varToValue)
      const;

  ///the constraint of this rule
  expression::PropositionPtr _constraint = nullptr;

  ///trace on which to evaluate the constraint
  harm::TracePtr _trace;

  ///string representation of 'to' edit
  std::string _to;

  ///regex for 'rewrite' or 'remove' edits
  std::string _ruleRegex;

  ///segmented 'to' rule: this is mainly an optimization to avoid recomputing the segments for each assertion
  std::vector<std::string> _segmentedTo;

  ///map from variable names to their types (N, P, ..##..)
  std::vector<std::pair<std::string, std::string>> _varNameToType;
};

//smart pointer
using EditPtr = std::shared_ptr<Edit>;

/** \brief check if an assertion should be removed according to the 'remove' edits
   */
bool toBeRemoved(const std::string assertionStr,
                 const std::vector<EditPtr> &remove,
                 const harm::TracePtr &trace);

/** \brief check if an assertion should rewritten according to the 'rewrite' edits; ass is modified by this function if the rule matches
   */
bool rewriteAssertion(const harm::AssertionPtr &ass,
                      const std::vector<EditPtr> &rewrite,
                      const harm::TracePtr &trace);
} // namespace harm
