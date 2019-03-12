CCSDK
=====

Software Development Kit for ChipCraft microcontrollers.

Requirements
------------

Python interpreter is required for debugging support. Python 2 is recommended but Python 3 should work too. You can download Python interpreter from [https://www.python.org/downloads/] or your Linux package manager.

Install required Python modules:

    pip install pyserial

Usage
-----

Start CCIDE by running `ide/ccide` executable file.
IDE has special support for CCSDK projects.
To create a new project or import existing one click `New -> CCSDK Project...` and
follow instructions from the wizard.
To build click hammer icon.
To start a hardware debugging session create `CCSDK Application` launch configuration.
To start a simulation create `CCSDK Simulation` launch configuration.
To write program in RAM or Flash memory select `Write RAM Memory` or `Write Flash Memory`
in Build Targets (in project tree).

Usage (in terminal)
-------------------

SDK uses environment variables for its configuration.

To simplify environment configuration `ccenv.sh`/`ccenv.cmd` scripts are provided.

Essential environment variables:

* `CCSDK_HOME` - CCSDK root directory, e.g. `/home/user/ccsdk`
* `CCSDK_DBG_PORT` - debug UART port, e.g. `/dev/ttyUSB1` (Linux), `COM1` (Windows)
* `CCSDK_UART_PORT` - console UART port, e.g. `/dev/ttyUSB2` (Linux), `COM2` (Windows)
* `CCSDK_BOARD` - board identifier (see `boards` directory for example names), e.g. `ml605`

CCSDK contains script for quick definition of those variables.
Please run `ccenv.cmd` on Windows or `ccenv.sh` on Linux.
`ccenv` script sets `CCSDK_HOME` to current directory and asks user for values for the rest of variables.

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
`toolchain`      | GNU compiler toolchain (GCC, BinUtils, GDB, NewLib)
`tools`          | Tools for programming and debugging (e.g. ccprog, dbgserver)
