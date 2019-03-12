CCPROG_FLAGS          += --burst

ram-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) $(PROGSREC)

flash-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --data_flash $(PROGSREC)

flash-erase: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --data_flash --erase $(PROGSREC)
