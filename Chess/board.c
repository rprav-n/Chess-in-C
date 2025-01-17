#include "board.h"

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
