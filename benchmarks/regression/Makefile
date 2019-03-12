TESTS := $(shell cat benchmarks.list)
CCSIM_TESTS := $(addsuffix _ccsim,$(TESTS))

# default
all: tests ccsim

.PHONY: all tests ccsim before_tests after_tests $(TESTS) $(CCSIM_TESTS)

tests: before_tests $(TESTS) after_tests
ccsim: before_tests $(CCSIM_TESTS) after_tests

$(TESTS):
	$(MAKE) -C "../$@" clean all ram-write
	sleep 25

$(CCSIM_TESTS):
	$(MAKE) -C "../$@" clean all ccsim
	sleep 25

before_tests:
	@echo "----------------------------------------------------------------------------------"
	@echo "-------------------- START TESTS -------------------------------------------------"
	@echo "----------------------------------------------------------------------------------"

after_tests:
	@echo "----------------------------------------------------------------------------------"
	@echo "-------------------- END TESTS ---------------------------------------------------"
	@echo "----------------------------------------------------------------------------------"

	