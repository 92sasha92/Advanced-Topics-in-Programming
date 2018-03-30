#include "RPS.h"
#include "Parser.h"
#include "Moves.h"

int main() {
    RPS rps;
    EndOfGameHandler endOfGameHandler;
    bool check1, check2;
    Parser::parseBoard(rps, 0, endOfGameHandler);
    Parser::parseBoard(rps, 1, endOfGameHandler);
    if (!check1 && !check2) {
        cout << "two players use incorrect format file and no point are given" << endl;
    } else if (!check1) {
        cout << "player1 use incorrect format file and lose" << endl;
    } else if (!check2) {
        cout << "player2 use incorrect format file and lose" << endl;
    }

	RPS::printBoard(rps);
	Moves::parseMoves(rps, endOfGameHandler);
    RPS::createOutFile(rps);
    cout << "AND THE WINNER NUMBER IS: " << RPS::checkWinner(rps, endOfGameHandler).getGameState() << endl;
    return 0;
}

