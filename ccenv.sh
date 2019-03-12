#!/bin/bash
self_dir=$(readlink -f "$(dirname "$BASH_SOURCE")")

# Defaults
CCSDK_BOARD="sim"
CCSDK_DBG_PORT=""
CCSDK_UART_PORT=""

# Override defaults using file in home directory
if [ -f "$HOME/.ccenv" ]; then
  . "$HOME/.ccenv"
fi

export CCSDK_HOME="$self_dir"

echo -n "Available boards: "
ls $CCSDK_HOME/boards

read -p "Board [$CCSDK_BOARD]: " input
export CCSDK_BOARD="${input:-$CCSDK_BOARD}"

echo -n "Available ports: "
ls /dev/ttyUSB*

read -e -p "Debug Port (e.g. /dev/ttyUSBn) [$CCSDK_DBG_PORT]: " input
export CCSDK_DBG_PORT="${input:-$CCSDK_DBG_PORT}"

read -e -p "UART Port (e.g. /dev/ttyUSBn) [$CCSDK_UART_PORT]: " input
export CCSDK_UART_PORT="${input:-$CCSDK_UART_PORT}"

export PATH="$PATH:$CCSDK_HOME/toolchain/mips-cc-elf/bin"

cat >"$HOME/.ccenv" <<EOF
CCSDK_BOARD="$CCSDK_BOARD"
CCSDK_DBG_PORT="$CCSDK_DBG_PORT"
CCSDK_UART_PORT="$CCSDK_UART_PORT"
EOF

if [[ $PS1 != CC* ]]; then
  export PS1="CC $PS1"
fi
if [ "$0" = "$BASH_SOURCE" ]; then
  # Script was started as new process instead of being sourced
  echo "Starting new shell"
  bash --rcfile <(cat ~/.bashrc; echo 'PS1="CC $PS1"')
fi
