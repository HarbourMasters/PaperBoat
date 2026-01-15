#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

case "$(uname -s)" in
    CYGWIN*|MINGW*|MSYS*|Windows_NT)
        TORCH_EXE="$PROJECT_ROOT/external/torch/build-cmake/torch.exe"
        ;;
    *)
        TORCH_EXE="$PROJECT_ROOT/external/torch/build-cmake/torch"
        ;;
esac

if [ ! -f "$TORCH_EXE" ]; then
    echo "Error: torch executable not found at $TORCH_EXE"
    echo "Please build torch first using: make -C external/torch"
    exit 1
fi

cd "$PROJECT_ROOT"
"$TORCH_EXE" header baserom.z64
