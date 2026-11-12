#!/usr/bin/env bash
# H14, acceptance A1: the report builds from a clean copy of doc/report with no LaTeX error, no
# undefined reference or citation, and no "??" in the PDF's text.
# Exit 77 (ctest: skipped) when latexmk or pdftotext is missing.
# Usage: check.sh <repository root>
set -euo pipefail
root=$(cd "$1" && pwd)
for t in latexmk pdftotext; do
    command -v "$t" >/dev/null || { echo "skipped: $t not found"; exit 77; }
done
[ -f "$root/doc/report/harm_v4.tex" ] || { echo "FAIL: doc/report/harm_v4.tex is missing"; exit 1; }
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
# a clean copy: no auxiliary file from an earlier build
cp -R "$root/doc/report" "$work/report"
rm -f "$work"/report/*.{aux,log,out,toc,bbl,blg,fls,fdb_latexmk,pdf}
cd "$work/report"
if ! latexmk -pdf -interaction=nonstopmode -halt-on-error harm_v4.tex >build.txt 2>&1; then
    echo "FAIL: latexmk"; tail -40 harm_v4.log; exit 1
fi
fail=0
if grep -E "LaTeX Warning: (Reference|Citation|Hyper reference).*undefined|There were undefined references" harm_v4.log; then
    echo "FAIL: undefined references or citations"; fail=1
fi
if grep -E "^! " harm_v4.log; then
    echo "FAIL: LaTeX errors in the log"; fail=1
fi
pdftotext harm_v4.pdf harm_v4.txt
if grep -n "??" harm_v4.txt; then
    echo "FAIL: '??' in the PDF text"; fail=1
fi
pages=$(pdfinfo harm_v4.pdf 2>/dev/null | awk '/^Pages:/ {print $2}' || true)
[ "$fail" = 0 ] && echo "ok: harm_v4.pdf builds (${pages:-?} pages)"
exit $fail
