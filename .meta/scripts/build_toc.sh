#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

DOC_ROOT="$PROJECT_ROOT/DOCUMENTATION"
GITBOOK_DIR="$DOC_ROOT/gitbook"

SRC_SUMMARY="$DOC_ROOT/SUMMARY.md"
DST_SUMMARY="$GITBOOK_DIR/SUMMARY.md"

TOC_TMP="$(mktemp)"
find "$GITBOOK_DIR" -mindepth 1 -print | sort | \
  sed "s|^$GITBOOK_DIR/||" | \
  awk -F'/' '{
    depth = NF - 1
    indent = ""
    for (i = 1; i <= depth; i++) indent = indent "  "
    name = $NF
    printf("%s* [%s](<%s>)\n", indent, name, $0)
  }' > "$TOC_TMP"

sed '/{{< include TOC\.md  >}}/{
  r '"$TOC_TMP"'
  d
}' "$SRC_SUMMARY" > "$DST_SUMMARY"

rm "$TOC_TMP"
echo "✅ Generated $DST_SUMMARY"
