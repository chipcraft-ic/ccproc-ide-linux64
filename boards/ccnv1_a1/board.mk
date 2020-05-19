CCPROG_FLAGS           = --mcu $(CCSDK_MCU)
ifeq ($(CCSDK_USE_JTAG),Yes)
 CCPROG_FLAGS          += $(CCSDK_JTAG_FLAG)
else
 CCPROG_FLAGS          += -p $(CCSDK_DBG_PORT) -b 38400
endif

FLASH_DRIVER           := flash/hhg110ullfmc.c
COMMON_SOURCES         += $(FLASH_DRIVER)

flash-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash $(PROGSREC)

flash-erase: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash --erase $(PROGSREC)

