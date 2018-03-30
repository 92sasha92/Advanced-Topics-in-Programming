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