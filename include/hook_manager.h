#ifndef HOOK_MANAGER_H
#define HOOK_MANAGER_H

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
