PROGNAME   := paranoia
COMMON_DIR := $(CCSDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

CPPFLAGS += -D_STARTUP_STACK_SIZE=8192

CFLAGS_OPT := -Os

CPPFLAGS += -DNOPAUSE

LDFLAGS += -u _printf_float
LDLIBS += -lm

include $(COMMON_DIR)/generic.mk
