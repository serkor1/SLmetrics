pkg-benchmark: ## Run package benchmarks
	@echo $(echo_prefix) "Running performance tests for $(PKGNAME)"
	@echo "==========================================="
	@$(scripts_directory)/run_performance_tests.sh
	@echo $(echo_success) "Performance tests completed successfully"
	@echo $(echo_warning) "Remember to rebuild $(PKGNAME) to use the new data!"

pkg-build: docs-document ## Build and install the package
	@echo $(echo_prefix) "Starting build process of $(PKGNAME)"
	@$(scripts_directory)/build_package.sh $(CHECK)
	@echo $(echo_success) "Build process completed"

pkg-check: ## Run R CMD CHECK
	@$(MAKE) pkg-build CHECK=true

pkg-test: docs-document ## Unit-tests with {testthat}
	@echo $(echo_prefix) "Running unit tests"
	@$(scripts_directory)/run_tests.sh
	@echo $(echo_success) "Unit tests completed"

pkg-r-hub: ## Run R-hub tests
	@echo $(echo_prefix) "Requesting R-hub tests"
	@echo "========================="
	@$(scripts_directory)/run_rhub_checks.sh
	@echo $(echo_success) "R-hub checks requested"

pkg-config: ## Compile configure
	@echo $(echo_prefix) "Compiling configure.ac"
	@echo "========================="
	@autoconf && ./configure
	@echo $(echo_success) "Configure done!"

pkg-format: ## Formate code (change -style=$1 for other styleguides)
	@clang-format -style=LLVM -dump-config > .clang-format
	@clang-format -i src/*.cpp src/*.h inst/include/*.h
	@clang-format -i inst/include/package-code/*.hpp
	@rm .clang-format 
