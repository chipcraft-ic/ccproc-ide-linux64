ifneq ($(CCSDK_USE_JTAG),Yes)
CCPROG_FLAGS          += --burst
endif

MAX2771_DRIVER        := max2771/max2771.c
COMMON_SOURCES        += $(MAX2771_DRIVER)

ram-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) $(PROGSREC)

flash-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --data_flash $(PROGSREC)

flash-erase: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --data_flash --erase $(PROGSREC)
