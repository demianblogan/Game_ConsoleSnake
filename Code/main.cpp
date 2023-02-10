#include "Game.h"

int main()
{
	Game& game = Game::GetInstance();
	
	if (!game.Start())
	{
		// TODO: write errors handling.
	}

	while (game.IsRunning())
	{
		game.HandleInput();
		game.Update();
		game.Render();
	}

	return 0;
}