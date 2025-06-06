docs-build: ## Build NEWS and README
	@echo $(echo_prefix) "Building all documentation"
	@$(MAKE) build-news
	@$(MAKE) build-readme
	@echo $(echo_success) "All documentation built successfully"

docs-news: ## Build NEWS
	@echo $(echo_prefix) "Rendering NEWS"
	@$(scripts_directory)/build_news.sh $(reset)
	@echo $(echo_success) "NEWS built successfully"

docs-readme: build ## Build README
	@echo $(echo_prefix) "Rendering README"
	@$(scripts_directory)/build_readme.sh $(reset)
	@echo $(echo_success) "README built successfully"

docs-gitbook: ## Build online documentation
	@echo $(echo_prefix) "Building Gitbook folder"
	@$(scripts_directory)/build_gitbook.sh
	@echo $(echo_success) "Gitbook folder ready"

docs-document: ## Build roxygen documentation
	@echo $(echo_prefix) "Documenting $(PKGNAME)"
	@$(scripts_directory)/build_roxygen.sh
	@echo $(echo_success) "Package documentation updated"

docs-add-entry: ## Create new version enty
	@echo $(echo_prefix) "Creating new NEWS entry for version $(VERSION)"
	@$(scripts_directory)/new_version.sh $(VERSION)
	@echo $(echo_success) "New version entry created"