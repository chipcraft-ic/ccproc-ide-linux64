ifneq ($(CHIPCRAFT_SDK_USE_JTAG),Yes)
CCPROG_FLAGS          += --burst
endif
