#include "AutoAlgorithm.h"

AutoAlgorithm::AutoAlgorithm(): player(0), opponent(0), opponentNumOfFlags(RPS::F), opponentNumOfUnknownPieces(0), isOpponentAttacked(false), lastMove(), selfGameBoard(){}

void AutoAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) {
    srand (time(NULL));
    this->player = player;
    if (player == 1) {
        this->opponent = 2;
    } else {
        this->opponent = 1;
    }

    int row, col, jokerRep;
    RPS rps;
    bool cellNotOccupied;
    Piece::RPSJokerTypes jokerType1;
    Piece::RPSPiecesTypes jokerType2;
    unique_ptr<PiecePosition> piecePos;
    rps.initializePiecesArsenal();
    int numOfPieceTypes = sizeof(rps.playerPiecesArsenal)/sizeof(int);

    for (int i = 0; i < numOfPieceTypes; i++ ) {
        for (int j = 0; j < rps.playerPiecesArsenal[i]; j++ ) {
            cellNotOccupied = true;
            while (cellNotOccupied) {
                row = rand() % RPS::Nrows;
                col = rand() % RPS::Mcols;
                MyPoint p(col, row);
                if (this->selfGameBoard[row][col] == nullptr) {
                    cellNotOccupied = false;
                    if (i == Piece::Joker) {
                        jokerRep = rand() % Piece::JNotAJoker;
                        jokerType1 = static_cast<Piece::RPSJokerTypes>(jokerRep);
                        jokerType2 = static_cast<Piece::RPSPiecesTypes>(jokerRep);
                    } else {
                        jokerType1 = Piece::JNotAJoker;
                        jokerType2 = Piece::Undefined;
                    }
                    MyPiecePosition piecePosition(static_cast<Piece::RPSPiecesTypes>(i), p, jokerType1);
                    unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(piecePosition);
                    vectorToFill.push_back(std::move(ptr));

                    unique_ptr<Piece> piecePtr = PieceFactory::createPiece(static_cast<Piece::RPSPiecesTypes>(i), player, jokerType2);
                    this->selfGameBoard[row][col] = std::move(piecePtr);
                }
            }
        }
    }
}

void AutoAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) {
    vector<unique_ptr<Piece>> trash;
    MyPoint p(0,0);
    for (const unique_ptr<FightInfo> &fightInfo: fights) {
        if (fightInfo->getPiece(opponent) == Piece::Flag) {
            opponentNumOfFlags--;
        }
        if (fightInfo->getWinner() != player) {
            trash.push_back(std::move(this->selfGameBoard[fightInfo->getPosition().getY()][fightInfo->getPosition().getX()]));
            if (fightInfo->getWinner() == opponent) { // not a tie
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo->getPiece(opponent)), opponent);
                this->selfGameBoard[fightInfo->getPosition().getY()][fightInfo->getPosition().getX()] = std::move(piecePtr);
            }
        }
    }

    for (int i = 0; i < RPS::Nrows; i++) {
        for (int j = 0; j < RPS::Mcols; j++) {
            p.setX(j);
            p.setY(i);
            if (b.getPlayer(p) == opponent && this->selfGameBoard[i][j].get() == nullptr) {
                opponentNumOfUnknownPieces++;
                unique_ptr<Piece> piecePtr = std::make_unique<Piece>(opponent);
                this->selfGameBoard[i][j] = std::move(piecePtr);
            }
        }
    }
}

void AutoAlgorithm::notifyOnOpponentMove(const Move& move) {
    if (this->selfGameBoard[move.getTo().getY()][move.getTo().getY()].get() != nullptr) {
        MyPoint pFrom(move.getFrom().getY(), move.getFrom().getX()); // TODO: over ride operator= of Move class
        MyPoint pTo(move.getTo().getY(), move.getTo().getX());
        lastMove.init(pFrom, pTo);
        isOpponentAttacked = true;
        return;
    }

    this->selfGameBoard[move.getTo().getY()][move.getTo().getY()] = std::move(this->selfGameBoard[move.getFrom().getY()][move.getFrom().getY()]);
    isOpponentAttacked = false;
}

void AutoAlgorithm::notifyFightResult(const FightInfo& fightInfo) {
    vector<unique_ptr<Piece>> trash;
    Piece::RPSPiecesTypes opponentType;

    if (fightInfo.getWinner() == TIE) {
        trash.push_back(std::move(selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));
        trash.push_back(std::move(selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()]));

    } else if (isOpponentAttacked) { // player defend
        if (fightInfo.getWinner() == player) {
            trash.push_back(std::move(selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));
        } else {
            opponentType = selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()]->type;
            trash.push_back(std::move(selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()]));

            if (opponentType == Piece::Undefined) {
                opponentNumOfUnknownPieces--;
                trash.push_back(std::move(selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo.getPiece(opponent)), opponent);
                selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr);

            } else if ((opponentType != Piece::Joker) && (opponentType != Piece::getEnumTypeRep(fightInfo.getPiece(opponent)))){
                trash.push_back(std::move(selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::Joker, opponent);
                selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr);

            } else {
                selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()]);
            }
        }
    } else { // player attack
        if (fightInfo.getWinner() == opponent) {
            opponentType = selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()]->type;
            trash.push_back(std::move(selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));

            if (opponentType == Piece::Undefined) {
                opponentNumOfUnknownPieces--;
                trash.push_back(std::move(selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo.getPiece(opponent)), opponent);
                selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr);

            } else if ((opponentType != Piece::Joker) && (opponentType != Piece::getEnumTypeRep(fightInfo.getPiece(opponent)))) {
                trash.push_back(std::move(selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::Joker, opponent);
                selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr);
            }
        } else {
            if (Piece::getEnumTypeRep(fightInfo.getPiece(opponent) == Piece::Flag)) {
                opponentNumOfFlags--;
            }
            trash.push_back(std::move(selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()]));
            selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()]);
        }
    }
}

EndOfGameHandler AutoAlgorithm::checkWinner(EndOfGameHandler& endOfGameHandler, int currentPlayer) {
    bool player1HaveFlag = false, player2HaveFlag = false ,player1HaveMovingPieces = false, player2HaveMovingPieces = false;
    for (int i = 0; i < RPS::Nrows; i++) {
        for (int j = 0; j < RPS::Mcols; j++) {
            if (this->selfGameBoard[i][j].get() != nullptr){
                if (this->selfGameBoard[i][j]->getPlayerNumber() == 1) {
                    if (this->selfGameBoard[i][j]->type != Piece::Undefined) {
                        player1HaveFlag = true;
                        if (opponentNumOfFlags < opponentNumOfUnknownPieces) {
                            player1HaveMovingPieces = true;
                        }
                    } else {
                        if (this->selfGameBoard[i][j]->type == Piece::Flag) {
                            player1HaveFlag = true;
                        } else if (this->selfGameBoard[i][j]->type == Piece::Rock || this->selfGameBoard[i][j]->type == Piece::Scissors || this->selfGameBoard[i][j]->type == Piece::Paper) {
                            player1HaveMovingPieces = true;
                        } else if (this->selfGameBoard[i][j]->type == Piece::Joker && ((JokerPiece *)this->selfGameBoard[i][j].get())->getJokerPiece() != Piece::Bomb) {
                            player1HaveMovingPieces = true;
                        }
                    }
                } else {
                    if (this->selfGameBoard[i][j]->type != Piece::Undefined) {
                        player2HaveFlag = true;
                        if (opponentNumOfFlags < opponentNumOfUnknownPieces) {
                            player2HaveMovingPieces = true;
                        }
                    } else {
                        if (this->selfGameBoard[i][j]->type == Piece::Flag) {
                            player2HaveFlag = true;
                        } else if (this->selfGameBoard[i][j]->type == Piece::Rock || this->selfGameBoard[i][j]->type == Piece::Scissors || this->selfGameBoard[i][j]->type == Piece::Paper) {
                            player2HaveMovingPieces = true;
                        } else if (this->selfGameBoard[i][j]->type == Piece::Joker && ((JokerPiece *)this->selfGameBoard[i][j].get())->getJokerPiece() != Piece::Bomb) {
                            player2HaveMovingPieces = true;
                        }
                    }
                }
            }
        }
    }

    if ((!player1HaveFlag) || (!player2HaveFlag)) {
        if (player1HaveFlag) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player1Win);
        } else if (player2HaveFlag) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player2Win);
        } else {
            endOfGameHandler.setGameState(EndOfGameHandler::Tie);
        }

    } else if ((!player1HaveMovingPieces && currentPlayer == 1) || (!player2HaveMovingPieces && currentPlayer == 2)) {
        if (player1HaveMovingPieces) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player1Win);
        } else if (player2HaveMovingPieces) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player2Win);
        } else {
            endOfGameHandler.setGameState(EndOfGameHandler::Tie);
        }
    }
    return endOfGameHandler;
}

int AutoAlgorithm::scoringFunction(int player) {
    EndOfGameHandler endOfGameHandler;
    checkWinner(endOfGameHandler, player);
    MyPoint p(0,0);
    int score = 0;

    if (endOfGameHandler.getGameState() == static_cast<EndOfGameHandler::GameState>(player)) {
        return WIN_SCORE;
    } else if (endOfGameHandler.getGameState() == static_cast<EndOfGameHandler::GameState>(TIE)) {
        return TIE_SCORE;
    }  else if (endOfGameHandler.getGameState() != static_cast<EndOfGameHandler::GameState>(GAME_NOT_OVER)) { // opponent wins
        return LOSE_SCORE;
    }

    for (int i = 0; i < RPS::Nrows; i++) {
        p.setY(i);
        for (int j = 0; j < RPS::Mcols; j++) {
            p.setX(j);
            if (this->selfGameBoard[i][j]->getPlayerNumber() == player){
                score += getPieceScore(this->selfGameBoard[i][j]);
            } else if (this->selfGameBoard[i][j]->getPlayerNumber() != EMPTY_CELL){
                score -= getPieceScore(this->selfGameBoard[i][j]);
            }
        }
    }
    return score;
}

int AutoAlgorithm::getPieceScore(unique_ptr<Piece> &piece) {
    switch (piece->type) {
        case Piece::Flag:
            return FLAG_SCORE;
        case Piece::Bomb:
            return BOMB_SCORE;
        case Piece::Joker:
            return JOKER_SCORE;
        case Piece::Undefined:
            return getUnknownPieceTypeScore();
        default:
            return SIMPLE_PIECE_SCORE; // TODO: create function that calculate the simple pieces score given the opponent neighbors and their distances from it
    }
}

int AutoAlgorithm::getUnknownPieceTypeScore() { // TODO: create more sophisticated function
    return (FLAG_SCORE * opponentNumOfFlags)/opponentNumOfUnknownPieces;
}

int AutoAlgorithm::swapTurn(int curPlayer) {
    if (curPlayer == 1) {
        return 2;
    }
    return 1;
}

void AutoAlgorithm::undoMove(MyMove &lastMove, unique_ptr<MyFightInfo>& fightInfo, int curPlayer) {
    vector<unique_ptr<Piece>> trash;

    if (fightInfo.get() != nullptr) {
        trash.push_back(std::move(selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()]));
        unique_ptr<Piece> piecePtr1 = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo->getPiece(curPlayer)), curPlayer);
        selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()] = std::move(piecePtr1);
        curPlayer = swapTurn(curPlayer);
        unique_ptr<Piece> piecePtr2 = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo->getPiece(curPlayer)), curPlayer);
        selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr2);

    } else {
        selfGameBoard[lastMove.getFrom().getY()][lastMove.getFrom().getX()] = std::move(selfGameBoard[lastMove.getTo().getY()][lastMove.getTo().getX()]);
    }

}

int AutoAlgorithm::recFunc(int curPlayer, int depth) {
    EndOfGameHandler endOfGameHandler;
    checkWinner(endOfGameHandler, curPlayer);

    int bestScore = INT_MIN;
    unique_ptr<Move> bestPtrMove = nullptr;
    MyMove curMove;
    MyPoint pTo(0,0), pFrom(0,0);
    curPlayer = swapTurn(curPlayer);

    if (endOfGameHandler.getGameState() == static_cast<EndOfGameHandler::GameState>(player)) {
        return WIN_SCORE;
    } else if (endOfGameHandler.getGameState() == static_cast<EndOfGameHandler::GameState>(TIE)) {
        return TIE_SCORE;
    }  else if (endOfGameHandler.getGameState() != static_cast<EndOfGameHandler::GameState>(GAME_NOT_OVER)) { // opponent wins
        return LOSE_SCORE;
    }

    if (depth == 0) {
        return scoringFunction(curPlayer);
    }

    for (int i = 0; i < RPS::Nrows; i++) {
        pFrom.setY(i);
        pTo.setY(i);
        for (int j = 0; j < RPS::Mcols; j++) {
            if ((selfGameBoard[i][j].get() != nullptr) && (selfGameBoard[i][j]->type != Piece::Undefined)) {
                pFrom.setX(j);
                curMove.setFrom(pFrom);

                pTo.setPoint(i + 1, j);
                recFuncHandler(curMove, pFrom , pTo, curPlayer, bestScore, bestPtrMove, depth);

                pTo.setPoint(i - 1, j);
                recFuncHandler(curMove, pFrom , pTo, curPlayer, bestScore, bestPtrMove, depth);

                pTo.setPoint(i, j + 1);
                recFuncHandler(curMove, pFrom , pTo, curPlayer, bestScore, bestPtrMove, depth);

                pTo.setPoint(i, j - 1);
                recFuncHandler(curMove, pFrom , pTo, curPlayer, bestScore, bestPtrMove, depth);
            }
        }
    }
    return bestScore;
}

void AutoAlgorithm::recFuncHandler(MyMove &curMove, MyPoint &pFrom , MyPoint &pTo,  int curPlayer, int &bestScore, unique_ptr<Move> &bestPtrMove, int depth) {
    int curScore;
    unique_ptr<Move> movesTrash; // TODO: should not be a vector
    unique_ptr<MyFightInfo> fightInfoTrash; // TODO: should not be a vector
    unique_ptr<MyFightInfo> fightInfo;

    curMove.setTo(pTo);
    if (RPS::checkIfMoveIsLegal(selfGameBoard, curMove, curPlayer)) {
        fightInfoTrash = std::move(fightInfo);
//        fightInfo = makeMove(curMove, curPlayer);
        curScore = recFunc(curPlayer, depth - 1);
        if (curScore > bestScore) {
            movesTrash = std::move(bestPtrMove);
            bestScore = curScore;
            bestPtrMove = std::make_unique<MyMove>(pFrom, pTo);
        }
        undoMove(curMove, fightInfo, curPlayer);
    }
}

unique_ptr<Move> AutoAlgorithm::getMove() {
    int depth = AUTO_ALGORITHM_DEPTH, curPlayer = player;
    int bestScore = INT_MIN;
    unique_ptr<Move> bestPtrMove = nullptr;
    MyMove curMove;
    MyPoint pTo(0,0), pFrom(0,0);

    for (int i = 0; i < RPS::Nrows; i++) {
        pFrom.setY(i);
        pTo.setY(i);
        for (int j = 0; j < RPS::Mcols; j++) {
            if ((selfGameBoard[i][j].get() != nullptr) && (selfGameBoard[i][j]->type != Piece::Undefined)) {
                pFrom.setX(j);
                curMove.setFrom(pFrom);

                pTo.setPoint(i + 1, j);
                recFuncHandler(curMove, pFrom , pTo, curPlayer, bestScore, bestPtrMove, depth);

                pTo.setPoint(i - 1, j);
                recFuncHandler(curMove, pFrom , pTo, curPlayer, bestScore, bestPtrMove, depth);

                pTo.setPoint(i, j + 1);
                recFuncHandler(curMove, pFrom , pTo, curPlayer, bestScore, bestPtrMove, depth);

                pTo.setPoint(i, j - 1);
                recFuncHandler(curMove, pFrom , pTo, curPlayer, bestScore, bestPtrMove, depth);
            }
        }
    }

    pFrom.setPoint(bestPtrMove->getFrom().getY(), bestPtrMove->getFrom().getX()); // TODO: override operator= of Move class
    pTo.setPoint(bestPtrMove->getTo().getY(), bestPtrMove->getTo().getX());
    lastMove.init(pFrom, pTo);
    isOpponentAttacked = false;
    return std::move(bestPtrMove);
}

int AutoAlgorithm::getScoreForJokerRep(int row, int col, Piece::RPSJokerTypes jokerRep) {
    int score = 0;
    unique_ptr<Piece> tmpPiece = PieceFactory::createPiece(((JokerPiece *)selfGameBoard[row][col].get())->getJokerPiece(), player);

    if (row + 1 < RPS::Nrows) { // TODO: handle isStrongerThan Joker!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (maybe create new pieces like we did in fight)
        if ((selfGameBoard[row + 1][col].get() != nullptr) && (selfGameBoard[row + 1][col]->getPlayerNumber() != player) && (selfGameBoard[row + 1][col]->type != Piece::Undefined)) {
            if (Piece::PiecesPower::Stronger == tmpPiece->isStrongerThan(*(selfGameBoard[row + 1][col].get()))) {
                score++;
            } else {
                score--;
            }
        }
    }
    if (row - 1 > 0) {
        if ((selfGameBoard[row - 1][col].get() != nullptr) && (selfGameBoard[row - 1][col]->getPlayerNumber() != player) && (selfGameBoard[row - 1][col]->type != Piece::Undefined)) {
            if (Piece::PiecesPower::Stronger == tmpPiece->isStrongerThan(*(selfGameBoard[row + 1][col].get()))) {
                score++;
            } else {
                score--;
            }
        }
    }
    if (col + 1 < RPS::Mcols) {
        if ((selfGameBoard[row][col + 1].get() != nullptr) && (selfGameBoard[row][col + 1]->getPlayerNumber() != player) && (selfGameBoard[row][col + 1]->type != Piece::Undefined)) {
            if (Piece::PiecesPower::Stronger == tmpPiece->isStrongerThan(*(selfGameBoard[row + 1][col].get()))) {
                score++;
            } else {
                score--;
            }
        }
    }
    if (col - 1 > 0) {
        if ((selfGameBoard[row][col - 1].get() != nullptr) && (selfGameBoard[row][col - 1]->getPlayerNumber() != player) && (selfGameBoard[row][col - 1]->type != Piece::Undefined)) {
            if (Piece::PiecesPower::Stronger == tmpPiece->isStrongerThan(*(selfGameBoard[row + 1][col].get()))) {
                score++;
            } else {
                score--;
            }
        }
    }
    return score;
}

unique_ptr<JokerChange> AutoAlgorithm::getJokerChange() {
    unique_ptr<MyJokerChange> jokerChangePtr;
    Piece::RPSJokerTypes jokerRep;
    int curScore, bestScore = INT_MIN;
    MyPoint p(-1,-1);

    for (int i = 0; i < RPS::Nrows; i++) {
        p.setY(i);
        for (int j = 0; j < RPS::Mcols; j++) {
            if ((selfGameBoard[i][j].get() != nullptr) && (selfGameBoard[i][j]->type == Piece::Joker) && (selfGameBoard[i][j]->getPlayerNumber() == player)) {
                p.setX(j);
                jokerRep = Piece::JScissors;
                curScore = getScoreForJokerRep(i,j, jokerRep);
                if (bestScore < curScore) {
                    bestScore = curScore;
                    jokerChangePtr->init(p, jokerRep);
                }

                jokerRep = Piece::JRock;
                curScore = getScoreForJokerRep(i,j, jokerRep);
                if (bestScore < curScore) {
                    bestScore = curScore;
                    jokerChangePtr->init(p, jokerRep);
                }

                jokerRep = Piece::JPaper;
                curScore = getScoreForJokerRep(i,j, jokerRep);
                if (bestScore < curScore) {
                    bestScore = curScore;
                    jokerChangePtr->init(p, jokerRep);
                }
            }
        }
    }
    return std::move(jokerChangePtr);
}
