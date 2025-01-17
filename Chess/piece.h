#pragma once
#include "raylib.h"

enum Type
{
	PAWN,
	ROOK, // elephant
	BISHOP,
	KNIGHT, // horse
	KING,
	QUEEN
};

typedef struct 
{
	Vector2 pos;
	enum Type type;
	Rectangle src;
	Rectangle dest;
	bool is_black;
} Piece;

void draw_piece(Texture2D atlas_texture, Piece piece);