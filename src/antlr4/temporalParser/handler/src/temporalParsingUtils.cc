#include "temporalParsingUtils.hh"
#include "ANTLRInputStream.h"
#include "CommonTokenStream.h"
#include "Float.hh"
#include "TemplateImplication.hh"
#include "TemporalParserHandler.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"

#include "formula/temporal/Property.hh"
#include "formula/temporal/Sere.hh"
#include "formula/temporal/TemporalExpression.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "temporalLexer.h"
#include "temporalParser.h"
#include "tree/ParseTreeWalker.h"
#include <memory>

namespace antlr4 {
namespace tree {
class ParseTree;
} // namespace tree
} // namespace antlr4

namespace hparser {
using namespace expression;

static std::shared_ptr<hparser::TemporalParserHandler>
parse(std::string formula, const harm::TracePtr &trace,
      bool useCache) {

  auto decls = trace->getDeclarations();
  addTypeToExp(formula, decls);

  // parse typed propositions
  std::shared_ptr<hparser::TemporalParserHandler> listener =
      std::make_shared<hparser::TemporalParserHandler>(trace);

  listener->addErrorMessage("\t\t\tIn formula: " + formula);
  listener->_useCache = useCache;
  antlr4::ANTLRInputStream input(formula);
  temporalLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  temporalParser parser(&tokens);
  //print tokens
  /*
    std::map<size_t, std::string> indexToToken;
    for (auto [token,index] : parser.getTokenTypeMap()) {
        indexToToken[index] = token;
    }
    for (auto &i : lexer.getAllTokens()) {
        std::cout << i->toString() <<" "<<indexToToken.at(i->getType())<<"\n";
    }
    */
  antlr4::tree::ParseTree *treeFragAnt = parser.formula();
  /*
  DEBUG
  std::cout << treeFragAnt->toStringTree(&parser) << "\n\n\n";
    exit(0);
  */
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(&*listener,
                                              treeFragAnt);

  return listener;
}

harm::TemplateImplicationPtr parseTemplateImplication(
    std::string formula, const harm::TracePtr &trace,
    const harm::DTLimits &limits, bool useCache) {

  auto listener = parse(formula, trace, useCache);

  TemporalExpressionPtr te = listener->getTemporalExpression();

  auto limits_copy = limits;
  limits_copy._dto_param = listener->getDTOParam();
  if (limits_copy._saveOffset &&
      !isSimple(getConsequent(te->getItems()[0]))) {
    limits_copy._saveOffset = false;
    messageWarning(
        "Offset disabled in template " +
        temp2String(te, Language::SpotLTL,
                    PrintMode::ShowOnlyPermuationPlaceholders) +
        ". Saving the offset is not reccomended in "
        "complex consequents");
  }
  if (limits_copy._saveOffset &&
      isMultipleMatch(getAntecedent(te->getItems()[0]))) {
    limits_copy._saveOffset = false;
    messageWarning(
        "Offset disabled in template " +
        temp2String(te, Language::SpotLTL,
                    PrintMode::ShowOnlyPermuationPlaceholders) +
        ". Saving the offset is not supported in "
        "templates with multiple matches in the antecedent");
  }

  harm::TemplateImplicationPtr newTemp =
      generatePtr<harm::TemplateImplication>(te, trace, limits_copy);
  newTemp->setPhIds(listener->getPhToIdsDomain());
  return newTemp;
}

TemporalExpressionPtr
parseTemporalExpression(std::string formula,
                        const harm::TracePtr &trace) {

  return parse(formula, trace, false)->getTemporalExpression();
}

} // namespace hparser
