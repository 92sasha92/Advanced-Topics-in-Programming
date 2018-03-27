#pragma once
#include "Piece.h"
class FlagPiece : public Piece {
public:
	FlagPiece(int player) :Piece(player) {
	}
	std::string toString() override;
};

