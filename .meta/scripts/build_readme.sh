#!/bin/bash
# Script to build README.md from README.qmd

# Get the reset flag from command line arguments
RESET=$1

# Render the README file
if [ "$RESET" = "true" ]; then
    quarto render .meta/README/README.qmd --cache-refresh
else
    quarto render .meta/README/README.qmd
fi

# Move the file to the root directory
mv .meta/README/README.md .

# Update file paths in README.md
Rscript -e "file_path <- 'README.md'; \
             file_contents <- readLines(file_path); \
             modified_contents <- gsub('README_files/', '.meta/README/README_files/', file_contents); \
             writeLines(modified_contents, file_path); \
             cat('Replacements completed in README.md\n')"