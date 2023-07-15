#ifndef KEYLOGGER_H

#define KEYLOGGER_H

#include <os_manager.h>

enum LoggingFormat
{
    Default,
    Decimal,
    Hexadecimal
};

class Keylogger {
public:
    Keylogger(LoggingFormat loggingFormat, OSManager manager, bool mouseIgnore);

    void start();

private:
    const LoggingFormat LOGGING_FORMAT;
    const OSManager manager_;
    const bool MOUSE_IGNORE;
};

#endif