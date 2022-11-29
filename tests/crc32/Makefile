PROGNAME      := crc32

COMMON_SOURCES := syscalls.c uart.c ccproc-verification.c core.S libc_multicore.c core_util.c

LDLIBS += -lm

-include ../../common/legacy-env-var-support.mk
include $(CHIPCRAFT_SDK_HOME)/common/generic.mk
