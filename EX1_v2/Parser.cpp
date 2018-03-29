#include "Parser.h"

//string Parser::player_0_name_ = "C:\/Users\/sasha\/Desktop\/Advanced_Topics_in_Programming\/Advanced-Topics-in-Programming\/EX1_v2\/player1.rps_board";
//string Parser::player_1_name_ = "C:\/Users\/sasha\/Desktop\/Advanced_Topics_in_Programming\/Advanced-Topics-in-Programming\/EX1_v2\/player2.rps_board";
string Parser::player_0_name_ = "/Users/guy/school/Advanced-Topics-in-Programming/EX1_v2/player1.rps_board";
string Parser::player_1_name_ = "/Users/guy/school/Advanced-Topics-in-Programming/EX1_v2/player2.rps_board";
//string Parser::player_0_name_ = "player1.rps_board";
//string Parser::player_1_name_ = "player2.rps_board";

void Parser::initializePiecesArsenal(RPS& rps) {
    rps.playerPiecesArsenal[PieceFactory::Rock] = RPS::R;
    rps.playerPiecesArsenal[PieceFactory::Paper] = RPS::P;
    rps.playerPiecesArsenal[PieceFactory::Scissors] = RPS::S;
    rps.playerPiecesArsenal[PieceFactory::Bomb] = RPS::B;
    rps.playerPiecesArsenal[PieceFactory::Joker] = RPS::J;
    rps.playerPiecesArsenal[PieceFactory::Flag] = RPS::F;
    rps.playerPiecesArsenal[PieceFactory::Undefined] = 0;
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
            return false;
        }
        check = setPiece(rps, playerIndex, line_words);
        if (!check) {
            // TODO: raise relevant error
            return false;
        }

    }

    if (rps.playerPiecesArsenal[PieceFactory::Flag] > 0) {
        // TODO: flag not placed error other player wins
        return false;
    }
    // TODO: check if need to close ss
    fin.close();
    return true;
}
