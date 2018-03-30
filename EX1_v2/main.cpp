#include "RPS.h"
#include "Parser.h"
#include "Moves.h"

int main() {
    RPS rps;
    EndOfGameHandler endOfGameHandler;
    bool isBadInputFile[2] = {false, false};
    int ErrorLine[2] = {0, 0};

    Parser::parseBoard(rps, 0, endOfGameHandler);
    if (endOfGameHandler.getEndOfGameReason() == EndOfGameHandler::BadInputFile) {
        isBadInputFile[0] = true;
        ErrorLine[0] = endOfGameHandler.getEndGamelineNumber();
    }
    endOfGameHandler.clear();
    Parser::parseBoard(rps, 1, endOfGameHandler);
    if (endOfGameHandler.getEndOfGameReason() == EndOfGameHandler::BadInputFile) {
        isBadInputFile[1] = true;
        ErrorLine[1] = endOfGameHandler.getEndGamelineNumber();
    }

    if (EndOfGameHandler::isInputFileOk(isBadInputFile)) {
        RPS::printBoard(rps);
        Moves::parseMoves(rps, endOfGameHandler);
    }

    RPS::createOutFile(rps, endOfGameHandler, isBadInputFile, ErrorLine);
    cout << "AND THE WINNER NUMBER IS: " << RPS::checkWinner(rps, endOfGameHandler).getGameState() << endl;
    return 0;
}

