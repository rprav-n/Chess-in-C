#pragma once
#include "raylib.h"
#include "piece.h"

typedef struct 
{
	Rectangle white_src;
	Rectangle black_src;
	int grid[8][8];
	Piece total_pieces[12]; // total pieces
	Piece pieces[32]; // individual game pieces
}Board;

void draw_board(Texture2D atlas_texture, Board board);
void draw_pieces(Texture2D atlas_texture, Board board);