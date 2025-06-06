## Makefile
##
## Collects all available Makefiles
## found in .meta/development_tools/makefiles

## Make variables
include .meta/development_tools/makefiles/variables.mk

## default target
.PHONY: help
help:
	@grep -h -E '^[[:space:]]*[A-Za-z0-9_.-]+:.*?## .*$$' $(MAKEFILE_LIST) \
		| sed -E 's/^[[:space:]]*//' \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[1;34m%-15s\033[m \xE2\x80\x94 %s\n", $$1, $$2}'

	@echo "\n\033[1;32mNote: \033[mAll source files are located in \033[3m.meta/development_tools/scripts/\033[0m"

## Make files
include $(makefile_directory)/maintenance.mk
include $(makefile_directory)/package.mk
include $(makefile_directory)/documentation.mk




