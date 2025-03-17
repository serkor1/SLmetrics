# Package information
PKGNAME := SLmetrics
VERSION := $(shell grep "^Version:" DESCRIPTION | sed "s/Version: //")
TARBALL := $(PKGNAME)_$(VERSION).tar.gz

# Directory structure
META_DIR := .meta
DOC_DIR := $(META_DIR)/DOCUMENTATION
DEVTOOLS_DIR := $(META_DIR)/DEVTOOLS
README_DIR := $(META_DIR)/README
CHANGELOG_DIR := $(META_DIR)/CHANGELOG
SCRIPTS_DIR := $(META_DIR)/scripts

# File paths
NEWS_QMD := $(CHANGELOG_DIR)/NEWS.qmd
NEWS_MD := NEWS.md
README_QMD := $(README_DIR)/README.qmd
README_MD := README.md

# Command options
RESET ?= false
CHECK ?= false

# Output formatting
ECHO_PREFIX := "\033[1;36m>>\033[0m"
SUCCESS := "\033[1;32m✓\033[0m"
WARNING := "\033[1;33m⚠️\033[0m"
ERROR := "\033[1;31m✗\033[0m"
