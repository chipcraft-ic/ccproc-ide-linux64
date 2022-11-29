-include ../../common/legacy-env-var-support.mk

PROGNAME   := fft-test
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c core.S core_util.c pwd_util.c

CPPFLAGS += -D_STARTUP_STACK_SIZE=8192

include $(COMMON_DIR)/generic.mk
