PROGNAME   := basicmath
COMMON_DIR := $(CCSDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

LDFLAGS += -u _printf_float
LDLIBS += -lm

include $(COMMON_DIR)/generic.mk
