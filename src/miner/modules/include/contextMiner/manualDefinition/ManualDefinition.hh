#pragma once

#include "ContextMiner.hh"

#include <map>
#include <string>

namespace harm {
class ManualDefinition : public ContextMiner {

public:
explicit ManualDefinition(std::string &configFile);

  ~ManualDefinition() override = default;

  void mineContexts(Trace *trace, std::vector<Context*> &context) override;
};

} // namespace harm
