#include "../../include/os_manager.h"

#include <Windows.h>

void OSManager::setTerminalVisibility(bool isVisible = true) {
    if (isVisible)
        ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1); 
    else
        ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
}