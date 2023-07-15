#ifndef HOOKMANAGER_H
#define HOOKMANAGER_H

#include <Windows.h>

typedef LRESULT(__stdcall *HookCallback)(int, WPARAM, LPARAM);

class HookManager {
public:
    HookManager();
    void InstallKeyboardHook(HookCallback hookCallback);
    void ReleaseHook();

private:
    HHOOK _hook;
    void displayErrorMessage();
};

#endif
