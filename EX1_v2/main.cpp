#include "RPS.h"
#include "Parser.h"

int main() {
    RPS rps;
    bool check1, check2;
    check1 = Parser::parseBoard(rps, 0);
    check2 = Parser::parseBoard(rps, 1);
    if (!check1 && !check2) {
        cout << "two players use incorrect format file and no point are given" << endl;
    } else if (!check1) {
        cout << "player1 use incorrect format file and lose" << endl;
    } else if (!check2) {
        cout << "player2 use incorrect format file and lose" << endl;
    } else {
        // TODO: game should be played
    }
    rps.printBoard();
    return 0;
}
