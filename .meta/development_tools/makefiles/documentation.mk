# Build NEWS document
.PHONY: build-news
build-news:
	@echo $(echo_prefix) "Rendering NEWS"
	@$(scripts_directory)/build_news.sh $(reset)
	@echo $(echo_success) "NEWS built successfully"

# Build readme document
.PHONY: build-readme
build-readme: build
	@echo $(echo_prefix) "Rendering README"
	@$(scripts_directory)/build_readme.sh $(reset)
	@echo $(echo_success) "README built successfully"

# Build all meta documentation
.PHONY: build-meta
build-meta:
	@echo $(echo_prefix) "Building all documentation"
	@$(MAKE) build-news
	@$(MAKE) build-readme
	@echo $(echo_success) "All documentation built successfully"

# Build docs
.PHONY: build-gitbook
build-gitbook:
	@echo $(echo_prefix) "Building Gitbook folder"
	@$(scripts_directory)/build_gitbook.sh
	@echo $(echo_success) "Gitbook folder ready"

# Document the package functions
.PHONY: document
document:
	@echo $(echo_prefix) "Documenting $(PKGNAME)"
	@$(scripts_directory)/build_roxygen.sh
	@echo $(echo_success) "Package documentation updated"
