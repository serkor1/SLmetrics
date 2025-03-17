#!/bin/bash
# Script to run R-hub checks

# Run R-hub checks excluding 'suggests' and 'rchk' platforms
Rscript -e "
    rhub::rhub_check(
        platforms = grep(
            pattern     = 'suggests|rchk',
            x           = rhub::rhub_platforms()[['name']],
            ignore.case = TRUE,
            value       = TRUE,
            invert      = TRUE
        )
    )
"

# Check if R-hub check request was successful
if [ $? -ne 0 ]; then
    echo "Error: R-hub check request failed."
    exit 1
fi