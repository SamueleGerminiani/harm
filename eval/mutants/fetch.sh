#!/usr/bin/env bash
# H45-mutant-eval: fetch the corpus's sources (PULP common_cells, Solderpad 0.51) at the pinned commit into
# build/h45/common_cells. Usage: eval/mutants/fetch.sh [repository root]
set -euo pipefail
root=${1:-$(cd "$(dirname "$0")/../.." && pwd)}
url=https://github.com/pulp-platform/common_cells.git
tag=v1.40.0
commit=1281545696eb3fcba50ec5b4275993476a3c710e
dst=$root/build/h45/common_cells
if [ -d "$dst/.git" ] && [ "$(git -C "$dst" rev-parse HEAD)" = "$commit" ]; then
  echo "common_cells already at $commit"; exit 0
fi
rm -rf "$dst"
mkdir -p "$(dirname "$dst")"
git -c advice.detachedHead=false clone -q --depth 1 --branch "$tag" "$url" "$dst"
got=$(git -C "$dst" rev-parse HEAD)
if [ "$got" != "$commit" ]; then
  echo "common_cells $tag is $got, expected $commit" >&2; exit 1
fi
echo "common_cells $tag at $commit in $dst"
