#include "Game.h"

#include "Console.h"

bool Game::Start()
{
	Console::SetTitle(windowSettings.title.c_str());
	Console::SetFont(windowSettings.fontName.c_str(), windowSettings.fontSize);
	Console::SetSize(windowSettings.width, windowSettings.height);
	Console::DisableManualResizing();
	Console::DisableMaximizeButton();
	Console::DisableScrollBars();
	Console::CenterPosition();
	Console::ChangeTextColor(Console::Color::LightGreen);
	Console::ChangeBackgroundColor(Console::Color::Black);
	Console::ToggleCursorVisibility(false);

	isRunning = true;
	return true;
}

bool Game::IsRunning() const
{
	return isRunning;
}

void Game::HandleInput()
{
	// TODO: write input handling.
}

void Game::Update()
{
	// TODO: write update handling.
}

void Game::Render()
{
	// TODO: write render handling.
}

Game& Game::GetInstance()
{
	static Game game;
	return game;
}