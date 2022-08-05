#pragma once

#include "xmlUtils.hh"

namespace harm {

class Context;
class Trace;

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
  virtual void mineContexts(Trace *trace, std::vector<Context *> &contexts) = 0;

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
