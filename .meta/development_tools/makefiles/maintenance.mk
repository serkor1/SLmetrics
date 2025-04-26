# Clean repository
.PHONY: clean
clean:
	@echo $(echo_prefix) "Cleaning repository"
	@echo "========================="
	@$(scripts_directory)/clean_repo.sh
	@echo $(echo_success) "Repository cleaned"

# Purge repository
.PHONY: purge
purge:
	@echo $(echo_prefix) "Purging repository"
	@echo "========================="
	@$(scripts_directory)/purge_repo.sh
	@echo $(echo_success) "Repository purged"

# Create new version entry
.PHONY: new-version
new-version:
	@echo $(echo_prefix) "Creating new NEWS entry for version $(VERSION)"
	@$(scripts_directory)/new_version.sh $(VERSION)
	@echo $(echo_success) "New version entry created"
