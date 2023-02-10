#include "Console.h"

#include <cassert>
#include <exception>
#include <Windows.h>

int Console::winAPI_textColor = 0;
int Console::winAPI_backgroundColor = 0;

static RECT GetWindowRectangle()
{
	HWND consoleWindow = ::GetConsoleWindow();
	RECT windowRectanle = {};
	::GetWindowRect(consoleWindow, &windowRectanle);

	return windowRectanle;
}

static int ConvertColorToWinApiTextColor(Console::Color color)
{
	assert((int)color >= 0 && (int)color < (int)Console::Color::Count);

	int winAPIcolor = 0;

	switch (color)
	{
	case Console::Color::Red:
		winAPIcolor = FOREGROUND_RED;
		break;
	case Console::Color::Green:
		winAPIcolor = FOREGROUND_GREEN;
		break;
	case Console::Color::Blue:
		winAPIcolor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case Console::Color::DarkBlue:
		winAPIcolor = FOREGROUND_BLUE;
		break;
	case Console::Color::LightRed:
		winAPIcolor = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case Console::Color::LightGreen:
		winAPIcolor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case Console::Color::Cyan:
		winAPIcolor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case Console::Color::Gray:
		winAPIcolor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	case Console::Color::White:
		winAPIcolor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case Console::Color::Purple:
		winAPIcolor = FOREGROUND_BLUE | FOREGROUND_RED;
		break;
	case Console::Color::Orange:
		winAPIcolor = FOREGROUND_GREEN | FOREGROUND_RED;
		break;
	case Console::Color::Pink:
		winAPIcolor = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case Console::Color::Yellow:
		winAPIcolor = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case Console::Color::Black:
		winAPIcolor = 0;
		break;
	}

	return winAPIcolor;
}

static int ConvertColorToWinApiBackgroundColor(Console::Color color)
{
	assert((int)color >= 0 && (int)color < (int)Console::Color::Count);

	int winAPIcolor = 0;

	switch (color)
	{
	case Console::Color::Red:
		winAPIcolor = BACKGROUND_RED;
		break;
	case Console::Color::Green:
		winAPIcolor = BACKGROUND_GREEN;
		break;
	case Console::Color::Blue:
		winAPIcolor = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case Console::Color::DarkBlue:
		winAPIcolor = BACKGROUND_BLUE;
		break;
	case Console::Color::LightRed:
		winAPIcolor = BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case Console::Color::LightGreen:
		winAPIcolor = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case Console::Color::Cyan:
		winAPIcolor = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case Console::Color::Gray:
		winAPIcolor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	case Console::Color::White:
		winAPIcolor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case Console::Color::Purple:
		winAPIcolor = BACKGROUND_BLUE | BACKGROUND_RED;
		break;
	case Console::Color::Orange:
		winAPIcolor = BACKGROUND_GREEN | BACKGROUND_RED;
		break;
	case Console::Color::Pink:
		winAPIcolor = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case Console::Color::Yellow:
		winAPIcolor = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case Console::Color::Black:
		winAPIcolor = 0;
		break;
	}

	return winAPIcolor;
}

void Console::SetTitle(const wchar_t* title)
{
	::SetConsoleTitleW(title);
}

const wchar_t* Console::GetTitle()
{
	static const size_t WINDOW_TITLE_SIZE = 256;
	static wchar_t windowTitle[WINDOW_TITLE_SIZE] = {};
	::GetConsoleTitleW(windowTitle, WINDOW_TITLE_SIZE);

	return windowTitle;
}

void Console::EnableMaximizeButton()
{
	HWND consoleWindow = ::GetConsoleWindow();
	LONG windowStyle = ::GetWindowLongW(consoleWindow, GWL_STYLE);
	LONG newWindowStyle = windowStyle | WS_MAXIMIZEBOX;

	::SetWindowLongW(consoleWindow, GWL_STYLE, newWindowStyle);
}

void Console::DisableMaximizeButton()
{
	HWND consoleWindow = ::GetConsoleWindow();
	LONG windowStyle = ::GetWindowLongW(consoleWindow, GWL_STYLE);
	LONG newWindowStyle = windowStyle & ~WS_MAXIMIZEBOX;

	::SetWindowLongW(consoleWindow, GWL_STYLE, newWindowStyle);
}

void Console::EnableManualResizing()
{
	HWND consoleWindow = ::GetConsoleWindow();
	LONG windowStyle = ::GetWindowLongW(consoleWindow, GWL_STYLE);
	LONG newWindowStyle = windowStyle | WS_SIZEBOX;

	::SetWindowLongW(consoleWindow, GWL_STYLE, newWindowStyle);
}

void Console::DisableManualResizing()
{
	HWND consoleWindow = ::GetConsoleWindow();
	LONG windowStyle = ::GetWindowLongW(consoleWindow, GWL_STYLE);
	LONG newWindowStyle = windowStyle & ~WS_SIZEBOX;

	::SetWindowLongW(consoleWindow, GWL_STYLE, newWindowStyle);
}

void Console::EnableHorizontalScrollBar()
{
	HWND consoleWindow = ::GetConsoleWindow();
	::ShowScrollBar(consoleWindow, SB_HORZ, true);
}

void Console::DisableHorizontalScrollBar()
{
	HWND consoleWindow = ::GetConsoleWindow();
	::ShowScrollBar(consoleWindow, SB_HORZ, false);
}

void Console::EnableVerticalScrollBar()
{
	HWND consoleWindow = ::GetConsoleWindow();
	::ShowScrollBar(consoleWindow, SB_VERT, true);
}

void Console::DisableVerticalScrollBar()
{
	HWND consoleWindow = ::GetConsoleWindow();
	::ShowScrollBar(consoleWindow, SB_VERT, false);
}

void Console::EnableScrollBars()
{
	EnableHorizontalScrollBar();
	EnableVerticalScrollBar();
}

void Console::DisableScrollBars()
{
	DisableHorizontalScrollBar();
	DisableVerticalScrollBar();
}

void Console::SetFont(const wchar_t* fontName, short fontSize)
{
	HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX fontInfo = {};
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.nFont = 0;
	fontInfo.dwFontSize.X = 0;
	fontInfo.FontFamily = FF_DONTCARE;
	fontInfo.FontWeight = FW_NORMAL;

	fontInfo.dwFontSize.Y = fontSize;
	::wcscpy_s(fontInfo.FaceName, fontName);

	::SetCurrentConsoleFontEx(console, false, &fontInfo);
}

void Console::SetPositionX(int newX)
{
	HWND consoleWindow = ::GetConsoleWindow();
	RECT windowRectanle = GetWindowRectangle();
	long y = windowRectanle.top;

	::SetWindowPos(consoleWindow, HWND_TOP, newX, y, 0, 0, SWP_NOSIZE);
}

void Console::SetPositionY(int newY)
{
	HWND consoleWindow = ::GetConsoleWindow();
	RECT windowRectanle = GetWindowRectangle();
	long x = windowRectanle.left;

	::SetWindowPos(consoleWindow, HWND_TOP, x, newY, 0, 0, SWP_NOSIZE);
}

void Console::SetPosition(int newX, int newY)
{
	HWND consoleWindow = ::GetConsoleWindow();
	::SetWindowPos(consoleWindow, HWND_TOP, newX, newY, 0, 0, SWP_NOSIZE);
}

void Console::CenterPosition()
{
	HWND consoleWindow = ::GetConsoleWindow();
	RECT windowRectanle = GetWindowRectangle();
	int windowWidth = GetWidth();
	int windowHeight = GetHeight();
	int centerX = (::GetSystemMetrics(SM_CXSCREEN) / 2) - (windowWidth / 2);
	int centerY = (::GetSystemMetrics(SM_CYSCREEN) / 2) - (windowHeight / 2);

	::SetWindowPos(consoleWindow, HWND_TOP, centerX, centerY, 0, 0, SWP_NOSIZE);
}

int Console::GetPositionX()
{
	RECT windowRectanle = GetWindowRectangle();
	int x = windowRectanle.left;

	return x;
}

int Console::GetPositionY()
{
	RECT windowRectanle = GetWindowRectangle();
	int y = windowRectanle.top;

	return y;
}

void Console::SetWidth(int newWidth)
{
	HWND consoleWindow = ::GetConsoleWindow();
	RECT windowRectanle = GetWindowRectangle();
	int x = windowRectanle.left;
	int y = windowRectanle.top;
	int height = GetHeight();

	::SetWindowPos(consoleWindow, HWND_TOP, x, y, newWidth, height, SWP_SHOWWINDOW);
}

void Console::SetHeight(int newHeight)
{
	HWND consoleWindow = ::GetConsoleWindow();
	RECT windowRectanle = GetWindowRectangle();
	int x = windowRectanle.left;
	int y = windowRectanle.top;
	int width = GetWidth();

	::SetWindowPos(consoleWindow, HWND_TOP, x, y, width, newHeight, SWP_SHOWWINDOW);
}

void Console::SetSize(int newWidth, int newHeight)
{
	HWND consoleWindow = ::GetConsoleWindow();
	RECT windowRectanle = GetWindowRectangle();
	int x = windowRectanle.left;
	int y = windowRectanle.top;

	::SetWindowPos(consoleWindow, HWND_TOP, x, y, newWidth, newHeight, SWP_SHOWWINDOW);
}

int Console::GetWidth()
{
	RECT windowRectanle = GetWindowRectangle();
	int width = windowRectanle.right - windowRectanle.left;

	return width;
}

int Console::GetHeight()
{
	RECT windowRectanle = GetWindowRectangle();
	int height = windowRectanle.bottom - windowRectanle.top;

	return height;
}

void Console::ChangeTextColor(Color color)
{
	HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
	winAPI_textColor = ConvertColorToWinApiTextColor(color);

	::SetConsoleTextAttribute(console, winAPI_textColor | winAPI_backgroundColor);
}

void Console::ChangeBackgroundColor(Color color)
{
	HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
	winAPI_backgroundColor = ConvertColorToWinApiBackgroundColor(color);

	::SetConsoleTextAttribute(console, winAPI_textColor | winAPI_backgroundColor);
}

void Console::ToggleCursorVisibility(bool isVisible)
{
	HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = isVisible;
	cursorInfo.dwSize = 100; // % of the character cell that is filled by the cursor.
	::SetConsoleCursorInfo(console, &cursorInfo);
}

void Console::ClearScreen()
{
	HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	::GetConsoleScreenBufferInfo(console, &screenInfo);

	COORD topLeftCoordinate = { 0, 0 };
	DWORD charsWritten;
	::FillConsoleOutputCharacterW(console, ' ', screenInfo.dwSize.X * screenInfo.dwSize.Y, topLeftCoordinate, &charsWritten);

	DWORD length = screenInfo.dwSize.X * screenInfo.dwSize.Y;
	::FillConsoleOutputAttribute(console, winAPI_textColor | winAPI_backgroundColor, length, topLeftCoordinate, &charsWritten);
	::SetConsoleCursorPosition(console, topLeftCoordinate);
}