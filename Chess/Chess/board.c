#include "board.h"
#include <stdio.h>
#include <math.h>

void update_board(Board* board)
{
	// update board mouse_grid_pos
	Vector2 mouse_pos = GetMousePosition();
	Vector2 grid_pos = { 0 };
	grid_pos.x = floor(mouse_pos.x / 72.f);
	grid_pos.y = floor(mouse_pos.y / 72.f);

	board->mouse_grid_pos.x = grid_pos.x;
	board->mouse_grid_pos.y = grid_pos.y;

	// updating the board pieces based on the 2D grid array
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece piece = board->pieces[i][j];
			if (piece.type != -1)
			{

			}
		}
	}

	// select a piece
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Piece piece = board->pieces[i][j];
				if (piece.dest.x/72.f == grid_pos.x && piece.dest.y/72.f == grid_pos.y && piece.type != -1)
				{
					board->pieces[i][j].selected = true;
				}
				else
				{
					board->pieces[i][j].selected = false;
				}
			}
		}
	}


	// ability to move the selected piece
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{

				Piece selected_piece = board->pieces[j][i];
				int x = (int)grid_pos.x;
				int y = (int)grid_pos.y;
				Piece placement_piece = board->pieces[y][x];
				
				if (selected_piece.selected && placement_piece.type == -1)
				{
					board->pieces[y][x] = (Piece){
						.src = selected_piece.src,
						.dest = (Rectangle){x*72, y*72, 72.f, 72.f},
						.selected = false,
						.type = selected_piece.type,
					};
					board->pieces[j][i] = (Piece){
						.src = (Rectangle){0},
						.dest = (Rectangle){j * 72, i * 72, 0.f, 0.f},
						.selected = false,
						.type = -1,
					};
				}
			}
		}
	}
	

}

void draw_board(Texture2D atlas_texture, Board board)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			DrawRectangle(i*72, j*72, 72, 72, RED);
			Rectangle dest = (Rectangle){ i * 72, j * 72, 72, 72 };
			Vector2 origin = (Vector2){0};
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
					DrawTexturePro(atlas_texture, board.white_src, dest, origin, 0.f, WHITE);
				else
					DrawTexturePro(atlas_texture, board.black_src, dest, origin, 0.f, WHITE);
			}
			else
			{
				if (j % 2 == 0)
					DrawTexturePro(atlas_texture, board.black_src, dest, origin, 0.f, WHITE);
				else
					DrawTexturePro(atlas_texture, board.white_src, dest, origin, 0.f, WHITE);
			}
		}
	}

	// draw the mouse hover
	DrawRectangle(board.mouse_grid_pos.x*72, board.mouse_grid_pos.y*72, 72, 72, GetColor(0xb1a7fcff));

}

void draw_pieces(Texture2D atlas_texture, Board board)
{
	int l = sizeof(board.grid) / sizeof(board.grid[0]);
	int total_pieces = sizeof(board.total_pieces) / sizeof(board.total_pieces[0]);
	
	// draw bg for selected piece
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece piece = board.pieces[i][j];
			if (piece.selected)
			{
				DrawRectangleRec(piece.dest, GetColor(0xb1a7fcff));
			}
		}
	}

	// draw pieces
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			Piece piece = board.pieces[i][j];
			
			if (piece.type != -1)
			{
				for (int k = 0; k < 12; k++)
				{
					Rectangle src = board.total_pieces[k].src;
					Rectangle dest = piece.dest;
					if (piece.type == board.total_pieces[k].type)
					{
						DrawTexturePro(atlas_texture, src, dest, (Vector2) { 0 }, 0.f, WHITE);
						break;
					}
				}
			}
		}
	}

}
