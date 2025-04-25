# Load common variables
include .meta/development_tools/makefiles/variables.mk

# Default target
.PHONY: all
all: build

# Install target - sets permissions correctly
.PHONY: install-build-system
install-build-system:
	@echo $(echo_prefix) "Setting up build system"
	@chmod +x .meta/scripts/*.sh
	@echo $(echo_success) "Build system installed"

# Load modular makefiles
include .meta/development_tools/makefiles/documentation.mk
include .meta/development_tools/makefiles/package.mk
include .meta/development_tools/makefiles/maintenance.mk

# Default help target
.PHONY: help
help:
	@echo "{SLmetrics} Package Build System"
	@echo "================================"
	@echo ""
	@echo "Documentation:"
	@echo "  make build-meta      - Build README and NEWS files"
	@echo "  make build-news      - Build only NEWS file"
	@echo "  make build-readme    - Build only README file"
	@echo "  make build-gitbook   - Build only Gitbook files"
	@echo "  make document        - Update package documentation"
	@echo ""
	@echo "Package Building:"
	@echo "  make build           - Build and install the package"
	@echo "  make check           - Build, check and install the package"
	@echo "  make test-pkg        - Run unit tests"
	@echo "  make r-hub-check     - Run R-hub checks"
	@echo ""
	@echo "Maintenance:"
	@echo "  make performance     - Run performance tests"
	@echo "  make clean           - Clean repository"
	@echo "  make purge           - Aggressively clean repository. Deletes all branches except main and development."
	@echo "  make new-version     - Create a new NEWS entry"
	@echo ""
	@echo "Options:"
	@echo "  RESET=true           - Reset cache when building documentation"
	@echo "  CHECK=true           - Run R CMD check before installing"