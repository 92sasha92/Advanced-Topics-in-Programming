#include "RPS.h"


string RPS::player_0_name_ = "player1.rps_board";
string RPS::player_1_name_ = "player2.rps_board";

void RPS::initializePiecesArsenal() {
    this->playerPiecesArsenal[PieceFactory::Rock] = R;
    this->playerPiecesArsenal[PieceFactory::Paper] = P;
    this->playerPiecesArsenal[PieceFactory::Scissors] = S;
    this->playerPiecesArsenal[PieceFactory::Bomb] = B;
    this->playerPiecesArsenal[PieceFactory::Joker] = J;
    this->playerPiecesArsenal[PieceFactory::Flag] = F;
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
    PieceFactory::RPSPiecesTypes pieceType = PieceFactory::charToPieceType(piece);
    if (rps.playerPiecesArsenal[pieceType] == 0) {
        // TODO: error other player wins not enouth pieces of the type
    }
    rps.playerPiecesArsenal[pieceType]--;
    if (pieceType == PieceFactory::Joker) {
        if (pieceDescription.size() != 4) {
            // TODO: error, too much arguments in line
            return false;
        }
//        char jokerPiece = pieceDescription[3][0];
//        PieceFactory::RPSPiecesTypes jokerPieceType = PieceFactory::charToPieceType(jokerPiece);
//        rps.board[row][col][playerIndex] = PieceFactory::createPiece(pieceType, playerIndex, jokerPieceType);
    } else {
        if (pieceDescription.size() != 3) {
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
        for (int j = 0; j < this->Nrows; j++) {
            if (this->board[i][j][0] != nullptr && this->board[i][j][1] != nullptr) {
                cout << "ERROR: two pieces in the same sale" << endl;
                break;
            } else if (this->board[i][j][0] != nullptr) {
                cout << this->board[i][j][0]->toString() << " "; // TODO: implement toString function
            } else if (this->board[i][j][1] != nullptr) {
                cout << this->board[i][j][1]->toString() << " ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

