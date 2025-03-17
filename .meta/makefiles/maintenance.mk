# Clean repository
.PHONY: clean
clean:
	@echo $(ECHO_PREFIX) "Cleaning repository"
	@echo "========================="
	@$(SCRIPTS_DIR)/clean_repo.sh
	@echo $(SUCCESS) "Repository cleaned"

# Purge repository
.PHONY: purge
purge:
	@echo $(ECHO_PREFIX) "Purging repository"
	@echo "========================="
	@$(SCRIPTS_DIR)/purge_repo.sh
	@echo $(SUCCESS) "Repository purged"

# Create new version entry
.PHONY: new-version
new-version:
	@echo $(ECHO_PREFIX) "Creating new NEWS entry for version $(VERSION)"
	@$(SCRIPTS_DIR)/new_version.sh $(VERSION)
	@echo $(SUCCESS) "New version entry created"
