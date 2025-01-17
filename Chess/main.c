#include "raylib.h"
#include "game.h"


int main()
{
	Game game = { 0 };
	game.screen_height = 504;
	game.screen_width = 504;
	game.name = "Chess";
	game_start(game);
}