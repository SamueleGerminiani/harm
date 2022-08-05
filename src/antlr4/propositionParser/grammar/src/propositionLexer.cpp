
// Generated from proposition.g4 by ANTLR 4.10.1

#include "propositionLexer.h"

using namespace antlr4;

using namespace antlr4;

namespace {

struct PropositionLexerStaticData final {
  PropositionLexerStaticData(std::vector<std::string> ruleNames,
                             std::vector<std::string> channelNames,
                             std::vector<std::string> modeNames,
                             std::vector<std::string> literalNames,
                             std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PropositionLexerStaticData(const PropositionLexerStaticData &) = delete;
  PropositionLexerStaticData(PropositionLexerStaticData &&) = delete;
  PropositionLexerStaticData &
  operator=(const PropositionLexerStaticData &) = delete;
  PropositionLexerStaticData &operator=(PropositionLexerStaticData &&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag propositionlexerLexerOnceFlag;
PropositionLexerStaticData *propositionlexerLexerStaticData = nullptr;

void propositionlexerLexerInitialize() {
  assert(propositionlexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<PropositionLexerStaticData>(
      std::vector<std::string>{"T__0",
                               "T__1",
                               "T__2",
                               "T__3",
                               "T__4",
                               "T__5",
                               "SIGN",
                               "LGPAREN",
                               "RGPAREN",
                               "LCPAREN",
                               "RCPAREN",
                               "LPAREN",
                               "RPAREN",
                               "VARIABLE",
                               "VALID_ID_START",
                               "VALID_ID_CHAR",
                               "NUMERIC",
                               "VERILOG_BINARY",
                               "GCC_BINARY",
                               "HEX",
                               "BOOLEAN",
                               "PLUS",
                               "MINUS",
                               "TIMES",
                               "DIV",
                               "GT",
                               "GE",
                               "LT",
                               "LE",
                               "EQ",
                               "NEQ",
                               "BAND",
                               "BOR",
                               "BXOR",
                               "NEG",
                               "LSHIFT",
                               "RSHIFT",
                               "AND",
                               "OR",
                               "NOT",
                               "WS"},
      std::vector<std::string>{"DEFAULT_TOKEN_CHANNEL", "HIDDEN"},
      std::vector<std::string>{"DEFAULT_MODE"},
      std::vector<std::string>{"",
                               "',bool>'",
                               "':'",
                               "',logic('",
                               "','",
                               "')>'",
                               "',numeric('",
                               "",
                               "'{'",
                               "'}'",
                               "'['",
                               "']'",
                               "'('",
                               "')'",
                               "",
                               "",
                               "",
                               "",
                               "",
                               "",
                               "'+'",
                               "'-'",
                               "'*'",
                               "'/'",
                               "'>'",
                               "'>='",
                               "'<'",
                               "'<='",
                               "'=='",
                               "'!='",
                               "'&'",
                               "'|'",
                               "'^'",
                               "'~'",
                               "'<<'",
                               "'>>'",
                               "'&&'",
                               "'||'",
                               "'!'"},
      std::vector<std::string>{"",
                               "",
                               "",
                               "",
                               "",
                               "",
                               "",
                               "SIGN",
                               "LGPAREN",
                               "RGPAREN",
                               "LCPAREN",
                               "RCPAREN",
                               "LPAREN",
                               "RPAREN",
                               "VARIABLE",
                               "NUMERIC",
                               "VERILOG_BINARY",
                               "GCC_BINARY",
                               "HEX",
                               "BOOLEAN",
                               "PLUS",
                               "MINUS",
                               "TIMES",
                               "DIV",
                               "GT",
                               "GE",
                               "LT",
                               "LE",
                               "EQ",
                               "NEQ",
                               "BAND",
                               "BOR",
                               "BXOR",
                               "NEG",
                               "LSHIFT",
                               "RSHIFT",
                               "AND",
                               "OR",
                               "NOT",
                               "WS"});
  static const int32_t serializedATNSegment[] = {
      4,   0,   39,  266, 6,   -1,  2,   0,   7,   0,   2,   1,   7,   1,   2,
      2,   7,   2,   2,   3,   7,   3,   2,   4,   7,   4,   2,   5,   7,   5,
      2,   6,   7,   6,   2,   7,   7,   7,   2,   8,   7,   8,   2,   9,   7,
      9,   2,   10,  7,   10,  2,   11,  7,   11,  2,   12,  7,   12,  2,   13,
      7,   13,  2,   14,  7,   14,  2,   15,  7,   15,  2,   16,  7,   16,  2,
      17,  7,   17,  2,   18,  7,   18,  2,   19,  7,   19,  2,   20,  7,   20,
      2,   21,  7,   21,  2,   22,  7,   22,  2,   23,  7,   23,  2,   24,  7,
      24,  2,   25,  7,   25,  2,   26,  7,   26,  2,   27,  7,   27,  2,   28,
      7,   28,  2,   29,  7,   29,  2,   30,  7,   30,  2,   31,  7,   31,  2,
      32,  7,   32,  2,   33,  7,   33,  2,   34,  7,   34,  2,   35,  7,   35,
      2,   36,  7,   36,  2,   37,  7,   37,  2,   38,  7,   38,  2,   39,  7,
      39,  2,   40,  7,   40,  1,   0,   1,   0,   1,   0,   1,   0,   1,   0,
      1,   0,   1,   0,   1,   1,   1,   1,   1,   2,   1,   2,   1,   2,   1,
      2,   1,   2,   1,   2,   1,   2,   1,   2,   1,   3,   1,   3,   1,   4,
      1,   4,   1,   4,   1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,
      5,   1,   5,   1,   5,   1,   5,   1,   5,   1,   6,   1,   6,   1,   7,
      1,   7,   1,   8,   1,   8,   1,   9,   1,   9,   1,   10,  1,   10,  1,
      11,  1,   11,  1,   12,  1,   12,  1,   13,  1,   13,  3,   13,  132, 8,
      13,  1,   13,  1,   13,  5,   13,  136, 8,   13,  10,  13,  12,  13,  139,
      9,   13,  1,   14,  1,   14,  3,   14,  143, 8,   14,  1,   14,  3,   14,
      146, 8,   14,  3,   14,  148, 8,   14,  1,   15,  1,   15,  1,   15,  3,
      15,  153, 8,   15,  1,   16,  3,   16,  156, 8,   16,  1,   16,  4,   16,
      159, 8,   16,  11,  16,  12,  16,  160, 1,   16,  1,   16,  4,   16,  165,
      8,   16,  11,  16,  12,  16,  166, 3,   16,  169, 8,   16,  1,   17,  1,
      17,  1,   17,  4,   17,  174, 8,   17,  11,  17,  12,  17,  175, 1,   18,
      1,   18,  1,   18,  1,   18,  4,   18,  182, 8,   18,  11,  18,  12,  18,
      183, 1,   19,  1,   19,  1,   19,  1,   19,  4,   19,  190, 8,   19,  11,
      19,  12,  19,  191, 1,   19,  1,   19,  1,   19,  1,   19,  4,   19,  198,
      8,   19,  11,  19,  12,  19,  199, 3,   19,  202, 8,   19,  1,   20,  1,
      20,  1,   20,  1,   20,  1,   20,  1,   20,  1,   20,  1,   20,  1,   20,
      1,   20,  1,   20,  3,   20,  215, 8,   20,  1,   21,  1,   21,  1,   22,
      1,   22,  1,   23,  1,   23,  1,   24,  1,   24,  1,   25,  1,   25,  1,
      26,  1,   26,  1,   26,  1,   27,  1,   27,  1,   28,  1,   28,  1,   28,
      1,   29,  1,   29,  1,   29,  1,   30,  1,   30,  1,   30,  1,   31,  1,
      31,  1,   32,  1,   32,  1,   33,  1,   33,  1,   34,  1,   34,  1,   35,
      1,   35,  1,   35,  1,   36,  1,   36,  1,   36,  1,   37,  1,   37,  1,
      37,  1,   38,  1,   38,  1,   38,  1,   39,  1,   39,  1,   40,  1,   40,
      1,   40,  1,   40,  0,   0,   41,  1,   1,   3,   2,   5,   3,   7,   4,
      9,   5,   11,  6,   13,  7,   15,  8,   17,  9,   19,  10,  21,  11,  23,
      12,  25,  13,  27,  14,  29,  0,   31,  0,   33,  15,  35,  16,  37,  17,
      39,  18,  41,  19,  43,  20,  45,  21,  47,  22,  49,  23,  51,  24,  53,
      25,  55,  26,  57,  27,  59,  28,  61,  29,  63,  30,  65,  31,  67,  32,
      69,  33,  71,  34,  73,  35,  75,  36,  77,  37,  79,  38,  81,  39,  1,
      0,   7,   2,   0,   115, 115, 117, 117, 3,   0,   65,  90,  95,  95,  97,
      122, 5,   0,   65,  79,  81,  87,  89,  90,  95,  95,  97,  122, 5,   0,
      46,  46,  48,  57,  65,  90,  95,  95,  97,  122, 2,   0,   48,  57,  97,
      102, 2,   0,   48,  57,  65,  70,  3,   0,   9,   10,  13,  13,  32,  32,
      277, 0,   1,   1,   0,   0,   0,   0,   3,   1,   0,   0,   0,   0,   5,
      1,   0,   0,   0,   0,   7,   1,   0,   0,   0,   0,   9,   1,   0,   0,
      0,   0,   11,  1,   0,   0,   0,   0,   13,  1,   0,   0,   0,   0,   15,
      1,   0,   0,   0,   0,   17,  1,   0,   0,   0,   0,   19,  1,   0,   0,
      0,   0,   21,  1,   0,   0,   0,   0,   23,  1,   0,   0,   0,   0,   25,
      1,   0,   0,   0,   0,   27,  1,   0,   0,   0,   0,   33,  1,   0,   0,
      0,   0,   35,  1,   0,   0,   0,   0,   37,  1,   0,   0,   0,   0,   39,
      1,   0,   0,   0,   0,   41,  1,   0,   0,   0,   0,   43,  1,   0,   0,
      0,   0,   45,  1,   0,   0,   0,   0,   47,  1,   0,   0,   0,   0,   49,
      1,   0,   0,   0,   0,   51,  1,   0,   0,   0,   0,   53,  1,   0,   0,
      0,   0,   55,  1,   0,   0,   0,   0,   57,  1,   0,   0,   0,   0,   59,
      1,   0,   0,   0,   0,   61,  1,   0,   0,   0,   0,   63,  1,   0,   0,
      0,   0,   65,  1,   0,   0,   0,   0,   67,  1,   0,   0,   0,   0,   69,
      1,   0,   0,   0,   0,   71,  1,   0,   0,   0,   0,   73,  1,   0,   0,
      0,   0,   75,  1,   0,   0,   0,   0,   77,  1,   0,   0,   0,   0,   79,
      1,   0,   0,   0,   0,   81,  1,   0,   0,   0,   1,   83,  1,   0,   0,
      0,   3,   90,  1,   0,   0,   0,   5,   92,  1,   0,   0,   0,   7,   100,
      1,   0,   0,   0,   9,   102, 1,   0,   0,   0,   11,  105, 1,   0,   0,
      0,   13,  115, 1,   0,   0,   0,   15,  117, 1,   0,   0,   0,   17,  119,
      1,   0,   0,   0,   19,  121, 1,   0,   0,   0,   21,  123, 1,   0,   0,
      0,   23,  125, 1,   0,   0,   0,   25,  127, 1,   0,   0,   0,   27,  131,
      1,   0,   0,   0,   29,  147, 1,   0,   0,   0,   31,  152, 1,   0,   0,
      0,   33,  155, 1,   0,   0,   0,   35,  170, 1,   0,   0,   0,   37,  177,
      1,   0,   0,   0,   39,  201, 1,   0,   0,   0,   41,  214, 1,   0,   0,
      0,   43,  216, 1,   0,   0,   0,   45,  218, 1,   0,   0,   0,   47,  220,
      1,   0,   0,   0,   49,  222, 1,   0,   0,   0,   51,  224, 1,   0,   0,
      0,   53,  226, 1,   0,   0,   0,   55,  229, 1,   0,   0,   0,   57,  231,
      1,   0,   0,   0,   59,  234, 1,   0,   0,   0,   61,  237, 1,   0,   0,
      0,   63,  240, 1,   0,   0,   0,   65,  242, 1,   0,   0,   0,   67,  244,
      1,   0,   0,   0,   69,  246, 1,   0,   0,   0,   71,  248, 1,   0,   0,
      0,   73,  251, 1,   0,   0,   0,   75,  254, 1,   0,   0,   0,   77,  257,
      1,   0,   0,   0,   79,  260, 1,   0,   0,   0,   81,  262, 1,   0,   0,
      0,   83,  84,  5,   44,  0,   0,   84,  85,  5,   98,  0,   0,   85,  86,
      5,   111, 0,   0,   86,  87,  5,   111, 0,   0,   87,  88,  5,   108, 0,
      0,   88,  89,  5,   62,  0,   0,   89,  2,   1,   0,   0,   0,   90,  91,
      5,   58,  0,   0,   91,  4,   1,   0,   0,   0,   92,  93,  5,   44,  0,
      0,   93,  94,  5,   108, 0,   0,   94,  95,  5,   111, 0,   0,   95,  96,
      5,   103, 0,   0,   96,  97,  5,   105, 0,   0,   97,  98,  5,   99,  0,
      0,   98,  99,  5,   40,  0,   0,   99,  6,   1,   0,   0,   0,   100, 101,
      5,   44,  0,   0,   101, 8,   1,   0,   0,   0,   102, 103, 5,   41,  0,
      0,   103, 104, 5,   62,  0,   0,   104, 10,  1,   0,   0,   0,   105, 106,
      5,   44,  0,   0,   106, 107, 5,   110, 0,   0,   107, 108, 5,   117, 0,
      0,   108, 109, 5,   109, 0,   0,   109, 110, 5,   101, 0,   0,   110, 111,
      5,   114, 0,   0,   111, 112, 5,   105, 0,   0,   112, 113, 5,   99,  0,
      0,   113, 114, 5,   40,  0,   0,   114, 12,  1,   0,   0,   0,   115, 116,
      7,   0,   0,   0,   116, 14,  1,   0,   0,   0,   117, 118, 5,   123, 0,
      0,   118, 16,  1,   0,   0,   0,   119, 120, 5,   125, 0,   0,   120, 18,
      1,   0,   0,   0,   121, 122, 5,   91,  0,   0,   122, 20,  1,   0,   0,
      0,   123, 124, 5,   93,  0,   0,   124, 22,  1,   0,   0,   0,   125, 126,
      5,   40,  0,   0,   126, 24,  1,   0,   0,   0,   127, 128, 5,   41,  0,
      0,   128, 26,  1,   0,   0,   0,   129, 130, 5,   58,  0,   0,   130, 132,
      5,   58,  0,   0,   131, 129, 1,   0,   0,   0,   131, 132, 1,   0,   0,
      0,   132, 133, 1,   0,   0,   0,   133, 137, 3,   29,  14,  0,   134, 136,
      3,   31,  15,  0,   135, 134, 1,   0,   0,   0,   136, 139, 1,   0,   0,
      0,   137, 135, 1,   0,   0,   0,   137, 138, 1,   0,   0,   0,   138, 28,
      1,   0,   0,   0,   139, 137, 1,   0,   0,   0,   140, 142, 5,   80,  0,
      0,   141, 143, 7,   1,   0,   0,   142, 141, 1,   0,   0,   0,   143, 148,
      1,   0,   0,   0,   144, 146, 7,   2,   0,   0,   145, 144, 1,   0,   0,
      0,   146, 148, 1,   0,   0,   0,   147, 140, 1,   0,   0,   0,   147, 145,
      1,   0,   0,   0,   148, 30,  1,   0,   0,   0,   149, 153, 7,   3,   0,
      0,   150, 151, 5,   58,  0,   0,   151, 153, 5,   58,  0,   0,   152, 149,
      1,   0,   0,   0,   152, 150, 1,   0,   0,   0,   153, 32,  1,   0,   0,
      0,   154, 156, 5,   45,  0,   0,   155, 154, 1,   0,   0,   0,   155, 156,
      1,   0,   0,   0,   156, 158, 1,   0,   0,   0,   157, 159, 2,   48,  57,
      0,   158, 157, 1,   0,   0,   0,   159, 160, 1,   0,   0,   0,   160, 158,
      1,   0,   0,   0,   160, 161, 1,   0,   0,   0,   161, 168, 1,   0,   0,
      0,   162, 164, 5,   46,  0,   0,   163, 165, 2,   48,  57,  0,   164, 163,
      1,   0,   0,   0,   165, 166, 1,   0,   0,   0,   166, 164, 1,   0,   0,
      0,   166, 167, 1,   0,   0,   0,   167, 169, 1,   0,   0,   0,   168, 162,
      1,   0,   0,   0,   168, 169, 1,   0,   0,   0,   169, 34,  1,   0,   0,
      0,   170, 171, 5,   39,  0,   0,   171, 173, 5,   98,  0,   0,   172, 174,
      2,   48,  49,  0,   173, 172, 1,   0,   0,   0,   174, 175, 1,   0,   0,
      0,   175, 173, 1,   0,   0,   0,   175, 176, 1,   0,   0,   0,   176, 36,
      1,   0,   0,   0,   177, 178, 5,   48,  0,   0,   178, 179, 5,   98,  0,
      0,   179, 181, 1,   0,   0,   0,   180, 182, 2,   48,  49,  0,   181, 180,
      1,   0,   0,   0,   182, 183, 1,   0,   0,   0,   183, 181, 1,   0,   0,
      0,   183, 184, 1,   0,   0,   0,   184, 38,  1,   0,   0,   0,   185, 186,
      5,   48,  0,   0,   186, 187, 5,   120, 0,   0,   187, 189, 1,   0,   0,
      0,   188, 190, 7,   4,   0,   0,   189, 188, 1,   0,   0,   0,   190, 191,
      1,   0,   0,   0,   191, 189, 1,   0,   0,   0,   191, 192, 1,   0,   0,
      0,   192, 202, 1,   0,   0,   0,   193, 194, 5,   48,  0,   0,   194, 195,
      5,   120, 0,   0,   195, 197, 1,   0,   0,   0,   196, 198, 7,   5,   0,
      0,   197, 196, 1,   0,   0,   0,   198, 199, 1,   0,   0,   0,   199, 197,
      1,   0,   0,   0,   199, 200, 1,   0,   0,   0,   200, 202, 1,   0,   0,
      0,   201, 185, 1,   0,   0,   0,   201, 193, 1,   0,   0,   0,   202, 40,
      1,   0,   0,   0,   203, 204, 5,   64,  0,   0,   204, 205, 5,   116, 0,
      0,   205, 206, 5,   114, 0,   0,   206, 207, 5,   117, 0,   0,   207, 215,
      5,   101, 0,   0,   208, 209, 5,   64,  0,   0,   209, 210, 5,   102, 0,
      0,   210, 211, 5,   97,  0,   0,   211, 212, 5,   108, 0,   0,   212, 213,
      5,   115, 0,   0,   213, 215, 5,   101, 0,   0,   214, 203, 1,   0,   0,
      0,   214, 208, 1,   0,   0,   0,   215, 42,  1,   0,   0,   0,   216, 217,
      5,   43,  0,   0,   217, 44,  1,   0,   0,   0,   218, 219, 5,   45,  0,
      0,   219, 46,  1,   0,   0,   0,   220, 221, 5,   42,  0,   0,   221, 48,
      1,   0,   0,   0,   222, 223, 5,   47,  0,   0,   223, 50,  1,   0,   0,
      0,   224, 225, 5,   62,  0,   0,   225, 52,  1,   0,   0,   0,   226, 227,
      5,   62,  0,   0,   227, 228, 5,   61,  0,   0,   228, 54,  1,   0,   0,
      0,   229, 230, 5,   60,  0,   0,   230, 56,  1,   0,   0,   0,   231, 232,
      5,   60,  0,   0,   232, 233, 5,   61,  0,   0,   233, 58,  1,   0,   0,
      0,   234, 235, 5,   61,  0,   0,   235, 236, 5,   61,  0,   0,   236, 60,
      1,   0,   0,   0,   237, 238, 5,   33,  0,   0,   238, 239, 5,   61,  0,
      0,   239, 62,  1,   0,   0,   0,   240, 241, 5,   38,  0,   0,   241, 64,
      1,   0,   0,   0,   242, 243, 5,   124, 0,   0,   243, 66,  1,   0,   0,
      0,   244, 245, 5,   94,  0,   0,   245, 68,  1,   0,   0,   0,   246, 247,
      5,   126, 0,   0,   247, 70,  1,   0,   0,   0,   248, 249, 5,   60,  0,
      0,   249, 250, 5,   60,  0,   0,   250, 72,  1,   0,   0,   0,   251, 252,
      5,   62,  0,   0,   252, 253, 5,   62,  0,   0,   253, 74,  1,   0,   0,
      0,   254, 255, 5,   38,  0,   0,   255, 256, 5,   38,  0,   0,   256, 76,
      1,   0,   0,   0,   257, 258, 5,   124, 0,   0,   258, 259, 5,   124, 0,
      0,   259, 78,  1,   0,   0,   0,   260, 261, 5,   33,  0,   0,   261, 80,
      1,   0,   0,   0,   262, 263, 7,   6,   0,   0,   263, 264, 1,   0,   0,
      0,   264, 265, 6,   40,  0,   0,   265, 82,  1,   0,   0,   0,   19,  0,
      131, 137, 142, 145, 147, 152, 155, 160, 166, 168, 175, 183, 189, 191, 197,
      199, 201, 214, 1,   6,   0,   0};
  staticData->serializedATN = antlr4::atn::SerializedATNView(
      serializedATNSegment,
      sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) {
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i),
                                           i);
  }
  propositionlexerLexerStaticData = staticData.release();
}

} // namespace

propositionLexer::propositionLexer(CharStream *input) : Lexer(input) {
  propositionLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(
      this, *propositionlexerLexerStaticData->atn,
      propositionlexerLexerStaticData->decisionToDFA,
      propositionlexerLexerStaticData->sharedContextCache);
}

propositionLexer::~propositionLexer() { delete _interpreter; }

std::string propositionLexer::getGrammarFileName() const {
  return "proposition.g4";
}

const std::vector<std::string> &propositionLexer::getRuleNames() const {
  return propositionlexerLexerStaticData->ruleNames;
}

const std::vector<std::string> &propositionLexer::getChannelNames() const {
  return propositionlexerLexerStaticData->channelNames;
}

const std::vector<std::string> &propositionLexer::getModeNames() const {
  return propositionlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary &propositionLexer::getVocabulary() const {
  return propositionlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView propositionLexer::getSerializedATN() const {
  return propositionlexerLexerStaticData->serializedATN;
}

const atn::ATN &propositionLexer::getATN() const {
  return *propositionlexerLexerStaticData->atn;
}

void propositionLexer::initialize() {
  std::call_once(propositionlexerLexerOnceFlag,
                 propositionlexerLexerInitialize);
}
