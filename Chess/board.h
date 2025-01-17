#pragma once
#include "raylib.h"

typedef struct 
{
	Rectangle white_src;
	Rectangle black_src;
}Board;

void draw_board(Texture2D atlas_texture, Board board);