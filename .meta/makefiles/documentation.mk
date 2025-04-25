# Build NEWS document
.PHONY: build-news
build-news:
	@echo $(ECHO_PREFIX) "Rendering NEWS"
	@$(SCRIPTS_DIR)/build_news.sh $(RESET)
	@echo $(SUCCESS) "NEWS built successfully"

# Build readme document
.PHONY: build-readme
build-readme: build
	@echo $(ECHO_PREFIX) "Rendering README"
	@$(SCRIPTS_DIR)/build_readme.sh $(RESET)
	@echo $(SUCCESS) "README built successfully"

# Build all meta documentation
.PHONY: build-meta
build-meta:
	@echo $(ECHO_PREFIX) "Building all documentation"
	@$(MAKE) build-news
	@$(MAKE) build-readme
	@echo $(SUCCESS) "All documentation built successfully"

# Build docs
.PHONY: build-gitbook
build-gitbook:
	@echo $(ECHO_PREFIX) "Building Gitbook folder"
	@$(SCRIPTS_DIR)/build_gitbook.sh
	@echo $(SUCCESS) "Gitbook folder ready"

# Document the package functions
.PHONY: document
document:
	@echo $(ECHO_PREFIX) "Documenting $(PKGNAME)"
	@Rscript $(DEVTOOLS_DIR)/document.R
	@echo $(SUCCESS) "Package documentation updated"
