#!/bin/bash
# Script to preview the documentation

# Create required directories if they don't exist
mkdir -p .meta/DOCUMENTATION/ref_regression
mkdir -p .meta/DOCUMENTATION/ref_classification

# Run R script to build QMD files
Rscript -e "source('.meta/DEVTOOLS/doc-builders/build-qmd.R')"

# Run Python script to build YAML files
python3 .meta/DEVTOOLS/doc-builders/build-yaml.py

# Preview the Quarto book
cd .meta/DOCUMENTATION/ && quarto preview