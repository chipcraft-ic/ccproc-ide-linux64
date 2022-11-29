-include ../../common/legacy-env-var-support.mk

PROGNAME   := i2c-test
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c core.S

CPPLAGS += -D_STARTUP_STACK_SIZE=4096

include $(COMMON_DIR)/generic.mk
