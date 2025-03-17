#!/bin/bash
# Script to create a new version entry in NEWS

# Get the version from command line arguments
VERSION=$1

# Run the changelog template script
./.meta/DEVTOOLS/changelog_template.sh