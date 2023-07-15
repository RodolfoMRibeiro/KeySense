#ifndef WINDOWS_INFO_H
#define WINDOWS_INFO_H

#include <Windows.h>
#include <sstream>

class WindowInfo {
public:
    WindowInfo();
    void GetActiveWindowInfo(std::stringstream& output);

private:
    char lastwindow[256];
    void appendWindowTitle(std::stringstream& output, const char* window_title);
};

#endif