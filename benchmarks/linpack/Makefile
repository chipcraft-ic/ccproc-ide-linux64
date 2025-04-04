-include ../../common/legacy-env-var-support.mk

PROGNAME   := linpack
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

CFLAGS_OPT := -Os

CPPFLAGS += -DSP -DROLL

LDFLAGS += -u _printf_float
LDLIBS += -lm

include $(COMMON_DIR)/generic.mk
