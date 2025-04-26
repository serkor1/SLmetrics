#--------------------------------#
# Global variables for Makefiles #
#--------------------------------#

# Package information
package_name     := SLmetrics
package_version  := $(shell grep "^Version:" DESCRIPTION | sed "s/Version: //")
tarball_location := $(package_name)_$(package_version).tar.gz

# Directory structure
export root_directory              := $(shell pwd)
export meta_directory              := .meta
export documentation_directory     := $(meta_directory)/documentation
export development_tools_directory := $(meta_directory)/development_tools
export readme_directory            := $(meta_directory)/readme
export changelog_directory         := $(meta_directory)/changelog
export scripts_directory           := $(meta_directory)/development_tools/scripts
export makefile_directory          := $(meta_directory)/development_tools/makefiles

# File paths
changelog_qmd := $(changelog_directory)/NEWS.qmd
changelog_md  := NEWS.md
readme_qmd    := $(readme_directory)/README.qmd
readme_md     := README.md

# Command options
reset ?= false
check ?= false

# Output formatting
export echo_prefix  := "\033[1;36m>>\033[0m"
export echo_success := "\033[1;32m✓\033[0m"
export echo_warning := "\033[1;33m⚠️\033[0m"
export echo_error   := "\033[1;31m✗\033[0m"
export echo_bullet  := \t \033[1;36m*\033[0m
