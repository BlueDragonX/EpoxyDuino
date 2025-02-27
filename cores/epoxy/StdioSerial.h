/*
 * Copyright (c) 2019 Brian T. Park
 * MIT License
 */

#ifndef EPOXY_DUINO_STDIO_SERIAL_H
#define EPOXY_DUINO_STDIO_SERIAL_H

#include "Print.h"
#include "Stream.h"

/**
 * A version of Serial that reads from STDIN and sends output to STDOUT on
 * Linux or MacOS.
 */
class StdioSerial: public Stream {
  public:
    void begin(unsigned long /*baud*/) { bufch = -1; }

    size_t write(uint8_t c) override;

    // Pull in all other overloaded versions of the write() function from the
    // Print parent class. This is required because when we override one version
    // of write() above, C++ performs a static binding to the write() function
    // in the current class and doesn't bother searching the parent classes for
    // any other overloaded function that it could bind to. (30 years of C++ and
    // I still get shot with C++ footguns like this. I have no idea what happens
    // if the Stream class overloaded the write() function.)
    using Print::write;

    operator bool() { return true; }

    int available() override;

    int read() override;

    int peek() override;

    void end();

  private:
    int bufch;
};

extern StdioSerial Serial;

#define SERIAL_PORT_MONITOR Serial
#define HardwareSerial StdioSerial

#endif
