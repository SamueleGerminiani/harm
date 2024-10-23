#pragma once

#include <memory>
#include <string>
#include <vector>

#include "rapidxml.hh"
#include "rapidxml_utils.hh"
#include "xmlUtils.hh"

namespace harm {

class Context;
using ContextPtr = std::shared_ptr<Context>;
class Trace;
using TracePtr = std::shared_ptr<Trace>;

/// @brief ContextMiner declaration.
/// This is an interface for a generic context miner
class ContextMiner {

public:
  /// @brief Destructor.
  virtual ~ContextMiner() {
    if (_xmlFile != nullptr) {
      delete _xmlFile;
    }
    if (_doc != nullptr) {
      delete _doc;
    }
  }

  /// @brief An implementation of this method generates
  /// contexts in some way.
  virtual void mineContexts(const harm::TracePtr &trace,
                            std::vector<ContextPtr> &contexts) = 0;

  /// @brief Unsupported constructor.
  ContextMiner(const ContextMiner &other) = delete;

  /// @brief Unsupported operator.
  ContextMiner &operator=(const ContextMiner &other) = delete;

protected:
  /// @brief Constructor.
  explicit ContextMiner(std::string &configFile);

  /// @brief The xml node containing the configuration
  /// parameters for the module.
  rapidxml::XmlNode *_configuration;
  rapidxml::file<> *_xmlFile;

  rapidxml::xml_document<> *_doc;
};

} // namespace harm
