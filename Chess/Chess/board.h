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
	Vector2 possible_moves[64];
	Vector2 capture_pos[10];
	Piece selected_piece;
	bool picked;
}Board;

void update_board(Board* board);
void cross_moves(Board* board, int x, int y, int* last_index, int* capture_index, bool single);
void plus_moves(Board* board, int x, int y, int* last_index, int* capture_index, bool single);

void draw_board(Texture2D atlas_texture, Board board);
void draw_pieces(Texture2D atlas_texture, Board board);
void draw_possible_moves(Board board);
void draw_capture_pos(Board board);

void reset_capture_pos(Board* board);