PROGNAME   := isa32ds-test
COMMON_DIR := $(CCSDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

ifdef NO_ICACHE
	CPPFLAGS += -DNO_ICACHE
endif
ifdef NO_DCACHE
	CPPFLAGS += -DNO_DCACHE
endif

include $(COMMON_DIR)/generic.mk
