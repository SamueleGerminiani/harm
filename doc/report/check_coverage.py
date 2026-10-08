#!/usr/bin/env python3
"""H14, acceptance A2, A4, A5: the v4 documentation covers what changed since v3.

- A4: every command-line option, XML name and metric variable that v3 did not have (current sources
  minus doc/report/inventory/v3_*.txt) appears in the release notes, the README and the report; every
  decision in inventory/default_output_decisions.txt appears in the release notes, the migration guide
  and the report.
- A5: every milestone on PLAN.md's status board (except H14) and every finding F-L<n>/F-M<n> in
  VALIDATION.md is cited in the report and in the release notes; every decision D-<nnn> named in
  doc/plan is cited in the report.
- A2: the developer guide names every top-level directory, every module under src/, src/miner/ and
  src/miner/modules/src/, every directory under tests/, every harm-coi module and every file in eval/;
  every repository path cited in the guide or the report (`\\file{...}`) exists.
Usage: check_coverage.py <repository root>
"""
import re
import subprocess
import sys
from pathlib import Path

root = Path(sys.argv[1]).resolve()
inv = root / "doc/report/inventory"
failures = []


def read(rel):
    p = root / rel
    if not p.exists():
        failures.append(f"missing document: {rel}")
        return ""
    return p.read_text(encoding="utf-8")


def report_text():
    texs = sorted((root / "doc/report").rglob("*.tex"))
    if not texs:
        failures.append("missing document: doc/report/*.tex")
    return "\n".join(t.read_text(encoding="utf-8") for t in texs)


def listed(rel):
    return {l.strip() for l in (inv / rel).read_text().splitlines() if l.strip() and not l.startswith("#")}


DOCS = {
    "release notes": read("doc/RELEASE_NOTES_v4.md"),
    "README": read("README.md"),
    "migration guide": read("doc/MIGRATING_v3_to_v4.md"),
    "developer guide": read("doc/DEVELOPER_GUIDE.md"),
    "report": report_text(),
}


def need(item, pattern, where):
    for doc in where:
        if not re.search(pattern, DOCS[doc]):
            failures.append(f"{doc}: {item} not found")


# ---- A4: options, XML names, metric variables ------------------------------------------------------
opt_re = re.compile(r'^\s*\(\s*"([a-z][a-z0-9-]*)"', re.M)
options = set(opt_re.findall((root / "src/commandLineParser/src/commandLineParser.cc").read_text()))
new_options = sorted(options - listed("v3_options.txt"))
for o in new_options:
    # Markdown writes --name; the report writes --name or \opt{name}
    need(f"option --{o}", rf"--{re.escape(o)}(?![a-z0-9-])|\\opt\{{{re.escape(o)}\}}",
         ["release notes", "README", "report"])

md = (root / "src/miner/modules/src/contextMiner/manualDefinition/ManualDefinition.cc").read_text()
xml_re = re.compile(r'(?:getAttributeValue\([\w\[\]]+, *"([A-Za-z]+)"|getNodesFromName\(\w+, *"([A-Za-z]+)")')
xml = {a or b for a, b in xml_re.findall(md)}
elements = {b for _, b in xml_re.findall(md) if b}
for n in sorted(xml - listed("v3_xml_names.txt")):
    pat = rf"<{n}\b" if n in elements else rf"\b{n}="
    need(f"XML {'element <' + n + '>' if n in elements else 'attribute ' + n + '='}", pat,
         ["release notes", "README", "report"])

metric = (root / "src/miner/utils/src/Metric.cc").read_text()
mvars = set(re.findall(r'make_tuple\("([A-Za-z]+)"', metric))
for v in sorted(mvars - listed("v3_metric_variables.txt")):
    need(f"metric variable {v}", rf"\b{v}\b", ["release notes", "README", "report"])

decisions_text = (root / "doc/plan/DECISIONS.md").read_text()
for d in sorted(listed("default_output_decisions.txt")):
    if f"## {d}:" not in decisions_text:
        failures.append(f"inventory: {d} is not a decision in DECISIONS.md")
    need(f"default-output decision {d}", rf"\b{d}\b", ["release notes", "migration guide", "report"])

# ---- A5: milestones, findings, decisions ---------------------------------------------------------------
plan = (root / "doc/plan/PLAN.md").read_text()
board = plan.split("## 6. Status board", 1)[1]
milestones = [m for m in re.findall(r"^\| (H\w+) \|", board, re.M) if m != "H14"]
if len(milestones) < 20:
    failures.append(f"PLAN.md status board: only {len(milestones)} milestones read")
for m in milestones:
    need(f"milestone {m}", rf"\b{m}\b", ["release notes", "report"])

validation = (root / "doc/plan/VALIDATION.md").read_text()
for f in sorted(set(re.findall(r"\bF-[LM]\d+\b", validation)), key=lambda s: (s[2], int(s[3:]))):
    need(f"finding {f}", rf"\b{f}\b", ["release notes", "report"])

plan_docs = "\n".join(p.read_text() for p in (root / "doc/plan").glob("*.md"))
for d in sorted(set(re.findall(r"\bD-0\d\d\b", plan_docs))):
    need(f"decision {d}", rf"\b{d}\b", ["report"])

# ---- A2: the developer guide covers the repository; cited paths exist ------------------------------
dev = DOCS["developer guide"]
try:
    tracked = subprocess.run(["git", "-C", str(root), "ls-files"], capture_output=True, text=True,
                             check=True).stdout.splitlines()
except (OSError, subprocess.CalledProcessError):
    tracked = None
    print("note: not a git checkout; top-level directories taken from the file system")
if tracked is not None:
    top = sorted({t.split("/")[0] for t in tracked if "/" in t and not t.startswith(".")})
else:
    skip = {"build", "install"}
    top = sorted(p.name for p in root.iterdir()
                 if p.is_dir() and not p.name.startswith((".", "build")) and p.name not in skip)


def subdirs(rel):
    return sorted(f"{rel}/{p.name}" for p in (root / rel).iterdir()
                  if p.is_dir() and not p.name.startswith((".", "__")))


required = top + subdirs("src") + subdirs("src/miner") + subdirs("src/miner/modules/src") + subdirs("tests")
required += sorted(f"{p.name}" for p in (root / "tools/harm-coi/src/harm_coi").glob("*.py"))
required += sorted(f"eval/{p.name}" for p in (root / "eval").iterdir() if p.is_file())
for r in required:
    # a directory is named with its path (`src/exp/`), a harm-coi module by its file name
    if not re.search(rf"(?<![\w/.-]){re.escape(r)}(?![\w.-])", dev):
        failures.append(f"developer guide: {r} not described")

TOPS = tuple(f"{t}/" for t in top) + ("CMakeLists.txt", "README.md", "LICENSE.md")
cited = set(re.findall(r"`([^`\s]+)`", dev)) | set(re.findall(r"\\file\{([^}]+)\}", DOCS["report"]))
for doc in ("migration guide", "release notes"):
    cited |= set(re.findall(r"`([^`\s]+)`", DOCS[doc]))
for c in sorted(cited):
    c = c.replace("\\_", "_")
    if not c.startswith(TOPS) or re.search(r"[<>*{}$]|\.\.\.|…", c):
        continue
    path = c.split(":")[0].rstrip("/")
    if not (root / path).exists():
        failures.append(f"cited path does not exist: {c}")

# ---- result ---------------------------------------------------------------------------------------------
print(f"new options: {len(new_options)}; new XML names: {len(xml - listed('v3_xml_names.txt'))}; "
      f"new metric variables: {len(mvars - listed('v3_metric_variables.txt'))}; milestones: {len(milestones)}; "
      f"developer-guide items: {len(required)}; cited paths: {len(cited)}")
for f in failures:
    print("FAIL:", f)
print("ok" if not failures else f"{len(failures)} failure(s)")
sys.exit(1 if failures else 0)
