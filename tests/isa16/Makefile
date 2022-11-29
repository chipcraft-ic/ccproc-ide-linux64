-include ../../common/legacy-env-var-support.mk

PROGNAME   := isa16-test
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

ifdef NO_ICACHE
	CPPFLAGS += -DNO_ICACHE
endif
ifdef NO_DCACHE
	CPPFLAGS += -DNO_DCACHE
endif

include $(COMMON_DIR)/generic.mk
