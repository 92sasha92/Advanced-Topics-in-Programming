#pragma once
#include "Piece.h"

class FlagPiece : public Piece {
  public:
    FlagPiece(int player);
    std::string toString() const override;
    ~FlagPiece() final;
};