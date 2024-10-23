#pragma once

#include <memory>
#include <vector>

namespace harm {
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;
class Context;
class Trace;
using TracePtr = std::shared_ptr<Trace>;

/// @brief PropertyQualification declaration.
/// This is an interface for a generic property qualification module.
class PropertyQualifier {
public:
  /// @brief Destructor.
  virtual ~PropertyQualifier() = default;

  /// @brief An implementation of this module qualify the assertions of
  /// a context and return the ranked assertions.
  /// @param context A context of influence
  virtual std::vector<AssertionPtr>
  qualify(Context &context, const harm::TracePtr &trace) = 0;

  /// @brief Unsupported constructor.
  PropertyQualifier(const PropertyQualifier &other) = delete;

  /// @brief Unsupported operator
  PropertyQualifier &
  operator=(const PropertyQualifier &other) = delete;

protected:
  /// @brief Constructor.
  explicit PropertyQualifier();
};
using PropertyQualifierPtr = std::shared_ptr<PropertyQualifier>;

} // namespace harm
