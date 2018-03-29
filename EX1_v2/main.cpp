#include "RPS.h"
#include "Parser.h"

int main() {
    RPS rps;
    bool check1, check2;
    check1 = Parser::ParseBoard(rps, 0);
    check2 = Parser::ParseBoard(rps, 1);
    if (!check1 && !check2) {
        cout << "two players use incorrect format file and no point are given" << endl;
    } else if (!check1 && check2) {
        cout << "player1 use incorrect format file and lose" << endl;
    } else if (check1 && !check2) {
        cout << "player2 use incorrect format file and lose" << endl;
    } else {
        // TODO: game should be played
    }
    rps.PrintBoard();
    return 0;
}

