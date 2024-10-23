#pragma once

#include <string>
#include <vector>

#include "ContextMiner.hh"

namespace harm {
class Context;
class Trace;

/*! \class ManualDefinition
    \brief used to generated manually defined contexts (in the .xml file)
*/
class ManualDefinition : public ContextMiner {

public:
  explicit ManualDefinition(std::string &configFile);

  ~ManualDefinition() override = default;

  void mineContexts(const harm::TracePtr &trace,
                    std::vector<ContextPtr > &context) override;
};

} // namespace harm
