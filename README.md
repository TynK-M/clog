# CLogger (`clog`)

A lightweight, macro-based logging library for C with support for multiple log levels and automatic uppercase/lowercase function naming.

>⚠️ **Note**: Due to the use of specific macros, **C++ compatibility is not guaranteed**. This library is designed for C projects.

## Features

* Log levels: `DEBUG`, `INFO`, `WARNING`, `ERROR`, `CRITICAL`
* Simple macros to define logging functions automatically
* Prints log level in uppercase while allowing lowercase function names
* Easily extendable by modifying the `LOG_LEVELS` macro
* Minimal dependencies — works with standard C (`stdio.h`)

## Installation

1. Include `clog.h` and define `CLOG`:

```c
#define CLOG

#include "clog.h"
```

---

## Usage

### Initialize a logger

```c
CLogger logger = init_clog(.level=DEBUG);
```
If `.level` is not passed the used level will be `INFO`.

### Logging messages

Use the automatically generated logging functions:

```c
clog_debug(logger, "This is a debug message");
clog_info(logger, "This is an info message");
clog_warn(logger, "This is a warning message");
clog_err(logger, "This is an error message");
clog_crit(logger, "This is a critical message");
```

* Functions are generated via macros from the `LOG_LEVELS` macro.
* The printed log level is always uppercase:

```
[DEBUG] This is a debug message
[INFO] This is an info message
[WARNING] This is a warning message
```

## Customization

The log levels and function names are defined in `clog.h`:

```c
#define LOG_LEVELS(X) \
    X(DEBUG, debug)   \
    X(INFO, info)     \
    X(WARNING, warn)  \
    X(ERROR, err)     \
    X(CRITICAL, crit)
```

* First parameter → enum constant (uppercase)
* Second parameter → function suffix (lowercase)

You can add or remove levels easily by editing this macro.

---

## Example

```c
#include "clog.h"

int main() {
    CLogger logger = init_clog(.level=WARNING);

    clog_debug(logger, "Debug message");    // Will not print
    clog_info(logger, "Info message");      // Will not print
    clog_warn(logger, "Warning message");   // Will print

    return 0;
}
```

Output:

```bash
[WARNING] Warning message
```

---

## License

MIT License. Free to use and modify.