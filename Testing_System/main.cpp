// Context.h
#include "Context_Menu.h"

int main()
{
#pragma region Setting up the console Window

	SetConsoleTitle(L"Testing System"); // title programs
	/*
	 * Removes blinking caret (cursor)
	 */

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo); // get cursor information for handle and structCursorInfo
	structCursorInfo.bVisible = FALSE; // Set visibility to false
	SetConsoleCursorInfo(handle, &structCursorInfo); // set parameters for console
	//////////////////////////////////////////////

	/*
	 * Set Console Size
	 */

	HANDLE soh = GetStdHandle(STD_OUTPUT_HANDLE);  // Console screen user_name handle
	CONSOLE_FONT_INFOEX console_font_infoex;  // console info
	memset(&console_font_infoex, 0, sizeof(console_font_infoex));
	console_font_infoex.cbSize = sizeof(console_font_infoex);
	GetCurrentConsoleFontEx(soh, FALSE, &console_font_infoex);
	console_font_infoex.dwFontSize.Y = 24;
	SetCurrentConsoleFontEx(soh, FALSE, &console_font_infoex);
	//////////////////////////////////////////////

#pragma endregion

	// Creating directories

	dir_an_path::creating_directories();

	try
	{
		// Go in Main menu
		Context_Menu start;

		return 0;
	}
	catch (...)
	{
		MessageBoxA(GetActiveWindow(), "Program initialization error\nPlease restart the program\nor contact support", "Testing System", MB_ICONERROR);
		return 0;
	}
}