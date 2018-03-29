#pragma once
#include "Piece.h"

class BombPiece : public Piece {
  public:
    BombPiece(int player) :Piece(player){
			setCanMove(true);
    }
    std::string toString() override;
};