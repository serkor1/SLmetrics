repo-init: ## Initialize repository
	@echo $(echo_prefix) "Setting up build system"
	@chmod +x $(scripts_directory)/*.sh
	@echo $(echo_success) "Build system installed"

repo-clean: ## Delete all pkg-build artifacts
	@echo $(echo_prefix) "Cleaning repository"
	@echo "========================="
	@$(scripts_directory)/clean_repo.sh
	@echo $(echo_success) "Repository cleaned"

repo-purge: ## Delete all untracked files and branches except main and development
	@echo $(echo_prefix) "Purging repository"
	@echo "========================="
	@$(scripts_directory)/purge_repo.sh
	@echo $(echo_success) "Repository purged"
