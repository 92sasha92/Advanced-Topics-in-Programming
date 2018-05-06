#include "GameManager.h"


GameManager::GameManager(PlayerAlgorithm &player1Algoritm_, PlayerAlgorithm &player2Algoritm_): player1Algoritm(player1Algoritm_), player2Algoritm(player2Algoritm_), gameBoard(){
    startGame();
}

void GameManager::startGame(){
    std::vector<unique_ptr<PiecePosition>> vectorToFill_1;
    std::vector<unique_ptr<PiecePosition>> vectorToFill_2;
    player1Algoritm.getInitialPositions(1, vectorToFill_1);
    player2Algoritm.getInitialPositions(2, vectorToFill_2);

}
