#ifndef OS_MANAGER_H
#define OS_MANAGER_H

class OSManager {
public:
    void SetTerminalVisibility(bool isVisible);

    static void GracefulShutdown(int signal);
};

#endif