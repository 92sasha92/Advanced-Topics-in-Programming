#pragma once
#include "Piece.h"

class BombPiece : public Piece {
  public:
    BombPiece(int player) :Piece(player) {
    }
    std::string toString() override;
};