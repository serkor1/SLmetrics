#--------------------------------#
# Global variables for Makefiles #
#--------------------------------#

# Package information
package_name     := SLmetrics
package_version  := $(shell grep "^Version:" DESCRIPTION | sed "s/Version: //")
tarball_location := $(package_name)_$(package_version).tar.gz

# Directory structure
meta_directory              := .meta
documentation_directory     := $(meta_directory)/documentation
development_tools_directory := $(meta_directory)/development_tools
readme_directory            := $(meta_directory)/README
changelog_directory         := $(meta_directory)/changelog
scripts_directory           := $(meta_directory)/development_tools/scripts

# File paths
changelog_qmd := $(changelog_directory)/NEWS.qmd
changelog_md  := NEWS.md
readme_qmd    := $(readme_directory)/README.qmd
readme_md     := README.md

# Command options
reset ?= false
check ?= false

# Output formatting
echo_prefix  := "\033[1;36m>>\033[0m"
echo_success := "\033[1;32m✓\033[0m"
echo_warning := "\033[1;33m⚠️\033[0m"
echo_error   := "\033[1;31m✗\033[0m"
