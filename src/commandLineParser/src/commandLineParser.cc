#include "commandLineParser.hh"
// HARM
cxxopts::ParseResult parseHARM(int argc, char *argv[]) {
  try {
    cxxopts::Options options(argv[0], "");
    options.positional_help("[optional args]").show_positional_help();

    std::string file = "";

    options.add_options()("vcd", ".vcd trace", cxxopts::value<std::string>(),
                          "<FILE>")(
        "vcd-r", "recursively add signals for all sub-scopes")(
        "vcd-dir", "path to a directory containing .vcd traces",
        cxxopts::value<std::string>(),
        "<DIRECTORY>")("vcd-ss",
                       "select a scope of signals in the .vcd trace (use vcd-r "
                       "for recursive add)",
                       cxxopts::value<std::string>(), "<String>")(
        "csv", ".csv trace file", cxxopts::value<std::string>(),
        "<FILE>")("csv-dir", "path to a directory containing .csv traces",
                  cxxopts::value<std::string>(),
                  "<DIRECTORY>")("conf", ".xml configuration file",
                                 cxxopts::value<std::string>(), "<FILE>")(
        "clk", "clk signal", cxxopts::value<std::string>(), "<String>")(
        "sva", " output assertions in SystemVerilog Assertion format")(
        "fd", "path to the directory containing faulty traces",
        cxxopts::value<std::string>(), "<DIRECTORY>")(
        "ftm",
        "'fault-on-trace mode', give the path to a file containing comma "
        "seperated 'output variables', harm will perform fault coverage by "
        "inserting stuck-at faults in the 'outputs' of the trace",
        cxxopts::value<std::string>(), "<FILE>")(
        "max-threads", "max number of threads that harm is allowed to spawn",
        cxxopts::value<size_t>(),
        "<uint>")("test-level", "test one level of the 3lp (1,2 or 3)",
                  cxxopts::value<size_t>(), "<uint>")(
        "generate-config", "generate template xml configuration")(
        "find-min-subset",
        "find the minimum number of assertions covering all faults")(
        "dump", "dump assertions to file")("dump-stat",
                                           "dump statistics to file")
(
        "dump-to", "dump assertions to file with given path",
        cxxopts::value<std::string>(), "<DIRECTORY>")(
        "max-ass", "maximum number of assertions to keep after the ranking",
        cxxopts::value<size_t>(),
        "<uint>")("dont-fill-ass",
                  "do not populate assertions with values (saves memory)")(
        "interactive", "enable interactive assertion ranking")(
        "split-logic", "split bitvectors into boolean variabes")(
        "dont-print-ass", "do not print the mined assertions")(
        "silent", "disable all outputs")("wsilent", "disable all warning")(
        "isilent", "disable all info")("psilent", "disable all progress bars")(
        "cls-alg",
        "type of clustering algorithm; <kmeans>, <kde> kernel density "
        "estimation, <hc> hierarchical (default is kmeans)",
        cxxopts::value<std::string>(), "<String>")("help", "Show options")(
        "name", "name of this execution (used when dumping statistics)",
        cxxopts::value<std::string>(), "<String>");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }
    if (((result.count("vcd") == 1 || result.count("vcd-dir") == 1) &&
         result.count("clk") == 0) ||
        (result.count("vcd") == 0 && result.count("vcd-dir") == 0 &&
         result.count("csv") == 0 && result.count("csv-dir") == 0) ||
        result.count("conf") == 0) {
      std::cout << "Usage:\n";
      std::cout
          << "vcd input --> harm [--vcd <vcdFile> | --vcd-dir <dirPath>] --clk "
             "<clkSignal> --conf <xmlConfigFile> [<OptionalArguments...>]\n";
      std::cout << "csv input --> harm [--csv <csvFile> | --csv-dir <dirPath>] "
                   "--conf <xmlConfigFile> [<OptionalArguments...>]"
                << "\n";
      exit(0);
    }

    return result;

  } catch (const cxxopts::OptionException &e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}

// Trace generator
cxxopts::ParseResult parseTraceGenerator(int argc, char *argv[]) {
  try {
    cxxopts::Options options(argv[0], "");
    options.positional_help("[optional args]").show_positional_help();

    std::string file = "";

    options.add_options()("f", "", cxxopts::value<std::string>(),
                          "LTL formula")(
        "v", "", cxxopts::value<std::string>(),
        "types of vars used in the formual (C types): type1 var1, type2 "
        "var2,..., typeN varN")(
        "l", "", cxxopts::value<size_t>(),
        "length of the trace to be generated (default 100)")(
        "o", "", cxxopts::value<std::string>(), "output file")(
        "core", "", cxxopts::value<size_t>(),
        "max numbers of tests for each proposition (default 10)")(
        "dto", "", cxxopts::value<std::string>(),
        "operands in the dt operator: {prop1; depth1},{prop2; "
        "depth2},...,{propN; depthN}")("help", "Show options");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }
    if (result.count("f") == 0 || result.count("v") == 0) {
      std::cout
          << "Usage:\n traceGenerator -f <formula> -v <varsDecl> [-l <length>]"
          << "\n";
      exit(0);
    }

    return result;

  } catch (const cxxopts::OptionException &e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}

// Var estimator
cxxopts::ParseResult parseVarEstimator(int argc, char *argv[]) {
  try {
    cxxopts::Options options(argv[0], "");
    options.positional_help("[optional args]").show_positional_help();

    std::string file = "";

    options.add_options()("vcd", ".vcd trace", cxxopts::value<std::string>(),
                          "<FILE>")("csv", ".csv trace",
                                    cxxopts::value<std::string>(), "<FILE>")(
        "ass-file", "", cxxopts::value<std::string>(),
        "path to assertion file (one per each line)")(
        "cluster", "", cxxopts::value<std::string>(),
        "divide the score into N clusters")(
        "cs", "", cxxopts::value<std::string>(),
        "chunk-size number of assertions processed at a time (depends on the "
        "available memory) ")("tech", "", cxxopts::value<std::string>(),
                              "technique used to perform the estimation")(
        "clk", "clk signal", cxxopts::value<std::string>(), "<String>")

        ("info-list",
         "path to a csv file containing the the variables with their size",
         cxxopts::value<std::string>(), "<DIRECTORY>")

            ("fd", "path to the directory containing faulty traces",
             cxxopts::value<std::string>(),
             "<DIRECTORY>")("vars", "path to the file containing the variables",
                            cxxopts::value<std::string>(), "<FILE>")(
                "max-threads",
                "max number of threads that harm is allowed to spawn",
                cxxopts::value<size_t>(),
                "<uint>")("dump-to", "dump ranking to file with given path",
                          cxxopts::value<std::string>(), "<DIRECTORY>")(
                "n-stm",
                "The number of statements when yousing statement reduction",
                cxxopts::value<size_t>(), "<uint>")
                              ( "print-failing-ass", "")
                              ("help", "Show options");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }
    if (result.count("ass-file") == 0 || result.count("tech") == 0 ||
        (result.count("vcd") == 0 && result.count("csv") == 0) ||
        (result.count("vcd") == 1 && result.count("clk") == 0)) {
      std::cout << "Usage:\n evaluator --ass-file <FILE> --tech <string> "
                   "--vcd <FILE>"
                   " --clk <string>"
                   " [--info-list | --n-stm]"
                << "\n";
      exit(0);
    }

    return result;

  } catch (const cxxopts::OptionException &e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}
