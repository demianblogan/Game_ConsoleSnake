#pragma once

#include <string>

struct WindowSettings
{
	std::wstring title;
	std::wstring fontName;
	short fontSize;
	int width;
	int height;
};

class Game
{
private:
	bool isRunning = false;

	WindowSettings windowSettings
	{
		L"Snake",    // title
		L"Consolas", // font name
		30,          // font size
		500,         // width
		800          // height
	};

	Game() = default;

public:
	bool Start();
	bool IsRunning() const;
	void HandleInput();
	void Update();
	void Render();

	// ----------- Singleton pattern -----------
	static Game& GetInstance();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	// -----------------------------------------
};