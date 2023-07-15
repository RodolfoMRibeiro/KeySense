#ifndef OS_MANAGER_H

#define OS_MANAGER_H

class OSManager {
public:
    OSManager(bool isTerminalVisible);
    
private:
    const bool IS_TERMINAL_VISIBLE;

    void set_terminal_visibility();
};

#endif