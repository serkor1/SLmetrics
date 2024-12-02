# This makefile mimics
# the functionality of devtools::check() and devtools::document()
# but without triggering the entire re-writing
# of the package that rewrites RcppExports.R

#!/bin/sh
# global variables
PKGNAME = SLmetrics
VERSION = $(shell grep "^Version:" DESCRIPTION | sed "s/Version: //")
TARBALL = $(PKGNAME)_$(VERSION).tar.gz

py-setup:
	@echo "Setting up Python environment"
	@echo "============================="
	@python -m venv .venv
	@echo "Activating virtual environment"
	@pip cache purge
	@python -m pip install --upgrade pip
	@pip install numpy scipy torch torchmetrics scikit-learn imbalanced-learn mkl mkl-service mkl_fft mkl_random
	@echo "Done!"

py-check:
	@echo "Checking installed python modules"
	@echo "================================="
	@pip list

document:
	clear
	@echo "Documenting {$(PKGNAME)}"
	@Rscript tools/document.R

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

build-site:
	@echo "Building {pkgdown}"
	@Rscript -e "pkgdown::build_site()"
	
preview:
	@xdg-open docs/index.html
