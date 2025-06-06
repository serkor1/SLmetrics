#!/usr/bin/env bash
set -euo pipefail

# 0) Compile attributes
# to avoid trouble when running
# document more than once.
Rscript -e "Rcpp::compileAttributes()"

# 1) First Documentation
# NOTE: This builds the package
# before it does anything else if
# there is changes in .dll files
#
# As of now I have not found a way around
# this.
Rscript -e "suppressMessages(
  roxygen2::roxygenize(
    clean   = TRUE,
    roclets = c('collate', 'namespace', 'rd')
  )
)"

# 2) After the the initial
# roxygenize run; it is necessary to
# modify RcppExports.R so the function
# arg naming can be done.
types='factor|numeric|integer|default|matrix|cmatrix|data\.frame'
file_path="${1:-R/RcppExports.R}"
sed -E -i "s/, na_rm = (TRUE|FALSE)\) \{/, na.rm = \1) {/g" "${file_path}"
sed -E -i "s/\bna_rm\)/na_rm = na.rm)/g" "${file_path}"
sed -E -i "s#(\b[[:alnum:]_]+\.(${types})\s*<- function\()([^)]*)(\))#\1\3, ...\4#g" "${file_path}"

# 3) After the RcppExports.R
# has been modified, the Roxygenize can be run
# again to apply the changes made
# on RcppExports.
Rscript -e "suppressMessages(
  roxygen2::roxygenize(
    clean   = TRUE,
    roclets = c('collate', 'namespace', 'rd')
  )
)"