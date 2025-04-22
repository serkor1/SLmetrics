#!/bin/bash
# 0) error recovery
set -euo pipefail

# 1) build markdown
#    files
Rscript .meta/DEVTOOLS/build_md.R

# Recursively process all .md files under gitbook/
find gitbook/ -type f -name '*.md' -print0 |
while IFS= read -r -d '' file; do
  perl -0777 -i -pe '
    # 1) Match the opening <div class="sourceCode r"> (with any leading spaces)
    #    and replace it with exactly the Jekyll tag + R fence—no extra spaces.
    s{^[ \t]*<div\s+class="sourceCode\s+r">\s*\n}{
{% code overflow="wrap" lineNumbers="true" %}

``` R

}msg;

    # 2) Match the closing </div> (with any leading spaces or blank lines)
    #    and replace with exactly the closing fence + endcode.
    s{\n?[ \t]*</div>\s*(?=\n|$)}{
```
{% endcode %} 

}msg; ' "$file"
done
