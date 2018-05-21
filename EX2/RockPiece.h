#pragma once
#include "Piece.h"

class RockPiece: public Piece{
  public:
    RockPiece(int player);
    std::string toString() const override;
    ~RockPiece() final;
};