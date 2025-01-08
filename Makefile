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
	@clear
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

document:
	@clear
	@echo "📚 Documenting {$(PKGNAME)}"
	@quarto render README.qmd
	@quarto render NEWS.qmd
	@Rscript tools/document.R

build: document
	@echo "▶️ Starting build process of {$(PKGNAME)}"
	@echo "⚒️ Building {$(PKGNAME)} ..."
	@rm -f src/*.o src/*.so
	@R CMD build . > /dev/null 2>&1
	@echo "✅ Done!"
	@echo "⚒️ Installing {$(PKGNAME)} ..."
	@R CMD INSTALL $(TARBALL) > /dev/null 2>&1
	@echo "✅ Done!"
	@rm -f $(TARBALL)
	@rm -f src/*.o src/*.so
	@quarto render README.qmd
	@quarto render NEWS.qmd
	$(MAKE) build-docs
	@echo "✅ Build process done!"

check: document
	@echo "▶️ Starting R CMD check process of {$(PKGNAME)}"
	@rm -f src/*.o src/*.so
	@echo "⚒️ Building {$(PKGNAME)} ..."
	@R CMD build . > /dev/null 2>&1
	@echo "✅ Done!"
	@echo "🔎 Checking {$(PKGNAME)} ..."
	@R CMD check --no-manual --as-cran $(TARBALL)
	@echo "⚒️ Installing {$(PKGNAME)} ..."
	@R CMD INSTALL $(TARBALL) > /dev/null 2>&1
	@echo "✅ Done!"
	@rm -f $(TARBALL)
	@rm -rf $(PKGNAME).Rcheck
	@rm -f src/*.o src/*.so
	@quarto render README.qmd
	@quarto render NEWS.qmd
	@echo "✅ R CMD check process done!"


build-docs:
	@echo "📚 Building Quarto Book"
	@python3 tools/YAML.py
	cd docs/ && quarto preview