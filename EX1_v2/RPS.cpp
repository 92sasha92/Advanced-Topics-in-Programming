#include "RPS.h"

void RPS::PrintBoard() {
    for (int i = 0; i < this->Mcols; i++) {
        cout << "----------------------------------------" << endl;
        for (int j = 0; j < this->Nrows; j++) {
            if (this->board[i][j][0] != nullptr && this->board[i][j][1] != nullptr) {
                cout << "ERROR: two pieces in the same cell: (" << j << ", "<< i << ") should be fight" << endl;
                break;
            }
            else if (this->board[i][j][0] != nullptr) {
                cout << this->board[i][j][0]->toString() << " |";
            }
            else if (this->board[i][j][1] != nullptr) {
                cout << this->board[i][j][1]->toString() << " |";
            }
            else {
                cout << "   |";
            }
        }
        cout << endl;
    }
}

RPS::RPS() {
    for (int i = 0; i < this->Mcols; i++) {
        for (int j = 0; j < this->Nrows; j++) {
            this->board[i][j][0] = nullptr;
            this->board[i][j][1] = nullptr;
        }
    }
}
