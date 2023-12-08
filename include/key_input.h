#ifndef KEY_INPUT_H
#define KEY_INPUT_H

#include <Windows.h>
#include <sstream>
#include <map>

enum class LoggingFormat { Default, Decimal, Hexadecimal };

class KeyInput {
public:
    KeyInput(LoggingFormat logging_format);

    bool IgnoreMouse(int keyStroke);
    void FormatOutputBasedOnLogging(std::stringstream& output, int keyStroke);

private:
    const bool _MOUSE_IGNORE;
    const LoggingFormat _LOGGING_FORMAT;
    std::map<int, std::string> _VIRTUAL_KEY_NAME;

    void initializeKeyNames();
    void appendKeyNameOrCharacter(std::stringstream& output, int keyStroke);
    char getKeyCharacter(int keyStroke);
    HKL getKeyboardLayout();
};

#endif