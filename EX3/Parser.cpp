#include "Parser.h"

string Parser::player_1_name = "player1.rps_board";
string Parser::player_2_name = "player2.rps_board";


bool Parser::isInteger(string str) {
    for (char c : str) {
        if (c > '9' || c < '0') {
            cout << "not an integer" << endl;
            return false;
        }
    }
    return true;
}


bool Parser::parsePiece(RPS& rps, vector<string> pieceDescription, vector<unique_ptr<PiecePosition>> &vectorToFill) {
    if (pieceDescription[0].size() != 1) {
        cout << "incorrect piece type" << endl;
        return false;
    }
    char piece = pieceDescription[0][0];
    int col, row;
    if (isInteger(pieceDescription[1])) {
        // zero based
//        col = stoi(pieceDescription[1]) - 1;
        // 1 based
        col = stoi(pieceDescription[1]);
    } else {
        cout << "incorrect line format" << endl;
        return false;
    }
    if (isInteger(pieceDescription[2])) {
        // zero based
     //   row = stoi(pieceDescription[2]) - 1;
        // 1 based
        row = stoi(pieceDescription[2]);
    } else {
        cout << "incorrect line format" << endl;
        return false;
    }

    if (1 > row || row > RPS::NRows || 1 > col || col > RPS::MCols) {
        cout << "ERROR: piece set outside the board: row: " << row << ", col: " << col << endl;
        return false;
    }
    Piece::RPSPiecesTypes pieceType = PieceFactory::charToPieceType(piece);
    MyPoint p(col, row);
    if (rps.playerPiecesArsenal[pieceType] == 0) {
        cout << "ERROR: too many pieces of the same type, type enum:" << pieceType << endl;
        return false;
    }
    rps.playerPiecesArsenal[pieceType]--;
    if (pieceType == Piece::Joker) {
        if (pieceDescription.size() != 4) {
            cout << "ERROR: too much arguments" << endl;
            return false;
        }
        char jokerPiece = pieceDescription[3][0];
        Piece::RPSPiecesTypes jokerPieceType = PieceFactory::charToPieceType(jokerPiece);
        if (jokerPieceType == Piece::Joker || jokerPieceType == Piece::Flag || jokerPieceType == Piece::Undefined) {
            cout << "ERROR: joker piece type is wrong" << endl;
            return false;
        }
        MyPiecePosition piecePosition(pieceType, p, Piece::fromTypeRepToJRep(jokerPieceType));
        unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(piecePosition);
        vectorToFill.push_back(std::move(ptr));
    } else { // handle piece that is not a joker
        if (pieceDescription.size() != 3) {
            cout << "ERROR: too much arguments" << endl;
            return false;
        }
        MyPiecePosition piecePosition(pieceType, p);
        unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(piecePosition);
        vectorToFill.push_back(std::move(ptr));
    }
    return true;
}


void Parser::split(vector<string> &line_words, string &cur_line) {
	string word;
	istringstream ss(cur_line);
	line_words.clear();
	while (ss >> word) {
		line_words.push_back(word);
	}
}

void Parser::handleParseError(ifstream& fin, EndOfGameHandler& endOfGameHandler, int playerIndex, int fileLine, vector< unique_ptr<PiecePosition> > &vectorToFill) {
    MyPoint p(-1, -1);
    MyPiecePosition piecePosition(Piece::Undefined, p);
    unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(piecePosition);
    vectorToFill.push_back(std::move(ptr));
	fin.close();
	endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadInputFile); // set the error in the EndOfGameHandler object
	endOfGameHandler.setWinner(playerIndex, fileLine, fileLine);
}

void Parser::parseBoard(RPS& rps, int player, EndOfGameHandler& endOfGameHandler, vector< unique_ptr<PiecePosition> > &vectorToFill) {
    string cur_line, word;
    int fileLine = 1;
    bool check = true;
    ifstream fin;
    vector<string> line_words;
    rps.initializePiecesArsenal();
    unique_ptr<Piece> piecePtr;

    if (player == 1) {
        fin.open(player_1_name);
    } else if (player == 2) {
        fin.open(player_2_name);
    }

    if (!fin.is_open()) {
        cout << "ERROR: file didn't opened for player " << player << endl;
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::CantOpenInputFile);
        return;
    }

    while (!fin.eof()) {
        try {
            getline(fin, cur_line);
        } catch (std::ifstream::failure &e) {
            cout << "ERROR: could not read the next line from the file" << endl;
            handleParseError(fin, endOfGameHandler, player - 1, fileLine, vectorToFill);
            return;
        }
        
        split(line_words, cur_line);
        if (line_words.size() < 3 && !line_words.empty()) {
            cout << "ERROR: not enogh arguments " << line_words.size() << endl;
            handleParseError(fin, endOfGameHandler, player - 1, fileLine, vectorToFill);
            return;
        }
        if (!line_words.empty()) {
            check = parsePiece(rps, line_words, vectorToFill);
        }
        if (!check) {
            cout << "ERROR: could not set piece" << endl;
			handleParseError(fin, endOfGameHandler, player - 1, fileLine, vectorToFill);
            return;
        }
        fileLine++;
    }

    if (rps.playerPiecesArsenal[Piece::Flag] > 0) {
        cout << "ERROR: Not all Flags placed" << endl;
				handleParseError(fin, endOfGameHandler, player - 1, fileLine, vectorToFill);
        return;
    }

    fin.close();
}
