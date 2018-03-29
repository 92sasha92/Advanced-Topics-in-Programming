#include "Parser.h"

string Parser::player_0_name_ = "C:\/Users\/sasha\/Desktop\/Advanced_Topics_in_Programming\/Advanced-Topics-in-Programming\/EX1_v2\/player1.rps_board";
string Parser::player_1_name_ = "C:\/Users\/sasha\/Desktop\/Advanced_Topics_in_Programming\/Advanced-Topics-in-Programming\/EX1_v2\/player2.rps_board";
//string Parser::player_0_name_ = "/Users/guy/school/Advanced-Topics-in-Programming/EX1_v2/player1.rps_board";
//string Parser::player_1_name_ = "/Users/guy/school/Advanced-Topics-in-Programming/EX1_v2/player2.rps_board";
//string Parser::player_0_name_ = "player1.rps_board";
//string Parser::player_1_name_ = "player2.rps_board";

void Parser::initializePiecesArsenal(RPS& rps) {
    rps.playerPiecesArsenal[Piece::Rock] = RPS::R;
    rps.playerPiecesArsenal[Piece::Paper] = RPS::P;
    rps.playerPiecesArsenal[Piece::Scissors] = RPS::S;
    rps.playerPiecesArsenal[Piece::Bomb] = RPS::B;
    rps.playerPiecesArsenal[Piece::Joker] = RPS::J;
    rps.playerPiecesArsenal[Piece::Flag] = RPS::F;
    rps.playerPiecesArsenal[Piece::Undefined] = 0;
}

bool Parser::isInteger(string str) {
    for (char c : str) {
        if (c > '9' || c < '0') {
            return false;
        }
    }
    return true;
}

bool Parser::setPiece(RPS& rps, int playerIndex, vector<string> pieceDescription) {
    if (pieceDescription[0].size() != 1) {
        // TODO: incorrect piece type
        cout << "incorrect piece type" << endl;
        return false;
    }
    char piece = pieceDescription[0][0];
    int col, row;
    if (isInteger(pieceDescription[1])){
        col = stoi(pieceDescription[1]) - 1;
    } else {
        // TODO: incorrect line format
        cout << "incorrect line format" << endl;
        return false;
    }
    if (isInteger(pieceDescription[2])){
        row = stoi(pieceDescription[2]) - 1;
    } else {
        // TODO: incorrect line format
        cout << "incorrect line format" << endl;
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
    Piece::RPSPiecesTypes pieceType = PieceFactory::charToPieceType(piece);
    if (rps.playerPiecesArsenal[pieceType] == 0) {
        // TODO: error other player wins not enough pieces of the type
        cout << "ERROR: too many pieces of the same type, type enum:" << pieceType << endl;
        return false;
    }
    rps.playerPiecesArsenal[pieceType]--;
    if (pieceType == Piece::Joker) {
        if (pieceDescription.size() != 4) {
            cout << "ERROR: too much arguments" << endl;
            // TODO: error, too much arguments in line
            return false;
        }
        char jokerPiece = pieceDescription[3][0];
        Piece::RPSPiecesTypes jokerPieceType = PieceFactory::charToPieceType(jokerPiece);
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

bool Parser::parseBoard(RPS& rps, int playerIndex) {
    string cur_line, word;
    bool check;
    ifstream fin;
    vector<string> line_words;
    initializePiecesArsenal(rps);

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
						fin.close();
            return false;
        }
        check = setPiece(rps, playerIndex, line_words);
        if (!check) {
            // TODO: raise relevant error
					 fin.close();
            return false;
        }

    }

    if (rps.playerPiecesArsenal[Piece::Flag] > 0) {
        // TODO: flag not placed error other player wins
			 fin.close();
        return false;
    }
    // TODO: check if need to close ss
    fin.close();
    return true;
}
