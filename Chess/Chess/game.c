#include "game.h"
#include "board.h"
#include "piece.h"
#include <stdio.h>
#include <math.h>

void game_start(Game* game)
{
	InitWindow(game->screen_width, game->screen_height, game->name);
	game->atlas_texture = LoadTexture("..\\..\\Assets\\atlas.png");

	Board board = { 
		.grid = {
			{B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT, B_ROOK},
			{B_PAWN, B_PAWN,   B_PAWN,   B_PAWN,  B_PAWN, B_PAWN,   B_PAWN,   B_PAWN},
			{-1,	 -1,	   -1,       -1,      -1,     -1,       -1,       -1    },
			{-1,	 -1,	   -1,       -1,      -1,     -1,       -1,       -1    },
			{-1,	 -1,	   -1,       -1,      -1,     -1,       -1,       -1    },
			{-1,	 -1,	   -1,       -1,      -1,     -1,       -1,       -1    },
			{W_PAWN, W_PAWN,    W_PAWN,   W_PAWN, W_PAWN, W_PAWN,   W_PAWN,   W_PAWN},
			{W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK},
		}
	};
	board.white_src = (Rectangle){ 432, 0, 72, 72 };
	board.black_src = (Rectangle){ 432, 72, 72, 72 };
	board.mouse_grid_pos = (Vector2){ 0 };
	for (int i = 0; i < 10; i++)
	{
		board.capture_pos[i] = (Vector2){ -1, -1 };
	}

	for (size_t j = 0; j < 2; j++)
	{
		for (size_t i = 0; i < game->atlas_texture.width / 72; i++)
		{
			Piece piece;
			piece.src = (Rectangle){ i * 72, j * 72, 72, 72 };
			piece.is_moved_once = false;
			piece.selected = false;
			switch (i)
			{
			case 0:
				piece.type = j == 0 ? W_PAWN : B_PAWN;
				break;
			case 1:
				piece.type = j == 0 ? W_ROOK : B_ROOK;
				break;
			case 2:
				piece.type = j == 0 ? W_BISHOP : B_BISHOP;
				break;
			case 3:
				piece.type = j == 0 ? W_KNIGHT : B_KNIGHT;
				break;
			case 4:
				piece.type = j == 0 ? W_KING : B_KING;
				break;
			case 5:
				piece.type = j == 0 ? W_QUEEN : B_QUEEN;
				break;
			default:
				break;
			}
			board.total_pieces[i + (j*6)] = piece;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int grid_type = board.grid[i][j];
			Piece piece = { 0 };
			piece.type = grid_type;
			piece.selected = false;
			piece.pos = (Vector2){ j, i };
			if (grid_type != -1)
			{
				for (int k = 0; k < 12; k++)
				{
					Piece p =  board.total_pieces[k];
					if (p.type == piece.type) 
					{
						piece.src = p.src;
						piece.dest = (Rectangle){ j*72.f, i*72.f, 72.f, 72.f};
					}
				}
			}
			else
			{
				piece.src = (Rectangle){ 0 };
				piece.dest = (Rectangle){ j * 72.f, i * 72.f, 0.f, 0.f};
				
			}
			board.pieces[j][i] = piece;
		}
	}

	game->board = board;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		game_update(dt, game);

		BeginDrawing();
		game_draw(*game);
		EndDrawing();
		
	}

	game_end();
}

void game_end()
{
	CloseWindow();
}

void game_update(float dt, Game* game)
{
	Board* board = &(game->board);
	update_board(board);
}

void game_draw(Game game)
{
	draw_board(game.atlas_texture, game.board);
	draw_possible_moves(game.board);
	draw_capture_pos(game.board);
	draw_pieces(game.atlas_texture, game.board);
	
}

