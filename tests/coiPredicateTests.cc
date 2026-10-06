// H10 validation: the predicates harm-coi harvests (whose hand labels, tests/input/h10, A1
// requires them to equal) parse as HARM propositions, and HARM's Z3 canonicaliser (H2) finds no
// two of them equivalent: harm-coi's syntactic normalisation leaves no duplicates (D-023).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "PointerUtils.hh"
#include "PropositionCanonicalizer.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {
/// the variables of a VCD under tb::dut, named as HARM names them (any depth), with their widths
TracePtr vcdTrace(const std::string &vcd) {
  std::ifstream in(vcd);
  std::vector<std::string> stack;
  std::vector<VarDeclaration> decls;
  std::string line;
  while (std::getline(in, line)) {
    std::istringstream ss(line);
    std::vector<std::string> tok;
    for (std::string t; ss >> t;) {
      tok.push_back(t);
    }
    if (tok.empty()) {
      continue;
    }
    if (tok[0] == "$scope") {
      stack.push_back(tok[2]);
    } else if (tok[0] == "$upscope") {
      stack.pop_back();
    } else if (tok[0] == "$var" && stack.size() >= 2 && stack[0] == "tb" && stack[1] == "dut") {
      std::string name;
      for (size_t i = 2; i < stack.size(); i++) {
        name += stack[i] + "::";
      }
      name += tok[4];
      size_t w = std::stoul(tok[2]);
      decls.emplace_back(name, w == 1 ? ExpType::Bool : ExpType::ULogic, w);
    } else if (tok[0] == "$enddefinitions") {
      break;
    }
  }
  return generatePtr<Trace>(decls, 4);
}
} // namespace

TEST(CoiPredicateTest, noZ3DuplicatesAmongHarvestedPredicates) {
  struct Fixture {
    std::string name, vcd;
  };
  std::vector<Fixture> fixtures = {
      {"counter", "../tests/input/coi/counter/trace.vcd"},
      {"arbiter", "../tests/input/coi/arbiter/trace.vcd"},
      {"fsm", "../tests/input/coi/fsm/trace.vcd"},
      {"structs", "../tests/input/coi/structs/trace.vcd"},
      {"constructs", "../tests/input/h5/constructs/trace.vcd"},
  };
  size_t total = 0;
  for (const auto &f : fixtures) {
    TracePtr trace = vcdTrace(f.vcd);
    boost::property_tree::ptree root;
    boost::property_tree::read_json("../tests/input/h10/" + f.name + "_predicates.json", root);
    std::vector<PropositionPtr> props;
    std::vector<std::string> texts;
    for (const auto &[_, p] : root.get_child("predicates")) {
      std::string expr = p.get<std::string>("expr");
      hlog::ScopedThrowOnError throwOnError;
      try {
        props.push_back(hparser::parseProposition(expr, trace));
        texts.push_back(expr);
      } catch (const hlog::HarmError &e) {
        ADD_FAILURE() << f.name << ": '" << expr << "' does not parse: " << e.what();
      }
    }
    PropositionCanonicalizer canon(2000);
    canon.build(props);
    size_t duplicates = props.size() - canon.numberOfClasses();
    std::cout << "[" << f.name << "] " << props.size() << " predicates, " << canon.numberOfClasses()
              << " Z3 classes, " << duplicates << " duplicates\n";
    EXPECT_EQ(duplicates, 0u) << f.name;
    total += props.size();
  }
  EXPECT_GT(total, 0u);
}
