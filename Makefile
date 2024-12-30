# This makefile mimics
# the functionality of devtools::check() and devtools::document()
# but without triggering the entire re-writing
# of the package that rewrites RcppExports.R

#!/bin/sh
# global variables
PKGNAME = SLmetrics
VERSION = $(shell grep "^Version:" DESCRIPTION | sed "s/Version: //")
TARBALL = $(PKGNAME)_$(VERSION).tar.gz

document:
	clear
	@echo "Documenting {$(PKGNAME)}"
	@Rscript tools/document.R

build: document
	@echo "Installing {$(PKGNAME)}"
	rm -f src/*.o src/*.so
	R CMD build .
	R CMD INSTALL $(TARBALL)
	rm -f $(TARBALL)
	rm -f src/*.o src/*.so

check: document
	@echo "Checking {$(PKGNAME)}"
	rm -f src/*.o src/*.so
	R CMD build .
	R CMD check $(TARBALL)
	rm -f $(TARBALL)
	rm -rf $(PKGNAME).Rcheck
	rm -f src/*.o src/*.so

build-site:
	@echo "Building {pkgdown}"
	@Rscript -e "pkgdown::build_site()"
	
preview:
	@xdg-open docs/index.html
