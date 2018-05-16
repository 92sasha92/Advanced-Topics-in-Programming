#include "RPS.h"

string RPS::outputFile = "rps.output";

void RPS::initializePiecesArsenal() {
    this->playerPiecesArsenal[Piece::Rock] = RPS::R;
    this->playerPiecesArsenal[Piece::Paper] = RPS::P;
    this->playerPiecesArsenal[Piece::Scissors] = RPS::S;
    this->playerPiecesArsenal[Piece::Bomb] = RPS::B;
    this->playerPiecesArsenal[Piece::Joker] = RPS::J;
    this->playerPiecesArsenal[Piece::Flag] = RPS::F;
    this->playerPiecesArsenal[Piece::Undefined] = 0;
}

void RPS::printBoard(RPS& rps) {
//    cout << endl;
//    cout << "!@#$%^&*()(*&%^@$@#%@#%#$^%$&%&^%*^&(&^($" << endl;
//    cout << endl;
//
//    for (int i = 0; i < Nrows; i++) {
//        cout << "----------------------------------------" << endl;
//        for (int j = 0; j < Mcols; j++) {
//            if (rps.game[i][j].get() != nullptr) {
//                cout << rps.game[i][j]->toString() << " |";
//            } else {
//                cout << "   |";
//            }
//        }
//        cout << endl;
//    }
}

RPS::RPS() : game(0){ // TODO: game should not be initialize this way
    for (int i = 0; i < Nrows; i++){
        vector<unique_ptr<Piece>> line;
        for (int j = 0; j < Mcols; j++) {
            unique_ptr<Piece> ptr;
            line.push_back(move(ptr));
        }
        game.push_back(move(line));
    }
}

int RPS::getNumberOfRows() const{
    return Nrows;
}

int RPS::getNumberOfColumns() const{
    return Mcols;
}

void RPS::fight(RPS& rps, int row, int col, unique_ptr<Piece> &piecePtr) {
    cout << "fight!!!!!" << endl;
    unique_ptr<Piece> piece1 , piece2;

    if (rps.game[row][col]->type == Piece::Joker) {
        piece1 = PieceFactory::createPiece(((JokerPiece *)rps.game[row][col].get())->getJokerPiece(), 1);
    } else {
        piece1 = PieceFactory::createPiece(rps.game[row][col]->type ,1);
    }

    if (piecePtr->type == Piece::Joker) {
        piece2 = PieceFactory::createPiece(((JokerPiece *)piecePtr.get())->getJokerPiece(), 2);
    } else {
        piece2 = PieceFactory::createPiece(piecePtr->type ,2);
    }

    Piece::PiecesPower winner = piece1->isStrongerThan(*(piece2.get()));
    switch (winner){
        case Piece::Stronger:{
            cout << "player1 win in cell (" << row + 1 << "," << col + 1 << ")"  << endl;
        } break;
        case Piece::Weaker:{
            cout << "player2 win in cell (" << row + 1 << "," << col + 1 << ")"  << endl;
            rps.game[row][col].release();
            rps.game[row][col] = move(piecePtr);
        } break;
        case Piece::Equal:{
            cout << "tie cell (" << row + 1 << "," << col + 1 << ")"  << endl;
            rps.game[row][col].release();
        } break;
        default:
            cout << "ERROR: wrong PiecesPower type returned" << endl;
    }
}

EndOfGameHandler RPS::checkWinner(RPS& rps, EndOfGameHandler& endOfGameHandler, int currentPlayer) {
    bool player1HaveFlag = false, player2HaveFlag = false ,player1HaveMovingPieces = false, player2HaveMovingPieces = false;
    for (int i = 0; i < rps.Nrows; i++) {
        for (int j = 0; j < rps.Mcols; j++) {
            if (rps.game[i][j].get() != nullptr) {
                if (rps.game[i][j]->getPlayerNumber() == 0) {
                    if (rps.game[i][j]->type == Piece::Flag) {
                        player1HaveFlag = true;
                    } else if (rps.game[i][j]->type == Piece::Rock || rps.game[i][j]->type == Piece::Scissors || rps.game[i][j]->type == Piece::Paper) {
                        player1HaveMovingPieces = true;
                    } else if (rps.game[i][j]->type == Piece::Joker && ((JokerPiece *)rps.game[i][j].get())->getJokerPiece() != Piece::Bomb) {
                        player1HaveMovingPieces = true;
                    }
                } else {
                    if (rps.game[i][j]->type == Piece::Flag) {
                        player2HaveFlag = true;
                    } else if (rps.game[i][j]->type == Piece::Rock || rps.game[i][j]->type == Piece::Scissors || rps.game[i][j]->type == Piece::Paper) {
                        player2HaveMovingPieces = true;
                    } else if (rps.game[i][j]->type == Piece::Joker && ((JokerPiece *)rps.game[i][j].get())->getJokerPiece() != Piece::Bomb) {
                        player2HaveMovingPieces = true;
                    }
                }
            }
        }
    }

    if ((!player1HaveFlag) || (!player2HaveFlag)) {
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::LooserAllFlagsEaten);
        if (player1HaveFlag) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player1Win);
        } else if (player2HaveFlag) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player2Win);
        } else {
            endOfGameHandler.setEndOfGameReason(EndOfGameHandler::TieAllFlagsEaten);
            endOfGameHandler.setGameState(EndOfGameHandler::Tie);
        }

    } else if ((!player1HaveMovingPieces && currentPlayer == 0) || (!player2HaveMovingPieces && currentPlayer)) {
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::AllMovingPiecesEaten);
        if (player1HaveMovingPieces) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player1Win);
        } else if (player2HaveMovingPieces) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player2Win);
        } else {
            endOfGameHandler.setGameState(EndOfGameHandler::Tie);
            endOfGameHandler.setEndOfGameReason(EndOfGameHandler::TieAllMovingPiecesEaten);
        }
    }
    return endOfGameHandler;
}

//void RPS::createOutFile(RPS& rps, EndOfGameHandler& endOfGameHandler, bool isBadInputFile[2], int ErrorLine[2]) {
//    ofstream fout(outputFile);
//    if ((isBadInputFile[0] || isBadInputFile[1])) {
//        if (!isBadInputFile[0]) {
//            fout << "Winner: " << 1 << endl;
//        } else if (!isBadInputFile[1]) {
//            fout << "Winner: " << 2 << endl;
//        } else {
//            fout << "Winner: " << 0 << endl;
//        }
//    } else if (endOfGameHandler.getGameState() == EndOfGameHandler::GameNotOver) {
//        fout << "Winner: " << 0 << endl;
//    } else {
//        fout << "Winner: " << endOfGameHandler.getGameState() << endl;
//    }
//    fout << "Reason: ";
//    if (isBadInputFile[0] && isBadInputFile[1]) {
//        fout << "Bad Positioning input file for both players - player 1: line ";
//        fout << ErrorLine[0] << ", player 2: line " << ErrorLine[1] << endl;
//    } else if (isBadInputFile[0]) {
//        fout << "Bad Positioning input file for player 1 - line " << ErrorLine[0] << endl;
//    } else if (isBadInputFile[1]) {
//        fout << "Bad Positioning input file for player 2 - line " << ErrorLine[1] << endl;
//    } else {
//        fout << endOfGameHandler.toString() << endl;
//    }
//    // empty line
//    fout << endl;
//    for (int i = 0; i < rps.Nrows; i++) {
//        for (int j = 0; j < rps.Mcols; j++) {
//            if (rps.game[i][j].get() == nullptr) {
//               fout << " ";
//            } else {
//                fout << rps.game[i][j]->toString();
//            }
//        }
//        fout << endl;
//    }
//    fout.close();
//}

bool RPS::checkIfMoveIsLegal(std::vector<std::vector<std::unique_ptr<Piece>>> &board, const Move &move, int player, bool printMessages) {
    //bool isJoker = false;
    RPS rps;
    unique_ptr<Piece> piecePtr;
    const Point *fPoint = &(move.getFrom());
    const Point *toPoint = &(move.getTo());
    if (fPoint->getY() < 0 || fPoint->getX() < 0 || toPoint->getX() < 0 || toPoint->getY() < 0) {
        if (printMessages) {
            cout << "ERROR: move index is out of bound" << endl;
        }
        return false;
    } else if (fPoint->getY() >= rps.getNumberOfRows() || fPoint->getX() >= rps.getNumberOfColumns() || toPoint->getX() >= rps.getNumberOfColumns() || toPoint->getY() >= rps.getNumberOfRows()) {
        if (printMessages) {
            cout << "ERROR: move index is out of bound" << endl;
        }
        return false;
    }

    if (board[fPoint->getY()][fPoint->getX()].get() == nullptr) {
        cout << "ERROR: no piece in the given position" << endl;
        return false;
    }
//    if (gameBoard.board[fPoint->getY()][fPoint->getX()]->type == Piece::Joker) {
//        isJoker = true;
//    }
    if (!(board[fPoint->getY()][fPoint->getX()]->getCanMove())) {
        if (printMessages) {
            cout << "ERROR " << board[fPoint->getY()][fPoint->getX()]->toString() << " can't move" << endl;
        }
        return false;
    }
    if ((fPoint->getY() + 1 != toPoint->getY() && fPoint->getY() - 1 != toPoint->getY() && fPoint->getX() + 1 != toPoint->getX() && fPoint->getX() - 1 != toPoint->getX()) || (fPoint->getY() != toPoint->getY() && fPoint->getX() != toPoint->getX())) {
        if (printMessages) {
            cout << "ERROR: illegal move, can't move from: (" << fPoint->getX() + 1 << ", " << fPoint->getY() + 1 << ") to: (" << toPoint->getX() + 1 << ", " << toPoint->getY() + 1 << ")" << endl;
        }
        return false;
    }
    if (board[toPoint->getY()][toPoint->getX()].get() != nullptr && board[toPoint->getY()][toPoint->getX()]->getPlayerNumber() == player) {
        if (printMessages) {
            cout << "ERROR: the cell already occupied by other piece of the same player" << endl;
        }
        return false;
    }
    return true;
}

RPS::~RPS() {

}
