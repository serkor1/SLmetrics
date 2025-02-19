# This makefile mimics
# the functionality of devtools::check() and devtools::document()
# but without triggering the entire re-writing
# of the package that rewrites RcppExports.R

#!/bin/sh
# global variables
PKGNAME = SLmetrics
VERSION = $(shell grep "^Version:" DESCRIPTION | sed "s/Version: //")
TARBALL = $(PKGNAME)_$(VERSION).tar.gz

# ---------- MAKE helpers ---------- #
# build-meta
#
# This command renders README.qmd and NEWS.qmd and moves
# them to root directory.
#
# Call it as build-meta CHECK=true to reset the cache
#
# Because of stuff, the command now replaces all dirs with meta/dir... Otherwise images are
# not rendered
build-meta:
	@echo "📚 Rendering README and NEWS"

	@if [ "$(RESET)" = "true" ]; then \
		quarto render meta/README.qmd --cache-refresh;  \
	    quarto render meta/NEWS.qmd --cache-refresh; \
	else \
		quarto render  meta/README.qmd; \
		quarto render  meta/NEWS.qmd; \
	fi

	@mv meta/README.md .
	@mv meta/NEWS.md .

	@Rscript -e "file_path <- 'NEWS.md'; \
	             file_contents <- readLines(file_path); \
	             modified_contents <- gsub('NEWS_files/', 'meta/NEWS_files/', file_contents); \
	             writeLines(modified_contents, file_path); \
	             cat('Replacements completed in NEWS.md\\n')"

	@Rscript -e "file_path <- 'README.md'; \
	             file_contents <- readLines(file_path); \
	             modified_contents <- gsub('README_files/', 'meta/README_files/', file_contents); \
	             writeLines(modified_contents, file_path); \
	             cat('Replacements completed in README.md\\n')"


# preview-docs
#
# This command runs all builders in 
# in tools for the online documentation.
#
# NOTE: Its primarily meant for debugging, as the documentation
# is built via Github actions.
preview-docs:
	@echo "📚 Building Quarto Book"
	
	@mkdir docs/ref_regression -p
	@mkdir docs/ref_classification -p

	@Rscript -e "source('tools/doc-builders/build-qmd.R')"
	@python3 tools/doc-builders/build-yaml.py

	@cd docs/ && quarto preview

# document:
#
# This command runs all top-level scripts in
# tools/
#
# document.R: This file recompiles the attributes in the .cpp-files, modifiess the RcppExports.R via
# tools/modifyRcppExports.R and then runs roxygenize twice to build the documentation
# with arguments like ellipsis and `na.rm`
document:
	@echo "📚 Documenting {$(PKGNAME)}"

	@Rscript tools/document.R

# ---------- MAKE commands ---------- #
# performance:
# 
# This command runs all scripts in data-raw
# individually and stores them in sysdata.rd
#
# NOTE: The command overwrites the file, so it will have to 
# be run to finish.
# 
# The scripts can be run individually if only parts of the
# performance tests are needed to be re-run.
performance:
	@echo "🚀 Running performance-tests in {${PKGNAME}}"
	@echo "==========================================="
	@Rscript -e "DT <- list(); usethis::use_data(DT, internal = TRUE, overwrite = TRUE)" > /dev/null 2>&1
	@for script in data-raw/*.R; do \
		echo "Running $$script ..."; \
		Rscript $$script > /dev/null 2>&1; \
		if [ $$? -ne 0 ]; then \
			echo "Error: $$script failed."; \
			exit 1; \
		fi \
	done
	@echo "✅ All performance tests completed successfully!"
	@echo "⚠️ Remember to rebuild {${PKGNAME}} to use the new data!"

# build:
#
# This command is runs R CMD build ., R CMD INSTALL .
# which builds and installs {SLmetrics}.
#
# When the process is done it will clean up
# the repository by executing the clean command, and rebuild 
# the README and NEWS
#
# Call it with buld CHECK=true if the package needs to
# be checked before install. Or run the check-wrapper
#
# NOTE: If the check fails, it will not install.
build: document
	@echo "▶️ Starting build process of {$(PKGNAME)}"
	@echo "⚒️ Building {$(PKGNAME)} ..."
	@echo ""

	@R CMD build . > /dev/null 2>&1
	@echo "✅ Done!"
	@echo ""

	@if [ "$(CHECK)" = "true" ]; then \
		echo "🔎 Checking {$(PKGNAME)} ..."; \
		R CMD check --no-manual --as-cran $(TARBALL); \
			echo "🗑️ Cleaning branches"; \
	fi

	@echo "⚒️ Installing {$(PKGNAME)} ..."
	@R CMD INSTALL $(TARBALL) > /dev/null 2>&1
	@echo "✅ Done!"
	@echo ""


	$(MAKE) clean BRANCH=false
	$(MAKE) build-meta
	@echo "✅ Build process done!"

# check:
#
# This command is a wrapper of 
# build with CHECK=true
check:
	$(MAKE) build CHECK=true

# clean:
#
# This command performs a clean
# up of the repository. It conditionally deletes branches, and deletes
# README.md, NEWS.md and all build files.S
#
# Use make clean BRANCH=true to delete all branches
# excecpt main and development.
clean:
	@echo "🗑️ Cleaning reposiory"
	@echo ""

	@if [ "$(BRANCH)" = "true" ]; then \
		echo "🗑️ Cleaning branches"; \
		git branch | grep -v "main" | grep -v "development" | xargs git branch -D; \
	fi

	@rm NEWS.md --f
	@rm README.md --f

	@git clean -d -x -f

	@rm -f src/*.o src/*.so
	@rm -f $(TARBALL)

# r-hub:
# 
# This command performs most checks available
# on all R consortium runners.
r-hub:
	@echo "▶️ Requesting r-hub tests"
	@echo "========================="

	@Rscript -e "rhub::rhub_check(platforms = rhub::rhub_platforms()[['name']])"

