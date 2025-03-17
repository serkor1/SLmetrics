#!/bin/bash
# Script to clean the repository

# Remove generated files
rm -f NEWS.md
rm -f README.md
rm -f src/*.o src/*.so
rm -f *.tar.gz

echo "Repository cleaned successfully."