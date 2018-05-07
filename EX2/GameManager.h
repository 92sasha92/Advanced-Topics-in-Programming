#pragma once
#include "PlayerAlgorithm.h"
#include <vector>
#include <memory>
#include "MyBoard.h"
#include "Mypoint.h"
#include "MyFightInfo.h"

class GameManager {
private:
    PlayerAlgorithm &player1Algoritm;
    PlayerAlgorithm &player2Algoritm;
    MyBoard gameBoard;

    void startGame();
    unique_ptr<MyFightInfo> fight(unique_ptr<PiecePosition> player1PiecePos, unique_ptr<PiecePosition> player2PiecePos);

public:
    GameManager(PlayerAlgorithm &player1Algoritm_, PlayerAlgorithm &player2Algoritm_);
};



