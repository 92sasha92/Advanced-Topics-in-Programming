#include "RPS.h"

//string RPS::outputFile = "C:\\Users\\sasha\\Desktop\\Advanced_Topics_in_Programming\\Advanced-Topics-in-Programming\\EX1_v2\\rps.output";
//string RPS::outputFile = "C:\\Users\\drucker16\\git\\Advanced-Topics-in-Programming\\EX1_v2\\rps.output";
string RPS::outputFile = "rps.output";

void RPS::printBoard(RPS& rps) {
    for (int i = 0; i < rps.Nrows; i++) {
        cout << "----------------------------------------" << endl;
        for (int j = 0; j < rps.Mcols; j++) {
            if (rps.board[i][j][0] != nullptr && rps.board[i][j][1] != nullptr) {
                cout << "ERROR: two pieces in the same cell: (" << i << ", "<< j << ") should be fight" << endl;
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
    for (int i = 0; i < this->Nrows; i++) {
        for (int j = 0; j < this->Mcols; j++) {
            this->board[i][j][0] = nullptr;
            this->board[i][j][1] = nullptr;
        }
    }
}

int RPS::getNumberOfRows() const{
    return Nrows;
}

int RPS::getNumberOfColumns() const{
    return Mcols;
}

void RPS::fight(RPS& rps, int row, int col) {
    cout << "fight!!!" << endl;
    Piece *piece1 = rps.board[row][col][0], *piece2 = rps.board[row][col][1];

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
            cout << "player1 win in cell (" << row + 1 << "," << col + 1 << ")"  << endl;
            delete piece2;
            rps.board[row][col][1] = nullptr;
        } break;
        case Piece::Weaker:{
            cout << "player2 win in cell (" << row + 1 << "," << col + 1 << ")"  << endl;
            delete piece1;
            rps.board[row][col][0] = nullptr;
        } break;
        case Piece::Equal:{
            cout << "tie cell (" << row + 1 << "," << col + 1 << ")"  << endl;
            delete piece1;
            delete piece2;
            rps.board[row][col][0] = nullptr;
            rps.board[row][col][1] = nullptr;
        } break;
        default:
            cout << "ERROR: wrong PiecesPower type returned" << endl;
    }
}

EndOfGameHandler RPS::checkWinner(RPS& rps, EndOfGameHandler& endOfGameHandler, int currentPlayer) {
    bool player1HaveFlag = false, player2HaveFlag = false ,player1HaveMovingPieces = false, player2HaveMovingPieces = false;
    for (int i = 0; i < rps.Nrows; i++) {
        for (int j = 0; j < rps.Mcols; j++) {

            if (rps.board[i][j][0] != nullptr) {
                if (rps.board[i][j][0]->type == Piece::Flag) {
                    player1HaveFlag = true;
                } else if (rps.board[i][j][0]->type == Piece::Rock || rps.board[i][j][0]->type == Piece::Scissors || rps.board[i][j][0]->type == Piece::Paper) {
                    player1HaveMovingPieces = true;
                } else if (rps.board[i][j][0]->type == Piece::Joker && ((JokerPiece *)rps.board[i][j][0])->getJokerPiece() != Piece::Bomb) {
                    player1HaveMovingPieces = true;
                }
            }

            if (rps.board[i][j][1] != nullptr) {
                if (rps.board[i][j][1]->type == Piece::Flag) {
                    player2HaveFlag = true;
                } else if (rps.board[i][j][1]->type == Piece::Rock || rps.board[i][j][1]->type == Piece::Scissors || rps.board[i][j][1]->type == Piece::Paper) {
                    player2HaveMovingPieces = true;
                } else if (rps.board[i][j][1]->type == Piece::Joker && ((JokerPiece *)rps.board[i][j][1])->getJokerPiece() != Piece::Bomb) {
                    player2HaveMovingPieces = true;
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

void RPS::createOutFile(RPS& rps, EndOfGameHandler& endOfGameHandler, bool isBadInputFile[2], int ErrorLine[2]) {
    ofstream fout(outputFile);
    if ((isBadInputFile[0] || isBadInputFile[1])) {
        if (!isBadInputFile[0]) {
            fout << "Winner: " << 1 << endl;
        } else if (!isBadInputFile[1]) {
            fout << "Winner: " << 2 << endl;
        } else {
            fout << "Winner: " << 0 << endl;
        }
    } else if (endOfGameHandler.getGameState() == EndOfGameHandler::GameNotOver) {
        fout << "Winner: " << 0 << endl;
    } else {
        fout << "Winner: " << endOfGameHandler.getGameState() << endl;
    }
		fout << "Reason: ";
    if (isBadInputFile[0] && isBadInputFile[1]) {
        fout << "Bad Positioning input file for both players - player 1: line ";
        fout << ErrorLine[0] << ", player 2: line " << ErrorLine[1] << endl;
    } else if (isBadInputFile[0]) {
        fout << "Bad Positioning input file for player 1 - line " << ErrorLine[0] << endl;
    } else if (isBadInputFile[1]) {
        fout << "Bad Positioning input file for player 2 - line " << ErrorLine[1] << endl;
    } else {
        fout << endOfGameHandler.toString() << endl;
    }
		// empty line
		fout << endl;
    for (int i = 0; i < rps.Nrows; i++) {
        for (int j = 0; j < rps.Mcols; j++) {
            if (rps.board[i][j][0] != nullptr && rps.board[i][j][1] != nullptr) {
                fout << "ERROR: two pieces in the same cell: (" << i << ", " << j << ") should be fight" << endl;
                break;
            } else if (rps.board[i][j][0] != nullptr) {
                fout << rps.board[i][j][0]->toString();
            } else if (rps.board[i][j][1] != nullptr) {
                fout << rps.board[i][j][1]->toString();
            } else {
                fout << " ";
            }
        }
        fout << endl;
    }
    fout.close();
}

RPS::~RPS() {
	for (int row = 0; row < this->Nrows; row++) {
		for (int col = 0; col < this->Mcols; col++) {
			for (int playerIndex = 0; playerIndex < this->numOfPlayers; playerIndex++) {
				if (this->board[row][col][playerIndex] != nullptr) {
					delete this->board[row][col][playerIndex];
				}
			}
		}
	}
}
