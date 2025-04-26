#!/bin/bash
# Script to run unit tests

# Build the package
R CMD build . > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "Error: Package build failed."
    exit 1
fi

# Run testthat tests
Rscript -e "testthat::test_local()"

# Check if tests were successful
if [ $? -ne 0 ]; then
    echo "Error: Tests failed."
    exit 1
fi