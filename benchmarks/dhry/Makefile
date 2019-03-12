PROGNAME   := dhry
COMMON_DIR := $(CCSDK_HOME)/common

DEFAULT_COMMON_SOURCES ?= board.c
COMMON_SOURCES := syscalls.c uart.c

ifndef RUNS_NUMBER
	CPPFLAGS += -DRUNS_NUMBER=1500000
else
	CPPFLAGS += -DRUNS_NUMBER=$(RUNS_NUMBER)
endif

ifdef MI16_ENABLE
	CPPFLAGS += -D_MI16_ENABLE -mips16
	ifdef MI16_FLIP
		CPPFLAGS += -mflip-mips16
	endif
endif

#CPPFLAGS += -DREG=register
CPPFLAGS += -DHZ=1000 # see _CLOCKS_PER_SEC_ definition in NewLib
CPPFLAGS += -DNO_DEFAULT_SBRK

CFLAGS_WARN := -Wno-implicit-function-declaration
CFLAGS_OPT  := -O3 -fno-inline-functions

LDFLAGS += -u _printf_float

# Put .data section in SPRAM
#LINKERSCRIPT := ccproc.ld
#STARTUP_SRC := startup.S

include $(COMMON_DIR)/generic.mk
