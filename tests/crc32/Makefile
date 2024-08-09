PROGNAME      := crc32

COMMON_SOURCES := syscalls.c uart.c crc-verification.c core.S core_util.c

LDLIBS += -lm

-include ../../common/legacy-env-var-support.mk
include $(CHIPCRAFT_SDK_HOME)/common/generic.mk
