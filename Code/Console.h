#pragma once

class Console
{
private:
	static int winAPI_textColor;
	static int winAPI_backgroundColor;

public:

	enum class Color
	{
		Red,
		Green,
		Blue,
		DarkBlue,
		LightRed,
		LightGreen,
		Cyan,
		Gray,
		White,
		Purple,
		Orange,
		Pink,
		Yellow,
		Black,
		Count
	};

	static void SetTitle(const wchar_t* title);
	static const wchar_t* GetTitle();

	static void EnableMaximizeButton();
	static void DisableMaximizeButton();

	static void EnableManualResizing();
	static void DisableManualResizing();

	static void EnableHorizontalScrollBar();
	static void DisableHorizontalScrollBar();

	static void EnableVerticalScrollBar();
	static void DisableVerticalScrollBar();

	static void EnableScrollBars();
	static void DisableScrollBars();

	static void SetFont(const wchar_t* fontName, short fontSize);

	static void SetPositionX(int newX);
	static void SetPositionY(int newY);
	static void SetPosition(int newX, int newY);
	static void CenterPosition();
	static int GetPositionX();
	static int GetPositionY();

	static void SetWidth(int newWidth);
	static void SetHeight(int newHeight);
	static void SetSize(int newWidth, int newHeight);
	static int GetWidth();
	static int GetHeight();
	
	static void ChangeTextColor(Color color);
	static void ChangeBackgroundColor(Color color);

	static void ToggleCursorVisibility(bool isVisible);

	static void ClearScreen();
};