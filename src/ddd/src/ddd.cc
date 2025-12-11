#include "ddd.hh"
#include "Location.hh"
#include "globals.hh"
#include "message.hh"
#include <SQLiteCpp/SQLiteCpp.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

namespace ddd {

std::shared_ptr<SQLite::Database> db = nullptr;
std::mutex dbMutex;

void createDebugDB() {
  std::lock_guard<std::mutex> lock(dbMutex);

  try {
    // Open a database file in read/write mode
    db = std::make_shared<SQLite::Database>(
        clc::debugDataPath + "/data.db",
        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  } catch (const std::exception &e) {
    messageError("Error opening database: " + clc::debugDataPath +
                 "/data.db " + std::string(e.what()));
  }

  const char *sqlContext = "CREATE TABLE IF NOT EXISTS Context ("
                           "id INTEGER PRIMARY KEY,"
                           "name TEXT NOT NULL"
                           ");";

  const char *sqlProposition =
      "CREATE TABLE IF NOT EXISTS Proposition ("
      "id INTEGER PRIMARY KEY,"
      "context_id INTEGER NOT NULL,"
      "exp TEXT NOT NULL,"
      "FOREIGN KEY(context_id) REFERENCES Context(id)"
      ");";

  const char *sqlNumeric =
      "CREATE TABLE IF NOT EXISTS Numeric ("
      "id INTEGER PRIMARY KEY,"
      "context_id INTEGER NOT NULL,"
      "exp TEXT NOT NULL,"
      "FOREIGN KEY(context_id) REFERENCES Context(id)"
      ");";

  //  const char *sqlClustering =
  //      "CREATE TABLE IF NOT EXISTS Clustering ("
  //      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
  //      "numeric_id INTEGER NOT NULL,"
  //      "option TEXT NOT NULL,"
  //      "value TEXT NOT NULL,"
  //      "FOREIGN KEY(numeric_id) REFERENCES Numeric(id)"
  //      ");";

  const char *sqlExpandedFromNumeric =
      "CREATE TABLE IF NOT EXISTS ExpandedFromNumeric ("
      "proposition_id INTEGER NOT NULL,"
      "numeric_id INTEGER NOT NULL,"
      "from_decision_tree TEXT NOT NULL,"
      "path_to_clustering_values TEXT NOT NULL,"
      "PRIMARY KEY(proposition_id, numeric_id),"
      "FOREIGN KEY(proposition_id) REFERENCES Proposition(id),"
      "FOREIGN KEY(numeric_id) REFERENCES Numeric(id)"
      ");";

  //  const char *sqlMetric =
  //      "CREATE TABLE IF NOT EXISTS Metric ("
  //      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
  //      "context_id INTEGER NOT NULL,"
  //      "type TEXT NOT NULL,"
  //      "name TEXT NOT NULL,"
  //      "exp TEXT NOT NULL,"
  //      "FOREIGN KEY(context_id) REFERENCES Context(id)"
  //      ");";

  const char *sqlTemplate =
      "CREATE TABLE IF NOT EXISTS Template ("
      "id INTEGER PRIMARY KEY,"
      "context_id INTEGER NOT NULL,"
      "exp TEXT NOT NULL,"
      "FOREIGN KEY(context_id) REFERENCES Context(id)"
      ");";

  const char *sqlPlaceholder =
      "CREATE TABLE IF NOT EXISTS Placeholder ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "template_id INTEGER NOT NULL,"
      "token TEXT NOT NULL,"
      "location TEXT NOT NULL,"
      "FOREIGN KEY(template_id) REFERENCES Template(id)"
      ");";

  //  const char *sqlDTLimits =
  //      "CREATE TABLE IF NOT EXISTS DTLimits ("
  //      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
  //      "template_id INTEGER NOT NULL,"
  //      "option TEXT NOT NULL,"
  //      "value TEXT NOT NULL,"
  //      "FOREIGN KEY(template_id) REFERENCES Template(id)"
  //      ");";

  const char *sqlPermutation =
      "CREATE TABLE IF NOT EXISTS Permutation ("
      "template_id INTEGER NOT NULL,"
      "number INTEGER NOT NULL,"
      "exp TEXT NOT NULL,"
      "decision_tree_path TEXT,"
      "PRIMARY KEY(template_id, number),"
      "FOREIGN KEY(template_id) REFERENCES Template(id)"
      ");";

  const char *sqlDomain = "CREATE TABLE IF NOT EXISTS Domain ("
                          "id INTEGER PRIMARY KEY,"
                          "type TEXT NOT NULL,"
                          "label TEXT NOT NULL"
                          ");";

  const char *sqlExpDomain =
      "CREATE TABLE IF NOT EXISTS ExpDomain ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "type TEXT NOT NULL,"
      "prop_or_numeric_or_placeholder_id INTEGER NOT NULL,"
      "domain_id INTEGER NOT NULL,"
      "FOREIGN KEY(domain_id) REFERENCES Domain(id)"
      ");";

  const char *sqlAssertion =
      "CREATE TABLE IF NOT EXISTS Assertion ("
      "id INTEGER PRIMARY KEY, "
      "template_id INTEGER NOT NULL,"
      "perm_number INTEGER NOT NULL,"
      "exp TEXT NOT NULL,"
      "note TEXT,"
      "FOREIGN KEY(template_id) REFERENCES Template(id),"
      "FOREIGN KEY (perm_number) REFERENCES Permutation(number));";

  const char *sqlContingencyTable =
      "CREATE TABLE IF NOT EXISTS ContingencyTable ("
      "assertion_id INTEGER PRIMARY KEY, "
      "ATCT INTEGER NOT NULL, "
      "ATCF INTEGER NOT NULL, "
      "ATCU INTEGER NOT NULL, "
      "AFCT INTEGER NOT NULL, "
      "AFCF INTEGER NOT NULL, "
      "AFCU INTEGER NOT NULL, "
      "AUCT INTEGER NOT NULL, "
      "AUCF INTEGER NOT NULL, "
      "AUCU INTEGER NOT NULL, "
      "FOREIGN KEY (assertion_id) REFERENCES Assertion(id));";

  const char *tableCreationQueries[] = {
      sqlContext,         sqlProposition,
      sqlNumeric,         sqlExpandedFromNumeric,
      sqlTemplate,        sqlPlaceholder,
      sqlPermutation,     sqlDomain,
      sqlExpDomain,       sqlAssertion,
      sqlContingencyTable
      //,sqlClustering,
      //sqlMetric,
      //sqlDTLimits,

  };

  try {
    for (const char *query : tableCreationQueries) {
      db->exec(query);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error creating tables: " << e.what() << std::endl;
  }
}

void addContext(void *id, const std::string &name) {
  std::lock_guard<std::mutex> lock(dbMutex);
  try {
    SQLite::Statement query(
        *db, "INSERT INTO Context (id,name) VALUES (?,?)");
    query.bind(1, reinterpret_cast<int64_t>(id));
    query.bind(2, name);
    query.exec();
  } catch (const std::exception &e) {
    std::cerr << "Error adding context: " << e.what() << std::endl;
  }
}

int64_t getContextId(const std::string &name) {

  try {
    SQLite::Statement query(*db,
                            "SELECT id FROM Context WHERE name = ?");
    query.bind(
        1,
        name); // Bind the name to the first (and only) parameter in the SQL statement

    if (query.executeStep()) {
      return (int64_t)query.getColumn(0).getInt64();
    } else {
      std::cerr << "Context not found: " << name << std::endl;
      return -1;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error retrieving context ID: " << e.what()
              << std::endl;
    return -1;
  }
}

void addTemplate(
    void *id, const std::string &context_name, const std::string &exp,
    const std::unordered_map<
        std::string, std::pair<std::string, std::unordered_set<int>>>
        &placeholderData) {
  int64_t context_id = getContextId(context_name);
  if (context_id == -1) {
    std::cerr << "Failed to add template due to missing context: "
              << context_name << std::endl;
    return;
  }

  std::lock_guard<std::mutex> lock(dbMutex);

  try {
    SQLite::Transaction transaction(*db);

    // Insert into Template table
    SQLite::Statement templateQuery(
        *db,
        "INSERT INTO Template (id,context_id, exp) VALUES (?, ?, ?)");
    templateQuery.bind(1, reinterpret_cast<int64_t>(id));
    templateQuery.bind(2, context_id);
    templateQuery.bind(3, exp);
    if (!templateQuery.exec()) {
      std::cerr << "Error executing template query: "
                << db->getErrorMsg() << std::endl;
      return;
    }

    // Insert into Domain table and prepare for ExpDomain insertion
    SQLite::Statement domainQuery(*db,
                                  "INSERT OR IGNORE INTO Domain (id, "
                                  "type, label) VALUES (?, ?, ?)");
    SQLite::Statement getDomainIdQuery(
        *db, "SELECT id FROM Domain WHERE id = ?");
    SQLite::Statement expDomainQuery(
        *db, "INSERT INTO ExpDomain (type, "
             "prop_or_numeric_or_placeholder_id, "
             "domain_id) VALUES (?, ?, ?)");

    // Process each placeholder in placeholderData
    for (const auto &entry : placeholderData) {
      const std::string &token = entry.first;
      const std::string &location = entry.second.first;
      const std::unordered_set<int> &domainSet = entry.second.second;

      // Insert Placeholder into Placeholder table
      SQLite::Statement placeholderQuery(
          *db, "INSERT INTO Placeholder (template_id, token, "
               "location) VALUES (?, ?, ?)");
      placeholderQuery.bind(1, reinterpret_cast<int64_t>(id));
      placeholderQuery.bind(2, token);
      placeholderQuery.bind(3, location);
      if (!placeholderQuery.exec()) {
        std::cerr << "Error executing placeholder query: "
                  << db->getErrorMsg() << std::endl;
        return;
      }

      int placeholderId = static_cast<int>(db->getLastInsertRowid());

      // Process domains for the current placeholder
      for (int domainId : domainSet) {
        // Insert domain into Domain table if it doesn't exist
        getDomainIdQuery.reset();
        getDomainIdQuery.bind(1, domainId);
        if (getDomainIdQuery.executeStep()) {
          // Domain already exists, retrieve its ID
          int domainId = getDomainIdQuery.getColumn(0).getInt64();

          // Insert into ExpDomain with type "Placeholder"
          expDomainQuery.reset();
          expDomainQuery.bind(1, "Placeholder");
          expDomainQuery.bind(2, placeholderId);
          expDomainQuery.bind(3, domainId);
          if (!expDomainQuery.exec()) {
            std::cerr << "Error executing expDomain query: "
                      << db->getErrorMsg() << std::endl;
            return;
          }
        } else {
          // Domain doesn't exist, insert into Domain table
          domainQuery.reset();
          domainQuery.bind(1, domainId);
          domainQuery.bind(2, harm::getDomainType(domainId));
          domainQuery.bind(3, harm::domainIdToString(domainId));
          if (!domainQuery.exec()) {
            std::cerr << "Error executing domain query: "
                      << db->getErrorMsg() << std::endl;
            return;
          }

          int domainId = static_cast<int>(db->getLastInsertRowid());

          // Insert into ExpDomain with type "Placeholder"
          expDomainQuery.reset();
          expDomainQuery.bind(1, "Placeholder");
          expDomainQuery.bind(2, placeholderId);
          expDomainQuery.bind(3, domainId);
          if (!expDomainQuery.exec()) {
            std::cerr << "Error executing expDomain query: "
                      << db->getErrorMsg() << std::endl;
            return;
          }
        }
      }
    }

    transaction.commit();

  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error adding template: " << e.what() << std::endl;
  }
}

int64_t addProposition(void *id, const std::string &context_name,
                       const std::string &exp,
                       const std::vector<int> &domain_tokens,
                       SQLite::Transaction *transaction) {
  int64_t context_id = getContextId(context_name);
  if (context_id == -1) {
    std::cerr << "Failed to add proposition due to missing context: "
              << context_name << std::endl;
    return -1;
  }

  bool localTransaction = false;
  try {
    if (!transaction) {
      dbMutex.lock();
      transaction = new SQLite::Transaction(*db);
      localTransaction = true;
    }

    SQLite::Statement propositionQuery(
        *db, "INSERT INTO Proposition (id, context_id, "
             "exp) VALUES "
             "(?, ?, ?)");
    propositionQuery.bind(1, reinterpret_cast<int64_t>(id));
    propositionQuery.bind(2, context_id);
    propositionQuery.bind(3, exp);
    propositionQuery.exec();

    SQLite::Statement getDomainIdQuery(
        *db, "SELECT id FROM Domain WHERE id = ?");
    SQLite::Statement domainQuery(*db,
                                  "INSERT OR IGNORE INTO Domain (id, "
                                  "type, label) VALUES (?, ?, ?)");
    SQLite::Statement expDomainQuery(
        *db,
        "INSERT INTO ExpDomain (prop_or_numeric_or_placeholder_id, "
        "domain_id, type) VALUES (?, ?, 'Proposition')");

    for (const auto &domain_id : domain_tokens) {
      getDomainIdQuery.reset();
      domainQuery.reset();
      expDomainQuery.reset();
      int64_t domainId = -1;
      getDomainIdQuery.bind(1, domain_id);

      if (getDomainIdQuery.executeStep()) {
        domainId = getDomainIdQuery.getColumn(0).getInt64();
      } else {
        domainQuery.bind(1, domain_id);
        domainQuery.bind(2, harm::getDomainType(domain_id));
        domainQuery.bind(3, harm::domainIdToString(domain_id));
        domainQuery.exec();
        domainId = static_cast<int64_t>(db->getLastInsertRowid());
      }

      expDomainQuery.bind(1, reinterpret_cast<int64_t>(id));
      expDomainQuery.bind(2, domainId);
      expDomainQuery.exec();
    }

    if (localTransaction) {
      transaction->commit();
      delete transaction;
      dbMutex.unlock();
    }

    return reinterpret_cast<int64_t>(id);
  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
    if (localTransaction) {
      delete transaction;
      dbMutex.unlock();
    }
    return -1;
  } catch (const std::exception &e) {
    std::cerr << "Error inserting proposition: " << e.what()
              << std::endl;
    if (localTransaction) {
      delete transaction;
      dbMutex.unlock();
    }
    return -1;
  }
}

int64_t addNumeric(void *id, const std::string &context_name,
                   const std::string &exp,
                   const std::vector<int> &domain_tokens,
                   SQLite::Transaction *transaction) {
  int64_t context_id = getContextId(context_name);
  if (context_id == -1) {
    std::cerr << "Failed to add numeric due to missing context: "
              << context_name << std::endl;
    return -1;
  }

  bool localTransaction = false;
  try {
    if (!transaction) {
      transaction = new SQLite::Transaction(*db);
      localTransaction = true;
      dbMutex.lock();
    }

    SQLite::Statement numericQuery(
        *db, "INSERT OR IGNORE INTO Numeric (id,context_id, exp) "
             "VALUES (?, ?, ?)");
    numericQuery.bind(1, reinterpret_cast<int64_t>(id));
    numericQuery.bind(2, context_id);
    numericQuery.bind(3, exp);
    numericQuery.exec();

    SQLite::Statement getDomainIdQuery(
        *db, "SELECT id FROM Domain WHERE id = ?");
    SQLite::Statement domainQuery(
        *db, "INSERT OR IGNORE INTO Domain (id, type, label) "
             "VALUES (?, ?, ?)");
    SQLite::Statement expDomainQuery(
        *db,
        "INSERT INTO ExpDomain (prop_or_numeric_or_placeholder_id, "
        "domain_id, type) VALUES (?, ?, 'Numeric')");

    for (const auto &domain_token : domain_tokens) {
      getDomainIdQuery.reset();
      domainQuery.reset();
      expDomainQuery.reset();
      int domainId = -1;
      getDomainIdQuery.bind(1, domain_token);

      if (getDomainIdQuery.executeStep()) {
        domainId = getDomainIdQuery.getColumn(0).getInt64();
      } else {
        domainQuery.bind(1, domain_token);
        domainQuery.bind(2, harm::getDomainType(domain_token));
        domainQuery.bind(3, harm::domainIdToString(domain_token));
        domainQuery.exec();
        domainId = static_cast<int>(db->getLastInsertRowid());
      }

      expDomainQuery.bind(1, reinterpret_cast<int64_t>(id));
      expDomainQuery.bind(2, domainId);
      expDomainQuery.exec();
    }

    if (localTransaction) {
      transaction->commit();
      delete transaction;
      dbMutex.unlock();
    }

    return reinterpret_cast<int64_t>(id);
  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
    if (localTransaction) {
      delete transaction;
      dbMutex.unlock();
    }
    return -1;
  } catch (const std::exception &e) {
    std::cerr << "Error inserting numeric: " << e.what() << std::endl;
    if (localTransaction) {
      delete transaction;
      dbMutex.unlock();
    }
    return -1;
  }
}
std::string getContextNameFromNumeric(void *numeric_id) {
  std::lock_guard<std::mutex> lock(dbMutex);
  try {
    // SQL query to join Numeric and Context tables and retrieve the context name
    SQLite::Statement query(
        *db, "SELECT Context.name FROM Numeric JOIN Context ON "
             "Numeric.context_id = Context.id WHERE Numeric.id = ?");
    query.bind(1, reinterpret_cast<int64_t>(numeric_id));

    if (query.executeStep()) {
      // Retrieve and return the context name
      return query.getColumn(0).getText();
    } else {
      std::cerr << "Numeric ID not found: "
                << reinterpret_cast<int64_t>(numeric_id) << std::endl;
      return "";
    }
  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
    return "";
  } catch (const std::exception &e) {
    std::cerr << "Error retrieving context name: " << e.what()
              << std::endl;
    return "";
  }
}

int64_t addNumericWithExpansion(
    void *id, std::string context_name, const std::string &exp,
    const std::vector<int> &domain_tokens,
    const std::vector<std::pair<void *, std::string>> &propositions,
    const std::string &path_to_clustering_values, bool inDT) {

  if (context_name == "") {
    context_name = getContextNameFromNumeric(id);
  }

  std::lock_guard<std::mutex> lock(dbMutex);

  try {
    SQLite::Transaction transaction(*db);

    int64_t numeric_id = addNumeric(id, context_name, exp,
                                    domain_tokens, &transaction);
    if (numeric_id == -1) {
      return -1;
    }

    SQLite::Statement expandedFromNumericQuery(
        *db,
        "INSERT INTO ExpandedFromNumeric (proposition_id, "
        "numeric_id, path_to_clustering_values,from_decision_tree) "
        "VALUES (?, ?, ?, ?)");

    for (const auto &[id, prop] : propositions) {
      int64_t proposition_id = addProposition(
          id, context_name, prop, domain_tokens, &transaction);

      if (proposition_id == -1) {
        std::cerr
            << "addNumericWithExpansion, Failed to add proposition: "
            << prop << std::endl;
        continue;
      }

      expandedFromNumericQuery.reset();
      expandedFromNumericQuery.bind(1, proposition_id);
      expandedFromNumericQuery.bind(2, numeric_id);
      expandedFromNumericQuery.bind(3, path_to_clustering_values);
      expandedFromNumericQuery.bind(4, inDT ? "Yes" : "No");

      expandedFromNumericQuery.exec();
    }

    transaction.commit();

    return numeric_id;
  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
    return -1;
  } catch (const std::exception &e) {
    std::cerr << "Error adding numeric expression with expansion: "
              << e.what() << std::endl;
    return -1;
  }
}

void addPermutation(void *template_id, int number,
                    const std::string &exp) {
  std::lock_guard<std::mutex> lock(dbMutex);
  try {
    SQLite::Transaction transaction(*db);

    SQLite::Statement query(*db,
                            "INSERT INTO Permutation (template_id, "
                            "number, exp, decision_tree_path) VALUES "
                            "(?, ?, ?,'Not used')");
    query.bind(1, reinterpret_cast<int64_t>(template_id));
    query.bind(2, number);
    query.bind(3, exp);
    query.exec();

    transaction.commit();

  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error adding permutation: " << e.what()
              << std::endl;
  }
}
void addDecisionTree(void *template_id, int number,
                     const std::string &decision_tree_path) {
  std::lock_guard<std::mutex> lock(dbMutex);
  try {
    SQLite::Transaction transaction(*db);

    SQLite::Statement query(
        *db, "UPDATE Permutation SET decision_tree_path = ? WHERE "
             "template_id = ? AND number = ?");
    query.bind(1, decision_tree_path);
    query.bind(2, reinterpret_cast<int64_t>(template_id));
    query.bind(3, number);
    query.exec();

    transaction.commit();

  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error adding decision tree path: " << e.what()
              << std::endl;
  }
}
void addAssertion(void *id, void *template_id, int perm_number,
                  const std::string &exp, const std::string &note) {
  std::lock_guard<std::mutex> lock(dbMutex);
  try {
    SQLite::Transaction transaction(*db);

    SQLite::Statement query(*db,
                            "INSERT INTO Assertion (id, template_id, "
                            "perm_number, exp, "
                            "note) VALUES (?, ?, ?, ?, ?)");
    query.bind(1, reinterpret_cast<int64_t>(id));
    query.bind(2, reinterpret_cast<int64_t>(template_id));
    query.bind(3, perm_number);
    query.bind(4, exp);
    query.bind(5, note);
    query.exec();

    transaction.commit();

  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error adding assertion: " << e.what() << std::endl;
  }
}
void addContingency(void *assertion_id,
                    const size_t contingencyTable[3][3]) {
  std::lock_guard<std::mutex> lock(dbMutex);
  try {
    SQLite::Transaction transaction(*db);

    SQLite::Statement query(
        *db, "INSERT INTO ContingencyTable (assertion_id, ATCT, "
             "ATCF, ATCU, AFCT, AFCF, AFCU, AUCT, AUCF, AUCU) VALUES "
             "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.bind(1, reinterpret_cast<int64_t>(assertion_id));
    query.bind(2, (int64_t)contingencyTable[0][0]);
    query.bind(3, (int64_t)contingencyTable[0][1]);
    query.bind(4, (int64_t)contingencyTable[0][2]);
    query.bind(5, (int64_t)contingencyTable[1][0]);
    query.bind(6, (int64_t)contingencyTable[1][1]);
    query.bind(7, (int64_t)contingencyTable[1][2]);
    query.bind(8, (int64_t)contingencyTable[2][0]);
    query.bind(9, (int64_t)contingencyTable[2][1]);
    query.bind(10, (int64_t)contingencyTable[2][2]);
    query.exec();

    transaction.commit();

  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error adding contingency table: " << e.what()
              << std::endl;
  }
}

void removeAssertion(void *assertion_id) {
  std::lock_guard<std::mutex> lock(dbMutex);
  try {
    SQLite::Transaction transaction(*db);

    int64_t id = reinterpret_cast<int64_t>(assertion_id);

    // Remove from ContingencyTable
    SQLite::Statement deleteContingency(
        *db, "DELETE FROM ContingencyTable WHERE assertion_id = ?");
    deleteContingency.bind(1, id);
    deleteContingency.exec();

    // Remove from Assertion
    SQLite::Statement deleteAssertion(
        *db, "DELETE FROM Assertion WHERE id = ?");
    deleteAssertion.bind(1, id);
    deleteAssertion.exec();

    transaction.commit();

  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error removing assertion: " << e.what()
              << std::endl;
  }
}

void appendNote(void *assertion_id, const std::string &text) {
  std::lock_guard<std::mutex> lock(dbMutex);
  try {
    SQLite::Transaction transaction(*db);

    int64_t id = reinterpret_cast<int64_t>(assertion_id);

    // Fetch existing note
    SQLite::Statement selectQuery(
        *db, "SELECT note FROM Assertion WHERE id = ?");
    selectQuery.bind(1, id);
    std::string currentNote;

    if (selectQuery.executeStep()) {
      currentNote = selectQuery.getColumn(0).getString();
    }

    if (currentNote != "") {
      currentNote += ", ";
    }
    // Append new text to the existing note
    currentNote += text;

    // Update the note
    SQLite::Statement updateQuery(
        *db, "UPDATE Assertion SET note = ? WHERE id = ?");
    updateQuery.bind(1, currentNote);
    updateQuery.bind(2, id);
    updateQuery.exec();

    transaction.commit();

  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error appending to note: " << e.what() << std::endl;
  }
}
void unrollAndDumpAssertion(const std::string &dumpPath) {
  try {
    SQLite::Statement query(
        *db, "SELECT "
             "Assertion.exp, Assertion.note, "
             "Context.name, "
             "Permutation.exp, Permutation.decision_tree_path, "
             "ContingencyTable.ATCT, ContingencyTable.ATCF, "
             "ContingencyTable.ATCU, "
             "ContingencyTable.AFCT, ContingencyTable.AFCF, "
             "ContingencyTable.AFCU, "
             "ContingencyTable.AUCT, ContingencyTable.AUCF, "
             "ContingencyTable.AUCU "
             "FROM Assertion "
             "JOIN Permutation ON Assertion.template_id = "
             "Permutation.template_id AND Assertion.perm_number = "
             "Permutation.number "
             "JOIN Template ON Permutation.template_id = Template.id "
             "JOIN Context ON Template.context_id = Context.id "
             "JOIN ContingencyTable ON Assertion.id = "
             "ContingencyTable.assertion_id");

    std::ofstream file(dumpPath);
    if (!file.is_open()) {
      std::cerr << "Error opening file: " << dumpPath << std::endl;
      return;
    }

    file << "AssertionExp,Note,Context,PermutationExp,"
            "DecisionTreePath,"
            "ATCT,ATCF,ATCU,AFCT,AFCF,AFCU,AUCT,AUCF,AUCU\n";

    while (query.executeStep()) {
      file << query.getColumn(0).getText() << ","
           << query.getColumn(1).getText() << ","
           << query.getColumn(2).getText() << ","
           << query.getColumn(3).getText() << ","
           << query.getColumn(4).getText() << ","
           << query.getColumn(5).getInt() << ","
           << query.getColumn(6).getInt() << ","
           << query.getColumn(7).getInt() << ","
           << query.getColumn(8).getInt() << ","
           << query.getColumn(9).getInt() << ","
           << query.getColumn(10).getInt() << ","
           << query.getColumn(11).getInt() << ","
           << query.getColumn(12).getInt() << ","
           << query.getColumn(13).getInt() << "\n";
    }

    file.close();
  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error during unroll and dump: " << e.what()
              << std::endl;
  }
}
void unrollAndDumpExpandedFromNumeric(const std::string &dumpPath) {
  try {
    SQLite::Statement query(
        *db,
        "SELECT "
        "Numeric.exp, "
        "GROUP_CONCAT(Proposition.exp, ';') AS propositions, "
        "ExpandedFromNumeric.from_decision_tree, "
        "ExpandedFromNumeric.path_to_clustering_values "
        "FROM ExpandedFromNumeric "
        "JOIN Proposition ON ExpandedFromNumeric.proposition_id = "
        "Proposition.id "
        "JOIN Numeric ON ExpandedFromNumeric.numeric_id = Numeric.id "
        "GROUP BY Numeric.exp, "
        "ExpandedFromNumeric.from_decision_tree, "
        "ExpandedFromNumeric.path_to_clustering_values");

    std::ofstream file(dumpPath);
    if (!file.is_open()) {
      std::cerr << "Error opening file: " << dumpPath << std::endl;
      return;
    }

    file << "NumericExp,Propositions,FromDecisionTree,"
            "PathToClusteringValues\n";

    while (query.executeStep()) {
      file << query.getColumn(0).getText() << ","
           << query.getColumn(1).getText() << ","
           << query.getColumn(2).getText() << ","
           << query.getColumn(3).getText() << "\n";
    }

    file.close();
  } catch (const SQLite::Exception &e) {
    std::cerr << "SQLite error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error during unroll and dump: " << e.what()
              << std::endl;
  }
}

} // namespace ddd
