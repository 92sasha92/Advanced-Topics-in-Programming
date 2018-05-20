#include "RPS.h"


void RPS::initializePiecesArsenal() {
    this->playerPiecesArsenal[Piece::Rock] = RPS::R;
    this->playerPiecesArsenal[Piece::Paper] = RPS::P;
    this->playerPiecesArsenal[Piece::Scissors] = RPS::S;
    this->playerPiecesArsenal[Piece::Bomb] = RPS::B;
    this->playerPiecesArsenal[Piece::Joker] = RPS::J;
    this->playerPiecesArsenal[Piece::Flag] = RPS::F;
    this->playerPiecesArsenal[Piece::Undefined] = 0;
}

int RPS::getNumberOfRows() const{
    return Nrows;
}

int RPS::getNumberOfColumns() const{
    return Mcols;
}


bool RPS::checkIfMoveIsLegal(std::vector<std::vector<std::unique_ptr<Piece>>> &board, const Move &move, int player, bool printMessages) {
    //bool isJoker = false;
    RPS rps;
    unique_ptr<Piece> piecePtr;
    MyPoint fPoint(move.getFrom().getX(), move.getFrom().getY());
    MyPoint toPoint(move.getTo().getX(), move.getTo().getY());
    if (fPoint.getY() < 0 || fPoint.getX() < 0 || toPoint.getX() < 0 || toPoint.getY() < 0) {
        if (printMessages) {
            cout << "ERROR: move index is out of bound" << endl;
        }
        return false;
    } else if (fPoint.getY() >= rps.getNumberOfRows() || fPoint.getX() >= rps.getNumberOfColumns() || toPoint.getX() >= rps.getNumberOfColumns() || toPoint.getY() >= rps.getNumberOfRows()) {
        if (printMessages) {
            cout << "ERROR: move index is out of bound" << endl;
        }
        return false;
    }

    if (board[fPoint.getY()][fPoint.getX()].get() == nullptr) {
        if (printMessages) {
            cout << "ERROR: no piece in the given position" << endl;
        }

        return false;
    }
//    if (gameBoard.board[fPoint->getY()][fPoint->getX()]->type == Piece::Joker) {
//        isJoker = true;
//    }
    if(board[fPoint.getY()][fPoint.getX()]->getPlayerNumber() != player){
        if (printMessages) {
            cout << "ERROR: cannot move opponent piece" << endl;
        }
        return false;
    }
    if (!(board[fPoint.getY()][fPoint.getX()]->getCanMove())) {
        if (printMessages) {
            cout << "ERROR " << board[fPoint.getY()][fPoint.getX()]->toString() << " can't move" << endl;
        }
        return false;
    }
    if ((fPoint.getY() + 1 != toPoint.getY() && fPoint.getY() - 1 != toPoint.getY() && fPoint.getX() + 1 != toPoint.getX() && fPoint.getX() - 1 != toPoint.getX()) || (fPoint.getY() != toPoint.getY() && fPoint.getX() != toPoint.getX())) {
        if (printMessages) {
            cout << "ERROR: illegal move, can't move from: (" << fPoint.getX() + 1 << ", " << fPoint.getY() + 1 << ") to: (" << toPoint.getX() + 1 << ", " << toPoint.getY() + 1 << ")" << endl;
        }
        return false;
    }
    if (board[toPoint.getY()][toPoint.getX()].get() != nullptr && board[toPoint.getY()][toPoint.getX()]->getPlayerNumber() == player) {
//        cout << board[toPoint->getY()][toPoint->getX()]->getPlayerNumber();
        if (printMessages) {
            cout << "ERROR: the cell already occupied by other piece of the same player" << endl;
        }
        return false;
    }

    return true;
}

