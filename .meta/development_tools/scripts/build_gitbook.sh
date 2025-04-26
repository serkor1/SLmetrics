#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

## 1) Validate Environment
##     Ensure Makefile-exported vars are defined
: "${documentation_directory:?Need documentation_directory}"
: "${scripts_directory:?Need scripts_directory}"

## 2) Set Up Directories & Temp Storage
##     Define source, output and temp directories
MAN_DIR="man"
DOC_DIR="$documentation_directory"
GITBOOK_DIR="$DOC_DIR/gitbook"
OUT_BASE="$(mktemp -d)"

## 3) Gather and Group .Rd Files
##     Find classification_/regression_ Rd files (excluding “documentation”) and bucket by task
mapfile -t ALL_FILES < <(
  find "$MAN_DIR" -maxdepth 1 -type f \
    \( -name "classification_*.Rd" -o -name "regression_*.Rd" \) \
    ! -name "*documentation*" -print
)
declare -A FILES_BY_TASK
for f in "${ALL_FILES[@]}"; do
  base="$(basename "$f")"
  task="${base%%_*}"
  FILES_BY_TASK["$task"]+="$f"$'\n'
done

## 4) Extract Unique Metrics
##     Strip prefixes/suffixes from filenames, sort & dedupe to list metrics per task
for task in "${!FILES_BY_TASK[@]}"; do
  metrics=()
  while read -r f; do
    base="$(basename "$f")"
    m="$(echo "$base" \
         | sed -E "s/^${task}_//; s/weighted\.//; s/(\.factor|\.numeric|\.matrix|\.cmatrix)//g; s/\.Rd$//")"
    [[ -n "$m" ]] && metrics+=("$m")
  done <<< "${FILES_BY_TASK[$task]}"
  readarray -t METRICS < <(printf "%s\n" "${metrics[@]}" | sort -u)

  ## 4.1) Render .Rd → HTML
  ##       For each (task,metric), create temp dir and call Rd2HTML
  for metric in "${METRICS[@]}"; do
    dir_task="${task^} metrics"
    out_dir="$OUT_BASE/$dir_task/$metric"
    mkdir -p "$out_dir"
    while read -r f; do
      if [[ "$(basename "$f")" == *"${metric}"*".Rd" ]]; then
        html_name="$(basename "$f" .Rd).html"
        Rscript -e "tools::Rd2HTML('$f', out = '$out_dir/$html_name')"
      fi
    done <<< "${FILES_BY_TASK[$task]}"
  done
done

## 5) Convert HTML → Markdown
##     Use pandoc to generate .md under gitbook folder, mirroring structure
find "$OUT_BASE" -type f -name '*.html' | while read -r html; do
  rel="${html#"$OUT_BASE"}"
  md="$GITBOOK_DIR/${rel%.html}.md"
  md="$(dirname "$md")/$(basename "$md" | sed 's/^[a-z]*_//')"
  mkdir -p "$(dirname "$md")"
  pandoc -f html -t gfm+raw_html --wrap=auto "$html" -o "$md"
done

## 6) Replace Code Blocks with GitBook Fences
##     Swap <div class="sourceCode r">…</div> into {% code %} and ``` R ```
find "$GITBOOK_DIR" -type f -name '*.md' -print0 | \
while IFS= read -r -d '' file; do
  perl -0777 -i -pe '
    s{^[ \t]*<div\s+class="sourceCode\s+r">\s*\n}{\
{% code overflow="wrap" lineNumbers="true" %}\n\n``` R\n}msg;
    s{\n?[ \t]*</div>\s*(?=\n|$)}{```\n\n{% endcode %}\n}msg;
  ' "$file"
done

## 7) Remove Indentation in Code
##     Strip leading four spaces inside R fences, preserve fences themselves
find "$GITBOOK_DIR" -type f -name '*.md' -print0 | \
while IFS= read -r -d '' file; do
  sed -E -i \
    '/^```[[:space:]]*R[[:space:]]*$/,/^```[[:space:]]*$/ { /^```/b; s/^ {4}// }' \
    "$file"
done

## 8) Remove “See Also” Sections
##     Delete `### See Also` through next third-level header
find "$GITBOOK_DIR" -type f -name '*.md' -print0 | \
while IFS= read -r -d '' file; do
  sed -E -i \
    '/^### See Also$/,/^###[[:space:]]/ { /^### See Also$/d; /^###[[:space:]]/!d }' \
    "$file"
done

## 9) Regenerate SUMMARY.md
##      Build a TOC from gitbook/ directory tree and inject into SUMMARY.md
TOC_TMP="$(mktemp)"
find "$GITBOOK_DIR" -mindepth 1 -print | sort | \
  sed "s|^$GITBOOK_DIR/||" | \
  awk -F'/' '{
    depth = NF - 1; indent = ""
    for (i = 1; i <= depth; i++) indent = indent "  "
    printf("%s* [%s](<%s>)\n", indent, $NF, $0)
  }' > "$TOC_TMP"
sed '/{{< include TOC\.md >}}/ {
  r '"$TOC_TMP"'
  d
}' "$DOC_DIR/SUMMARY.md" > "$GITBOOK_DIR/SUMMARY.md"
rm "$TOC_TMP"

## 10) Copy Top-Level Docs + NEWS.md
##     Copy all .md in documentation_directory (excluding “summary*”) plus NEWS.md into gitbook/
mapfile -t FILE_LIST < <(
  find "$DOC_DIR" -maxdepth 1 -type f -name "*.md" ! -iname "*summary*" -print
)
if [[ -f NEWS.md ]]; then
  FILE_LIST+=(NEWS.md)
fi
mkdir -p "$GITBOOK_DIR"
for file in "${FILE_LIST[@]}"; do
  cp -f "$file" "$GITBOOK_DIR/$(basename "$file")"
done



echo "✅ Documentation built into $GITBOOK_DIR"
