#!/usr/bin/env bash

# 0. construct variables
#
# VERSION: the literal version number as per the description.
# PKGNAME: the package name as per the description.
VERSION=$(grep '^Version:' DESCRIPTION | sed 's/Version: //')
PKGNAME=$(grep '^Package:' DESCRIPTION | sed 's/Package: //')

# 1. Write the front matter
cat <<EOF > meta/NEWS.qmd
---
format:
    gfm:
        default-image-extension: ".png"
        toc: true
always_allow_html: true
execute:
  cache: true
  freeze: auto
  dir: meta
knitr:
  opts_chunk:
    collapse: true
    comment: "#>"
    dpi: 1280
    fig.height: 6
    out.width: 100%
---

> Version $VERSION is considered pre-release of {$PKGNAME}. We do not
> expect any breaking changes, unless a major bug/issue is reported and its nature
> forces breaking changes.

EOF

# 2. Render .qmd files to md
for f in $(ls meta/CHANGELOG/*.qmd | sort -rV);
do
    quarto render $f
done

# 3. List the files in CHANGELOG/ and add to the
#    NEWS.qmd document
for f in $(ls meta/CHANGELOG/*.md | sort -rV);
do
  clean_path="${f#meta/}"
  echo -e "{{< include $clean_path >}}\n" >> meta/NEWS.qmd
done
