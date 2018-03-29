#include "RPS.h"

void RPS::printBoard(RPS& rps) {
    for (int i = 0; i < rps.Mcols; i++) {
        cout << "----------------------------------------" << endl;
        for (int j = 0; j < rps.Nrows; j++) {
            if (rps.board[i][j][0] != nullptr && rps.board[i][j][1] != nullptr) {
                cout << "ERROR: two pieces in the same cell: (" << j << ", "<< i << ") should be fight" << endl;
                break;
            }
            else if (rps.board[i][j][0] != nullptr) {
                cout << rps.board[i][j][0]->toString() << " |";
            }
            else if (rps.board[i][j][1] != nullptr) {
                cout << rps.board[i][j][1]->toString() << " |";
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

int RPS::getNumberOfRows() {
    return Nrows;
}

int RPS::getNumberOfColumns(){
    return Mcols;
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

RPS::GameState RPS::checkWinner(RPS& rps) {
    bool player1HaveFlag = false, player2HaveFlag = false ,player1HaveMovingPieces = false, player2HaveMovingPieces = false;
    for (int i = 0; i < rps.Mcols; i++) {
        for (int j = 0; j < rps.Nrows; j++) {

            if (rps.board[i][j][0] != nullptr) {
                if (rps.board[i][j][0]->type == Piece::Flag) {
                    player1HaveFlag = true;
                } else if (rps.board[i][j][0]->type != Piece::Flag && rps.board[i][j][0]->type != Piece::Undefined) {
                    player1HaveMovingPieces = true;
                }
            }

            if (rps.board[i][j][1] != nullptr) {
                if (rps.board[i][j][1]->type == Piece::Flag) {
                    player2HaveFlag = true;
                } else if (rps.board[i][j][1]->type != Piece::Flag && rps.board[i][j][1]->type != Piece::Undefined) {
                    player2HaveMovingPieces = true;
                }
            }

        }
    }
    if ((!player1HaveFlag || !player1HaveMovingPieces) && (!player2HaveFlag || !player2HaveMovingPieces)) {
        return Tie;
    } else if (!player1HaveFlag || !player1HaveMovingPieces) {
        return Player2Win;
    } else if (!player2HaveFlag || !player2HaveMovingPieces) {
        return Player1Win;
    }
    return GameNotOver;
}

RPS::~RPS() {
}
