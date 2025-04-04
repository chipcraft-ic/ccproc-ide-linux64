-include ../../common/legacy-env-var-support.mk

PING_PONG_DEBUG ?= 0

export COMMON_DIR := $(CHIPCRAFT_SDK_HOME)/common
export COMMON_SOURCES := syscalls.c uart.c

CPPFLAGS += -DPING_PONG_DEBUG=$(PING_PONG_DEBUG)
LDFLAGS += -u _printf_float

all: $(CURDIR)/build/rx/ping-pong-rx.srec $(CURDIR)/build/tx/ping-pong-tx.srec

$(CURDIR)/build/rx/ping-pong-rx.srec: export PROGNAME = ping-pong-rx
$(CURDIR)/build/rx/ping-pong-rx.srec: export BUILDDIR = $(CURDIR)/build/rx
$(CURDIR)/build/rx/ping-pong-rx.srec: export PING_PONG_TRX = RX
$(CURDIR)/build/rx/ping-pong-rx.srec: export CPPFLAGS += -DPING_PONG_TRX=RX
$(CURDIR)/build/rx/ping-pong-rx.srec:
	$(MAKE) -f $(COMMON_DIR)/generic.mk all

$(CURDIR)/build/tx/ping-pong-tx.srec: export PROGNAME = ping-pong-tx
$(CURDIR)/build/tx/ping-pong-tx.srec: export BUILDDIR = $(CURDIR)/build/tx
$(CURDIR)/build/tx/ping-pong-tx.srec: export PING_PONG_TRX = TX
$(CURDIR)/build/tx/ping-pong-tx.srec: export CPPFLAGS += -DPING_PONG_TRX=TX
$(CURDIR)/build/tx/ping-pong-tx.srec:
	$(MAKE) -f $(COMMON_DIR)/generic.mk all

