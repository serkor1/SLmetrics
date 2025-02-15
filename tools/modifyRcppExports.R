# script: Modify RcppExports
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-04
# objective: This script
# modifies the RcppExports.R so it adds
# ... and modifies its args
# script start;

# 0) define path
# to file
file_path <- "R/RcppExports.R"

# 1) read the RcppExports.R
# file
content <- readLines(file_path)

# 2) start by modifying
# the na_rm = TRUE to na.rm = TRUE, ...
# Replace all occurrences of ') {' with ', ...) {'
updated_content <- gsub(", na_rm = (TRUE|FALSE)\\) \\{", ", na.rm = \\1) {", content)

# 3) now replace na_rm with na_rm = na.rm
# to pass the argument
updated_content <- gsub("na_rm)", "na_rm = na.rm)", updated_content)

# 4) Modify all functions
# so it ends with ", ...)"
foo_update <- as.vector(
  outer(
    "[a-z]*",
     c("factor", "numeric", "default", "matrix", "data.frame"),
     paste, 
     sep = "."
  )
)

# 4.1) iterate through all
# functions
for (fname in foo_update) {
  
  # Match the exact function definition, capture arguments, and append ', ...'
  pattern <- paste0("\\b(", fname, " <- function\\(.*)\\)")
  replacement <- "\\1, ...)"

  # Ensure we append ', ...' to the existing arguments
  updated_content <- gsub(pattern, replacement, updated_content, perl = TRUE)
}

# Write the updated content back to the file
writeLines(updated_content, file_path)

# script end;
