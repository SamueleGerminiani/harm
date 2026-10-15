#!/bin/bash
# H27: one download helper for every install script. Sourced, not run.
# fetch <url> <sha256> <file>: downloads over HTTPS with the certificate checked (curl, else wget; curl also takes
# file:// for the tests), and keeps <file> only if its SHA-256 is <sha256>; otherwise fails, naming both values.
fetch() {
    local url=$1 want=$2 out=$3 got
    local part="$out.part"
    rm -f "$part"
    if command -v curl >/dev/null; then
        curl -fsSL --proto '=https,file' -o "$part" "$url" || { rm -f "$part"; echo "fetch: download failed: $url" >&2; return 1; }
    elif command -v wget >/dev/null; then
        [[ "$url" == https://* ]] || { echo "fetch: not https: $url" >&2; return 1; }
        wget -q -O "$part" "$url" || { rm -f "$part"; echo "fetch: download failed: $url" >&2; return 1; }
    else
        echo "fetch: needs curl or wget" >&2
        return 1
    fi
    if command -v sha256sum >/dev/null; then got=$(sha256sum "$part" | cut -d' ' -f1); else got=$(shasum -a 256 "$part" | cut -d' ' -f1); fi
    if [ "$got" != "$want" ]; then
        rm -f "$part"
        echo "fetch: $url: SHA-256 $got, expected $want" >&2
        return 1
    fi
    mv "$part" "$out"
}
