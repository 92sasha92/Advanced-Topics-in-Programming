#pragma once
#include "Piece.h"

class BombPiece : public Piece {
  public:
    BombPiece(int player);
    std::string toString() override;
    ~BombPiece() final;
};