-include ../../common/legacy-env-var-support.mk

PROGNAME   := eth-test
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

ifdef ETH_SIM_TEST
	CFLAGS += -DETH_SIM_TEST
	ASFLAGS += -D_DONT_BREAK_ON_EXCEPTION
endif

include $(COMMON_DIR)/generic.mk
