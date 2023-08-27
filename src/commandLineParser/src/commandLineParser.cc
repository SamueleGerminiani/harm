#include "commandLineParser.hh"
#include <cstddef>
// HARM
cxxopts::ParseResult parseHARM(int argc, char *argv[]) {
  try {
    cxxopts::Options options(argv[0], "");
    options.positional_help("[optional args]").show_positional_help();

    std::string file = "";

    options.add_options()("csv", ".csv trace", cxxopts::value<std::string>(),
                          "<FILE>")("vcd", ".vcd trace",
                                    cxxopts::value<std::string>(), "<FILE>")(
        "vcd-dir", "path to a directory containing .vcd traces",
        cxxopts::value<std::string>(),
        "<DIRECTORY>")("vcd-ss",
                       "select a scope of signals in the .vcd trace (disables vcd-r, use \"--vcd-r 1\" to enable it again)",
                       cxxopts::value<std::string>(), "<String>")
            ("vcd-r", "recursively add signals for all sub-scopes, default is enabled (1)", cxxopts::value<size_t>(), "0 or 1")
            ("vcd-unroll", "create a context for each scope when generating the config file (mutually esclusive with vcd-r, default is <max depth>)", cxxopts::value<std::string>()->implicit_value(std::to_string((size_t)-1)), "depth of unroll")
            
("csv-dir", "path to a directory containing .csv traces", cxxopts::value<std::string>(), "<DIRECTORY>")
("conf", ".xml configuration file",
                        cxxopts::value<std::string>(), "<FILE>")(
            "clk", "clk signal", cxxopts::value<std::string>(), "<String>")(
            "sva", " output assertions in SystemVerilog Assertion format")(
            "fd", "path to the directory containing faulty traces",
            cxxopts::value<std::string>(), "<DIRECTORY>")(
            "ftm",
            "'fault-on-trace mode', give the path to a file containing comma "
            "seperated 'output variables', harm will perform fault coverage by "
            "inserting stuck-at faults in the 'outputs' of the trace",
            cxxopts::value<std::string>(),
            "<FILE>")
                ("max-threads", "max number of threads that harm is allowed to spawn", cxxopts::value<size_t>(), "<uint>")(
            "test-level", "test one level of the 3lp (1,2 or 3)",
            cxxopts::value<size_t>(),
            "<uint>")("generate-config", "generate template xml configuration")(
            "dont-normalize",
            "discard assertions using the absolute value (not "
            "normalized) of filterig metrics ")(
            "find-min-subset",
            "find the minimum number of assertions covering all faults")(
            "dump", "dump assertions to file")("dump-stat",
                                               "dump statistics to file")(
            "dump-to", "dump assertions to file with given path",
            cxxopts::value<std::string>(), "<DIRECTORY>")(
            "max-ass", "maximum number of assertions to keep after the ranking",
            cxxopts::value<size_t>(),
            "<uint>")("dump-vac-ass", "dump vacuous assertions to file",
                      cxxopts::value<std::string>(), "<FILE>")(
            "keep-vac-ass", "do not discard vacuous assertions")(
            "include-ass",
            "create a new context 'external' with the assertions contained in "
            "the provided FILE (one assertion per line), if a context named "
            "'external' is present in the config file, then the assertions "
            "will be added to that context",
            cxxopts::value<std::string>(), "<FILE>")(
            "sample-by-con",
            "if the number of mined assertions exceeds the value provided by "
            "max-ass, assertions are selected favouring consequent diversity")(
            "dont-fill-ass",
            "do not populate assertions with values (saves memory)")(
            "interactive", "enable interactive assertion ranking")(
            "split-logic", "split bitvectors into boolean variabes")(
            "dont-print-ass", "do not print the mined assertions")(
            "silent", "disable all outputs")("wsilent", "disable all warnings")(
            "isilent", "disable all infos")("psilent",
                                            "disable all progress bars")(
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

// dea
cxxopts::ParseResult parseDEA(int argc, char *argv[]) {
  try {
    cxxopts::Options options(argv[0], "");
    options.positional_help("[optional args]").show_positional_help();

    std::string file = "";

    options.add_options()("vcd", "vcd trace file type")("csv",
                                                        "csv trace file type")(
        "ass-file", "", cxxopts::value<std::string>(),
        "path to assertion file (one per each line)")(
        "metric-name", "", cxxopts::value<std::string>(),
        "name of the metric (default is 'Metric')")(
        "metric-search-interval", "",
        cxxopts::value<std::vector<std::string>>(),
        "narrow the search of the nsga2 algo phase 2 clustering to a specified "
        "interval 'lower,upper' (default is '0.0,1.0')")(
        "max-clusters", "max number of clusters (must be used with kmeans)",
        cxxopts::value<std::string>(), "divide the score into N clusters")(
        "cs", "<INT>", cxxopts::value<std::string>(),
        "chunk-size number of assertions processed at a time (to avoid memory "
        "explosion) ")(
        "nsga2-mi", "<FLOAT>", cxxopts::value<std::string>(),
        "minimum surface dominance increment to continue the nsga2 algo with "
        "an other iteration, default is 1% (1)")(
        "tech", "", cxxopts::value<std::string>(),
        "name axc technique used to perform the estimation (used to label the "
        "output files)")(
        "cls-type", "", cxxopts::value<std::string>(),
        "technique used to perform the clustering (nsga2, kmeans)")(
        "clk", "clk signal", cxxopts::value<std::string>(), "<String>")(
        "at-list",
        "path to a file containing a list of approximation token ids",
        cxxopts::value<std::string>(), "<FILE>")

        ("fd",
         "path to the directory containing the faulty traces (this is the "
         "second input of the script)",
         cxxopts::value<std::string>(),
         "<DIRECTORY>")("bash",
                        "path to the bash script capable of simulating the "
                        "design (will be called using the 'bash' command)",
                        cxxopts::value<std::string>(), "<FILE>")

            ("debug-script",
             "debug the input script (enables the script output)")(
                "max-threads",
                "max number of threads that harm is allowed to spawn",
                cxxopts::value<size_t>(),
                "<uint>")("dump-to",
                          "directory path to dump dea output (dea will not "
                          "create the directory)",
                          cxxopts::value<std::string>(), "<DIRECTORY>")(
                "recover-diff",
                "reuse the evaluation result of the previous run")(
                "gen-rand", "add the random clusters to the front of "
                            "non-dominated solutions")(
                "push",
                "push the front: executes phase 2 of the nsga2 clustering")(
                "max-push-time",
                "max time to push the pareto frontier of phase II of the nsga2 "
                "clustering (in seconds)",
                cxxopts::value<std::size_t>(),
                "<unint>")("min-push-time",
                           "min time to push the pareto frontier of phase II "
                           "of the nsga2 clustering (in seconds)",
                           cxxopts::value<std::size_t>(),
                           "<unint>")("min-time",
                                      "min time to push the pareto frontier of "
                                      "phase I of the nsga2 clustering "
                                      "(in seconds)",
                                      cxxopts::value<std::size_t>(), "<unint>")(
                "only-sim", "run only phase 2 of the nsga2 clustering")(
                "plot-dominance",
                "plot the pareto dominance over time when running nsga2")(
                "metric-direction",
                "if 0, metric direction is from 0 (best) to 1 (worst), else "
                "metric direction is from 1 (best) to 0 (worst), default is 0",
                cxxopts::value<std::size_t>(),
                "<unint>")("silent", "disable all outputs")(
                "wsilent", "disable all warning")("isilent",
                                                  "disable all info")(
                "psilent", "disable all progress bars")("help", "Show options");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }
    if (!result.count("ass-file") ||
        (result.count("vcd") && !result.count("clk")) ||
        (!result.count("vcd") && !result.count("csv")) ||
        (!result.count("ass-file")) || (!result.count("at-list")) ||
        (!result.count("fd")) || (!result.count("bash")) ||
        (!result.count("dump-to"))

    ) {

      std::cout << "Usage:\n evaluator"
                   " [--vcd --clk <string> | --csv]\n"
                   " --ass-file <ASSERTIONS FILE>\n"
                   " --at-list <AT FILE>\n"
                   " --bash <BASH SCRIPT>\n"
                   " --fd <FAULTY TRACES DIRECTORY>\n"
                   " --dump-to <DEA OUTPUT DIRECTORY>"
                << "\n";
      exit(0);
    }

    return result;

  } catch (const cxxopts::OptionException &e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}
