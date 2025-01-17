#include "board.h"
#include <stdio.h>

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
}

void draw_pieces(Texture2D atlas_texture, Board board)
{
	int l = sizeof(board.grid) / sizeof(board.grid[0]);
	int total_pieces = sizeof(board.total_pieces) / sizeof(board.total_pieces[0]);
	
	for (size_t i = 0; i < l; i++)
	{
		for (size_t j = 0; j < l; j++)
		{
			int grid_type = board.grid[i][j];

			for (size_t k = 0; k < total_pieces; k++)
			{
				Piece piece = board.total_pieces[k];
				if (grid_type  == piece.type)
				{
					Rectangle dest = piece.dest;
					if (dest.width == 0 && dest.height == 0)
					{
						dest.x = (j * piece.src.width);
						dest.y = (i * piece.src.height);
						dest.width = piece.src.width;
						dest.height = piece.src.height;
						//printf("%f, %f\n", dest.x, dest.y);
					}
					DrawTexturePro(atlas_texture, piece.src, dest, (Vector2) { 0 }, 0.f, WHITE);
					break;
				}
			}
		}
		//printf("---\n");
	}

}
