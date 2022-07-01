#pragma once

#include <string>
#include <unordered_map>
#include "exp.hh"
#include "expUtils/VarType.hh"
#include "message.hh"

namespace harm {
class Template;
std::ostream & operator<<(std::ostream &os,ClsOp op) ;


std::pair<expression::VarType, uint8_t> variableTypeFromString( const std::string &type, uint8_t size = 1);

std::vector<expression::Proposition *> genPropsThroughClustering(std::vector<size_t> &ivs, expression::CachedAllNumeric *cn, size_t max_length);





}  // namespace harm
