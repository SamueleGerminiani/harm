// H17, acceptance test A4 (D-030): a --check-dump-eval file that cannot be opened gives a warning
// and "file": null in the index; the run continues. The dump directory is a regular file, so the
// open fails for every user, root included (a read-only directory would not stop root).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "message.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

TEST(CheckDumpTest, unopenableFileIsNullInTheIndex) {
  std::vector<VarDeclaration> decls = {{"a", ExpType::Bool, 1}, {"c", ExpType::Bool, 1}};
  TracePtr tr = generatePtr<Trace>(decls, 3);
  for (size_t t = 0; t < 3; t++) {
    tr->getBooleanVariable("a")->assign(t, t != 1);
    tr->getBooleanVariable("c")->assign(t, t != 2);
  }

  auto notADir = std::filesystem::temp_directory_path() / "harm_h17_check_dump_not_a_dir";
  std::ofstream(notADir) << "a regular file\n";
  clc::checkDumpEvalDirectory = notADir.string();
  hs::checkDumpEvalIndex.clear();

  hlog::ScopedThrowOnError throwOnError; // an exit would throw here instead
  for (std::string f : {"G(a -> c)", "G(c -> a)"}) {
    TemplateImplicationPtr ti = hparser::parseTemplateImplication(f, tr, DTLimits(), false);
    ASSERT_NO_THROW(ti->check("ctx")) << f;
  }

  ASSERT_EQ(hs::checkDumpEvalIndex.size(), 2u);
  EXPECT_EQ(hs::checkDumpEvalIndex[0], "    {\"file\": null, \"context\": \"ctx\", \"spot\": "
                                       "\"G(a -> c)\", \"sva\": \"always (a |-> c)\"}");
  EXPECT_EQ(hs::checkDumpEvalIndex[1], "    {\"file\": null, \"context\": \"ctx\", \"spot\": "
                                       "\"G(c -> a)\", \"sva\": \"always (c |-> a)\"}");
  EXPECT_TRUE(std::filesystem::is_regular_file(notADir));

  clc::checkDumpEvalDirectory = "";
  hs::checkDumpEvalIndex.clear();
  std::filesystem::remove(notADir);
}
