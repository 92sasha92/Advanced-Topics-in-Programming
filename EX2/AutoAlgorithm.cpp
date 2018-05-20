#include "AutoAlgorithm.h"

AutoAlgorithm::AutoAlgorithm(): player(0), opponent(0), opponentNumOfFlags(RPS::F), opponentNumOfUnknownPieces(0), isOpponentAttacked(false), lastMove(), selfGameBoard(){
    srand (time(NULL));
    for (int i = 0; i < RPS::NRows; i++){
        vector<unique_ptr<Piece>> line;
        for (int j = 0; j < RPS::MCols; j++) {
            unique_ptr<Piece> ptr;
            line.push_back(move(ptr));
        }
        selfGameBoard.push_back(move(line));
    }
}

void AutoAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) {
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
                row = rand() % RPS::NRows;
                col = rand() % RPS::MCols;
                MyPoint p(col, row);
                if (this->selfGameBoard[row][col].get() == nullptr) {
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

    for (int i = 0; i < RPS::NRows; i++) {
        for (int j = 0; j < RPS::MCols; j++) {
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
    // 1 based
//    MyPoint fPoint(move.getFrom().getX(), move.getFrom().getY());
//    MyPoint toPoint(move.getTo().getX(), move.getTo().getY());
    // zero based - correct
    MyPoint fPoint(move.getFrom().getX() - 1, move.getFrom().getY() - 1);
    MyPoint toPoint(move.getTo().getX() - 1, move.getTo().getY() - 1);
    if (this->selfGameBoard[toPoint.getY()][toPoint.getX()].get() != nullptr) {
//        MyPoint pFrom(move.getFrom().getX(), move.getFrom().getY()); // TODO: over ride operator= of Move class
//        MyPoint pTo(move.getTo().getX(), move.getTo().getY());
// 1 based
//        lastMove.init(pFrom, pTo);
        // zero based - correct
        lastMove.init(fPoint, toPoint);
        isOpponentAttacked = true;
        return;
    }

    this->selfGameBoard[toPoint.getY()][toPoint.getX()] = std::move(this->selfGameBoard[fPoint.getY()][fPoint.getX()]);
    isOpponentAttacked = false;
}

void AutoAlgorithm::notifyFightResult(const FightInfo& fightInfo) {
    vector<unique_ptr<Piece>> trash;
    Piece::RPSPiecesTypes opponentType;
    // 1 based - correct
    MyPoint fLastPoint(lastMove.getFrom().getX(), lastMove.getFrom().getY());
    MyPoint toLastPoint(lastMove.getTo().getX(), lastMove.getTo().getY());
    // zero based
//    MyPoint fLastPoint(lastMove.getFrom().getX() - 1, lastMove.getFrom().getY() - 1);
//    MyPoint toLastPoint(lastMove.getTo().getX() - 1, lastMove.getTo().getY() - 1);
    if (fightInfo.getWinner() == TIE) {
        trash.push_back(std::move(selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]));
        trash.push_back(std::move(selfGameBoard[toLastPoint.getY()][toLastPoint.getX()]));

    } else if (isOpponentAttacked) { // player defend
        if (fightInfo.getWinner() == player) {
            trash.push_back(std::move(selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]));
        } else {
            opponentType = selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]->type;
            trash.push_back(std::move(selfGameBoard[toLastPoint.getY()][toLastPoint.getX()]));

            if (opponentType == Piece::Undefined) {
                opponentNumOfUnknownPieces--;
                trash.push_back(std::move(selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo.getPiece(opponent)), opponent);
                selfGameBoard[toLastPoint.getY()][toLastPoint.getX()] = std::move(piecePtr);

            } else if ((opponentType != Piece::Joker) && (opponentType != Piece::getEnumTypeRep(fightInfo.getPiece(opponent)))){
                trash.push_back(std::move(selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::Joker, opponent, opponentType);
                selfGameBoard[toLastPoint.getY()][toLastPoint.getX()] = std::move(piecePtr);

            } else {
                selfGameBoard[toLastPoint.getY()][toLastPoint.getX()] = std::move(selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]);
            }
        }
    } else { // player attack
        if (fightInfo.getWinner() == opponent) {
            opponentType = selfGameBoard[toLastPoint.getY()][toLastPoint.getX()]->type;
            trash.push_back(std::move(selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]));

            if (opponentType == Piece::Undefined) {
                opponentNumOfUnknownPieces--;
                trash.push_back(std::move(selfGameBoard[toLastPoint.getY()][toLastPoint.getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo.getPiece(opponent)), opponent);
                selfGameBoard[toLastPoint.getY()][toLastPoint.getX()] = std::move(piecePtr);

            } else if ((opponentType != Piece::Joker) && (opponentType != Piece::getEnumTypeRep(fightInfo.getPiece(opponent)))) {
                trash.push_back(std::move(selfGameBoard[toLastPoint.getY()][toLastPoint.getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::Joker, opponent, opponentType);
                selfGameBoard[toLastPoint.getY()][toLastPoint.getX()] = std::move(piecePtr);
            }
        } else {
            if (Piece::getEnumTypeRep(fightInfo.getPiece(opponent) == Piece::Flag)) {
                opponentNumOfFlags--;
            }
            trash.push_back(std::move(selfGameBoard[toLastPoint.getY()][toLastPoint.getX()]));
            selfGameBoard[toLastPoint.getY()][toLastPoint.getX()] = std::move(selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]);
        }
    }

//    cout << "@@@@@@@@@@@@@@@@@@------NOTIFY-----@@@@@@@@@@@@@@@@@@" << endl;
//    this->printBoard();
//    cout << "@@@@@@@@@@@@@@@@@@------NOTIFY-----@@@@@@@@@@@@@@@@@@" << endl;
}

EndOfGameHandler AutoAlgorithm::checkWinner(EndOfGameHandler& endOfGameHandler, int currentPlayer) {
    bool player1HaveFlag = false, player2HaveFlag = false ,player1HaveMovingPieces = false, player2HaveMovingPieces = false;
    for (int i = 0; i < RPS::NRows; i++) {
        for (int j = 0; j < RPS::MCols; j++) {
            if (this->selfGameBoard[i][j].get() != nullptr){
                if (this->selfGameBoard[i][j]->getPlayerNumber() == 1) {
                    if (this->selfGameBoard[i][j]->type == Piece::Undefined) {
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
                    if (this->selfGameBoard[i][j]->type == Piece::Undefined) {
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

    for (int i = 0; i < RPS::NRows; i++) {
        p.setY(i);
        for (int j = 0; j < RPS::MCols; j++) {
            p.setX(j);
            if (this->selfGameBoard[i][j].get() != nullptr) {
                if (this->selfGameBoard[i][j]->getPlayerNumber() == player){
                    score += getPieceScore(this->selfGameBoard[i][j]);
                } else if (this->selfGameBoard[i][j]->getPlayerNumber() != EMPTY_CELL){
                    score -= getPieceScore(this->selfGameBoard[i][j]);
                }
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
            return SIMPLE_PIECE_SCORE;
    }
}

int AutoAlgorithm::getUnknownPieceTypeScore() {
    return (FLAG_SCORE * opponentNumOfFlags)/opponentNumOfUnknownPieces;
}

int AutoAlgorithm::swapTurn(int curPlayer) {
    if (curPlayer == 1) {
        return 2;
    }
    return 1;
}

void AutoAlgorithm::undoMove(MyMove &lastMove, unique_ptr<Piece>& fromPiece, unique_ptr<Piece>& toPiece) {
        MyPoint fLastPoint(lastMove.getFrom().getX(), lastMove.getFrom().getY());
    MyPoint toLastPoint(lastMove.getTo().getX(), lastMove.getTo().getY());
    vector<unique_ptr<Piece>> trash;
    trash.push_back(std::move(selfGameBoard[toLastPoint.getY()][toLastPoint.getX()]));
    trash.push_back(std::move(selfGameBoard[fLastPoint.getY()][fLastPoint.getX()]));

    selfGameBoard[fLastPoint.getY()][fLastPoint.getX()] = std::move(fromPiece);
    selfGameBoard[toLastPoint.getY()][toLastPoint.getX()] = std::move(toPiece);
}

unique_ptr<MyFightInfo> AutoAlgorithm::fight(unique_ptr<PiecePosition> &player1PiecePos, unique_ptr<PiecePosition> &player2PiecePos) {
    unique_ptr<Piece> piece1 , piece2;
    Piece::PiecesPower winner;

    if (player1PiecePos->getPosition().getY() != player2PiecePos->getPosition().getY() || player1PiecePos->getPosition().getX() != player2PiecePos->getPosition().getX()) {
        cout << "ERROR: The pieces are not in the same cell" << endl;
        return nullptr;
    }

    MyPoint point(player1PiecePos->getPosition().getX(), player1PiecePos->getPosition().getY());

    if ((Piece::getEnumTypeRep(player2PiecePos->getPiece()) == Piece::Undefined) || (Piece::getEnumTypeRep(player1PiecePos->getPiece()) == Piece::Undefined)) {
        return std::make_unique<MyFightInfo>(point, Piece::getEnumTypeRep(player1PiecePos->getPiece()),Piece::getEnumTypeRep(player2PiecePos->getPiece()), 0);
    }


    if (Piece::getEnumTypeRep(player1PiecePos->getPiece()) == Piece::Joker) {
        piece1 = PieceFactory::createPiece(Piece::getEnumTypeRep(player1PiecePos->getJokerRep()), 1);
    } else {
        piece1 = PieceFactory::createPiece(Piece::getEnumTypeRep(player1PiecePos->getPiece()) ,1);
    }

    if (Piece::getEnumTypeRep(player2PiecePos->getPiece()) == Piece::Joker) {
        piece2 = PieceFactory::createPiece(Piece::getEnumTypeRep(player2PiecePos->getJokerRep()), 2);
    } else {
        piece2 = PieceFactory::createPiece(Piece::getEnumTypeRep(player2PiecePos->getPiece()) ,2);
    }

    winner = piece1->isStrongerThan(*(piece2.get()));

    switch (winner){
        case Piece::Stronger:{
            return std::make_unique<MyFightInfo>(point, piece1->type, piece2->type, 1);
        }
        case Piece::Weaker:{
            return std::make_unique<MyFightInfo>(point, piece1->type, piece2->type, 2);
        }
        case Piece::Equal:{
            return std::make_unique<MyFightInfo>(point, piece1->type, piece2->type, 0);
        }
        default:
            cout << "ERROR: wrong PiecesPower type returned" << endl;
            return nullptr;
    }
}

unique_ptr<MyFightInfo> AutoAlgorithm::makeMove(unique_ptr<Move> &pieceMove, int player) {
    unique_ptr<MyFightInfo> fightInfo = nullptr;
    unique_ptr<Piece> releasePiece1, releasePiece2, piecePtr;
    unique_ptr<PiecePosition> defenderPtr, attackingPtr;

    if (pieceMove.get() == nullptr) {
        cout << "cannot set piece because piece was nullptr" << endl;
        return nullptr;
    }

    if (selfGameBoard[pieceMove->getTo().getY()][pieceMove->getTo().getX()].get() != nullptr) {
        Piece::RPSPiecesTypes defenderPieceType = selfGameBoard[pieceMove->getTo().getY()][pieceMove->getTo().getX()]->type;
        Piece::RPSPiecesTypes attackingPieceType = selfGameBoard[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]->type;
        Piece::RPSJokerTypes defenderJokerPieceType = Piece::JNotAJoker, attackingJokerPieceType = Piece::JNotAJoker;
        MyPoint FightingPoint(pieceMove->getTo().getX(), pieceMove->getTo().getY());

        if (attackingPieceType == Piece::Joker) {
            attackingJokerPieceType = Piece::fromTypeRepToJRep(((JokerPiece *)selfGameBoard[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()].get())->getJokerPiece());
            MyPiecePosition attackingPiecePos(attackingPieceType, FightingPoint, attackingJokerPieceType);
            attackingPtr = std::make_unique<MyPiecePosition>(attackingPiecePos);
        } else {
            MyPiecePosition attackingPiecePos(attackingPieceType, FightingPoint, Piece::JNotAJoker);
            attackingPtr = std::make_unique<MyPiecePosition>(attackingPiecePos);
        }

        if (defenderPieceType == Piece::Joker) {
            defenderJokerPieceType = Piece::fromTypeRepToJRep(((JokerPiece *)selfGameBoard[pieceMove->getTo().getY()][pieceMove->getTo().getX()].get())->getJokerPiece());
            MyPiecePosition defenderPiecePos(defenderPieceType, FightingPoint, defenderJokerPieceType);
            defenderPtr = std::make_unique<MyPiecePosition>(defenderPiecePos);

        } else {
            MyPiecePosition defenderPiecePos(defenderPieceType, FightingPoint, Piece::JNotAJoker);
            defenderPtr = std::make_unique<MyPiecePosition>(defenderPiecePos);

        }

        if (player == 1) {
            fightInfo = fight(attackingPtr, defenderPtr);
        } else if (player == 2) {
            fightInfo = fight(defenderPtr, attackingPtr);
        }

        if (fightInfo->getWinner() == 0) {
            releasePiece1 = std::move(selfGameBoard[pieceMove->getTo().getY()][pieceMove->getTo().getX()]);
            releasePiece2 = std::move(selfGameBoard[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]);
        } else if (fightInfo->getWinner() == player) {
            releasePiece1 = std::move(selfGameBoard[pieceMove->getTo().getY()][pieceMove->getTo().getX()]);
            selfGameBoard[pieceMove->getTo().getY()][pieceMove->getTo().getX()] = std::move(selfGameBoard[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]);
        } else {
            releasePiece1 = std::move(selfGameBoard[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]);
        }
        return std::move(fightInfo);

    } else {
        selfGameBoard[pieceMove->getTo().getY()][pieceMove->getTo().getX()] = std::move(selfGameBoard[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]);
        unique_ptr<Piece> attackingPieceType = std::move(selfGameBoard[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]);
    }
    return nullptr;
}


bool AutoAlgorithm::indexCheck(int row, int col){
    if(row < 0 || col < 0 || row >= RPS::NRows || col >= RPS::MCols){
        return false;
    }
    return true;
}
int AutoAlgorithm::recFunc(int curPlayer, int depth, bool isMax) {
    EndOfGameHandler endOfGameHandler;
    checkWinner(endOfGameHandler, curPlayer);

    int bestScore = INT_MAX , curScore;
    if (isMax) {
        bestScore = INT_MIN;
    }
    MyMove curMove;
    MyPoint pTo(0,0), pFrom(0,0);
    curPlayer = swapTurn(curPlayer);

    if (endOfGameHandler.getGameState() == static_cast<EndOfGameHandler::GameState>(curPlayer)) {
        return WIN_SCORE;
    } else if (endOfGameHandler.getGameState() == static_cast<EndOfGameHandler::GameState>(TIE)) {
        return TIE_SCORE;
    }  else if (endOfGameHandler.getGameState() != static_cast<EndOfGameHandler::GameState>(GAME_NOT_OVER)) { // opponent wins
        return LOSE_SCORE;
    }

    if (depth == 0) {
        return scoringFunction(swapTurn(curPlayer));
    }

    for (int i = 0; i < RPS::NRows; i++) {
        pFrom.setY(i);
        pTo.setY(i);
        for (int j = 0; j < RPS::MCols; j++) {
            if ((selfGameBoard[i][j].get() != nullptr) && (selfGameBoard[i][j]->type != Piece::Undefined)) {
                pFrom.setX(j);
                curMove.setFrom(pFrom);

                pTo.setPoint(i + 1, j);
                curMove.setTo(pTo);
                curScore = recFuncHandler(curMove, curPlayer, depth, isMax);
                if (indexCheck(pTo.getX(), pTo.getY()) && ((isMax && (curScore >= bestScore)) || (!isMax && curScore < bestScore))) {
                    bestScore = curScore;
                }
                pTo.setPoint(i - 1, j);
                curMove.setTo(pTo);
                curScore = recFuncHandler(curMove, curPlayer, depth, isMax);
                if (indexCheck(pTo.getX(), pTo.getY()) && ((isMax && (curScore >= bestScore)) || (!isMax && curScore < bestScore))) {
                    bestScore = curScore;
                }
                pTo.setPoint(i, j + 1);
                curMove.setTo(pTo);
                curScore = recFuncHandler(curMove, curPlayer, depth, isMax);
                if (indexCheck(pTo.getX(), pTo.getY()) && ((isMax && (curScore >= bestScore)) || (!isMax && curScore < bestScore))) {
                    bestScore = curScore;
                }
                pTo.setPoint(i, j - 1);
                curMove.setTo(pTo);
                curScore = recFuncHandler(curMove, curPlayer, depth, isMax);
                if (indexCheck(pTo.getX(), pTo.getY()) && ((isMax && (curScore >= bestScore)) || (!isMax && curScore < bestScore))) {
                    bestScore = curScore;
                }
            }
        }
    }
    return bestScore;
}

int AutoAlgorithm::recFuncHandler(MyMove &curMove,  int curPlayer, int depth, bool isMax) {
    int curScore = INT_MAX;
    if (isMax) {
        curScore = INT_MIN;
    }
    unique_ptr<Move> movesTrash;
    unique_ptr<MyFightInfo> fightInfoTrash;
    unique_ptr<MyFightInfo> fightInfo;
    unique_ptr<Piece> fromPiece = nullptr, toPiece = nullptr;

    MyPoint p1(curMove.getFrom().getX(), curMove.getFrom().getY()), p2(curMove.getTo().getX(), curMove.getTo().getY());
    unique_ptr<Move> curPtrMove = make_unique<MyMove>(p1, p2);

    if (RPS::checkIfMoveIsLegal(selfGameBoard, curMove, curPlayer, false)) {
        fightInfoTrash = std::move(fightInfo);
        if (selfGameBoard[curMove.getFrom().getY()][curMove.getFrom().getX()]->type == Piece::Undefined) {
            fromPiece = std::make_unique<Piece>(curPlayer);
        } else if (selfGameBoard[curMove.getFrom().getY()][curMove.getFrom().getX()]->type == Piece::Joker) {
            fromPiece = PieceFactory::createPiece(Piece::Joker, curPlayer, ((JokerPiece *)selfGameBoard[curMove.getFrom().getY()][curMove.getFrom().getX()].get())->getJokerPiece());
        } else {
            fromPiece = PieceFactory::createPiece(selfGameBoard[curMove.getFrom().getY()][curMove.getFrom().getX()]->type, curPlayer);
        }

        if (selfGameBoard[curMove.getTo().getY()][curMove.getTo().getX()].get() != nullptr) {
            if (selfGameBoard[curMove.getTo().getY()][curMove.getTo().getX()]->type == Piece::Undefined) {
                toPiece = std::make_unique<Piece>(swapTurn(curPlayer));
            } else if (selfGameBoard[curMove.getTo().getY()][curMove.getTo().getX()]->type == Piece::Joker) {
                toPiece = PieceFactory::createPiece(Piece::Joker, swapTurn(curPlayer), ((JokerPiece *)selfGameBoard[curMove.getTo().getY()][curMove.getTo().getX()].get())->getJokerPiece());
            } else {
                toPiece = PieceFactory::createPiece(selfGameBoard[curMove.getTo().getY()][curMove.getTo().getX()]->type, swapTurn(curPlayer));
            }

        }

        fightInfo = makeMove(curPtrMove, curPlayer);
        curScore = recFunc(curPlayer, depth - 1, !isMax);
        undoMove(curMove, fromPiece, toPiece);
    }
    return curScore;
}



void AutoAlgorithm::handleOneOfTheMoveChoice(int row, int col, MyPoint &pTo, MyPoint &bestPFrom, MyPoint &bestPTo, int curPlayer, int &curScore, int &bestScore, MyMove &curMove, int depth, bool isMax, vector<unique_ptr<Move>> &bestMovesVec){
    pTo.setPoint(col, row);
    curMove.setTo(pTo);
    vector<unique_ptr<Move>> trashVec;
    curScore = recFuncHandler(curMove, curPlayer, depth, isMax);
    MyPoint pFrom(curMove.getFrom().getX(), curMove.getFrom().getY());
    if (RPS::checkIfMoveIsLegal(selfGameBoard, curMove, curPlayer, false)) {
        if (curScore > bestScore) {
            bestScore = curScore;
            bestPTo.setPoint(pTo.getX(), pTo.getY());
            bestPFrom.setPoint(pFrom.getX(), pFrom.getY());
            unique_ptr<Move> movePtr = make_unique<MyMove>(bestPFrom, bestPTo);
            for (unique_ptr<Move> &ptr : bestMovesVec) {
                trashVec.push_back(std::move(ptr));
            }
            bestMovesVec.clear();
            bestMovesVec.push_back(std::move(movePtr));
//        cout << "found new best" << pFrom << " " << pTo << endl;
        } else if (curScore == bestScore) {
            bestPTo.setPoint(pTo.getX(), pTo.getY());
            bestPFrom.setPoint(pFrom.getX(), pFrom.getY());
            unique_ptr<Move> movePtr = make_unique<MyMove>(bestPFrom, bestPTo);
            bestMovesVec.push_back(std::move(movePtr));
        }
    }
}
unique_ptr<Move> AutoAlgorithm::getMove() {
    bool isMax = true;
    int depth = AUTO_ALGORITHM_DEPTH, curPlayer = player;
    int bestScore = INT_MIN, curScore;
    vector<unique_ptr<Move>> bestMovesVec;

    MyMove curMove, bestMove;
    MyPoint pTo(0,0), pFrom(0,0), bestPTo(-1, -1), bestPFrom(-1, -1) ;

    for (int i = 0; i < RPS::NRows; i++) {
        pFrom.setY(i);
        for (int j = 0; j < RPS::MCols; j++) {
            if ((selfGameBoard[i][j].get() != nullptr) && (selfGameBoard[i][j]->type != Piece::Undefined)) {
                pFrom.setX(j);
                curMove.setFrom(pFrom);
                handleOneOfTheMoveChoice(i + 1, j, pTo, bestPFrom, bestPTo, curPlayer, curScore, bestScore, curMove, depth, isMax , bestMovesVec);
                handleOneOfTheMoveChoice(i - 1, j, pTo, bestPFrom, bestPTo, curPlayer, curScore, bestScore, curMove, depth, isMax, bestMovesVec);
                handleOneOfTheMoveChoice(i, j + 1, pTo, bestPFrom, bestPTo, curPlayer, curScore, bestScore, curMove, depth, isMax, bestMovesVec);
                handleOneOfTheMoveChoice(i, j - 1, pTo, bestPFrom, bestPTo, curPlayer, curScore, bestScore, curMove, depth, isMax, bestMovesVec);

            }
        }
    }

    int randMove = rand() % bestMovesVec.size();
    unique_ptr<Move> bestPtrMove = std::move(bestMovesVec.at(randMove));
    // zero based - correct
    bestPTo.setPoint(bestPtrMove->getTo().getX(), bestPtrMove->getTo().getY());
    bestPFrom.setPoint(bestPtrMove->getFrom().getX(), bestPtrMove->getFrom().getY());
    // 1 based - the correct
//    bestPTo.setPoint(bestPtrMove->getTo().getX() + 1, bestPtrMove->getTo().getY()+ 1);
//    bestPFrom.setPoint(bestPtrMove->getFrom().getX() + 1, bestPtrMove->getFrom().getY()+ 1);
    lastMove.init(bestPFrom, bestPTo);
    isOpponentAttacked = false;

    if (this->selfGameBoard[bestPtrMove->getTo().getY()][bestPtrMove->getTo().getX()].get() == nullptr) {
        this->selfGameBoard[bestPtrMove->getTo().getY()][bestPtrMove->getTo().getX()] = std::move(this->selfGameBoard[bestPtrMove->getFrom().getY()][bestPtrMove->getFrom().getX()]);
    }

    this->printBoard();
    MyPoint pFrom1(bestPFrom.getX() + 1, bestPFrom.getY() + 1);
    MyPoint pTo1(bestPTo.getX() + 1, bestPTo.getY() + 1);
    unique_ptr<Move> bestPtrMove1Based = make_unique<MyMove>(pFrom1, pTo1);
    // zero based
    //return std::move(bestPtrMove);
    // 1 based - correct
    return std::move(bestPtrMove1Based);
}

int AutoAlgorithm::getScoreForJokerRep(int row, int col, Piece::RPSJokerTypes jokerRep) {
    int score = 0;
    unique_ptr<Piece> tmpPiece = PieceFactory::createPiece(Piece::getEnumTypeRep(Piece::fromJRepToChar(jokerRep)), player);

    if (row + 1 < RPS::NRows) { // TODO: handle isStrongerThan Joker!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (maybe create new pieces like we did in fight)
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
            if (Piece::PiecesPower::Stronger == tmpPiece->isStrongerThan(*(selfGameBoard[row - 1][col].get()))) {
                score++;
            } else {
                score--;
            }
        }
    }
    if (col + 1 < RPS::MCols) {
        if ((selfGameBoard[row][col + 1].get() != nullptr) && (selfGameBoard[row][col + 1]->getPlayerNumber() != player) && (selfGameBoard[row][col + 1]->type != Piece::Undefined)) {
            if (Piece::PiecesPower::Stronger == tmpPiece->isStrongerThan(*(selfGameBoard[row][col + 1].get()))) {
                score++;
            } else {
                score--;
            }
        }
    }
    if (col - 1 > 0) {
        if ((selfGameBoard[row][col - 1].get() != nullptr) && (selfGameBoard[row][col - 1]->getPlayerNumber() != player) && (selfGameBoard[row][col - 1]->type != Piece::Undefined)) {
            if (Piece::PiecesPower::Stronger == tmpPiece->isStrongerThan(*(selfGameBoard[row][col - 1].get()))) {
                score++;
            } else {
                score--;
            }
        }
    }
    return score;
}

unique_ptr<JokerChange> AutoAlgorithm::getJokerChange() {
    unique_ptr<MyJokerChange> jokerChangePtr = make_unique<MyJokerChange>();
    Piece::RPSJokerTypes jokerRep;
    int curScore, bestScore = INT_MIN;
    MyPoint p(-1,-1);

    for (int i = 0; i < RPS::NRows; i++) {
        p.setY(i);
        for (int j = 0; j < RPS::MCols; j++) {
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

    if ((jokerChangePtr->getJokerChangePosition().getY() == this->lastMove.getFrom().getY()) && (jokerChangePtr->getJokerChangePosition().getX() == this->lastMove.getFrom().getX())) {
       //zero based correct
       // MyPoint p(this->lastMove.getTo().getX() - 1, this->lastMove.getTo().getY() - 1);
        //1 based
        MyPoint p(this->lastMove.getTo().getX(), this->lastMove.getTo().getY());
        jokerChangePtr->setPosition(p);
    }

    if ((jokerChangePtr->getJokerChangePosition().getY() != -1) && (jokerChangePtr->getJokerChangePosition().getX() != -1)){
        if (this->selfGameBoard[jokerChangePtr->getJokerChangePosition().getY()][jokerChangePtr->getJokerChangePosition().getX()].get() != nullptr) {
            ((JokerPiece *)this->selfGameBoard[jokerChangePtr->getJokerChangePosition().getY()][jokerChangePtr->getJokerChangePosition().getX()].get())->setJokerPiece(Piece::getEnumTypeRep(jokerChangePtr->getJokerNewRep()));
            MyPoint jokerPos(jokerChangePtr->getJokerChangePosition().getX() + 1, jokerChangePtr->getJokerChangePosition().getY() + 1);
            unique_ptr<MyJokerChange> jokerChangeOneBase = make_unique<MyJokerChange>(jokerPos, Piece::fromTypeRepToJRep(Piece::getEnumTypeRep(jokerChangePtr->getJokerNewRep())));
            // zero based joker
            //return std::move(jokerChangePtr);
            // 1 based - manager expects this
            return std::move(jokerChangeOneBase);
        }
    }


    return nullptr;
}

void AutoAlgorithm::printBoard() {
    cout << "player " << player << ":" << endl;
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    cout << "     ";
    for(int i = 0; i < RPS::NRows; i++){
        cout << i + 1 << "   ";
    }
    cout << endl;
    for (int i = 0; i < RPS::NRows; i++) {
        cout << "   ------------------------------------------" << endl;
        if ((i + 1) / 10 == 0){
            cout << i + 1 << "  |";
        } else {
            cout << i + 1 << " |";
        }

        for (int j = 0; j < RPS::MCols; j++) {
            if (this->selfGameBoard[i][j].get() != nullptr) {
                cout << " " << this->selfGameBoard[i][j]->toString() << " |";
            } else {
                cout << "   |";
            }
        }
        cout << endl;
    }
}
