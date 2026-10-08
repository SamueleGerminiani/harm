#!/usr/bin/env bash
# H13: a default build of HARM writes no gmon.out (the old unconditional "--profile" link option did,
# in every directory HARM ran in). Usage: check_no_gmon.sh <harm>
set -u
d=$(mktemp -d)
cd "$d" && "$1" --version > /dev/null 2>&1
if [ -e "$d/gmon.out" ]; then echo "FAIL: gmon.out written by a default build"; rm -rf "$d"; exit 1; fi
rm -rf "$d"; echo "PASS: no gmon.out"
