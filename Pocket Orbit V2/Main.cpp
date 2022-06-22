#include <iostream>
#include "Game.h"

int main()
{
	// Init Game engine
	Game game;

	while (game.running())
	{
		// Update
		game.update();

		// render
		game.render();
	}

	return 0;
}