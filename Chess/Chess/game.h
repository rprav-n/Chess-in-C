#pragma once
#include "raylib.h"
#include "board.h"
#include "piece.h"

typedef struct
{
	int screen_width;
	int screen_height;
	char* name;
	Texture2D atlas_texture;
	Board board;
	Piece peice; // single piece for testing
}Game;

void game_start(Game* game);
void game_end();

void game_update(float dt, Game* game);
void game_draw(Game game);
