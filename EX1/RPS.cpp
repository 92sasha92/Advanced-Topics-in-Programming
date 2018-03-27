#include "RPS.h"


string RPS::player_0_name_ = "player1.rps_board";
string RPS::player_1_name_ = "player2.rps_board";

void RPS::initializePiecesArsenal()
{
	this->playerPiecesArsenal[RPSPiecesTypes::Rock] = R;
	this->playerPiecesArsenal[RPSPiecesTypes::Paper] = P;
	this->playerPiecesArsenal[RPSPiecesTypes::Scissors] = S;
	this->playerPiecesArsenal[RPSPiecesTypes::Bomb] = B;
	this->playerPiecesArsenal[RPSPiecesTypes::Joker] = J;
	this->playerPiecesArsenal[RPSPiecesTypes::Flag] = F;
}

bool RPS::SetPiece(RPS& rps, int playerIndex, vector<string> pieceDescription) {
    char piece = pieceDescription[0][0];
		int col = stoi(pieceDescription[1]) - 1;
		int row = stoi(pieceDescription[2]) - 1;
		if (0 > row || row >= rps.Nrows || 0 > col || col >= rps.Mcols) {
			// TODO: the other player win the game 
			return false;
		} else if (rps.board[row][col] == nullptr) {
			// TODO: the other player win the game to many pieces in one 
			return false;
		}
		RPSPiecesTypes pieceType = charToPieceType(piece);
		if (rps.playerPiecesArsenal[pieceType] == 0) {
			// TODO: error other player wins not enouth pieces of the type
		}
		rps.playerPiecesArsenal[pieceType]--;
    if (pieceType == RPSPiecesTypes::Joker) {
			if (pieceDescription.size() != 4) {
				// TODO: error, too much arguments in line
				return false;
			}
			char jokerPiece = pieceDescription[3][0];
			RPSPiecesTypes jokerPieceType = charToPieceType(jokerPiece);
			rps.board[row][col][playerIndex] = createPiece(pieceType, playerIndex, jokerPieceType);
    } else {
			if (pieceDescription.size() != 3) {
				// TODO: error, too much arguments in line
				return false;
			}
			rps.board[row][col][playerIndex] = createPiece(pieceType, playerIndex);
    }

		return true;
}

bool RPS::Parser(RPS& rps, int playerIndex) {
    string cur_line, word;
    bool check;
    ifstream fin;
    vector<string> line_words;
		rps.initializePiecesArsenal();
    if (playerIndex == 0) {
        fin.open(player_0_name_);
    } else if (playerIndex == 1) {
        fin.open(player_1_name_);
    } else {
      // TODO: raise relevant error (probably not needed)
			return false;
    }

    while (!fin.eof()) {
        getline(fin, cur_line);
        istringstream ss(cur_line);

        while (getline(ss,word,' ')) {
            line_words.push_back(word);
        }
				if (line_words.size() < 3) {
					// TODO: error, not enogh arguments in line
					return false;
				}
        check = SetPiece(rps, playerIndex, line_words);
        if (!check) {
            // TODO: raise relevant error
					return false;
        }

    }


		if (rps.playerPiecesArsenal[RPSPiecesTypes::Flag] > 0) {
			// TODO: flag not placed error other player wins
			return false;
		}
    // TODO: check if need to close ss
    fin.close();
		return true;
}

void RPS::PrintBoard(RPS& rps) {
	for (int i = 0; i < rps.Mcols; i++) {
		for (int j = 0; j < rps.Nrows; j++) {
			if (rps.board[i][j][0] != nullptr && rps.board[i][j][1] != nullptr) {
				cout << "ERROR: two pieces in the same sale" << endl;
				break;
			} else if (rps.board[i][j][0] != nullptr) {
				cout << rps.board[i][j][0].toString() << " ";
			} else if (rps.board[i][j][1] != nullptr) {
				cout << rps.board[i][j][1].toString() << " ";
			} else {
				cout << "  ";
			}
		}
		cout << endl;
	}
}

