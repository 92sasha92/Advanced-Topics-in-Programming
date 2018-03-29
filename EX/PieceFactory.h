#pragma once
#include "RockPiece.h"
#include "PaperPiece.h"
#include "ScissorsPiece.h"
#include "BombPiece.h"
#include "JokerPiece.h"
#include "FlagPiece.h"

class PieceFactory {
  public:
    typedef enum {
        Rock,
        Paper,
        Scissors,
        Bomb,
        Joker,
        Flag,
        Undefined
    } RPSPiecesTypes;

    static RPSPiecesTypes charToPieceType(char c);
    static Piece *createPiece(RPSPiecesTypes cPiece, int player, RPSPiecesTypes jokerPiece = Undefined);
};


