#!/bin/bash
# H11g A1 (finding F-M1): on macOS, tools_common.sh must make Homebrew's keg-only flex usable by the
# compiler, not only by the shell: Verilator's lexer includes <FlexLexer.h>, which the SDK lacks.
# Runs on any system: macOS and Homebrew are faked (OSTYPE, brew, sysctl), and the fake flex prefix
# holds a FlexLexer.h with a marker, so a system copy of the header cannot make the test pass.
# Usage: check_tools_common.sh <repository root>
set -euo pipefail
src=$1
work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT

mkdir -p "$work/flex/bin" "$work/flex/include" "$work/fakebin" "$work/prefix"
echo 'int harm_h11g_fake_flexlexer_marker;' > "$work/flex/include/FlexLexer.h"
cat > "$work/fakebin/brew" <<EOF
#!/bin/sh
# brew --prefix <formula>: only flex is "installed"
[ "\$1" = "--prefix" ] && [ "\$2" = "flex" ] && { echo "$work/flex"; exit 0; }
exit 1
EOF
printf '#!/bin/sh\necho 2\n' > "$work/fakebin/sysctl"
chmod +x "$work/fakebin/brew" "$work/fakebin/sysctl"

out=$(
    export PATH="$work/fakebin:$PATH" SDKROOT=/fake-sdk
    unset CPATH
    OSTYPE=darwin24
    source "$src/third_party/tools_common.sh"
    tools_setup verilator "$work/prefix" >/dev/null
    # what the tool builds see: the compiler, with the environment tools_setup leaves behind
    echo '#include <FlexLexer.h>' | env -u SDKROOT "$CXX" -E -x c++ - 2>&1 || true
)
if grep -q harm_h11g_fake_flexlexer_marker <<<"$out"; then
    echo "ok: the compiler finds Homebrew flex's FlexLexer.h"
else
    echo "FAIL: after tools_setup on macOS, the compiler does not find Homebrew flex's FlexLexer.h"
    echo "$out" | tail -5
    exit 1
fi
