#include "Parser.h"

string Parser::player_0_name_ = "player1.rps_board";
string Parser::player_1_name_ = "player2.rps_board";

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
            cout << "not an integer" << endl;
            return false;
        }
    }
    return true;
}



//bool Parser::setPiece(RPS& rps, int playerIndex, vector<string> pieceDescription, vector<unique_ptr<PiecePosition>> &vectorToFill) {
//    if (pieceDescription[0].size() != 1) {
//        cout << "incorrect piece type" << endl;
//        return false;
//    }
//    char piece = pieceDescription[0][0];
//    int col, row;
//    if (isInteger(pieceDescription[1])){
//        col = stoi(pieceDescription[1]) - 1;
//    } else {
//        cout << "incorrect line format" << endl;
//        return false;
//    }
//    if (isInteger(pieceDescription[2])){
//        row = stoi(pieceDescription[2]) - 1;
//    } else {
//        cout << "incorrect line format" << endl;
//        return false;
//    }
//
//    if (0 > row || row >= rps.Nrows || 0 > col || col >= rps.Mcols) {
//        cout << "ERROR: piece set outside the board: row: " << row << ", col: "<< col <<endl;
//        return false;
//    } else if (rps.board[row][col][playerIndex] != nullptr) {
//        cout << "ERROR: two pieces of the same player in one cell: row: " << row << ", col: "<< col <<endl;
//        return false;
//    }
//    Piece::RPSPiecesTypes pieceType = PieceFactory::charToPieceType(piece);
//    MyPoint p(col, row);
//    if (rps.playerPiecesArsenal[pieceType] == 0) {
//        cout << "ERROR: too many pieces of the same type, type enum:" << pieceType << endl;
//        return false;
//    }
//    rps.playerPiecesArsenal[pieceType]--;
//    if (pieceType == Piece::Joker) {
//        if (pieceDescription.size() != 4) {
//            cout << "ERROR: too much arguments" << endl;
//            return false;
//        }
//        char jokerPiece = pieceDescription[3][0];
//        Piece::RPSPiecesTypes jokerPieceType = PieceFactory::charToPieceType(jokerPiece);
//        if (jokerPieceType == Piece::Joker || jokerPieceType == Piece::Flag || jokerPieceType == Piece::Undefined) {
//            cout << "ERROR: joker piece type is wrong" << endl;
//            return false;
//        }
//        MyPiecePosition piecePosition(pieceType, p, Piece::fromTypeRepToJRep(jokerPieceType));
//        unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(piecePosition);
//        vectorToFill.push_back(std::move(ptr));
//        rps.board[row][col][playerIndex] = PieceFactory::createPiece(pieceType, playerIndex, jokerPieceType);
//    } else {
//        if (pieceDescription.size() != 3) {
//            cout << "ERROR: too much arguments" << endl;
//            return false;
//        }
//        MyPiecePosition piecePosition(pieceType, p);
//        unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(piecePosition);
//        vectorToFill.push_back(std::move(ptr));
//        rps.board[row][col][playerIndex] = PieceFactory::createPiece(pieceType, playerIndex);
//    }
//    return true;
//}

bool Parser::setPiece(RPS& rps, int playerIndex, vector<string> pieceDescription, vector<unique_ptr<PiecePosition>> &vectorToFill) {
    if (pieceDescription[0].size() != 1) {
        cout << "incorrect piece type" << endl;
        return false;
    }
    char piece = pieceDescription[0][0];
    int col, row;
    if (isInteger(pieceDescription[1])){
        col = stoi(pieceDescription[1]) - 1;
    } else {
        cout << "incorrect line format" << endl;
        return false;
    }
    if (isInteger(pieceDescription[2])){
        row = stoi(pieceDescription[2]) - 1;
    } else {
        cout << "incorrect line format" << endl;
        return false;
    }

    if (0 > row || row >= rps.Nrows || 0 > col || col >= rps.Mcols) {
        cout << "ERROR: piece set outside the board: row: " << row << ", col: "<< col <<endl;
        return false;
    } else if (rps.game[row][col] && rps.game[row][col]->getPlayerNumber() == playerIndex) {
        cout << "ERROR: two pieces of the same player in one cell: row: " << row << ", col: "<< col <<endl;
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
    } else {
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


void Parser::clearLine(vector<string> &line_words, string &cur_line) {
	string word;
	istringstream ss(cur_line);
	line_words.clear();
	while (ss >> word) {
		line_words.push_back(word);
	}
}

void Parser::handleParseError(ifstream& fin, EndOfGameHandler& endOfGameHandler, int playerIndex, int fileLine) {
	fin.close();
	endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadInputFile);
	endOfGameHandler.setWinner(playerIndex, fileLine, fileLine);
}

void Parser::printVector(vector<unique_ptr<PiecePosition>> &vector){
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    for(const auto &vPtr : vector){
        cout << "Piece from unique: " << vPtr->getPiece() << "    piece position: (" << vPtr->getPosition().getX() << ", " << vPtr->getPosition().getY() << ")" << endl;
    }
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
}

void Parser::parseBoard(RPS& rps, int playerIndex, EndOfGameHandler& endOfGameHandler) {
    string cur_line, word;
    int fileLine = 1;
    bool check = true;
    ifstream fin;
    vector<string> line_words;
    initializePiecesArsenal(rps);
    vector<unique_ptr<PiecePosition>> vectorToFill;
    unique_ptr<Piece> piecePtr;

    if (playerIndex == 0) {
        fin.open(player_0_name_);
    } else if (playerIndex == 1) {
        fin.open(player_1_name_);
    }

    if (!fin.is_open()) {
        cout << "ERROR: file didn't opened for player " << playerIndex + 1 << endl;
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::CantOpenInputFile);
        return;
    }

    while (!fin.eof()) {
				try {
					getline(fin, cur_line);
				} catch (std::ifstream::failure e){
					cout << "ERROR: could not read the next line from the file" << endl;
					handleParseError(fin, endOfGameHandler, playerIndex, fileLine);
					return;
				}
        
				clearLine(line_words, cur_line);
        if (line_words.size() < 3 && line_words.size() != 0) {
            cout << "ERROR: not enogh arguments " << line_words.size() << endl;
						handleParseError(fin, endOfGameHandler, playerIndex, fileLine);
            return;
        }
        if (line_words.size() != 0) {
            check = setPiece(rps, playerIndex, line_words, vectorToFill);
        }
        if (!check) {
            cout << "ERROR: could not set piece" << endl;
			handleParseError(fin, endOfGameHandler, playerIndex, fileLine);
            return;
        }
        fileLine++;
    }

     for (unsigned int i=0; i< vectorToFill.size(); i++) {
         piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(vectorToFill[i]->getPiece()), playerIndex, Piece::getEnumTypeRep(vectorToFill[i]->getJokerRep()));
         cout << "%%%%%%%%%%%%%%%%%%%%  (" << vectorToFill[i]->getPosition().getX()<< ", " << vectorToFill[i]->getPosition().getY()<< ")" << endl;
         if (rps.game[vectorToFill[i]->getPosition().getY()][vectorToFill[i]->getPosition().getX()].get() != nullptr) {
             RPS::fight(rps, vectorToFill[i]->getPosition().getY(),vectorToFill[i]->getPosition().getX(), piecePtr);
         } else {
             rps.game[vectorToFill[i]->getPosition().getY()][vectorToFill[i]->getPosition().getX()] = move(piecePtr);
         }
         piecePtr.release();
//         cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~: " << (rps.game[vectorToFill[i]->getPosition().getY()][vectorToFill[i]->getPosition().getX()])->toString() << endl;
     }

    if (rps.playerPiecesArsenal[Piece::Flag] > 0) {
        cout << "ERROR: Not all Flags placed" << endl;
				handleParseError(fin, endOfGameHandler, playerIndex, fileLine);
        return;
    }

//    for (int i = 0; i < rps.Mcols; i++) {
//        for (int j = 0; j < rps.Nrows; j++) {
//            if (rps.board[i][j][0] != nullptr && rps.board[i][j][1]!= nullptr) {
//                RPS::fight(rps, i, j);
//            }
//        }
//    }
    RPS::checkWinner(rps, endOfGameHandler, 0);
    Parser::printVector(vectorToFill);
    fin.close();
}
