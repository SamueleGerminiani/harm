#include "harm.hh"
#include "harm/Assertion.hh"
#include <iostream>
int main() {
  harm::Parameters p;
  p.traceFiles.push_back("bl_master1h.vcd");
  p.configFile = "bl_masterConfig.xml";
  p.selectedScope = "::sim1::p::core::master_interface";
  p.clk = "wb_clk";
  p.parserType = "vcd";
  p.dontPrintAss = 1;
  auto res = harm::mine(p);
  for (auto &[context, ass] : res) {
    std::cout << context << "\n";
    for (auto &a : ass) {
      std::cout << "\t\t\t " << a->_toString.second << "\n";
    }
  }
}
