#include "RPS.h"
#include "Parser.h"
#include "Moves.h"
#include "MyMove.h"

int main() {
    MyPoint p1(3, 4), p2(5, 6), p3(6, 6);
    MyMove m;
    cout << "(" << m.getFrom().getX() << ", "<< m.getFrom().getY() << ")" << endl;
    cout << "(" << m.getTo().getX() << ", " << m.getTo().getY() << ")" << endl << "isInitialized: " << m.getIsInitialized() << endl;
    m.init(p1, p2);
    cout << "(" << m.getFrom().getX() << ", "<< m.getFrom().getY() << ")" << endl;
    cout << "(" << m.getTo().getX() << ", " << m.getTo().getY() << ")" << endl << "isInitialized: " << m.getIsInitialized() << endl;
    m.setFrom(p3);
    cout << "(" << m.getFrom().getX() << ", "<< m.getFrom().getY() << ")" << endl;
    cout << "(" << m.getTo().getX() << ", " << m.getTo().getY() << ")" << endl << "isInitialized: " << m.getIsInitialized() << endl;
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

