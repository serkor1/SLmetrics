#!/bin/bash
# Script to run performance tests

# Initialize empty data table
Rscript -e "DT <- list(); usethis::use_data(DT, internal = TRUE, overwrite = TRUE)" > /dev/null 2>&1

# Run all R scripts in data-raw directory
for script in data-raw/*.R; do
    echo "Running $script ..."
    Rscript "$script" > /dev/null 2>&1
    
    # Check if script execution was successful
    if [ $? -ne 0 ]; then
        echo "Error: $script failed."
        exit 1
    fi
done