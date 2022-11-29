ifneq ($(CHIPCRAFT_SDK_USE_JTAG),Yes)
CCPROG_FLAGS          += --burst
endif

ram-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) $(PROGSREC)

flash-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --data_flash $(PROGSREC)

flash-erase: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --data_flash --erase $(PROGSREC)
