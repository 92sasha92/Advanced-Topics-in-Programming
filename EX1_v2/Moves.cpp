#include "Moves.h"

Moves::Move::Move(int fRow_, int fCol_, int toRow_, int toCol_, int player_): fRow(fRow_), fCol(fCol_), toRow(toRow_), toCol(toCol_), player(player_) {
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

    Piece *piece = rps.board[move.fRow][move.fCol][move.player];
    if (piece == nullptr) {
        cout << "ERROR: no piece in the given position";
        return false;
    }
    if (!(piece->getCanMove())) {
        cout << "ERROR " << piece->toString() << " can't move" << endl;
        return false;
    }
    if (rps.board[move.toRow][move.toCol][move.player] != nullptr) {
        cout << "ERROR: the cell already occupied by other piece of the same player";
        return false;
    }

    rps.board[move.toRow][move.toCol][move.player] = rps.board[move.fRow][move.fCol][move.player];
    rps.board[move.fRow][move.fCol][move.player] = nullptr;
    if (rps.board[move.toRow][move.toCol][!move.player] != nullptr) {
        RPS::fight(rps, move.toRow, move.toCol);
    }

    return true;
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
		cout << arr[1] << " " << arr[0] << " " << arr[3] << " " << arr[2] << " " << playerIndex<< endl;
    return new Move(arr[1], arr[0], arr[3], arr[2], playerIndex);
}

void Moves::exitMoves(ifstream &fin1, ifstream &fin2, EndOfGameHandler& endOfGameHandler, EndOfGameHandler::EndOfGameReason reason) {
	fin1.close();
	fin2.close();
	endOfGameHandler.setEndOfGameReason(reason);
}

void Moves::clearLine(vector<string> &line_words, string &cur_line){
	string word;
	istringstream ss(cur_line);
	line_words.clear();
	while (getline(ss, word, ' ')) {
		if (word.compare("") != 0) {
			line_words.push_back(word);
		}
	}
}
void Moves::updateLine(int currentTurn, ifstream fins[2], string playerNextLines[2], string &cur_line)
{
	if (!playerNextLines[currentTurn].empty()) {
		cur_line = playerNextLines[currentTurn];
	}
	else {
		getline(fins[currentTurn], cur_line);
	}
	if (!fins[currentTurn].eof()) {
		getline(fins[currentTurn], playerNextLines[currentTurn]);
	}
}
bool Moves::isNumOfArgsCorrect(int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler)
{
	if (line_words.size() != 4) {
		cout << "ERROR: num of arguments is incorrect" << line_words.size() << endl;
		exitMoves(fins[0], fins[1], endOfGameHandler, EndOfGameHandler::BadMoveFile);
		endOfGameHandler.setWinner(currentTurn, fileLinePlayer[0], fileLinePlayer[1]);
		return false;
	}
	return true;
}
bool Moves::checkJokerChangeAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, string playerNextLines[2])
{
	bool check;
	if ((((!(playerNextLines[0].empty()) && !currentTurn) || ((!(playerNextLines[1].empty()) && currentTurn))) && (RPS::checkWinner(rps, endOfGameHandler)).getGameState() == EndOfGameHandler::GameNotOver)) {
		clearLine(line_words, playerNextLines[currentTurn]);
		if (!isNumOfArgsCorrect(currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler)) {
			return false;
		}
		if (!(line_words[0].compare("J:"))) {
			check = setNewJokerPiece(rps, line_words, currentTurn);
			if (!check) {
				cout << "ERROR: Move change Joker type fail" << endl;
				exitMoves(fins[0], fins[1], endOfGameHandler, EndOfGameHandler::BadMoveFile);
				endOfGameHandler.setWinner(currentTurn, fileLinePlayer[0], fileLinePlayer[1]);
				return false;
			}
			playerNextLines[currentTurn] = "";
			fileLinePlayer[currentTurn]++;
		}
	}
	return true;
}
bool Moves::checkMoveAndSet(RPS &rps, int currentTurn, vector<string>& line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler &endOfGameHandler, string playerNextLines[2])
{
	bool check;
	Move *move;
	if (!isNumOfArgsCorrect(currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler)) {
		return false;
	}
	move = parseMove(rps, currentTurn, line_words);
	if (move != nullptr) {
		check = movePiece(rps, *move);
		free(move);
		if (!check) {
			cout << "ERROR: in making move";
			exitMoves(fins[0], fins[1], endOfGameHandler, EndOfGameHandler::BadMoveFile);
			endOfGameHandler.setWinner(currentTurn, fileLinePlayer[0], fileLinePlayer[1]);
			return false;
		}
	}
	else {
		exitMoves(fins[0], fins[1], endOfGameHandler, EndOfGameHandler::BadMoveFile);
		endOfGameHandler.setWinner(currentTurn, fileLinePlayer[0], fileLinePlayer[1]);
		return false;
	}
	fileLinePlayer[currentTurn]++;
	return true;
}
void Moves::parseMoves(RPS& rps, EndOfGameHandler& endOfGameHandler) {
    int currentTurn = 0, fileLinePlayer[2] = {0, 0};
    string cur_line;
    ifstream fins[2];
    vector<string> line_words;
		string playerNextLines[2] = { "", "" };
		fins[0].open(player1Moves);
		fins[1].open(player2Moves);
    if (!fins[0].is_open() || !fins[1].is_open()) {
        cout << "ERROR: file didn't opened";
        exitMoves(fins[0], fins[1], endOfGameHandler, EndOfGameHandler::BadMoveFile);
        return;
    }
//	bool isOneFileLeft = false;
    while ((((!fins[0].eof() || !playerNextLines[0].empty()) && !currentTurn) || ((!fins[1].eof() || !playerNextLines[1].empty()) && currentTurn)) && ((RPS::checkWinner(rps, endOfGameHandler)).getGameState() == EndOfGameHandler::GameNotOver)) {
		    updateLine(currentTurn, fins, playerNextLines, cur_line);
        clearLine(line_words, cur_line);
        if (!checkMoveAndSet(rps, currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler, playerNextLines)) {
            return;
        }
        if (!checkJokerChangeAndSet(rps, currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler, playerNextLines)) {
            return;
        }
        cout << endl << "#######################################" << endl;
        RPS::printBoard(rps);
				//if (!isOneFileLeft) {
					currentTurn = !currentTurn;
				//}
				//if (fins[0].eof() || fins[1].eof()) {
				//	isOneFileLeft = true;
				//}
    }
		fins[0].close();
		fins[1].close();
		RPS::checkWinner(rps, endOfGameHandler);
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

		Piece *piece = rps.board[row][col][player];
		if (piece == nullptr) {
			cout << "ERROR: no joker in the given position";
			return false;
		}

    if (piece->type != Piece::Joker) {
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
        ((JokerPiece *)piece)->setJokerPiece(jokerPiece);
    } else {
        ((JokerPiece *)piece)->setJokerPiece(Piece::Undefined);
        std::cout << "ERROR: unsupported joker type" << std::endl;
        return false;
    }
    return true;
}
