-include ../../common/legacy-env-var-support.mk

PROGNAME   := whetstone
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

ifdef LOOPS
	CPPFLAGS += -DLOOPS=$(LOOPS)
endif

ifdef PRINTOUT
	CPPFLAGS += -DPRINTOUT
endif

ifdef MI16_ENABLE
	CPPFLAGS += -D_MI16_ENABLE -mips16
	ifdef MI16_FLIP
		CPPFLAGS += -mflip-mips16
	endif
endif

COMMON_SOURCES := syscalls.c uart.c

LDFLAGS += -u _printf_float
LDLIBS += -lm

include $(COMMON_DIR)/generic.mk
