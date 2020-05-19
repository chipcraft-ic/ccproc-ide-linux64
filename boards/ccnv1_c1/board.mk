CCPROG_FLAGS          += --burst
FLASH_DRIVER          := flash/hhg110ullfmc.c
COMMON_SOURCES        += $(FLASH_DRIVER)

flash-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash $(PROGSREC)

flash-erase: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash --erase $(PROGSREC)

