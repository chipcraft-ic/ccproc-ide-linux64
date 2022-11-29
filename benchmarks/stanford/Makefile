-include ../../common/legacy-env-var-support.mk

PROGNAME   := stanford
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

CFLAGS_OPT := -Os

LDFLAGS += -u _printf_float
LDLIBS += -lm

include $(COMMON_DIR)/generic.mk
