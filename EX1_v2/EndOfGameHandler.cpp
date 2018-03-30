#include "EndOfGameHandler.h"

int EndOfGameHandler::getEndGamelineNumber() {
    return this->endGamelineNumber;
}

void EndOfGameHandler::setEndGamelineNumber(int line_number) {
    this->endGamelineNumber = line_number;
}

EndOfGameHandler::EndOfGameReason EndOfGameHandler::getEndOfGameReason() {
    return this->endOfGameReason;
}

void EndOfGameHandler::setEndOfGameReason(EndOfGameReason reason) {
    this->endOfGameReason = reason;
}

EndOfGameHandler::GameState EndOfGameHandler::getGameState() {
    return this->gameState;
}
void EndOfGameHandler::setGameState(GameState state) {
    this->gameState = state;
}

void EndOfGameHandler::setWinner(int currentTurn ,int fileLinePlayer1, int fileLinePlayer2) {
    if (!currentTurn) {
        this->setEndGamelineNumber(fileLinePlayer1);
        this->setGameState(EndOfGameHandler::Player2Win);
    } else {
        this->setEndGamelineNumber(fileLinePlayer2);
        this->setGameState(EndOfGameHandler::Player1Win);
    }
}