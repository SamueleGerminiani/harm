#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace SQLite {
class Transaction;
}
namespace ddd {
void createDebugDB();
void addContext(void *id, const std::string &name);
void addTemplate(
    void *id, const std::string &context_name, const std::string &exp,
    const std::unordered_map<
        std::string, std::pair<std::string, std::unordered_set<int>>>
        &placeholderData);
int64_t addNumeric(void *id, const std::string &context_name,
                   const std::string &exp,
                   const std::vector<int> &domain_tokens,
                   SQLite::Transaction *transaction = nullptr);
int64_t addProposition(void *id, const std::string &context_name,
                       const std::string &exp,
                       const std::vector<int> &domain_tokens,
                       SQLite::Transaction *transaction = nullptr);
int64_t addNumericWithExpansion(
    void *id, std::string context_name, const std::string &exp,
    const std::vector<int> &domain_tokens,
    const std::vector<std::pair<void *, std::string>> &propositions,
    const std::string &path_to_clustering_values, bool inDT);
void addPermutation(void *template_id, int number,
                    const std::string &exp);
void addDecisionTree(void *template_id, int number,
                     const std::string &decision_tree_path);
std::string getContextNameFromNumeric(void *numeric_id);
void addAssertion(void *id, void *context_id, int perm_number,
                  const std::string &exp, const std::string &note);
void addContingency(void *assertion_id,
                    const size_t contingencyTable[3][3]);
void removeAssertion(void *assertion_id);
void appendNote(void *assertion_id, const std::string &text);
void unrollAndDumpAssertion(const std::string &dumpPath);
void unrollAndDumpExpandedFromNumeric(const std::string &dumpPath);
} // namespace ddd
