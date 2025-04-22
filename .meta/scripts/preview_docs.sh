#!/bin/bash
# 0) error recovery
set -euo pipefail

# 1) build markdown
#    files
Rscript .meta/DEVTOOLS/build_md.R

# 2) change all divs to proper R
#    code
find gitbook/ -type f -name '*.md' -print0 |
while IFS= read -r -d '' file; do
  perl -0777 -i -pe '
s{^[ \t]*<div\s+class="sourceCode\s+r">\s*\n}{
{% code overflow="wrap" lineNumbers="true" %}

``` R
}msg;
s{\n?[ \t]*</div>\s*(?=\n|$)}{```\n\n{% endcode %}\n}msg;
' "$file"
done

# 3) remove redundant indentation
#    from the divs
for file in gitbook/**/**/*.md; do
  sed -E -i '/^```[[:space:]]*R[[:space:]]*$/,/^```[[:space:]]*$/{
    /^```/b
    s/^ {4}// 
  }' "$file"
done

# 4) remove 'see also'-section
#    
for file in gitbook/**/**/*.md; do
    sed -E -i '/^### See Also$/,/^### /{ 
      /^### See Also$/d 
      /^### /!d 
  }' "$file"
done