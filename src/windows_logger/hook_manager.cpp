#include "../../include/hook_manager.h"

HookManager::HookManager() : _hook(nullptr) {}

void HookManager::InstallKeyboardHook(HookCallback hookCallback) {
    HHOOK hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, hookCallback, NULL, 0);

    if (!hookHandle) {
        displayErrorMessage();
    }
}

void HookManager::ReleaseHook() {
    UnhookWindowsHookEx(_hook);
}

void HookManager::displayErrorMessage() {
    LPCWSTR errorMessage = L"Failed to install hook!";
    LPCWSTR errorTitle = L"Error";

    MessageBox(NULL, errorMessage, errorTitle, MB_ICONERROR);
}