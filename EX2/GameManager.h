#pragma once
#include "PlayerAlgorithm.h"
#include <vector>
#include "MyBoard.h"

class GameManager {
private:
    PlayerAlgorithm &player1Algoritm;
    PlayerAlgorithm &player2Algoritm;
    MyBoard gameBoard;
    void startGame();
public:
    GameManager(PlayerAlgorithm &player1Algoritm_, PlayerAlgorithm &player2Algoritm_);
};



