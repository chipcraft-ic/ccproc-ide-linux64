HW_TESTS   := $(shell cat tests.list)
SIM_TESTS  := $(addsuffix _ccsim,$(HW_TESTS))
STDOUT_LOG ?= $(CURDIR)/tests.log
TEMP_LOG   ?= /tmp/cctest-last.log

Q ?= @

ANSI_YELLOW := \e[93m\e[1m
ANSI_RESET := \e[0m

# default
all: tests ccsim

.PHONY: all tests ccsim before_tests after_tests $(HW_TESTS) $(SIM_TESTS)

tests: before_tests $(HW_TESTS) after_tests parse_logs
sim-tests: before_tests $(SIM_TESTS) after_tests parse_logs

$(HW_TESTS):
	@echo -ne "$(ANSI_YELLOW)Compiling $@$(ANSI_RESET)\n"
	$(Q)$(MAKE) -C "../$@" clean all
	@echo -ne "$(ANSI_YELLOW)Running $@$(ANSI_RESET)\n"
	$(Q)cd "../$@" && $(CURDIR)/run-hw-test.sh "$(TEMP_LOG)"
	$(Q)cat "$(TEMP_LOG)" >> "$(STDOUT_LOG)"

$(SIM_TESTS):
	@echo -ne "$(ANSI_YELLOW)Compiling $@$(ANSI_RESET)\n"
	$(Q)$(MAKE) -C "../$(subst _ccsim,,$@)" clean
	$(Q)$(MAKE) -C "../$(subst _ccsim,,$@)"
	@echo -ne "$(ANSI_YELLOW)Running $@$(ANSI_RESET)\n"
	$(Q)$(MAKE) -C "../$(subst _ccsim,,$@)" sim | tee -a "$(STDOUT_LOG)"

before_tests:
	@echo "------------------------------------------------------------------------------"
	@echo "-------------------------------- START TESTS ---------------------------------"
	@echo "------------------------------------------------------------------------------"
	@echo "--- Started all tests ($(shell date)) ---" >"$(STDOUT_LOG)"

after_tests:
	@echo "------------------------------------------------------------------------------"
	@echo "--------------------------------- END TESTS ----------------------------------"
	@echo "------------------------------------------------------------------------------"

parse_logs:
	@echo -e "\n------------------------------------------------------------------------------" >> "$(STDOUT_LOG)"
	@echo -e "---------------------------------- SUMMARY -----------------------------------"   >> "$(STDOUT_LOG)"
	@echo -e "------------------------------------------------------------------------------\n" >> "$(STDOUT_LOG)"
	@./logParser.sh $(STDOUT_LOG)
