#include "raylib.h"
#include "game.h"


int main()
{
	Game game = { 0 };
	game.screen_height = 576;
	game.screen_width = 576;
	game.name = "Chess";
	game_start(game);
}