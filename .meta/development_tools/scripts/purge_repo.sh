#!/bin/bash
# Script to purge the repository

# Delete all branches except main and development
git branch | grep -v "main" | grep -v "development" | xargs git branch -D

# Delete all untracked files
git clean -d -x -f

echo "Repository purged successfully."