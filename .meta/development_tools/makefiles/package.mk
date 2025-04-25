# Run performance tests
.PHONY: performance
performance:
	@echo $(echo_prefix) "Running performance tests for $(PKGNAME)"
	@echo "==========================================="
	@$(scripts_directory)/run_performance_tests.sh
	@echo $(echo_success) "Performance tests completed successfully"
	@echo $(echjo_warning) "Remember to rebuild $(PKGNAME) to use the new data!"

# Build and install the package
.PHONY: build
build: document
	@echo $(echo_prefix) "Starting build process of $(PKGNAME)"
	@$(scripts_directory)/build_package.sh $(CHECK)
	@echo $(echo_success) "Build process completed"

# Check the package
.PHONY: check
check:
	@$(MAKE) build CHECK=true

# Run unit tests
.PHONY: test-pkg
test-pkg: document
	@echo $(echo_prefix) "Running unit tests"
	@$(scripts_directory)/run_tests.sh
	@echo $(echo_success) "Unit tests completed"

# Run R-hub checks
.PHONY: r-hub-check
r-hub-check:
	@echo $(echo_prefix) "Requesting R-hub tests"
	@echo "========================="
	@$(scripts_directory)/run_rhub_checks.sh
	@echo $(echo_success) "R-hub checks requested"