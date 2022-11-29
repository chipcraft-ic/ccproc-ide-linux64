-include ../../common/legacy-env-var-support.mk

PROGNAME   := bitcount
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

ifdef ITERATIONS
CPPFLAGS += -DITERATIONS=$(ITERATIONS)
endif

COMMON_SOURCES := syscalls.c uart.c

LDFLAGS += -u _printf_float
LDLIBS += -lm

include $(COMMON_DIR)/generic.mk
