#pragma once
#include "raylib.h"

enum Type
{
	W_PAWN,
	W_ROOK, // elephant
	W_BISHOP,
	W_KNIGHT, // horse
	W_KING,
	W_QUEEN,

	B_PAWN,
	B_ROOK, // elephant
	B_BISHOP,
	B_KNIGHT, // horse
	B_KING,
	B_QUEEN
};

typedef struct 
{
	Vector2 pos;
	enum Type type;
	Rectangle src;
	Rectangle dest;
} Piece;

