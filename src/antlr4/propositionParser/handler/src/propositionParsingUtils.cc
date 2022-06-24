#include "propositionParsingUtils.hh"
#include "PropositionParserHandler.hh"
#include "propositionLexer.h"

namespace hparser{
using namespace expression;
expression::Proposition *parseProposition(std::string formula, harm::Trace *trace){
  // formula="ePage == PAGE_MAIN && c8val==M_TEST+M_NULL";

  auto decls=trace->getDeclarations();
  addTypeToProposition(formula, decls);

  // parse typed propositions
  hparser::PropositionParserHandler listener(trace);
  listener.addErrorMessage("\t\t\tIn formula: "+formula);
  antlr4::ANTLRInputStream input(formula);
  propositionLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  propositionParser parser(&tokens);
  antlr4::tree::ParseTree *treeFragAnt = parser.file();
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  /*
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  DEBUG
  exit(0);
  */
  return listener.getProposition();
}
expression::Proposition *parsePropositionAlreadyTyped(std::string formula, harm::Trace *trace){

  // parse typed propositions
  hparser::PropositionParserHandler listener(trace);
  listener.addErrorMessage("\t\t\tIn formula: "+formula);
  antlr4::ANTLRInputStream input(formula);
  propositionLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  propositionParser parser(&tokens);
  antlr4::tree::ParseTree *treeFragAnt = parser.file();
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, treeFragAnt);
  /*
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
  DEBUG
  exit(0);
  */
  return listener.getProposition();
}
void addTypeToProposition(std::string &formula,
                          std::vector<harm::VarDeclaration> varDeclarations) {
  /*all this code is to solve the problem of
  adding types to the variables in the formula:
  The complexity of the code is to handle the following problems:*/
  //(1) A variable can be used mutiple times non sequentially(need to parse
  // the string n times) (2) A variable can contain the words bool, logic,
  // numeric (3) A variable name can be contained in an other variable, ex.
  // state, next_state


  /*now that with have all the variables, we can insert the types in the
  formula*/
  varDeclarations.push_back(std::make_tuple("true", VarType::Bool, 1));
  varDeclarations.push_back(std::make_tuple("false", VarType::Bool, 1));

  // match the longest variables first to solve (3)
  std::sort(begin(varDeclarations), end(varDeclarations),
            [](harm::VarDeclaration &e1,
               harm::VarDeclaration &e2) {
              return std::get<0>(e1).size() > std::get<0>(e2).size();
            });

  /* keep track of substitutions to solve (2) and (3)
   The false values correspond to characters of formula that can be
   substituted, the true values correspond to characters of formula that
   can not be substituted*/

  std::deque<bool> changes(formula.size());

  // Substitute each variable in the formula (if present)
  for (auto varDec : varDeclarations) {
    std::string nameType = "";
    switch (std::get<1>(varDec)) {
    case VarType::Bool:
      if (std::get<0>(varDec) == "true" || std::get<0>(varDec) == "false") {
        nameType = "@" + std::get<0>(varDec);
      } else {
        nameType = " <" + std::get<0>(varDec) + ",bool>";
      }
      break;
    case VarType::ULogic:
      nameType = " <" + std::get<0>(varDec) + ",logic(u," +
                 std::to_string(std::get<2>(varDec)) + ")>";
      break;
    case VarType::SLogic:
      nameType = " <" + std::get<0>(varDec) + ",logic(s," +
                 std::to_string(std::get<2>(varDec)) + ")>";
      break;
    case VarType::Numeric:
      nameType = " <" + std::get<0>(varDec) + ",numeric(" +
                 std::to_string(std::get<2>(varDec)) + ")>";
      break;
    default:
      messageError("Variable is of \'Uknown type\'");
      break;
    }

    // restart from the beginning of the current formula
    auto it = begin(formula);
    std::string toFind = std::get<0>(varDec);

    //    std::cout<<"matching:"<<toFind<<"\n";
    // add type to the variable (if present)
    while (1) {
      // search for the current var in the formula
      it = std::search(it, end(formula), begin(toFind), end(toFind));
      if (it == end(formula)) {
        // not found... terminating the substitution for this
        // variable
        //            std::cout<<"No\n";
        break;
      }

      /*check if you are trying to substitute a substring of an
      already substituted variable*/
      if (*(begin(changes) + (it - begin(formula)))) {
        /*increment the index iterator until the end of the
        forbidden area or until the end of the string*/
        while (*(begin(changes) + (it - begin(formula)))) {
          it++;
          if (it == end(formula)) {
            break;
          }
        }
        continue;
      }

      // substitute the typeless variable with <varName,type>

      // remove the plain variable
      formula.erase(it, it + toFind.size());

      /* keep track of substitutions: tranform the changes vector to
       mirror the state of formula*/
      std::transform(begin(changes) + (it - begin(formula)),
                     begin(changes) + (it - begin(formula)) + toFind.size(),
                     begin(changes) + (it - begin(formula)),
                     [](__attribute__((unused)) bool e) { return true; });

      /*calculate how much to extend the changes vector (must be of
      the same size of formula*/

      if (nameType.size() > toFind.size()) {
        size_t toAdd = nameType.size() - toFind.size();
        // extend changes to match the new size of formula
        changes.insert(begin(changes) + (it - begin(formula)), toAdd, true);
      } else {
        // restrict changes to match the new size of formula
        size_t toRemove = toFind.size() - nameType.size();
        changes.erase(begin(changes) + (it - begin(formula)),
                      begin(changes) + (it - begin(formula) + toRemove));
      }

      // insert the variable with its type
      size_t dist = std::distance(begin(formula), it);
      formula.insert(it, begin(nameType), end(nameType));
      it = begin(formula) + dist + nameType.size();
      /*'it' is an iterator to the character of formula after the last
      substitution*/
    } // end while(1) --> end of formula

    assert(changes.size() == formula.size());
  } // end var
//        std::cout << "After: " << formula << "\n";
}
}
