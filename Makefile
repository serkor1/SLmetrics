# This makefile mimics
# the functionality of devtools::check() and devtools::document()
# but without triggering the entire re-writing
# of the package that rewrites RcppExports.R

#!/bin/sh
# global variables
PKGNAME = SLmetrics
VERSION = $(shell grep "^Version:" DESCRIPTION | sed "s/Version: //")
TARBALL = $(PKGNAME)_$(VERSION).tar.gz

performance:
	clear
	@echo "Running performance-tests in {${PKGNAME}}"
	@echo "========================================"
	@Rscript -e "DT <- list(); usethis::use_data(DT, internal = TRUE, overwrite = TRUE)" > /dev/null 2>&1
	@for script in data-raw/*.R; do \
		echo "Running $$script ..."; \
		Rscript $$script > /dev/null 2>&1; \
		if [ $$? -ne 0 ]; then \
			echo "Error: $$script failed."; \
			exit 1; \
		fi \
	done
	@echo -e "\U2705 All performance tests completed successfully!"
	@echo "NOTE: Remember to rebuild {${PKGNAME}} to use the new data!"

document:
	clear
	@echo "Documenting {$(PKGNAME)}"
	@rm -f NEWS.md README.md
	@Rscript tools/document.R

build: document
	@echo "Installing {$(PKGNAME)}"
	rm -f src/*.o src/*.so
	R CMD build .
	R CMD INSTALL $(TARBALL)
	rm -f $(TARBALL)
	rm -f src/*.o src/*.so
	@Rscript tools/render.R
	$(MAKE) build-site

check: document
	@echo "Checking {$(PKGNAME)}"
	@rm -f src/*.o src/*.so
	R CMD build .
	R CMD check --no-manual --as-cran $(TARBALL)
	R CMD INSTALL $(TARBALL)
	@rm -f $(TARBALL)
	@rm -rf $(PKGNAME).Rcheck
	@rm -f src/*.o src/*.so

build-site:
	@echo "Building {pkgdown}"
	@Rscript -e "pkgdown::build_site()"
	
preview:
	@xdg-open docs/index.html
