#pragma once
#include "raylib.h"

enum Type
{
	W_PAWN,		// 0
	W_ROOK,		// 1 elephant
	W_BISHOP,	// 2
	W_KNIGHT,	// 3 horse
	W_KING,		// 4 
	W_QUEEN,	// 5

	B_PAWN,		// 6
	B_ROOK,		// 7 elephant
	B_BISHOP,	// 8
	B_KNIGHT,	// 9 horse
	B_KING,		// 10
	B_QUEEN		// 11
};

typedef struct 
{
	enum Type type;
	Rectangle src;
	Rectangle dest;
	bool is_moved_once; // for pawn only
	bool selected;
} Piece;

