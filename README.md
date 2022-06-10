CCSDK
=====

Software Development Kit for ChipCraft microcontrollers.

Requirements
------------

Python interpreter is required for debugging support. Python 2 is recommended but Python 3 should work too. You can download Python interpreter from [https://www.python.org/downloads/] or your Linux package manager.

Install required Python modules:

    pip install pyserial

Add program srec_cat to PATH variable. The binary for Linux is distributed as:
tools/resources/linux/srecord/srec_cat
This binary will be needed by ccprog.

Building ccsim from sources for Windows with PGO-optimization shall require
'wine'. It's recommended to install 'wine' using guide posted on WineHQ page:
https://wiki.winehq.org/Ubuntu

Usage (with GUI)
----------------

CCIDE user guide is located in `docs/user_guide` folder.

Usage (in terminal)
-------------------

SDK uses environment variables for its configuration.

To simplify environment configuration `ccenv.sh`/`ccenv.cmd` scripts are provided.

Essential environment variables:

* `CCSDK_HOME` - CCSDK root directory, e.g. `/home/user/ccsdk`
* `CCSDK_DBG_PORT` - debug UART port, e.g. `/dev/ttyUSB1` (Linux), `COM1` (Windows)
* `CCSDK_UART_PORT` - console UART port, e.g. `/dev/ttyUSB2` (Linux), `COM2` (Windows)
* `CCSDK_BOARD` - board identifier (see `boards` directory for example names), e.g. `ml605`
* `CCSDK_TOOLCHAIN_PATH` - path to MIPS toolchain binaries, e.g. /usr/local/mips-cc-elf/x86_64-chipcraft-linux-gnu/bin
* `CCSDK_LINUX_IDE_PATH` - path to Eclipse-based IDE for Linux platform, used to generate distribution package
* `CCSDK_WINDOWS_IDE_PATH` - path to Eclipse-based IDE for Windows platform, used to generate distribution package
* `PATH` - search paths for executable binaries, ${CCSDK_HOME}/tools/srecord (for release) and ${CCSDK_HOME}/tools/resources/{linux,windows}/srecord (for development) have to be added to PATH for ccprog to work correctly

CCSDK contains script for quick definition of those variables.
Please run `ccenv.cmd` on Windows or `ccenv.sh` on Linux.
`ccenv` script sets `CCSDK_HOME` to current directory and asks user for values for the rest of variables.

Optional environment variables:

* `CCSDK_TOOLS_PATH` - path to binaries of Chipcraft tools, default for distribution is ${CCSDK_HOME}/tools
* `VERILATOR_ROOT` - Verilator installation root directory, e.g. `/usr/local/share/verilator`
* `VTESTBENCH_ROOT` - VTestbench project files directory`

To build ccsim from source, both of these variables have to be defined.
Otherwise prebuilt ccsim version will be used.

Building example projects (in terminal)
---------------------------------------

SDK examples are built using GNU Make tool. All samples in the SDK include the generic Makefile (`common/generic.mk`) to avoid code repetition. SDK user can use the same approach.

When using SDK Makefiles following targets are available:

* `all` (default) - build the program,
* `clean` - remove build output,
* `ram-write` - write program into RAM memory,
* `flash-write` - write program into Flash memory (permanent),
* `debug` - run GDB debugger and connect to microcontroller,
* `term` - simple UART terminal connected to `CCSDK_UART_PORT`,
* `sim` - run program in CCSDK included simulator,
* `sim-debug` - run GDB and connect it to a program in the simulator,

To build and save in RAM `hello-world` example run:

    cd examples/hello-world
    make
    make ram-write term

Variables available in a SDK project Makefile (e.g. `examples/hello-world/Makefile`):

* `PROGNAME` - program name - used in names of generated files,
* `COMMON_SOURCES` - name of files from `common` and `drivers` directories to be included into project build,
* `SOURCE_DIRS` - list of directories to search for source code (project root is always used),
* `BUILDDIR` - name of output directory,
* `CFLAGS` - additional C compiler flags,
* `CXXFLAGS` - additional C++ compiler flags,
* `ASFLAGS` - additional GNU Assembler flags,
* `CPPFLAGS` - additional C preprocessor flags (used when compiling .c/.cpp/.S files),
* `LDFLAGS` - additional linker flags,
* `LDLIBS` - additional libraries to link,

Common sources:

`syscalls.c` - needed for C Standard Library implementation (NewLib),
`uart.c` - basic UART support - needed by `syscalls.c`,
`startup.S` - start code used by every program for microcontroller,
`core.S` - source code needed to use multiple processor cores,

SDK Content
-----------

Directory        | Description
---------------- | -----------
`common`         | Common sources used by applications
`docs`           | SDK Documentation
`drivers`        | Source code of device drivers, similar to `common`
`examples`       | Sample code for microcontroller. Can be used as template for a new project.
`ide`            | Eclipse-based IDE for ChipCraft microcontrollers
`include`        | Microcontroller header files
`linker`         | GNU LD compatible linker script
`svd`            | System View Description files
`tests`          | Source code of microcontroller tests. Can be used as examples of peripherial usage.
`tools`          | Tools for programming and debugging (e.g. ccprog, dbgserver)
