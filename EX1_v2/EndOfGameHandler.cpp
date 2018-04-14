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

void EndOfGameHandler::clear() {
    this->setEndOfGameReason(GameNotFinished);
    this->setGameState(GameNotOver);
    this->setEndGamelineNumber(0);
}

bool EndOfGameHandler::isInputFileOk(const bool isBadInputFile[2]) {
    if (isBadInputFile[0] && isBadInputFile[1]) {
        cout << "two players use incorrect format file and no point are given" << endl;
        return false;
    } else if (isBadInputFile[0]) {
        cout << "player1 use incorrect format file and lose" << endl;
        return false;
    } else if (isBadInputFile[1]) {
        cout << "player2 use incorrect format file and lose" << endl;
        return false;
    }
    return true;
}

string EndOfGameHandler::toString() {
    if (this->getEndOfGameReason() == EndOfGameHandler::BadMoveFile) {
        stringstream ss;
        ss << this->getEndGamelineNumber();
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
        default:
            return "Unsupported end of game state";
    }
}
