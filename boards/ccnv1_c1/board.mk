CCPROG_FLAGS          += --burst --jtag
FLASH_DRIVER          := flash/hhg110ullfmc.c
ATE_TEST_FUNC         := ate_test_functions.c
COMMON_SOURCES        += $(FLASH_DRIVER)
COMMON_SOURCES        += $(ATE_TEST_FUNC)

flash-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash $(PROGSREC)

flash-erase: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash --erase $(PROGSREC)

