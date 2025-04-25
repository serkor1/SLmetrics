#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

# Directories
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../../.." && pwd)"
DOC_ROOT="$PROJECT_ROOT/.meta/DOCUMENTATION"
GITBOOK_DIR="$DOC_ROOT/gitbook"
SRC_SUMMARY="$DOC_ROOT/SUMMARY.md"
DST_SUMMARY="$GITBOOK_DIR/SUMMARY.md"

# 0) Build markdown sources
Rscript .meta/development_tools/build_md.R

echo -e "\t ✅ Markdown sources built"

# 1) Convert <div class="sourceCode r"> blocks into GitBook code fences
find "$GITBOOK_DIR" -type f -name '*.md' -print0 | \
  while IFS= read -r -d '' file; do
    perl -0777 -i -pe '
      s{^[ \t]*<div\s+class="sourceCode\s+r">\s*\n}{\
{% code overflow="wrap" lineNumbers="true" %}\n\n``` R\n}msg;
      s{\n?[ \t]*</div>\s*(?=\n|$)}{```\n\n{% endcode %}\n}msg;
    ' "$file"
  done

echo -e "\t ✅ Code blocks converted"

# 2) Remove indentation from documents
find "$GITBOOK_DIR" -type f -name '*.md' -print0 | \
  while IFS= read -r -d '' file; do
    sed -E -i '/^```[[:space:]]*R[[:space:]]*$/,/^```[[:space:]]*$/ { 
      /^```/ b
      s/^ {4}//
    }' "$file"
  done

echo -e "\t ✅ Redundant indentation removed"

# 3) Strip '### See Also' sections
find "$GITBOOK_DIR" -type f -name '*.md' -print0 | \
  while IFS= read -r -d '' file; do
    sed -E -i '/^### See Also$/,/^###[[:space:]]/{
      /^### See Also$/d
      /^###[[:space:]]/!d
    }' "$file"
  done

echo -e "\t ✅ 'See Also' sections removed"
