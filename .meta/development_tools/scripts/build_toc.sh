#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

TOC_TMP="$(mktemp)"
find "$documentation_directory/gitbook" -mindepth 1 -print | sort | \
  sed "s|^$documentation_directory/gitbook/||" | \
  awk -F'/' '{
    depth = NF - 1
    indent = ""
    for (i = 1; i <= depth; i++) indent = indent "  "
    name = $NF
    printf("%s* [%s](<%s>)\n", indent, name, $0)
  }' > "$TOC_TMP"

sed '/{{< include TOC\.md >}}/{
  r '"$TOC_TMP"'
  d
}' "$documentation_directory/SUMMARY.md" > "$documentation_directory/gitbook/SUMMARY.md"

rm "$TOC_TMP"
echo -e "\t ✅ Generated SUMMARY.md"
