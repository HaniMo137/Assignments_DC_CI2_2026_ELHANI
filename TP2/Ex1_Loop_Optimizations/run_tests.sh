#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Build binaries
make clean
make

RAW_DIR="results"
mkdir -p "$RAW_DIR"

RAW_O0="$RAW_DIR/results_O0.txt"
RAW_O2="$RAW_DIR/results_O2.txt"

# Run binaries and capture raw output
./unroll_O0 | tee "$RAW_O0"
./unroll_O2 | tee "$RAW_O2"

printf "\nSaved raw output:\n  %s\n  %s\n" "$RAW_O0" "$RAW_O2"