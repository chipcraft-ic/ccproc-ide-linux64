CCPROG_FLAGS           = --mcu $(CHIPCRAFT_SDK_MCU)
ifeq ($(CHIPCRAFT_SDK_USE_JTAG),Yes)
 CCPROG_FLAGS          += $(CHIPCRAFT_SDK_JTAG_FLAG)
else
 CCPROG_FLAGS          += -p $(CHIPCRAFT_SDK_DBG_PORT) -b 38400
endif

FLASH_DRIVER           := flash/hhg110ullfmc.c
COMMON_SOURCES         += $(FLASH_DRIVER)

flash-write: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash $(PROGSREC)

flash-erase: $(PROGSREC)
	$(Q)$(CCPROG) $(CCPROG_FLAGS) --flash --erase $(PROGSREC)

