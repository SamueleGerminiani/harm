#pragma once

#include "Context.hh"
#include "Trace.hh"


namespace harm {

/// @brief PropertyQualification declaration.
/// This is an interface for a generic property qualification module.
class PropertyQualifier {
  public:
    /// @brief Destructor.
    virtual ~PropertyQualifier() = default;

    /// @brief An implementation of this module qualify the assertions of
    /// a context and return the ranked assertions.
    /// @param context A context of influence
    virtual std::vector<Assertion *> qualify(Context &context,Trace *trace) = 0;

    /// @brief Unsupported constructor.
    PropertyQualifier(const PropertyQualifier &other) = delete;

    /// @brief Unsupported operator
    PropertyQualifier &operator=(const PropertyQualifier &other) = delete;

  protected:
    /// @brief Constructor.
    explicit PropertyQualifier();

};

} // namespace harm
