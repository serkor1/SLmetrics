# Run performance tests
.PHONY: performance
performance:
	@echo $(ECHO_PREFIX) "Running performance tests for $(PKGNAME)"
	@echo "==========================================="
	@$(SCRIPTS_DIR)/run_performance_tests.sh
	@echo $(SUCCESS) "Performance tests completed successfully"
	@echo $(WARNING) "Remember to rebuild $(PKGNAME) to use the new data!"

# Build and install the package
.PHONY: build
build: document
	@echo $(ECHO_PREFIX) "Starting build process of $(PKGNAME)"
	@$(SCRIPTS_DIR)/build_package.sh $(CHECK)
	@echo $(SUCCESS) "Build process completed"

# Check the package
.PHONY: check
check:
	@$(MAKE) build CHECK=true

# Run unit tests
.PHONY: test-pkg
test-pkg: document
	@echo $(ECHO_PREFIX) "Running unit tests"
	@$(SCRIPTS_DIR)/run_tests.sh
	@echo $(SUCCESS) "Unit tests completed"

# Run R-hub checks
.PHONY: r-hub-check
r-hub-check:
	@echo $(ECHO_PREFIX) "Requesting R-hub tests"
	@echo "========================="
	@$(SCRIPTS_DIR)/run_rhub_checks.sh
	@echo $(SUCCESS) "R-hub checks requested"