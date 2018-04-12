#include "Moves.h"

Moves::Move::Move(int fRow_, int fCol_, int toRow_, int toCol_, int player_): fRow(fRow_), fCol(fCol_), toRow(toRow_), toCol(toCol_), player(player_) {
}
Moves::JokerSuitChange::JokerSuitChange(int row_, int col_, char type_): row(row_), col(col_), type(type_) {
}

//string Moves::player1Moves = "C:\\Users\\sasha\\Desktop\\Advanced_Topics_in_Programming\\Advanced-Topics-in-Programming\\EX1_v2\\player1.rps_moves";
//string Moves::player2Moves = "C:\\Users\\sasha\\Desktop\\Advanced_Topics_in_Programming\\Advanced-Topics-in-Programming\\EX1_v2\\player2.rps_moves";
string Moves::player1Moves = "C:\\Users\\drucker16\\git\\Advanced-Topics-in-Programming\\EX1_v2\\player1.rps_moves";
string Moves::player2Moves = "C:\\Users\\drucker16\\git\\Advanced-Topics-in-Programming\\EX1_v2\\player2.rps_moves";
//string Moves::player1Moves = "player1.rps_moves";
//string Moves::player2Moves = "player2.rps_moves";

void Moves::movesHandleError(ifstream fins[2], EndOfGameHandler& endOfGameHandler, EndOfGameHandler::EndOfGameReason reason, int fileLinePlayer[2], int currentTurn) {
	fins[0].close();
	fins[1].close();
	endOfGameHandler.setEndOfGameReason(reason);
	endOfGameHandler.setWinner(currentTurn, fileLinePlayer[0], fileLinePlayer[1]);
}

void Moves::movesHandleError(ifstream fins[2], EndOfGameHandler& endOfGameHandler, EndOfGameHandler::EndOfGameReason reason) {
	fins[0].close();
	fins[1].close();
	endOfGameHandler.setEndOfGameReason(reason);
}

bool Moves::isNumOfArgsCorrect(int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler)
{
	if (line_words.size() != 4 && line_words.size() != 8) {
		cout << "ERROR: num of arguments is incorrect" << line_words.size() << endl;
		movesHandleError(fins, endOfGameHandler, EndOfGameHandler::BadMoveFile, fileLinePlayer, currentTurn);
		return false;
	}
	return true;
}

Moves::Move* Moves::parseMove(int playerIndex, vector<string> pieceDescription) {
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
	cout << arr[1] << " " << arr[0] << " " << arr[3] << " " << arr[2] << " player:" << playerIndex + 1 << endl;
	return new Move(arr[1], arr[0], arr[3], arr[2], playerIndex);
}

bool Moves::movePiece(RPS & rps, Moves::Move& move, bool &isJokerDied)
{
	  bool isJoker = false;
    if (move.fRow < 0 || move.fCol < 0 || move.toCol < 0 || move.toRow < 0) {
        cout << "ERROR: move index is out of bound" << endl;
        return false;
    } else if (move.fRow >= rps.getNumberOfRows() || move.fCol >= rps.getNumberOfColumns() || move.toCol >= rps.getNumberOfColumns() || move.toRow >= rps.getNumberOfRows()) {
        cout << "ERROR: move index is out of bound" << endl;
        return false;
    }

    Piece *piece = rps.board[move.fRow][move.fCol][move.player];
    if (piece == nullptr) {
        cout << "ERROR: no piece in the given position" << endl;
        return false;
    }
		if (piece->type == Piece::Joker) {
			 isJoker = true;
		}
    if (!(piece->getCanMove())) {
        cout << "ERROR " << piece->toString() << " can't move" << endl;
        return false;
    }
		if ((move.fRow + 1 != move.toRow && move.fRow - 1 != move.toRow && move.fCol + 1 != move.toCol && move.fCol - 1 != move.toCol) || (move.fRow != move.toRow && move.fCol != move.toCol)) {
			cout << "ERROR: illegal move, can't move from: (" << move.fCol + 1 << ", " << move.fRow + 1 << ") to: (" << move.toCol + 1 << ", " << move.toRow + 1 << ")" << endl;
			return false;
		}
    if (rps.board[move.toRow][move.toCol][move.player] != nullptr) {
        cout << "ERROR: the cell already occupied by other piece of the same player" << endl;
        return false;
    }

    rps.board[move.toRow][move.toCol][move.player] = rps.board[move.fRow][move.fCol][move.player];
    rps.board[move.fRow][move.fCol][move.player] = nullptr;
    if (rps.board[move.toRow][move.toCol][!move.player] != nullptr) {
        RPS::fight(rps, move.toRow, move.toCol);
    }
		if (isJoker && rps.board[move.toRow][move.toCol][move.player] == nullptr) {
			isJokerDied = true;
		}
    return true;
}


bool Moves::checkMoveAndSet(RPS &rps, int currentTurn, vector<string>& line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler &endOfGameHandler, bool &isJokerDied)
{
	bool check;
	Move *move;
	Piece *curPiece = nullptr;
	if (!isNumOfArgsCorrect(currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler)) {
		return false;
	}
	move = parseMove(currentTurn, line_words);
	if (move != nullptr) {
		check = movePiece(rps, *move, isJokerDied);
		curPiece = rps.board[move->toRow][move->toCol][currentTurn];
		delete move;
		if (!check) {
			cout << "ERROR: in making move" << endl;
			movesHandleError(fins, endOfGameHandler, EndOfGameHandler::BadMoveFile, fileLinePlayer, currentTurn);
			return false;
		}
	}
	else {
		movesHandleError(fins, endOfGameHandler, EndOfGameHandler::BadMoveFile, fileLinePlayer, currentTurn);
		return false;
	}
	if (curPiece == nullptr) {
		isJokerDied = true;
	}
	return true;
}



Moves::JokerSuitChange* Moves::parseJokerSuitChange(vector<string> pieceDescription) {
	int col, row;
	char type;
	if (pieceDescription[4].compare("J:")) {
		return nullptr;
	}

	if (Parser::isInteger(pieceDescription[5])) {
		col = stoi(pieceDescription[5]) - 1;
	} else {
		return nullptr;
	}

	if (Parser::isInteger(pieceDescription[6])) {
		row = stoi(pieceDescription[6]) - 1;
	} else {
		return nullptr;
	}

	if (pieceDescription[7].size() != 1) {
		return nullptr;
	}
	type = pieceDescription[7][0];

	return new JokerSuitChange(row, col, type);
}




bool Moves::setNewJokerSuit(RPS& rps, Moves::JokerSuitChange& suitChange, int player) {
	if (suitChange.row < 0 || suitChange.col < 0 || suitChange.row >= rps.getNumberOfRows() || suitChange.col >= rps.getNumberOfColumns()) {
		cout << "ERROR: Joker suit change index is out of bound" << endl;
		return false;
	}

	Piece *piece = rps.board[suitChange.row][suitChange.col][player];
	if (piece == nullptr) {
		cout << "ERROR: no joker in the given position" << endl;
		return false;
	}

	if (piece->type != Piece::Joker) {
		cout << "ERROR: Piece in the current cell (" << suitChange.row << ", " << suitChange.col << ") is not a Joker type" << endl;
		return false;
	}

	Piece::RPSPiecesTypes jokerPiece = PieceFactory::charToPieceType(suitChange.type);

	if (jokerPiece != Piece::Joker && jokerPiece != Piece::Flag && jokerPiece != Piece::Undefined) {
		((JokerPiece *)piece)->setJokerPiece(jokerPiece);
	}
	else {
		((JokerPiece *)piece)->setJokerPiece(Piece::Undefined);
		cout << "ERROR: unsupported joker type" << endl;
		return false;
	}
	return true;
}

bool Moves::checkJokerChangeAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, bool &isJokerDied)
{
	bool check;
	if (((RPS::checkWinner(rps, endOfGameHandler)).getGameState() == EndOfGameHandler::GameNotOver)) {
		if (!isNumOfArgsCorrect(currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler)) {
			return false;
		}
		JokerSuitChange *suitChange = parseJokerSuitChange(line_words);
		if (suitChange == nullptr) {
			cout << "ERROR: incorrect line format" << endl;
			movesHandleError(fins, endOfGameHandler, EndOfGameHandler::BadMoveFile, fileLinePlayer, currentTurn);
			return false;
		}
		else {
			if (isJokerDied == true && !line_words[2].compare(line_words[5]) && !line_words[3].compare(line_words[6])) {
				return true;
			}
			check = setNewJokerSuit(rps, *suitChange, currentTurn);
			delete suitChange;
			if (!check) {
				cout << "ERROR: Move change Joker type fail" << endl;
				movesHandleError(fins, endOfGameHandler, EndOfGameHandler::BadMoveFile, fileLinePlayer, currentTurn);
				return false;
			}
		}
	}
	return true;
}

void Moves::parseMoves(RPS& rps, EndOfGameHandler& endOfGameHandler) {
	int currentTurn = 0, fileLinePlayer[2] = { 1, 1 };
	string cur_line;
	ifstream fins[2];
	vector<string> line_words;
	bool isJokerDied = false;
	fins[0].open(player1Moves);
	fins[1].open(player2Moves);
	if (!fins[0].is_open() || !fins[1].is_open()) {
		cout << "ERROR: file didn't opened" << endl;
		movesHandleError(fins, endOfGameHandler, EndOfGameHandler::BadMoveFile);
		return;
	}
	bool isOneFileLeft = false;
	while (((!fins[0].eof() && !currentTurn) || (!fins[1].eof() && currentTurn)) && ((RPS::checkWinner(rps, endOfGameHandler)).getGameState() == EndOfGameHandler::GameNotOver)) {
		isJokerDied = false;
		try {
			getline(fins[currentTurn], cur_line);
		} catch (std::ifstream::failure e) {
			cout << "ERROR: could not read the next line from the move file" << endl;
			movesHandleError(fins, endOfGameHandler, EndOfGameHandler::BadMoveFile, fileLinePlayer, currentTurn);
			return;
		}
		Parser::clearLine(line_words, cur_line);
		if (line_words.size() != 0) {
			if (!checkMoveAndSet(rps, currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler, isJokerDied)) {
				return;
			}
			if (line_words.size() != 4 && line_words.size() != 8) {
				return;
			}
			if (line_words.size() == 8 && !checkJokerChangeAndSet(rps, currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler, isJokerDied)) {
				return;
			}
            fileLinePlayer[currentTurn]++;
			cout << endl << "#######################################" << endl;
			RPS::printBoard(rps);
			if (!isOneFileLeft) {
				currentTurn = !currentTurn;
			}
			if (fins[!currentTurn].eof()) {
				isOneFileLeft = true;
			}
		}
	}
	fins[0].close();
	fins[1].close();
	RPS::checkWinner(rps, endOfGameHandler);
}