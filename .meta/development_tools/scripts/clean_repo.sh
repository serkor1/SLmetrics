#!/bin/bash
# Script to clean the repository

# Remove generated files
rm -f src/*.o src/*.so
rm -f *.tar.gz
rm -f test-omp.*
rm -f config.log
rm -f config.status
rm -f src/Makevars

echo "Repository cleaned successfully."