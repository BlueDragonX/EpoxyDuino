# Changelog

* Unreleased
* 1.3.1 (2022-08-13)
    * Add `tone()` and `noTone()` stubs. By @kwisii in
      [PR#69](https://github.com/bxparks/EpoxyDuino/pull/69).
    * Add `uint8_t digitalWriteValue(pin)` which returns the value of the
      most recent `digitalWrite(pin, val)`. By @kwisii in
      [PR#68](https://github.com/bxparks/EpoxyDuino/pull/68).
* 1.3.0 (2022-03-28)
    * Add support for `EXTRA_CPPFLAGS`, similar to `EXTRA_CXXFLAGS`.
    * Add `digitalReadValue(pin, val)` to control the return value of
      `digitalRead(pin)`.
        * May be useful for testing purposes.
        * The `pin` parameter must satisfy `0 <= pin < 32`, otherwise
          `digitalReadValue()` is a no-op.
        * See [PR#61](https://github.com/bxparks/EpoxyDuino/pull/61).
    * Add an empty `EpoxyDuino.h` at the top level to stop warning messages from
      the Arduino IDE.
        * Fixes [Issue#62](https://github.com/bxparks/EpoxyDuino/issues/62).
    * Add [libraries/EpoxyMockSTM32RTC](libraries/EpoxyMockSTM32RTC)
        * A mock of the [STM32RTC](https://github.com/stm32duino/STM32RTC)
          library.
* 1.2.3 (2022-02-24)
    * Rename `unixhostduino_main()` to `epoxyduino_main()`, and make it
      static. No need to expose it publicly.
    * Add `enableTerminalEcho()` function to enable terminal echoing.
      See [Enable Terminal Echo](README.md#EnableTerminalEcho).
    * Update examples and [EpoxyFS/README.md](libraries/EpoxyFS) to be
      compatible with new `LittleFS` library in ESP32 >=2.0.0.
    * Add [EpoxyFS/SeekBenchmark](libraries/EpoxyFSexamples/SeekBenchmark) to
      measure the performance loss of calling `seek()` before a `read()`.
        * Sometimes the client-code is simpler when reading multiple records
          if it can call `seek()` with an explicit offset before each `read()`.
        * The alternative would be calling `read()` multiple times sequentially
          and using its internal cursor to advance automatically.
        * This benchmark shows that `seek()` causes significant performance
          loss, even if the `seek()` offset is identical to the internal cursor,
          so might be expected to be optimized away.
    * Add notes about [Debugging](README.md#Debugging) tools and options
      under a Unix environment, such as Valgrind.
* 1.2.2 (2022-02-02)
    * Add a `using Print::write` statement in `StdioSerial.h` to
      pull in all other overloaded `write()` methods from the parent `Print`
      class.
* 1.2.1 (2022-01-10)
    * Add `strncasecmp_P()` to `pgmspace.h`. See
      [PR#52](https://github.com/bxparks/EpoxyDuino/pull/52).
    * Add [Bugs and Limitations](README.md#BugsAndLimitations) section in
      README.md
    * Add comment in [aunit_tests.yml](.github/workflows/aunit_tests.yml)
      that a `pull_request` event may be useful. Upgrade GitHub docker image to
      Ubuntu 20.04.
* 1.2.0 (2021-12-29)
    * Simplify `StdioSerial`  class, see
      [Issue#43](https://github.com/bxparks/EpoxyDuino/issues/43).
        * Replace input ring buffer with a buffer of one character.
        * Wire `StdioSerial::write(uint8_t)` directly to Posix `write()`,
          by-passing the `<stdio.h>` buffer. `flush()` is no longer necessary.
        * Thanks to @felias-fogg.
    * **Revert Breaking Change Made in v1.1.0** Revert 432e304, so that
      `Print::writeln()` writes `\r\n` again by default.
        * Fixes [Issue#45](https://github.com/bxparks/EpoxyDuino/issues/45).
        * Add `Print::setLineModeNormal()` and `Print::setLineModeUnix()`
          methods to control the line termination behavior.
        * See [README.md#UnixLineMode](README.md#UnixLineMode) for usage info.
* 1.1.0 (2021-12-09)
    * Add optional `DEPS` variable containing header files that the `*.ino`
      depends on.
    * **Potential Breaking** Change `Print::println()` to print just a `\n`
      instead of `\r\n`.
        * This is more compatible on Unix where the line terminator is a single
          `\n`
        * This allows the text output of Arduino programs to be redirected to
          a file or piped to another Unix program with the correct line
          termination character.
        * This change may break some programs (usually unit tests) which print
          to a
          [PrintStr](https://github.com/bxparks/AceCommon/tree/develop/src/print_str)
          object (from my [AceCommon](https://github.com/bxparks/AceCommon)
          library), and then expect `\r\n` instead of `\n`.
    * Add `pgm_read_XXX_near()` and `pgm_read_XXX_far()` macros which
      simply delegate to the `pgm_read_XXX()` macros.
    * Add `clockCyclesPerMicrosecond()`, `clockCyclesToMicroseconds(a)`,
      and `microsecondsToClockCycles(a)` macros. Set a fake `F_CPU` to 16MHz
      on Unix machines.
    * Add `bitRead()`, `bitSet()`, `bitClear()`, `bitWrite()` macros. Add
      `bitToggle()` macro as well, which seems to be defined only on the
      Arduino AVR core.
    * Add `min()`, `max()`, `abs()`, etc. I don't normally use these Arduino
      macros in my libraries, but many other 3rd party libraries do. To compile
      those libraries under EpoxyDuino, we have to define them.
    * Add a minimal mock implementation of
      [FastLED](https://github.com/FastLED/FastLED) sufficient for my personal
      project.
* 1.0.0 (2021-09-30)
    * Add `epoxy_argc` and `epoxy_argv` as extern global variables which
      are set to the `argc` and `argv` parameters passed into the global
      `main()`.
        * Allows command line arguments to be passed into an Arduino
          application, to facilitate debugging on a Unix desktop machine.
        * Add `examples/CommandLine` which provides a basic command line parser
          that can be copied and modified for other applications.
    * Add `toString()` to `IPAddress` class, activated with `EPOXY_CORE_ESP8266`
      for compatibility with ESP8266 Core.
    * Add `strstr_P()` to `pgmspace.h`.
    * Finally fix [Issue #2](https://github.com/bxparks/EpoxyDuino/issues/2) and
      [Issue #25](https://github.com/bxparks/EpoxyDuino/issues/25).
* 0.8 (2021-08-08)
    * Add `EpoxyMockTimerOne` mock library for `TimerOne`
      (https://github.com/PaulStoffregen/TimerOne).
    * Add `library.json` to support
      [PlaformIO in Native
      mode](https://docs.platformio.org/en/latest/platforms/native.html). (See
      [PR #31](https://github.com/bxparks/EpoxyDuino/pull/31) by
      https://github.com/lopsided98).
    * Move code that pumps the `Serial` object from `unixhostduino_main()`
      to `yield()`. Fix bug to allow correct handling of `NUL` byte in the
      serial stream. (See [PR #32] by https://github.com/lopsided98).
    * **Breaking** Repurpose the `EPOXY_CORE` make variable to be the name of
      the macro that defines the target architecture so that `Arduino.h` brings
      in definitions which target specific Arduino platforms:
        * The valid options are:
            * `EPOXY_CORE_AVR` (default)
            * `EPOXY_CORE_ESP8266`
        * Merge ESP8266-specific changes from
          https://github.com/hsaturn/EspMock/cores/esp8266 into
          EpoxyDuino/cores/epoxy, guarded by `EPOXY_CORE_ESP8266` macro.
    * Add `map()`, `makeWord()` functions to `WMath.cpp`.
* 0.7 (2021-04-28)
    * Add `libraries/EpoxyMockDigitalWriteFast`, a simple mock library for
      `digitalWriteFast` (https://github.com/NicksonYap/digitalWriteFast) to
      allow code using these functions (e.g. `digitalWriteFast()`) to compile
      under EpoxyDuino.
    * Rename `EpoxyPromAvr` to `EpoxyEepromAvr`, and `EpoxyPromEsp` to
      `EpoxyEepromEsp`, for consistency and better self-description.
    * Add `EPOXY_CORE` and `EPOXY_CORE_PATH` variables to allow alternate
      Arduino Core files to be specified. Move current Core files from top-level
      into `./cores/epoxy/` subdirectory.
    * Add `memcpy_P()` and `vsnprintf_P()` (Thanks pmp-p@, #28).
    * Add `EXTRA_CXXFLAGS` to allow additional c++ flags to be specified.
    * Add `-Wextra` (in addition to `-Wall`) because some Arduino platforms
      enable both when "warnings" are enabled, so it's convenient to catch those
      warnings on the desktop when using EpoxyDuino.
* 0.6.2 (2021-03-15)
    * Add more stubs for Arduino API functions: `pulseIn()`, `pulseInLong()`,
      `shiftOut()`, `shiftIn()`, I2C and SPI pins (SS, MOSI, MISO, SCK, SDA,
      SCL), `analogWrite()`, typedefs for `boolean`, `byte`, `word`.
* 0.6.1 (2021-02-25)
    * Add experimental support for FreeBSD 12.2.
* 0.6 (2021-02-19)
    * Add `libraries/EpoxyFS`, an implementation of the ESP8266 `FS` file system
      that runs on Linux and MacOS.
    * Add `delayMicroSeconds()`, `WCharacter.h`, and stub implementations of
      `IPAddress.h`, `SPI.h`, by Erik Tideman (@ramboerik), see
      [PR #18](https://github.com/bxparks/EpoxyDuino/pull/18).
    * Add `libraries/EpoxyPromEsp` (EEPROM using the API of ESP8266/ESP32).
    * Add `libraries/EpoxyPromAvr` (EEPROM using the API of AVR processors).
* 0.5 (2021-01-21)
    * **Breaking Change** Change project name to "EpoxyDuino". The
      `UNIX_HOST_DUINO` macro is replaced with `EPOXY_DUINO`, and the
      `UnixHostDuino.mk` file is now `EpoxyDuino.mk`. The old macro and file are
      retained for backwards compatibility, but the GitHub repo name has
      changed. See
      [Issue #15](https://github.com/bxparks/UnixHostDuino/issues/15).
* 0.4 (2021-01-21)
    * Wrap `#ifdef` around `main()` to avoid conflict when compiling other
      Arduino cores with UnixHostDuino inside the `libraries/` directory.
    * Make `Stream::readBytes()` and `Stream::readString()` virtual, for
      compatibility with ESP8266, ESP32, STM32 and probably other 3rd party
      cores.
* 0.3.1 (2020-11-16)
    * Add support for `random()` function.
    * Cleanup header files.
* 0.3 (2020-08-20)
    * Add `#define` for various digital and analog pins: `D0`-`D19`, `A0`-`A9`.
    * Add stub for `analogRead()`.
    * Add `Print.printf()` provided by a significant number of Arduino boards
      (ESP8266, ESP32, Teensy, etc).
* 0.2.1 (2020-05-02)
    * Add `MORE_CLEAN`, an optional user-provided make-target to do additional
      cleaning, such as removing directories created by code-generators.
* 0.2 (2020-03-21)
    * Mark `main()` as a weak reference (supported by g++ and clang++) so that
      UniHostDuino can be used as a library in programs that already provide a
      `main()` function. (Thanks to Max Prokhorov mcspr@).
    * Replace `ARDUINO_LIB_DIR` with `ARDUINO_LIB_DIRS` which supports
      multiple external library locations, in addition to siblings of the
      UnixHostDuino directory. The `ARDUINO_LIB_DIR` is no longer supported.
* 0.1.3 (2019-11-21)
    * Add 'Installation' section to the README.md.
    * Add `UNIX_HOST_DUINO` macro symbol  to the CPPFLAGS to allow conditional
      code that activates only when UnixHostDuino is used.
* 0.1.2 (2019-09-04)
    * Implement `StdioSerial::flush()` to enable `Serial.flush()`.
* 0.1.1 (2019-08-14)
    * If the STDIN is not a real tty, continue without putting it into raw mode
      or exiting with an error. This allows unit tests inside continuous build
      frameworks.
* 0.1 (2019-07-31)
    * Split from `AUnit` and renamed from `unitduino` to `UnixHostDuino`.
    * Add `UNIT_HOST_DUINO` macro.
    * Add `FPSTR()` macro for compatibilty with ESP8266 and ESP32.
    * Add `LED_BUILTIN` macro.
