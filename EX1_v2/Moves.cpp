#include "Moves.h"

Moves::Move::Move(int fCol_, int fRow_, int toCol_, int toRow_, int player_): fRow(fRow_), fCol(fCol_), toRow(toRow_), toCol(toCol_), player(player_) {
}

//string Moves::player1Moves = "C:\/Users\/sasha\/Desktop\/Advanced_Topics_in_Programming\/Advanced-Topics-in-Programming\/EX1_v2\/player1.rps_moves";
//string Moves::player2Moves = "C:\/Users\/sasha\/Desktop\/Advanced_Topics_in_Programming\/Advanced-Topics-in-Programming\/EX1_v2\/player2.rps_moves";
//string Moves::player1Moves = "/Users/guy/school/Advanced-Topics-in-Programming/EX1_v2/player1.rps_moves";
//string Moves::player2Moves = "/Users/guy/school/Advanced-Topics-in-Programming/EX1_v2/player2.rps_moves";
string Moves::player1Moves = "player1.rps_moves";
string Moves::player2Moves = "player2.rps_moves";

bool Moves::movePiece(RPS & rps, Moves::Move& move)
{
    if (move.fRow < 0 || move.fCol < 0 || move.toCol < 0 || move.toRow < 0) {
        cout << "ERROR: move index is out of bound";
        return false;
    } else if (move.fRow >= rps.getNumberOfRows() || move.fCol >= rps.getNumberOfColumns() || move.toCol >= rps.getNumberOfColumns() || move.toRow >= rps.getNumberOfRows()) {
        cout << "ERROR: move index is out of bound";
        return false;
    }

    Piece *piece = rps.board[move.fCol][move.fRow][move.player];
    if (piece == nullptr) {
        cout << "ERROR: no piece in the given position";
        return false;
    }
    if (!(piece->getCanMove())) {
        cout << "ERROR " << piece->toString() << "can't move" << endl;
        return false;
    }

    rps.board[move.toCol][move.toRow][move.player] = rps.board[move.fCol][move.fRow][move.player];
    rps.board[move.fCol][move.fRow][move.player] = nullptr;
    if (rps.board[move.toCol][move.toRow][!move.player] != nullptr) {
        RPS::fight(rps, move.toRow, move.toCol);
    }

    return false;
}

Moves::Move* Moves::parseMove(RPS& rps, int playerIndex, vector<string> pieceDescription) {
    int arr[4];
    for (int i = 0; i < 4; i++) {
        if (Parser::isInteger(pieceDescription[i])) {
            arr[i] = stoi(pieceDescription[i]) - 1;
        } else {
            cout << "incorrect line format" << endl;
            return nullptr;
        }
    }
    // arr[1] = fRow, arr[0] = fCol, arr[3] = toRow, arr[2] = toCol
    return new Move(arr[1], arr[0], arr[3], arr[2], playerIndex);
}


bool Moves::parseMoves(RPS& rps)
{
    int currentTurn = 0;
    bool check;
    string cur_line, word;
    ifstream fin1, fin2;
    Move *move;
    vector<string> line_words;
    fin1.open(player1Moves);
    fin2.open(player2Moves);

    if (!fin1.is_open() || !fin2.is_open()) {
        cout << "ERROR:@ file didn't opened";
        return false;
    }
    while (((!fin1.eof() && !currentTurn) || (!fin2.eof() && currentTurn)) && (RPS::checkWineer(rps) == RPS::GameNotOver)) {
        if (currentTurn == 0) {
            getline(fin1, cur_line);
        } else {
            getline(fin2, cur_line);
        }

        istringstream ss(cur_line);
        line_words.clear();
        while (getline(ss, word, ' ')) {
            if (word.compare("") != 0) {
                line_words.push_back(word);
            }
        }
        if (line_words.size() != 4) {
            cout << "ERROR: num of arguments is incorrect" << line_words.size() << endl;
            return false;
        }
        if (!(line_words[0].compare("J:"))) {
            check = setNewJokerPiece(rps, line_words, currentTurn);
            if (!check) {
                cout << "ERROR: Move change Joker type fail" << endl;
                return false;
            }
        } else {
            move = parseMove(rps, currentTurn, line_words);
            if (move != nullptr) {
                movePiece(rps, *move);
                free(move);
            } else {
                // ERROR
                cout << "ERROR: in parsing move";
                return false;
            }
        }
        cout << endl << "#######################################" << endl;
        RPS::printBoard(rps);
        currentTurn = !currentTurn;
    }

    if (!fin1.eof()) {
        // ??????
    }
    else if (!fin2.eof()) {
        // ???????
    }
    fin1.close();
    fin2.close();
    return false;
}

bool Moves::setNewJokerPiece(RPS& rps, vector<string> pieceDescription, int player) {
    int col, row;
    if (Parser::isInteger(pieceDescription[1])) {
        col = stoi(pieceDescription[1]) - 1;
    } else {
        cout << "incorrect line format" << endl;
        return false;
    }

    if (Parser::isInteger(pieceDescription[2])) {
        row = stoi(pieceDescription[2]) - 1;
    } else {
        cout << "incorrect line format" << endl;
        return false;
    }

    if (row < 0 || col < 0 || row >= rps.getNumberOfRows() || col >= rps.getNumberOfColumns()) {
        cout << "ERROR: Joker move index is out of bound";
        return false;
    }

    if (rps.board[row][col][player]->type != Piece::Joker) {
        cout << "ERROR: Piece in the current cell (" << row << ", " << col << ") is not a Joker type";
        return false;
    }

    if (pieceDescription[3].size() != 1) {
        cout << "incorrect piece type" << endl;
        return false;
    }
    char jokerPieceChar = pieceDescription[3][0];
    Piece::RPSPiecesTypes jokerPiece = PieceFactory::charToPieceType(jokerPieceChar);

    if (jokerPiece != Piece::Joker && jokerPiece != Piece::Flag && jokerPiece!= Piece::Undefined) {
        ((JokerPiece *)rps.board[row][col][player])->setJokerPiece(jokerPiece);
    } else {
        ((JokerPiece *)rps.board[row][col][player])->setJokerPiece(Piece::Undefined);
        std::cout << "ERROR: unsupported joker type" << std::endl;
        return false;
    }
    return true;

}
