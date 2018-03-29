#include "RPS.h"

int main() {
    RPS rps;
    bool check1, check2;
    check1 = rps.Parser(0);
    check2 = rps.Parser(1);
    if (!check1 && !check2) {
        cout << "two players use uncorrect format file and no point are given" << endl;
    } else if (!check1 && check2) {
        cout << "player1 use uncorrect format file and lose" << endl;
    } else if (check1 && !check2) {
        cout << "player2 use uncorrect format file and lose" << endl;
    } else {
        // TODO: game should be played
    }
    rps.PrintBoard();
    return 0;
}

