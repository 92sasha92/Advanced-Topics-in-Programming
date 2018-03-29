#include "RPS.h"

void RPS::printBoard() {
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

void RPS::fight(RPS& rps, int row, int col) {
    cout << "fight!!!" << endl;
    Piece *piece1 = rps.board[col][row][0], *piece2 = rps.board[col][row][1];
    if (piece1->type == Piece::Joker) {
        Piece::RPSPiecesTypes piece1jokerpiece = ((JokerPiece *)piece1)->getJokerPiece();
        piece1 = PieceFactory::createPiece(piece1jokerpiece ,0);
    }
    if (piece2->type == Piece::Joker) {
        Piece::RPSPiecesTypes piece2jokerpiece = ((JokerPiece *)piece2)->getJokerPiece();
        piece2 = PieceFactory::createPiece(piece2jokerpiece ,1);
    }
    Piece::PiecesPower winner = piece1->isStrongerThan(*piece2);
    switch (winner){
        case Piece::Stronger:{
            cout << "player1 win in cell (" << row+1 << "," << col+1 << ")"  << endl;
            delete piece2;
            rps.board[col][row][1] = nullptr;
        } break;
        case Piece::Weaker:{
            cout << "player2 win in cell (" << row+1 << "," << col+1 << ")"  << endl;
            delete piece1;
            rps.board[col][row][0] = nullptr;
        } break;
        case Piece::Equal:{
            cout << "tie cell (" << row+1 << "," << col+1 << ")"  << endl;
            delete piece1;
            delete piece2;
            rps.board[col][row][0] = nullptr;
            rps.board[col][row][1] = nullptr;
        } break;
        default:
            cout << "ERROR: wrong PiecesPower type returned" << endl;
    }
}
