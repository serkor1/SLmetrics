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

compile:
	clear
	Rscript -e "Rcpp::compileAttributes()"; \
		echo "Rcpp attributes recompiled."; \

	Rscript modifyRcppExports.R

build: compile
	R CMD build .
	R CMD INSTALL $(TARBALL)
	rm -f $(TARBALL)

check: compile
	clear
	Rscript build.R



