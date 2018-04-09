#include "RPS.h"
#include "Parser.h"
#include "Moves.h"

int main() {
    RPS rps;
    EndOfGameHandler endOfGameHandler;
    bool isBadInputFile[2] = {false, false};
    int ErrorLine[2] = {0, 0};
		for (int i = 0; i < 2; i++) {
			endOfGameHandler.clear();
			Parser::parseBoard(rps, i, endOfGameHandler);
			if (endOfGameHandler.getEndOfGameReason() == EndOfGameHandler::BadInputFile) {
				isBadInputFile[i] = true;
				ErrorLine[i] = endOfGameHandler.getEndGamelineNumber();
			} else if (endOfGameHandler.getEndOfGameReason() == EndOfGameHandler::CantOpenInputFile) {
				return 0;
			}
		}

    if (EndOfGameHandler::isInputFileOk(isBadInputFile)) {
        RPS::printBoard(rps);
        Moves::parseMoves(rps, endOfGameHandler);
    }

    RPS::createOutFile(rps, endOfGameHandler, isBadInputFile, ErrorLine);
//    cout << "AND THE WINNER NUMBER IS: " << RPS::checkWinner(rps, endOfGameHandler).getGameState() << endl;
    return 0;
}

