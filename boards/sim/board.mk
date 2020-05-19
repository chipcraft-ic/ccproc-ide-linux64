ifneq ($(CCSDK_USE_JTAG),Yes)
CCPROG_FLAGS          += --burst
endif
