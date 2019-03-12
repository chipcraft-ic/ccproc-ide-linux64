PROGNAME := fpu-arb-test
COMMON_DIR := $(CCSDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c core.S core_util.c

CPPFLAGS += -D_HARD_FLOAT
CPPFLAGS += -mhard-float -msingle-float
CPPFLAGS += -Wdouble-promotion
CPPFLAGS += -fsingle-precision-constant

LDFLAGS += -mhard-float -msingle-float
LDFLAGS += -u _printf_float

ASFLAGS += -D_DONT_BREAK_ON_EXCEPTION

include $(COMMON_DIR)/generic.mk
