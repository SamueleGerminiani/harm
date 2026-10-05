#!/usr/bin/env python3
"""H4, acceptance test A2: check_coi.py rejects invalid coi.json documents, each for the expected
reason. Every case is a small change to a valid document."""
import copy
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_coi  # noqa: E402

VALID = {
    "version": "1",
    "meta": {"design": "d", "top": "d", "vcd_scope": "tb::dut", "vcd_recursion": 0, "clock": "clk",
             "max_depth": 3, "generator": {"name": "hand-written", "version": ""}},
    "targets": {"q": {"sources": [{"sig": "a", "depths": [1]}, {"sig": "q", "depths": [1, 2, 3],
                                                                 "saturated": True}]}},
    "unknown": [],
    "predicates": [],
}


def case(name, change, expected):
    doc = copy.deepcopy(VALID)
    change(doc)
    problems = []
    check_coi.check(doc, problems)
    ok = any(expected in p for p in problems)
    print(f"{'ok  ' if ok else 'FAIL'} {name}: {problems if problems else 'accepted'}")
    return ok


def main():
    problems = []
    check_coi.check(copy.deepcopy(VALID), problems)
    results = [not problems]
    print(f"{'ok  ' if not problems else 'FAIL'} valid document: {problems if problems else 'accepted'}")

    def drop(key):
        return lambda d: d.pop(key)

    results += [
        case("missing version", drop("version"), "'version' is a required property"),
        case("wrong version", lambda d: d.update(version="2"), "'1' was expected"),
        case("missing clock", lambda d: d["meta"].pop("clock"), "'clock' is a required property"),
        case("negative depth", lambda d: d["targets"]["q"]["sources"][0].update(depths=[-1]),
             "less than the minimum"),
        case("empty depths without saturated",
             lambda d: d["targets"]["q"]["sources"][0].update(depths=[]),
             "empty depths without saturated"),
        case("unsorted depths", lambda d: d["targets"]["q"]["sources"][1].update(depths=[2, 1]),
             "not sorted and unique"),
        case("repeated depth", lambda d: d["targets"]["q"]["sources"][1].update(depths=[1, 1]),
             "not sorted and unique"),
        case("depth above max_depth", lambda d: d["targets"]["q"]["sources"][1].update(depths=[1, 4]),
             "above max_depth"),
        case("clock as a source", lambda d: d["targets"]["q"]["sources"].append(
            {"sig": "clk", "depths": [0]}), "cannot be a source"),
        case("source listed twice", lambda d: d["targets"]["q"]["sources"].append(
            {"sig": "a", "depths": [2]}), "listed twice"),
        case("unknown field", lambda d: d["targets"]["q"].update(extra=1),
             "Additional properties are not allowed"),
        case("bad predicate origin", lambda d: d.update(predicates=[{"expr": "a", "origin": "spec"}]),
             "'rtl' was expected"),
    ]
    sys.exit(0 if all(results) else 1)


if __name__ == "__main__":
    main()
