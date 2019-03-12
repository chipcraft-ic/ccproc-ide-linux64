PROGNAME   := mem-map-test
COMMON_DIR := $(CCSDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

ifdef MEM_SIM_TEST
CFLAGS += -DMEM_SIM_TEST
endif

include $(COMMON_DIR)/generic.mk
