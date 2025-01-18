#pragma once
#include "raylib.h"
#include "piece.h"


typedef struct 
{
	Rectangle white_src;
	Rectangle black_src;
	int grid[8][8];
	Piece total_pieces[12]; // total pieces
	Piece pieces[8][8];
	Vector2 mouse_grid_pos;
}Board;

void update_board(Board* board);

void draw_board(Texture2D atlas_texture, Board board);
void draw_pieces(Texture2D atlas_texture, Board board);