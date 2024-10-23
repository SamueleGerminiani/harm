#include <algorithm>
#include <limits.h>
#include <ostream>
#include <stddef.h>
#include <string>
#include <vector>

#include "Trace.hh"
#include "cxxopts.hpp"
#include "expUtils/expUtils.hh"
#include "formula/temporal/temporal.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"

namespace clc {
std::string formula = "";
}

using namespace harm;
using namespace expression;

/// @brief handle all the command line arguments
static void parseCommandLineArguments(int argc, char *args[]);

/// @brief handles all the unhandled exceptions
void exceptionHandler();

/// @brief handles all the unhandled errors
void handleErrors();

int main(int arg, char *argv[]) {

  //enforce deterministic rand
  srand(1);

  parseCommandLineArguments(arg, argv);

  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  auto te = hparser::parseTemporalExpression(clc::formula, trace);

  std::cout << printAST_terminal(
                   te, Language::SpotLTL,
                   PrintMode::ShowOnlyPermuationPlaceholders)
            << std::endl;

  return 0;
}

cxxopts::ParseResult parseAST(int argc, char *argv[]) {
  try {
    cxxopts::Options options(argv[0], "");
    options.positional_help("[optional args]").show_positional_help();

    std::string file = "";

    options.add_options()(
        "formula", "", cxxopts::value<std::string>(),
        "string representation of the temporal formula to print, the "
        "boolean layer can only contain placeholders")(
        "silent", "disable all outputs")("wsilent", "disable all "
                                                    "warning")(
        "isilent", "disable all "
                   "info")("psilent", "disable all progress bars")(
        "help", "Show options");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }
    if (!result.count("formula")

    ) {

      std::cout << "Usage:\n ast"
                   " --formula <tformula>"
                << "\n";
      exit(0);
    }

    return result;

  } catch (const cxxopts::OptionException &e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}

void parseCommandLineArguments(int argc, char *args[]) {
  //parse the cmd using an external library
  auto result = parseAST(argc, args);
  if (result.count("formula")) {
    clc::formula = result["formula"].as<std::string>();
  }
}

