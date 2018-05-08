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
//    PlayerAlgorithm &player1Algoritm;
//    PlayerAlgorithm &player2Algoritm;
    vector<unique_ptr<PlayerAlgorithm>> playerAlgoritms;
    MyBoard gameBoard;
    typedef enum {
        FIRST_PLAYER_TURN = 0,
        SECOND_PLAYER_TURN = 1
    }Turns;
    void startGame();
    unique_ptr<MyFightInfo> fight(unique_ptr<PiecePosition> &player1PiecePos, unique_ptr<PiecePosition> &player2PiecePos);
    unique_ptr<MyFightInfo> setPiece(unique_ptr<PiecePosition> &piecePos, int player);
    unique_ptr<MyFightInfo> setPiece(unique_ptr<Move> &pieceMove, int player);
    bool checkLegalPositioningVec(std::vector<unique_ptr<PiecePosition>> &vec);
    void printBoard();
    Turns changeTurn(Turns turn);

public:
//    GameManager(PlayerAlgorithm &player1Algoritm_, PlayerAlgorithm &player2Algoritm_);
    GameManager(unique_ptr<PlayerAlgorithm> &&player1Algoritm_, unique_ptr<PlayerAlgorithm> &&player2Algoritm_);
};



