#pragma once
#include "Piece.h"

class PieceFactory {
  public:
    typedef enum {
        Rock,
        Paper,
        Scissors,
        Bomb,
        Flag,
        Joker,
        Undefined
    } RPSPiecesTypes;



    static RPSPiecesTypes charToPieceType(char c);
    static Piece *createPiece(RPSPiecesTypes cPiece, int player, RPSPiecesTypes jokerPiece = Undefined);
};