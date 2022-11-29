-include ../../common/legacy-env-var-support.mk

PROGNAME   := mem-map-test
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c rtc_util.c

ifdef MEM_SIM_TEST
CFLAGS += -DMEM_SIM_TEST
endif

include $(COMMON_DIR)/generic.mk
