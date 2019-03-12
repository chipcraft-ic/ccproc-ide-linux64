PROGNAME   := coremark
COMMON_DIR := $(CCSDK_HOME)/common

CORE_FILES = core_list_join core_main core_matrix core_state core_util
SOURCES += $(addprefix coremark_v1.0/, $(addsuffix .c,$(CORE_FILES)))
SOURCES += $(wildcard ccproc_port/*.c) $(wildcard ccproc_port/*.S)

COMMON_SOURCES := syscalls.c uart.c core.S

CFLAGS_WARN := -Wall -Wno-format
CFLAGS_OPT  := -O3 -fomit-frame-pointer -finline-functions -finline-limit=1000

CPPFLAGS += -Icoremark_v1.0 -Iccproc_port
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
	ifeq ($(CCSDK_BOARD),ml605)
		CPPFLAGS += -DMULTITHREAD=3
	endif
else
	CPPFLAGS += -DMULTITHREAD=$(MULTITHREAD)
endif

include $(COMMON_DIR)/generic.mk
