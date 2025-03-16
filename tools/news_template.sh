#!/usr/bin/env bash

## 1) get latest version
##    from DESCRIPTION
VERSION=$(grep '^Version:' DESCRIPTION | sed 's/Version: //')

## 2) create file if
##    it exists prompt
new_entry="meta/CHANGELOG/v${VERSION}.qmd"

if [ -f "$new_entry" ]; then
    echo "File $new_entry already exists. Overwrite? (y/n): "
    read answer
    if [ "$answer" = "y" ]; then
        echo "Created!"
        > "$new_entry"
    else
        exit 1
    fi
else
    > "$new_entry"
fi

## 3) write the template
##    in the file
cat <<EOF > "$new_entry"
---
format:
    gfm:
        default-image-extension: ".png"
always_allow_html: true
execute:
  cache: true
  freeze: auto
  dir: meta/CHANGELOG
knitr:
  opts_chunk:
    collapse: true
    comment: "#>"
    dpi: 1280
    fig.height: 6
    out.width: 100%
---

\`\`\`{r install_version ($VERSION)}
#| echo: false
#| include: false
pak::pak(pkg = "serkor1/SLmetrics@v$VERSION", ask = FALSE)
\`\`\`

# :bookmark: Version $VERSION

## :sparkles: Improvements

### :rocket: New features

## :bug: Bug-fixes

## :boom: Breaking changes

EOF