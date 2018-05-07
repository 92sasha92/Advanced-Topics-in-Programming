#pragma once
#include "PlayerAlgorithm.h"
#include <vector>
#include <memory>
#include "MyBoard.h"
#include "Mypoint.h"
#include "MyFightInfo.h"
#include "MyPiecePosition.h"

class GameManager {
private:
    PlayerAlgorithm &player1Algoritm;
    PlayerAlgorithm &player2Algoritm;
    MyBoard gameBoard;

    void StartGame();
    unique_ptr<MyFightInfo> Fight(unique_ptr<PiecePosition> &player1PiecePos, unique_ptr<PiecePosition> &player2PiecePos);
    unique_ptr<MyFightInfo> SetPiece(unique_ptr<PiecePosition> &piecePos, int player);
    unique_ptr<MyFightInfo> SetPiece(unique_ptr<Move> &pieceMove, int player);
    void printBoard();

public:
    GameManager(PlayerAlgorithm &player1Algoritm_, PlayerAlgorithm &player2Algoritm_);
};



