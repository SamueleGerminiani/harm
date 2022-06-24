#include "BDTLimitsParserHandler.hh"
#include "limitsLexer.h"
using namespace harm;

namespace hparser{
BDTLimits parseLimits(const std::string &formula){


  // parse typed propositions
  hparser::BDTLimitsParserHandler listener;
  listener.addErrorMessage("\t\t\tIn bdtLimits: "+formula);
  antlr4::ANTLRInputStream input(formula);
  limitsLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  limitsParser parser(&tokens);
  antlr4::tree::ParseTree *treeFragAnt = parser.file();
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  /*
  DEBUG
  exit(0);
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  */
  BDTLimits limits= listener.getLimits();

  //handle special cases of missing options
  auto setOptions= listener.getSetOptions();
  if ((setOptions.count("W") xor setOptions.count("D")) && !setOptions.count("A")) {
      if (setOptions.count("D")) {
          limits._maxAll=limits._maxDepth;
          limits._maxWidth=limits._maxDepth;
      }else if (setOptions.count("W")) {
          limits._maxAll=limits._maxWidth;
          limits._maxDepth=limits._maxWidth;
      }
  }
  if ((!setOptions.count("W") && !setOptions.count("D")) && setOptions.count("A")) {
          limits._maxDepth=limits._maxAll;
          limits._maxWidth=limits._maxAll;
  }

  return limits;
}
}
