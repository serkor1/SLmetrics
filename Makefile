# This makefile mimics
# the functionality of devtools::check() and devtools::document()
# but without triggering the whole
# Rcpp::compileAttributes()
#
#!/bin/sh
# global variables
PKGNAME = SLmetrics
VERSION = $(shell grep "^Version:" DESCRIPTION | sed "s/Version: //")
TARBALL = $(PKGNAME)_$(VERSION).tar.gz

build: document
	@echo "Installing {$(PKGNAME)}"
	R CMD build .
	R CMD INSTALL $(TARBALL)
	rm -f $(TARBALL)

check: document
	@echo "Checking {$(PKGNAME)}"
	R CMD build .
	R CMD check $(TARBALL)
	rm -f $(TARBALL)
	rm -rf $(PKGNAME).Rcheck

document:
	clear
	@echo "Documenting {$(PKGNAME)}"
	@Rscript tools/document.R


