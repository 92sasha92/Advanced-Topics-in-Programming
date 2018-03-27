#pragma once
#include "Piece.h"

class ScissorsPiece : public Piece {
public:
	ScissorsPiece(int player) :Piece(player) {
	}
	std::string toString() override;
};