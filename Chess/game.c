#include "game.h"
#include "board.h"
#include "piece.h"

void game_start(Game game)
{
	InitWindow(game.screen_width, game.screen_height, game.name);
	game.atlas_texture = LoadTexture("..\\Assets\\atlas.png");

	Board board = { 0 };
	board.white_src = (Rectangle){ 432, 0, 72, 72 };
	board.black_src = (Rectangle){ 432, 72, 72, 72 };
	
	Piece piece;
	piece.pos = (Vector2){ 0 };
	piece.type = PAWN;
	piece.is_black = false;
	piece.src = (Rectangle){ 0, 0, 72, 72 };
	piece.dest = (Rectangle){ 0,0, 72, 72 };

	game.board = board;
	game.peice = piece;

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

	draw_piece(game.atlas_texture, game.peice);
}
