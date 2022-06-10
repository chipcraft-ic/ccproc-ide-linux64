CCPROG_FLAGS          += --burst --test --jtag
FLASH_DRIVER          := flash/hhg110ullfmc.c
COMMON_SOURCES        += $(FLASH_DRIVER)

flash-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash $(PROGSREC)

flash-verify: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash --verify $(PROGSREC)

flash-erase: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash --erase $(PROGSREC)

flash-erase-all:
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash --erase-all

flash-chip-erase:
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash --chip-erase
