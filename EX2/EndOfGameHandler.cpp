#include "EndOfGameHandler.h"

int EndOfGameHandler::getEndGameLineNumber() const {
    return this->endGameLineNumber;
}

void EndOfGameHandler::setEndGameLineNumber(int line_number) {
    this->endGameLineNumber = line_number;
}

EndOfGameHandler::EndOfGameReason EndOfGameHandler::getEndOfGameReason() const {
    return this->endOfGameReason;
}

void EndOfGameHandler::setEndOfGameReason(EndOfGameReason reason) {
    this->endOfGameReason = reason;
}

EndOfGameHandler::GameState EndOfGameHandler::getGameState() const {
    return this->gameState;
}
void EndOfGameHandler::setGameState(GameState state) {
    this->gameState = state;
}

void EndOfGameHandler::setWinner(int currentTurn ,int fileLinePlayer1, int fileLinePlayer2) {
    if (!currentTurn) {
        this->setEndGameLineNumber(fileLinePlayer1);
        this->setGameState(EndOfGameHandler::Player2Win);
    } else {
        this->setEndGameLineNumber(fileLinePlayer2);
        this->setGameState(EndOfGameHandler::Player1Win);
    }
}

string EndOfGameHandler::toString() const {
    if (this->getEndOfGameReason() == EndOfGameHandler::BadMoveFile) {
        stringstream ss;
        ss << this->getEndGameLineNumber();
        if (this->getGameState() == 1) {
            return "Bad Moves input file for player 2 - line " + ss.str();
        } else {
            return "Bad Moves input file for player 1 - line " + ss.str();
        }
    }

    switch (this->getEndOfGameReason()) {
        case LooserAllFlagsEaten: {
            return "All flags of the opponent are captured";
        }
        case AllMovingPiecesEaten: {
            return "All moving PIECEs of the opponent are eaten";
        }
        case GameNotFinished: {
            return "A tie - both Moves input files done without a winner";
        }
        case TieAllFlagsEaten: {
            return "A tie - all flags are eaten by both players in the position files";
        }
        case TieAllMovingPiecesEaten: {
            return "A tie - All moving PIECEs of both players are eaten";
        }
        case Tie100MovesNoFight: {
            return "A tie - 100 moves without a fight";
        }
        default:
            return "Unsupported end of game state";
    }
}
