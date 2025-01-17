#include "game.h"
#include "board.h"
#include "piece.h"
#include <stdio.h>

void game_start(Game game)
{
	InitWindow(game.screen_width, game.screen_height, game.name);
	game.atlas_texture = LoadTexture("..\\Assets\\atlas.png");

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
	
	for (size_t j = 0; j < 2; j++)
	{
		for (size_t i = 0; i < game.atlas_texture.width / 72; i++)
		{
			Piece piece;
			piece.src = (Rectangle){ i * 72, j * 72, 72, 72 };
			piece.dest = (Rectangle){ 0 };
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

	game.board = board;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		game_update(dt);

		BeginDrawing();
		game_draw(game);
		EndDrawing();
		
	}

	game_end();
}

void game_end()
{
	CloseWindow();
}

void game_update(float dt)
{
	
}

void game_draw(Game game)
{
	draw_board(game.atlas_texture, game.board);
	draw_pieces(game.atlas_texture, game.board);
}
