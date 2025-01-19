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

	// set is_selected to false for all piece
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board->pieces[i][j].selected = false;
		}
	}

	// select a piece
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !board->picked)
	{
		board->selected_piece = (Piece){ 0 };
		board->selected_piece.type == -1;
		
		int i = grid_pos.x;
		int j = grid_pos.y;

		Piece piece = board->pieces[i][j];
		if (piece.pos.x == grid_pos.x && piece.pos.y == grid_pos.y && piece.type != -1)
		{
			board->pieces[i][j].selected = true;
			board->selected_piece = board->pieces[i][j];
		}
	}
	
	for (int i = 0; i < 64; i++)
	{
		board->possible_moves[i] = (Vector2){ -1, -1 };
	}

	// when a pice is selected, update the grid possible moves for that selected piece
	if (board->selected_piece.selected)
	{
		int piece_grid_x = board->selected_piece.dest.x / 72;
		int piece_grid_y = board->selected_piece.dest.y / 72;

		switch (board->selected_piece.type)
		{
		case W_PAWN:
			{
				int x = piece_grid_x;
				int y = piece_grid_y;
				int max_moves = 2;
				int capture_index = 0;
				if (board->selected_piece.is_moved_once)
				{
					max_moves = 1;
				}
				// straight move
				for (int i = 0; i < max_moves; i++)
				{
					y -= 1;
					Piece piece = board->pieces[x][y];
					if (piece.type == -1)
					{
						board->possible_moves[i] = (Vector2){ x , y };
					}
				}

				int local_x_left = x - 1;
				int local_x_right = x + 1;
				int local_y = piece_grid_y - 1;
				if (local_x_left >= 0 && local_x_left <= 7)
				{
					Piece left_piece = board->pieces[local_x_left][local_y];
					if (left_piece.type != -1 && left_piece.type > 5)
					{
						board->capture_pos[capture_index] = (Vector2){ local_x_left, local_y };
						capture_index++;
					}

				}
				if (local_x_right >= 0 && local_x_right <= 7)
				{
					Piece right_piece = board->pieces[local_x_right][local_y];
					if (right_piece.type != -1 && right_piece.type > 5)
					{
						board->capture_pos[capture_index] = (Vector2){ local_x_right, local_y };
						capture_index++;
					}
				}
			}
			break;
		case B_PAWN:
			{
				int x = piece_grid_x;
				int y = piece_grid_y;
				int max_moves = 2;
				int capture_index = 0;
				if (board->selected_piece.is_moved_once)
				{
					max_moves = 1;
				}
				// straight move
				for (int i = 0; i < max_moves; i++)
				{
					y += 1;
					Piece piece = board->pieces[x][y];
					if (piece.type == -1)
					{
						board->possible_moves[i] = (Vector2){ x , y };
					}
				}

				// capture pos
				int local_x_left = x - 1;
				int local_x_right = x + 1;
				int local_y = piece_grid_y + 1;
				
				if (local_x_left >= 0 && local_x_left <= 7)
				{
					Piece left_piece = board->pieces[local_x_left][local_y];
					if (left_piece.type != -1 && left_piece.type < 6)
					{
						board->capture_pos[capture_index] = (Vector2){ local_x_left, local_y };
						capture_index++;
					}
					
				}
				if (local_x_right >= 0 && local_x_right <= 7)
				{
					Piece right_piece = board->pieces[local_x_right][local_y];
					if (right_piece.type != -1 && right_piece.type < 6)
					{
						board->capture_pos[capture_index] = (Vector2){ local_x_right, local_y };
						capture_index++;
					}
				}
			}
			break;
		case W_ROOK: // elephant
		case B_ROOK: // elephant
			{
				int x = piece_grid_x;
				int y = piece_grid_y;
				int last_index = 0;
				int capture_index = 0;
				plus_moves(board, x, y, &last_index, &capture_index, false);
				
			}
			break;
		case W_BISHOP: // mandhiri
		case B_BISHOP: // mandhiri
			{
				int x = piece_grid_x;
				int y = piece_grid_y;
				int last_index = 0;
				int capture_index = 0;
				cross_moves(board, x, y, &last_index, &capture_index, false);
			}
			break;
		case W_KNIGHT: // horse
		case B_KNIGHT: // horse
			{
				int x = piece_grid_x;
				int y = piece_grid_y;
				int last_index = 0;
				int capture_index = 0;
				// top left
				{
					int local_x = x - 1;
					int local_y = y - 2;
					if (local_x >= 0 && local_x <= 7 && local_y >= 0 && local_y <= 7)
					{
						Piece piece = board->pieces[local_x][local_y];
						if (piece.type == -1)
						{
							board->possible_moves[last_index] = (Vector2){ local_x, local_y };
							last_index++;
						}
						else
						{
							board->capture_pos[capture_index] = (Vector2){ local_x, local_y };
							capture_index++;
						}
					}
				}
				// top right
				{
					int local_x = x + 1;
					int local_y = y - 2;
					if (local_x >= 0 && local_x <= 7 && local_y >= 0 && local_y <= 7)
					{
						Piece piece = board->pieces[local_x][local_y];
						if (piece.type == -1)
						{
							board->possible_moves[last_index] = (Vector2){ local_x, local_y };
							last_index++;
						}
						else
						{
							board->capture_pos[capture_index] = (Vector2){ local_x, local_y };
							capture_index++;
						}
					}
				}
				// right top
				{
					int local_x = x + 2;
					int local_y = y - 1;
					if (local_x >= 0 && local_x <= 7 && local_y >= 0 && local_y <= 7)
					{
						Piece piece = board->pieces[local_x][local_y];
						if (piece.type == -1)
						{
							board->possible_moves[last_index] = (Vector2){ local_x, local_y };
							last_index++;
						}
						else
						{
							board->capture_pos[capture_index] = (Vector2){ local_x, local_y };
							capture_index++;
						}
					}
				}
				// right down
				{
					int local_x = x + 2;
					int local_y = y + 1;
					if (local_x >= 0 && local_x <= 7 && local_y >= 0 && local_y <= 7)
					{
						Piece piece = board->pieces[local_x][local_y];
						if (piece.type == -1)
						{
							board->possible_moves[last_index] = (Vector2){ local_x, local_y };
							last_index++;
						}
						else
						{
							board->capture_pos[capture_index] = (Vector2){ local_x, local_y };
							capture_index++;
						}
					}
				}
				// bottom right
				{
					int local_x = x + 1;
					int local_y = y + 2;
					if (local_x >= 0 && local_x <= 7 && local_y >= 0 && local_y <= 7)
					{
						Piece piece = board->pieces[local_x][local_y];
						if (piece.type == -1)
						{
							board->possible_moves[last_index] = (Vector2){ local_x, local_y };
							last_index++;
						}
						else
						{
							board->capture_pos[capture_index] = (Vector2){ local_x, local_y };
							capture_index++;
						}
					}
				}
				// bottom left
				{
					int local_x = x - 1;
					int local_y = y + 2;
					if (local_x >= 0 && local_x <= 7 && local_y >= 0 && local_y <= 7)
					{
						Piece piece = board->pieces[local_x][local_y];
						if (piece.type == -1)
						{
							board->possible_moves[last_index] = (Vector2){ local_x, local_y };
							last_index++;
						}
						else
						{
							board->capture_pos[capture_index] = (Vector2){ local_x, local_y };
							capture_index++;
						}
					}
				}
				// left bottom
				{
					int local_x = x - 2;
					int local_y = y + 1;
					if (local_x >= 0 && local_x <= 7 && local_y >= 0 && local_y <= 7)
					{
						Piece piece = board->pieces[local_x][local_y];
						if (piece.type == -1)
						{
							board->possible_moves[last_index] = (Vector2){ local_x, local_y };
							last_index++;
						}
						else
						{
							board->capture_pos[capture_index] = (Vector2){ local_x, local_y };
							capture_index++;
						}
					}
				}
				// left top
				{
					int local_x = x - 2;
					int local_y = y - 1;
					if (local_x >= 0 && local_x <= 7 && local_y >= 0 && local_y <= 7)
					{
						Piece piece = board->pieces[local_x][local_y];
						if (piece.type == -1)
						{
							board->possible_moves[last_index] = (Vector2){ local_x, local_y };
							last_index++;
						}
						else
						{
							board->capture_pos[capture_index] = (Vector2){ local_x, local_y };
							capture_index++;
						}
					}
				}

			}
			break;
		case W_QUEEN:
		case B_QUEEN:
			{
				int x = piece_grid_x;
				int y = piece_grid_y;
				int last_index = 0;
				int capture_index = 0;
				plus_moves(board, x, y, &last_index, &capture_index, false);
				cross_moves(board, x, y, &last_index, &capture_index, false);
			}
			break;
		case W_KING:
		case B_KING:
			{
				int x = piece_grid_x;
				int y = piece_grid_y;
				int last_index = 0;
				int capture_index = 0;
				plus_moves(board, x, y, &last_index, &capture_index, true);
				cross_moves(board, x, y, &last_index, &capture_index, true);
			}
		break;
		default:
			break;
		}
	}

	// ability to move the selected piece
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && board->picked)
	{
		Piece selected_piece = board->selected_piece;
		int i = board->selected_piece.pos.x;
		int j = board->selected_piece.pos.y;

		int x = grid_pos.x;
		int y = grid_pos.y;
		Piece placement_piece = board->pieces[x][y];
		bool possible = false;

		// check placement_piece x, y is present in board->possible_moves array 
		for (int k = 0; k < 64; k++)
		{
			Vector2 possible_move = board->possible_moves[k];
			if (placement_piece.pos.x == possible_move.x && placement_piece.pos.y == possible_move.y)
			{
				possible = true;
				break;
			}
		}
		for (int k = 0; k < 10; k++)
		{
			Vector2 capture_pos = board->capture_pos[k];
			if (placement_piece.pos.x == capture_pos.x && placement_piece.pos.y == capture_pos.y)
			{
				possible = true;
				break;
			}
		}
		board->selected_piece = (Piece){ 0 };
		board->selected_piece.type = -1;
		board->selected_piece.selected = false;
		board->picked = false;

		if (selected_piece.selected && possible)
		{
			board->pieces[x][y] = (Piece){
				.src = selected_piece.src,
				.dest = (Rectangle){x * 72, y * 72, 72.f, 72.f},
				.pos = (Vector2){x, y},
				.selected = false,
				.type = selected_piece.type,
				.is_moved_once = true,
			};
			board->pieces[i][j] = (Piece){
				.src = (Rectangle){0},
				.dest = (Rectangle){i * 72, j * 72, 0.f, 0.f},
				.selected = false,
				.type = -1,
				.pos = (Vector2){i, j},
				.is_moved_once = true,
			};
		}
		reset_capture_pos(board);
	}

	if (board->selected_piece.selected)
	{
		board->picked = true;
	}

}


void cross_moves(Board* board, int x, int y, int* last_index, int* capture_index, bool single)
{
	// top left
	{
		int local_x = x - 1;
		int local_y = y - 1;
		while (local_x >= 0 && local_y >= 0)
		{
			Piece piece = board->pieces[local_x][local_y];
			if (piece.type == -1)
			{
				board->possible_moves[(*last_index)] = (Vector2){local_x, local_y};
				local_x--;
				local_y--;
				(*last_index)++;
			}
			else
			{
				board->capture_pos[(*capture_index)] = (Vector2){local_x, local_y};
				(*capture_index)++;
				break;
			}
			if (single) break;
		}
	}
	// top right
	{
		int local_x = x + 1;
		int local_y = y - 1;
		while (local_x <= 7 && local_y >= 0)
		{

			Piece piece = board->pieces[local_x][local_y];
			if (piece.type == -1)
			{
				board->possible_moves[(*last_index)] = (Vector2){ local_x, local_y };
				local_x++;
				local_y--;
				(*last_index)++;
			}
			else
			{
				board->capture_pos[(*capture_index)] = (Vector2){local_x, local_y};
				(*capture_index)++;
				break;
			}
			if (single) break;
		}
	}
	// bottom right
	{
		int local_x = x + 1;
		int local_y = y + 1;
		while (local_x <= 7 && local_y <= 7)
		{

			Piece piece = board->pieces[local_x][local_y];
			if (piece.type == -1)
			{
				board->possible_moves[(*last_index)] = (Vector2){ local_x, local_y };
				local_x++;
				local_y++;
				(*last_index)++;
			}
			else
			{
				board->capture_pos[(*capture_index)] = (Vector2){local_x, local_y};
				(*capture_index)++;
				break;
			}
			if (single) break;
		}
	}
	// bottom left
	{
		int local_x = x - 1;
		int local_y = y + 1;
		while (local_x >= 0 && local_y <= 7)
		{

			Piece piece = board->pieces[local_x][local_y];
			if (piece.type == -1)
			{
				board->possible_moves[(*last_index)] = (Vector2){ local_x, local_y };
				local_x--;
				local_y++;
				(*last_index)++;
			}
			else
			{
				board->capture_pos[(*capture_index)] = (Vector2){local_x, local_y};
				(*capture_index)++;
				break;
			}
			if (single) break;
		}
	}
}


void reset_capture_pos(Board* board)
{
	for (int i = 0; i < 10; i++)
	{
		board->capture_pos[i] = (Vector2){ -1, -1 };
	}
}


void plus_moves(Board* board, int x, int y, int* last_index, int* capture_index, bool single)
{
	// top
	{
		int local_x = x;
		int local_y = y - 1;
		for (int i = local_y; i >= 0; i--)
		{
			Piece piece = board->pieces[local_x][i];
			int dest_x = piece.dest.x / 72;
			int dest_y = piece.dest.y / 72;
			if (piece.type == -1)
			{
				board->possible_moves[(*last_index)] = (Vector2){ local_x , i };
				(*last_index)++;
			}
			else
			{
				board->capture_pos[(*capture_index)] = (Vector2){ local_x , i };
				(*capture_index)++;
				break;
			}
			if (single) break;
		}
	}
	// right
	{
		int local_x = x + 1;
		int local_y = y;
		for (int i = local_x; i <= 7; i++)
		{
			Piece piece = board->pieces[i][local_y];
			int dest_x = piece.dest.x / 72;
			int dest_y = piece.dest.y / 72;
			if (piece.type == -1)
			{
				board->possible_moves[(*last_index)] = (Vector2){ i , local_y };
				(*last_index)++;
			}
			else
			{
				board->capture_pos[(*capture_index)] = (Vector2){ i , local_y };
				(*capture_index)++;
				break;
			}
			if (single) break;
		}
	}
	// left
	{
		int local_x = x - 1;
		int local_y = y;
		for (int i = local_x; i >= 0; i--)
		{
			Piece piece = board->pieces[i][local_y];
			int dest_x = piece.dest.x / 72;
			int dest_y = piece.dest.y / 72;
			if (piece.type == -1)
			{
				board->possible_moves[(*last_index)] = (Vector2){ i , local_y };
				(*last_index)++;
			}
			else
			{
				board->capture_pos[(*capture_index)] = (Vector2){ i , local_y };
				(*capture_index)++;
				break;
			}
			if (single) break;
		}
	}
	// bottom
	{
		int local_x = x;
		int local_y = y + 1;
		for (int i = local_y; i <= 7; i++)
		{
			Piece piece = board->pieces[local_x][i];
			int dest_x = piece.dest.x / 72;
			int dest_y = piece.dest.y / 72;
			if (piece.type == -1)
			{
				board->possible_moves[(*last_index)] = (Vector2){ local_x , i };
				(*last_index)++;
			}
			else
			{
				board->capture_pos[(*capture_index)] = (Vector2){ local_x , i };
				(*capture_index)++;
				break;
			}
			if (single) break;
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
	DrawRectangleRec(board.selected_piece.dest, GetColor(0xb1a7fcff));

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


void draw_possible_moves(Board board)
{
	for (int i = 0; i < 64; i++)
	{
		Vector2 possible_move = board.possible_moves[i];

		DrawCircleV((Vector2) { possible_move.x * 72 + (72 / 2), possible_move.y * 72 + 72 / 2 }, 10.f, GetColor(0xb1a7fcff));
	}
}


void draw_capture_pos(Board board)
{
	if (board.selected_piece.selected)
	{
		bool is_selected_piece_white = board.selected_piece.type < 6 ? true : false;
		for (int i = 0; i < 10; i++)
		{
			Vector2 cp = board.capture_pos[i];
			if (cp.x >= 0 && cp.x <= 7 && cp.y >= 0 && cp.y <= 7)
			{
				Piece piece = board.pieces[(int)cp.x][(int)cp.y];
				bool other_piece_white = piece.type < 6 ? true : false;
				if ((is_selected_piece_white && !other_piece_white) ||
					(!is_selected_piece_white && other_piece_white))
				{
					DrawRectangle(cp.x * 72, cp.y * 72, 72, 72, RED);
				}
			}
		}
	}
}


