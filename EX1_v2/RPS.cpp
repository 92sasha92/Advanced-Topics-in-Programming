#include "RPS.h"

<<<<<<< HEAD
string RPS::player_0_name_ = "player1.rps_board";
string RPS::player_1_name_ = "player2.rps_board";
=======
string RPS::player_0_name_ = "C:\/Users\/sasha\/Desktop\/Advanced_Topics_in_Programming\/Advanced-Topics-in-Programming\/EX1_v2\/player1.rps_board";
string RPS::player_1_name_ = "C:\/Users\/sasha\/Desktop\/Advanced_Topics_in_Programming\/Advanced-Topics-in-Programming\/EX1_v2\/player2.rps_board";
//string RPS::player_0_name_ = "./player1.rps_board";
//string RPS::player_1_name_ = "./player1.rps_board";
>>>>>>> c0d9424ddc0a95f8b91fb536ddb0cd987b2b2261

void RPS::initializePiecesArsenal() {
    this->playerPiecesArsenal[PieceFactory::Rock] = R;
    this->playerPiecesArsenal[PieceFactory::Paper] = P;
    this->playerPiecesArsenal[PieceFactory::Scissors] = S;
    this->playerPiecesArsenal[PieceFactory::Bomb] = B;
    this->playerPiecesArsenal[PieceFactory::Joker] = J;
    this->playerPiecesArsenal[PieceFactory::Flag] = F;
    this->playerPiecesArsenal[PieceFactory::Undefined] = 0;
}

bool RPS::isInteger(string str) {
    for (char c : str) {
        if (c > '9' || c < '0') {
            return false;
        }
    }
    return true;
}

bool RPS::SetPiece(RPS& rps, int playerIndex, vector<string> pieceDescription) {
    char piece = pieceDescription[0][0];
    int col, row;
    if (isInteger(pieceDescription[1])){
        col = stoi(pieceDescription[1]) - 1;
    } else {
        // TODO: uncorrect line format
        cout << "uncorrect line format" << endl;
        return false;
    }
    if (isInteger(pieceDescription[2])){
        row = stoi(pieceDescription[2]) - 1;
    } else {
        // TODO: uncorrect line format
        cout << "uncorrect line format" << endl;
        return false;
    }

    if (0 > row || row >= rps.Nrows || 0 > col || col >= rps.Mcols) {
        // TODO: the other player win the game
        cout << "ERROR: piece set outside the board: row: " << row << ", col: "<< col <<endl;
        return false;
    } else if (rps.board[row][col][playerIndex] != nullptr) {
        // TODO: the other player win the game, too many pieces in one cell
        cout << "ERROR: two pieces of the same player in one cell: row: " << row << ", col: "<< col <<endl;
        return false;
    }
    PieceFactory::RPSPiecesTypes pieceType = PieceFactory::charToPieceType(piece);
    if (rps.playerPiecesArsenal[pieceType] == 0) {
        // TODO: error other player wins not enough pieces of the type
        cout << "ERROR: too many pieces of the same type, type enum:" << pieceType << endl;
        return false;
    }
    rps.playerPiecesArsenal[pieceType]--;
    if (pieceType == PieceFactory::Joker) {
        if (pieceDescription.size() != 4) {
            cout << "ERROR: too much arguments" << endl;
            // TODO: error, too much arguments in line
            return false;
        }
        char jokerPiece = pieceDescription[3][0];
        PieceFactory::RPSPiecesTypes jokerPieceType = PieceFactory::charToPieceType(jokerPiece);
        rps.board[row][col][playerIndex] = PieceFactory::createPiece(pieceType, playerIndex, jokerPieceType);
    } else {
        if (pieceDescription.size() != 3) {
            cout << "ERROR: too much arguments" << endl;
            // TODO: error, too much arguments in line
            return false;
        }
        rps.board[row][col][playerIndex] = PieceFactory::createPiece(pieceType, playerIndex);
    }
    return true;
}

bool RPS::Parser(int playerIndex) {
    string cur_line, word;
    bool check;
    ifstream fin;
    vector<string> line_words;
    this->initializePiecesArsenal();
    if (playerIndex == 0) {
        fin.open(player_0_name_);
    }
    else if (playerIndex == 1) {
        fin.open(player_1_name_);
    } else {
        // TODO: raise relevant error (probably not needed)
        return false;
    }

		if (!fin.is_open()) {
			cout << "ERROR: file didn't opened";
			return false;
		}

    while (!fin.eof()) {
        getline(fin, cur_line);
        istringstream ss(cur_line);
        line_words.clear();
        while (getline(ss, word, ' ')) {
            if (word.compare("") != 0) {
//                cout << "word: " << word << ";" << endl;
                line_words.push_back(word);
            }
        }

        if (line_words.size() < 3) {
            // TODO: error, not enogh arguments in line
            cout << "ERROR: not enogh arguments " << line_words.size() << endl;
            return false;
        }
        check = SetPiece(*this, playerIndex, line_words);
        if (!check) {
            // TODO: raise relevant error
            return false;
        }

    }


    if (this->playerPiecesArsenal[PieceFactory::Flag] > 0) {
        // TODO: flag not placed error other player wins
        return false;
    }
    // TODO: check if need to close ss
    fin.close();
    return true;
}

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
