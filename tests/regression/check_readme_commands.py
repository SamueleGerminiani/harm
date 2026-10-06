#!/usr/bin/env python3
"""H11, acceptance A4: every ./harm command in the README's code blocks runs.

The README's commands use placeholders; each is replaced by a shipped example:
  trace.vcd / clock / config.xml   -> examples/vendingMachine (with its --vcd-ss scope)
  trace.csv / config.xml           -> examples/ex3
  path/to/newConfig.xml            -> a temporary file (--generate-config writes it)
A command must exit with 0; a mining command must print assertions, and --generate-config must
write the configuration. A command with an unknown placeholder fails the check, so that new README
examples cannot go untested.
Usage: check_readme_commands.py <harm> <README.md>
"""
import re
import subprocess
import sys
import tempfile
from pathlib import Path

harm, readme = sys.argv[1], Path(sys.argv[2])
root = readme.parent
blocks = re.findall(r"```[^\n]*\n(.*?)```", readme.read_text(), re.S)
commands = [l.strip() for b in blocks for l in b.splitlines() if l.strip().startswith("./harm ")]
EX = root / "examples"
ok = True
for cmd in commands:
    with tempfile.TemporaryDirectory() as d:
        c = cmd
        if "trace.vcd" in c:
            c = c.replace("trace.vcd", str(EX / "vendingMachine/vendingMachine.vcd")).replace("--clk clock", "--clk clk")
            c = c.replace("config.xml", str(EX / "vendingMachine/vendingMachineConfig.xml"))
            c += " --vcd-ss machine_bench::machine_"
        if "trace.csv" in c:
            c = c.replace("trace.csv", str(EX / "ex3/ex3.csv"))
            c = c.replace("config.xml", str(EX / "ex3/ex3Config.xml"))
        c = c.replace("path/to/newConfig.xml", str(Path(d) / "newConfig.xml"))
        args = c.split()
        args[0] = harm
        if any(re.search(r"\.(xml|vcd|csv)$", a) and not Path(a).exists() and "newConfig" not in a for a in args):
            print(f"FAIL (unknown placeholder): {cmd}")
            ok = False
            continue
        r = subprocess.run(args + ["--psilent"], cwd=d, capture_output=True, text=True)
        out = r.stdout + r.stderr
        if "--generate-config" in args:
            good = r.returncode == 0 and (Path(d) / "newConfig.xml").exists()
        else:
            good = r.returncode == 0 and "Assertion" in out
        print(f"{'ok  ' if good else 'FAIL'} {cmd}")
        if not good:
            print(out[-1500:])
        ok &= good
print(f"{len(commands)} README commands")
sys.exit(0 if ok and commands else 1)
