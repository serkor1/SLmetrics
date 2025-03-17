#!/bin/bash
# Script to build NEWS.md from NEWS.qmd

# Get the reset flag from command line arguments
RESET=$1

# Run the changelog build script
./.meta/DEVTOOLS/changelog_build.sh

# Render the NEWS file
if [ "$RESET" = "true" ]; then
    quarto render .meta/CHANGELOG/NEWS.qmd --cache-refresh
else
    quarto render .meta/CHANGELOG/NEWS.qmd
fi

# Move the file to the root directory
mv .meta/CHANGELOG/NEWS.md .

# Update file paths in NEWS.md
Rscript -e "file_path <- 'NEWS.md'; \
             file_contents <- readLines(file_path); \
             modified_contents <- gsub('(v.*_files/)', '.meta/CHANGELOG/\\\\1', file_contents, perl = TRUE, ignore.case = TRUE); \
             writeLines(modified_contents, file_path); \
             cat('Replacements completed in NEWS.md\n')"