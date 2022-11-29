-include ../../common/legacy-env-var-support.mk

PROGNAME   := cpp-test
COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common

COMMON_SOURCES := syscalls.c uart.c

# Bigger stack is needed
CPPFLAGS += -D_STARTUP_STACK_SIZE=8192

TEST_STL ?= 1

ifneq ($(TEST_STL),)
  #SIMFLAGS  += --rom 0x00100000
  CPPFLAGS += -DTEST_STL
endif

include $(COMMON_DIR)/generic.mk
