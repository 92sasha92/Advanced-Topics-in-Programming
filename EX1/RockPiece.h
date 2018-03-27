#pragma once
#include "Piece.h"

class RockPiece: public Piece{
public:
	RockPiece(int player):Piece(player) {
	}
	std::string toString() override;
};