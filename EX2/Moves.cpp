#include "Moves.h"


string Moves::player1Moves = "player1.rps_moves";
string Moves::player2Moves = "player2.rps_moves";

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

void Moves::parseMove(int playerIndex, vector<string> pieceDescription, MyMove &move) {
	int arr[4];
	for (int i = 0; i < 4; i++) {
		if (Parser::isInteger(pieceDescription[i])) {
			arr[i] = stoi(pieceDescription[i]) - 1;
		} else {
			cout << "incorrect line format" << endl;
			return;
		}
	}
	// arr[1] = fRow, arr[0] = fCol, arr[3] = toRow, arr[2] = toCol
	cout << arr[1] << " " << arr[0] << " " << arr[3] << " " << arr[2] << " player:" << playerIndex + 1 << endl;
	MyPoint p1(arr[0], arr[1]), p2(arr[2], arr[3]);
	move.init(p1, p2);
}

bool Moves::movePiece(RPS & rps, MyMove& move, bool &isJokerDied, int currentPlayer) {
	bool isJoker = false;
	unique_ptr<Piece> piecePtr;
	const Point *fPoint = &(move.getFrom());
	const Point *toPoint = &(move.getTo());
	int player = currentPlayer;
	if (fPoint->getY() < 0 || fPoint->getX() < 0 || toPoint->getX() < 0 || toPoint->getY() < 0) {
		cout << "ERROR: move index is out of bound" << endl;
		return false;
	} else if (fPoint->getY() >= rps.getNumberOfRows() || fPoint->getX() >= rps.getNumberOfColumns() || toPoint->getX() >= rps.getNumberOfColumns() || toPoint->getY() >= rps.getNumberOfRows()) {
		cout << "ERROR: move index is out of bound" << endl;
		return false;
	}

	if (rps.game[fPoint->getY()][fPoint->getX()].get() == nullptr) {
		cout << "ERROR: no piece in the given position" << endl;
		return false;
	}
	if (rps.game[fPoint->getY()][fPoint->getX()]->type == Piece::Joker) {
		isJoker = true;
	}
	if (!(rps.game[fPoint->getY()][fPoint->getX()]->getCanMove())) {
		cout << "ERROR " << rps.game[fPoint->getY()][fPoint->getX()]->toString() << " can't move" << endl;
		return false;
	}
	if ((fPoint->getY() + 1 != toPoint->getY() && fPoint->getY() - 1 != toPoint->getY() && fPoint->getX() + 1 != toPoint->getX() && fPoint->getX() - 1 != toPoint->getX()) || (fPoint->getY() != toPoint->getY() && fPoint->getX() != toPoint->getX())) {
		cout << "ERROR: illegal move, can't move from: (" << fPoint->getX() + 1 << ", " << fPoint->getY() + 1 << ") to: (" << toPoint->getX() + 1 << ", " << toPoint->getY() + 1 << ")" << endl;
		return false;
	}
	if (rps.game[toPoint->getY()][toPoint->getX()].get() != nullptr && rps.game[toPoint->getY()][toPoint->getX()]->getPlayerNumber() == player) {
		cout << "ERROR: the cell already occupied by other piece of the same player" << endl;
		return false;
	}

	if (rps.game[toPoint->getY()][toPoint->getX()].get() != nullptr) {

		if (rps.game[fPoint->getY()][fPoint->getX()]->type == Piece::Joker) {
			piecePtr = PieceFactory::createPiece(rps.game[fPoint->getY()][fPoint->getX()]->type, player, ((JokerPiece *)rps.game[fPoint->getY()][fPoint->getX()].get())->getJokerPiece() );
		} else {
			piecePtr = PieceFactory::createPiece(rps.game[fPoint->getY()][fPoint->getX()]->type, player);
		}
		RPS::fight(rps, toPoint->getY(), toPoint->getX(), piecePtr);
		rps.game[fPoint->getY()][fPoint->getX()].release();
	} else {
		rps.game[toPoint->getY()][toPoint->getX()] = std::move(rps.game[fPoint->getY()][fPoint->getX()]);
		rps.game[fPoint->getY()][fPoint->getX()].release();
	}
	if (isJoker && rps.game[toPoint->getY()][toPoint->getX()]) {
		isJokerDied = true;
	}
	return true;
}

bool Moves::checkMoveAndSet(RPS &rps, int currentTurn, vector<string>& line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler &endOfGameHandler, bool &isJokerDied) {
	bool check;
	MyMove move;
	unique_ptr<Piece> curPiece;
	if (!isNumOfArgsCorrect(currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler)) {
		return false;
	}
	parseMove(currentTurn, line_words, move);
	cout << "(" << move.getFrom().getX() << ", "<< move.getFrom().getY() << ")" << endl;
	if (move.getIsInitialized()) {
		check = movePiece(rps, move, isJokerDied, currentTurn);
		cout << "(" << move.getFrom().getX() << ", "<< move.getFrom().getY() << ")" << endl;
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

	if (rps.game[move.getTo().getY()][move.getTo().getX()].get() != nullptr) {
		isJokerDied = true;
	}
	return true;
}

void Moves::parseJokerSuitChange(vector<string> pieceDescription, MyJokerChange &jokerChange) {
	int col, row;
	char type;
	if (pieceDescription[4].compare("J:")) {
		return ;
	}

	if (Parser::isInteger(pieceDescription[5])) {
		col = stoi(pieceDescription[5]) - 1;
	} else {
		return ;
	}

	if (Parser::isInteger(pieceDescription[6])) {
		row = stoi(pieceDescription[6]) - 1;
	} else {
		return ;
	}

	if (pieceDescription[7].size() != 1) {
		return ;
	}
	type = pieceDescription[7][0];

	MyPoint p(col, row);
	jokerChange.init(p, Piece::fromTypeRepToJRep(Piece::getEnumTypeRep(type)));
}

bool Moves::setNewJokerSuit(RPS& rps, MyJokerChange &jokerChange, int player){
	if (jokerChange.getJokerChangePosition().getY() < 0 || jokerChange.getJokerChangePosition().getX() < 0 || jokerChange.getJokerChangePosition().getY() >= rps.getNumberOfRows() || jokerChange.getJokerChangePosition().getX() >= rps.getNumberOfColumns()) {
		cout << "ERROR: Joker suit change index is out of bound" << endl;
		return false;
	}

	if (rps.game[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()]->getPlayerNumber() != player) {
		cout << "ERROR: not current player piece" << endl;
		return false;
	}

	if (rps.game[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()].get() == nullptr) {
		cout << "ERROR: no joker in the given position" << endl;
		return false;
	}

	if (rps.game[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()]->type != Piece::Joker) {
		cout << "ERROR: Piece in the current cell (" << jokerChange.getJokerChangePosition().getY() << ", " << jokerChange.getJokerChangePosition().getX() << ") is not a Joker type" << endl;
		return false;
	}

	Piece::RPSPiecesTypes jokerPiece = PieceFactory::charToPieceType(jokerChange.getJokerNewRep());

	if (jokerPiece != Piece::Joker && jokerPiece != Piece::Flag && jokerPiece != Piece::Undefined) {
		((JokerPiece *)rps.game[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()].get())->setJokerPiece(jokerPiece);
	}
	else {
		((JokerPiece *)rps.game[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()].get())->setJokerPiece(Piece::Undefined);
		cout << "ERROR: unsupported joker type" << endl;
		return false;
	}
	return true;
}

bool Moves::checkJokerChangeAndSet(RPS& rps, int currentTurn, vector<string> &line_words, ifstream fins[2], int fileLinePlayer[2], EndOfGameHandler& endOfGameHandler, bool &isJokerDied)
{
	bool check;
	if (((RPS::checkWinner(rps, endOfGameHandler, !currentTurn)).getGameState() == EndOfGameHandler::GameNotOver)) {
		if (!isNumOfArgsCorrect(currentTurn, line_words, fins, fileLinePlayer, endOfGameHandler)) {
			return false;
		}
		MyJokerChange suitChange;
		parseJokerSuitChange(line_words, suitChange);
		if (!suitChange.getIsInitialized()) {
			cout << "ERROR: incorrect line format" << endl;
			movesHandleError(fins, endOfGameHandler, EndOfGameHandler::BadMoveFile, fileLinePlayer, currentTurn);
			return false;
		}
		else {
			if (isJokerDied == true && !line_words[2].compare(line_words[5]) && !line_words[3].compare(line_words[6])) {
				return true;
			}
			check = setNewJokerSuit(rps, suitChange, currentTurn);
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
	while (((!fins[0].eof() && !currentTurn) || (!fins[1].eof() && currentTurn)) && ((RPS::checkWinner(rps, endOfGameHandler, currentTurn)).getGameState() == EndOfGameHandler::GameNotOver)) {
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
		} else {
			if (fins[currentTurn].eof()) {
				isOneFileLeft = true;
				currentTurn = !currentTurn;
			}
		}
	}
	fins[0].close();
	fins[1].close();
	RPS::checkWinner(rps, endOfGameHandler, currentTurn);
}