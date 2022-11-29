-include ../../common/legacy-env-var-support.mk

PROGNAME   := coremark
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

CORE_FILES = core_list_join core_main core_matrix core_state core_util
SOURCES += $(addprefix coremark_v1.0/, $(addsuffix .c,$(CORE_FILES)))
SOURCES += $(wildcard ccproc_port/*.c) $(wildcard ccproc_port/*.S)

COMMON_SOURCES := syscalls.c uart.c core.S core_util.c crc-verification.c

CFLAGS_WARN := -Wall -Wno-format
CFLAGS_OPT  := -O3 -fomit-frame-pointer -finline-functions -finline-limit=1000

CPPFLAGS += -I$(CURDIR)/coremark_v1.0 -I$(CURDIR)/ccproc_port
CPPFLAGS += -DFLAGS_STR='"$(CFLAGS_OPT)"'

ifndef ITERATIONS
	CPPFLAGS += -DITERATIONS=3000
else
 CPPFLAGS += -DITERATIONS=$(ITERATIONS)
endif

ifdef MI16_ENABLE
	CPPFLAGS += -D_MI16_ENABLE -mips16
	ifdef MI16_FLIP
		CPPFLAGS += -mflip-mips16
	endif
endif

CFLAGS += -Wno-strict-prototypes

CPPFLAGS += -D_STARTUP_STACK_SIZE=4096

LDFLAGS += -u _printf_float

ifndef MULTITHREAD
	ifeq ($(CHIPCRAFT_SDK_BOARD),ml605)
		CPPFLAGS += -DMULTITHREAD=3
	endif
else
	CPPFLAGS += -DMULTITHREAD=$(MULTITHREAD)
endif

include $(COMMON_DIR)/generic.mk
