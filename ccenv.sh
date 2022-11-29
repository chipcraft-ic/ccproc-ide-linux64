#!/bin/bash
self_dir=$(readlink -f "$(dirname "$BASH_SOURCE")")

# Defaults
CHIPCRAFT_SDK_BOARD="sim"
CHIPCRAFT_SDK_DBG_PORT=""
CHIPCRAFT_SDK_UART_PORT=""
CHIPCRAFT_SDK_USE_JTAG="No"
CHIPCRAFT_SDK_JTAG_FLAG="--jtag"

# Override defaults using file in home directory
if [ -f "$HOME/.ccenv" ]; then
  . "$HOME/.ccenv"
fi

export CHIPCRAFT_SDK_HOME="$self_dir"

echo -n "Available boards: "
ls $CHIPCRAFT_SDK_HOME/boards

read -p "Board [$CHIPCRAFT_SDK_BOARD]: " input
export CHIPCRAFT_SDK_BOARD="${input:-$CHIPCRAFT_SDK_BOARD}"

read -e -p "Use OLIMEX ARM-USB-OCD-H JTAG debugger? (Type Yes or No.) [$CHIPCRAFT_SDK_USE_JTAG]: " input
export CHIPCRAFT_SDK_USE_JTAG="${input:-$CHIPCRAFT_SDK_USE_JTAG}"

echo -n "Available ports: "
ls /dev/ttyUSB*

read -e -p "Debug Port (e.g. /dev/ttyUSBn) [$CHIPCRAFT_SDK_DBG_PORT]: " input
export CHIPCRAFT_SDK_DBG_PORT="${input:-$CHIPCRAFT_SDK_DBG_PORT}"

read -e -p "UART Port (e.g. /dev/ttyUSBn) [$CHIPCRAFT_SDK_UART_PORT]: " input
export CHIPCRAFT_SDK_UART_PORT="${input:-$CHIPCRAFT_SDK_UART_PORT}"

export PATH="$PATH:${CHIPCRAFT_SDK_TOOLCHAIN_PATH}:${CHIPCRAFT_SDK_HOME}/tools/srecord:${CHIPCRAFT_SDK_HOME}/tools/resources/linux/srecord"

export CHIPCRAFT_SDK_USE_JTAG
if [[ "$CHIPCRAFT_SDK_USE_JTAG" == "Yes" ]]; then
	CHIPCRAFT_SDK_JTAG_FLAG="--jtag"
	export CHIPCRAFT_SDK_JTAG_FLAG
fi

cat >"$HOME/.ccenv" <<EOF
CHIPCRAFT_SDK_BOARD="$CHIPCRAFT_SDK_BOARD"
CHIPCRAFT_SDK_DBG_PORT="$CHIPCRAFT_SDK_DBG_PORT"
CHIPCRAFT_SDK_UART_PORT="$CHIPCRAFT_SDK_UART_PORT"
CHIPCRAFT_SDK_USE_JTAG="$CHIPCRAFT_SDK_USE_JTAG"
CHIPCRAFT_SDK_JTAG_FLAG="$CHIPCRAFT_SDK_JTAG_FLAG"
EOF

if [[ $PS1 != CC* ]]; then
  export PS1="CC $PS1"
fi
if [ "$0" = "$BASH_SOURCE" ]; then
  # Script was started as new process instead of being sourced
  echo "Starting new shell"
  bash --rcfile <(cat ~/.bashrc; echo 'PS1="CC $PS1"')
fi
