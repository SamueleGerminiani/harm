#pragma once

#include "exp.hh"
#include "expUtils/VarType.hh"
#include "message.hh"
#include <memory>
#include <spot/tl/formula.hh>
#include <spot/tl/parse.hh>
#include <spot/tl/print.hh>
#include <spot/twaalgos/hoa.hh>
#include <spot/twaalgos/isdet.hh>
#include <spot/twaalgos/ltl2tgba_fm.hh>
#include <spot/twaalgos/minimize.hh>
#include <spot/twaalgos/postproc.hh>
#include <spot/twaalgos/sccfilter.hh>
#include <spot/twaalgos/stripacc.hh>
#include <string>
#include <unordered_map>

namespace harm {
class Template;
class Automaton;
class EdgeProposition;

/** \brief To print a ClsOp
   */
std::ostream &operator<<(std::ostream &os, ClsOp op);

std::pair<expression::VarType, size_t>
variableTypeFromString(const std::string &type, size_t size = 1);

std::vector<expression::Proposition *>
genPropsThroughClustering(std::vector<size_t> &ivs,
                          expression::CachedAllNumeric *cn, size_t max_length);

/** \brief generate a FSM from a spot formula
   */
std::shared_ptr<spot::twa_graph>
generateDeterministicSpotAutomaton(spot::formula &formula);

/** \brief builds a custom automaton (see class Automaton) from a spotLTL automaton
   */
Automaton *buildAutomaton(
    spot::twa_graph_ptr &automata,
    std::unordered_map<std::string, expression::Proposition **> &tokenToProp);

/** \brief converts a spot LTL formula to a custom proposition
   */
EdgeProposition *edgeToProposition(
    const spot::formula &f,
    std::unordered_map<std::string, expression::Proposition **> &tokenToProp);
} // namespace harm
