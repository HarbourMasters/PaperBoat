#!/usr/bin/env bash
# Fails unless the output directory holds everything the game opens at runtime.
# A missing paperboat.o2r or assets/ still links and still produces an artifact
# that cannot start, or cannot extract a ROM, on the machine that downloads it.
#
# Usage: check-desktop-build.sh <build-dir> <executable-name>
set -euo pipefail

dir=${1:?build directory}
exe=${2:?executable name}

fail() {
    echo "::error::$1"
    exit 1
}

[ -x "$dir/$exe" ] || fail "$exe missing from $dir"
[ -s "$dir/paperboat.o2r" ] || fail "paperboat.o2r missing or empty in $dir"
[ -s "$dir/config.yml" ] || fail "config.yml missing or empty in $dir"
[ -d "$dir/assets" ] || fail "assets/ missing from $dir"

# An empty assets tree means Torch has nothing to extract with.
yamls=$(find "$dir/assets" \( -name '*.yaml' -o -name '*.yml' \) | wc -l | tr -d ' ')
[ "$yamls" -gt 0 ] || fail "no asset yamls under $dir/assets"

echo "$dir looks complete: $exe, paperboat.o2r, config.yml, $yamls asset yamls"
