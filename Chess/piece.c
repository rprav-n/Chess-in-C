#include "piece.h"

void draw_piece(Texture2D atlas_texture, Piece piece)
{
	DrawTexturePro(atlas_texture, piece.src, piece.dest, (Vector2) { 0 }, 0.f, WHITE);
}
