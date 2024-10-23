#pragma once
#include "message.hh"
#include "rapidxml.hh"
#include "rapidxml_utils.hh"
#include <string>
#include <vector>

namespace rapidxml {
using XmlNode = rapidxml::xml_node<>;
using XmlNodeList = std::vector<XmlNode *>;

/// @brief fill the list with the children called 'name' of node 'root'
inline void getNodesFromName(XmlNode *root, const std::string &name,
                             XmlNodeList &list) {
  XmlNode *node = root->first_node(name.c_str(), name.size());
  while (node != nullptr) {
    list.push_back(node);
    node = node->next_sibling(name.c_str());
  }
}

/// @brief return the value of the attribute 'attributeName' of node 'node'
/// if the attribute is not found, return the default value 'defaultValue'
inline std::string
getAttributeValue(XmlNode *node, const std::string &attributeName,
                  const std::string &defaultValue) {
  auto ret = node->first_attribute(attributeName.c_str());
  return ret == nullptr ? defaultValue : ret->value();
}

} // namespace rapidxml
