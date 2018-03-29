#pragma once
#include "Piece.h"

class FlagPiece : public Piece {
  public:
    FlagPiece(int player):Piece(player){
			setCanMove(true);
    }
    std::string toString() override;
};