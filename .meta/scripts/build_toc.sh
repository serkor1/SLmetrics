#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"


ROOT_DIR="$PROJECT_ROOT/DOCUMENTATION/gitbook"
OUTPUT_FILE="$PROJECT_ROOT/DOCUMENTATION/TOC.md"

find "$ROOT_DIR" -mindepth 1 -print | sort | \
  sed "s|^$ROOT_DIR/||" | \
  awk -F'/' '{
    depth = NF - 1
    indent = ""
    for (i = 1; i <= depth; i++) indent = indent "  "
    name = $NF
    printf("%s- [%s](%s)\n", indent, name, $0)
  }' > "$OUTPUT_FILE"

echo "Generated Markdown TOC in $OUTPUT_FILE"

# build summary
(cd .meta/DOCUMENTATION/gitbook \
  && quarto render ../SUMMARY.qmd --to markdown --output SUMMARY.md)

