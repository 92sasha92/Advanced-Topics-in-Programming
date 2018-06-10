#include "GameManager.h"

string GameManager::outputFile = "rps.output";

GameManager::GameManager(unique_ptr<PlayerAlgorithm> &&player1Algorithm_, unique_ptr<PlayerAlgorithm> &&player2Algorithm_): playerAlgorithms(), gameBoard() {
    playerAlgorithms.push_back(std::move(player1Algorithm_));
    playerAlgorithms.push_back(std::move(player2Algorithm_));
}

void GameManager::printBoard() {
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    cout << "    1   2   3   4   5   6   7   8   9   10" << endl;
    for (int i = 0; i < RPS::NRows; i++) {
        cout << "  ------------------------------------------" << endl;
        cout << i + 1 << " |";
        for (int j = 0; j < RPS::MCols; j++) {
            if (this->gameBoard.board[i][j].get() != nullptr) {
                cout << " " << this->gameBoard.board[i][j]->toString() << " |";
            } else {
                cout << "   |";
            }
        }
        cout << endl;
    }
}

unique_ptr<MyFightInfo> GameManager::fight(unique_ptr<PiecePosition> &player1PiecePos, unique_ptr<PiecePosition> &player2PiecePos) {
    unique_ptr<Piece> piece1 , piece2;
    MyPoint pos1(player1PiecePos->getPosition().getX() - 1, player1PiecePos->getPosition().getY() - 1);
    MyPoint pos2(player2PiecePos->getPosition().getX() - 1, player2PiecePos->getPosition().getY() - 1);
    if (pos1.getY() != pos2.getY() || pos1.getX() != pos2.getX()) {
        cout << "ERROR: The pieces are not in the same cell" << endl;
        return nullptr;
    }
    // fight info 1 based
    MyPoint point(player1PiecePos->getPosition().getX(), player1PiecePos->getPosition().getY());

    if (Piece::getEnumTypeRep(player1PiecePos->getPiece()) == Piece::Joker) {
        piece1 = PieceFactory::createPiece(Piece::getEnumTypeRep(player1PiecePos->getJokerRep()), 1);
    } else {
        piece1 = PieceFactory::createPiece(Piece::getEnumTypeRep(player1PiecePos->getPiece()), 1);
    }

    if (Piece::getEnumTypeRep(player2PiecePos->getPiece()) == Piece::Joker) {
        piece2 = PieceFactory::createPiece(Piece::getEnumTypeRep(player2PiecePos->getJokerRep()), 2);
    } else {
        piece2 = PieceFactory::createPiece(Piece::getEnumTypeRep(player2PiecePos->getPiece()), 2);
    }

    Piece::PiecesPower winner = piece1->isStrongerThan(*(piece2.get())); // check for the stronger piece
    switch (winner) {
        case Piece::Stronger: {
            //cout << "player 1 win in cell " << point  << endl;
            return std::make_unique<MyFightInfo>(point, piece1->type, piece2->type, 1);
        }
        case Piece::Weaker: {
            //cout << "player 2 win in cell " << point  << endl;
            return std::make_unique<MyFightInfo>(point, piece1->type, piece2->type, 2);
        }
        case Piece::Equal: {
            //cout << "tie cell " << point  << endl;
            return std::make_unique<MyFightInfo>(point, piece1->type, piece2->type, 0);
        }
        default:
            cout << "ERROR: wrong PiecesPower type returned" << endl;
            return nullptr;
    }
}

unique_ptr<MyFightInfo> GameManager::setPiece(unique_ptr<PiecePosition> &piecePos, int player) { //for the board initializition case only
    unique_ptr<MyFightInfo> fightInfo = nullptr;
    unique_ptr<Piece> releasePiece, piecePtr;

    if (piecePos.get() == nullptr) {
        cout << "cannot set piece because piece was nullptr" << endl;
        return nullptr;
    }
    MyPoint pos(piecePos->getPosition().getX() - 1, piecePos->getPosition().getY() - 1);
    if (gameBoard.board[pos.getY()][pos.getX()].get() != nullptr) { // check if the cell is empty or preper to fight
        Piece::RPSPiecesTypes type = gameBoard.board[pos.getY()][pos.getX()]->type;
        MyPoint point(pos.getX() + 1, pos.getY() + 1);

        if (gameBoard.board[pos.getY()][pos.getX()]->type == Piece::Joker) {
            MyPiecePosition player1PiecePos(type, point,Piece::fromTypeRepToJRep(((JokerPiece *)gameBoard.board[pos.getY()][pos.getX()].get())->getJokerPiece()));
            unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(player1PiecePos);
            fightInfo = fight(ptr, piecePos);
        } else {
            MyPiecePosition player1PiecePos(type, point, Piece::JNotAJoker);
            unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(player1PiecePos);
            fightInfo = fight(ptr, piecePos);
        }

        if (fightInfo->getWinner() == 0 || fightInfo->getWinner() == 2) { // if player1 wins we are not set the piece of player2 on board
            releasePiece = std::move(gameBoard.board[pos.getY()][pos.getX()]); // piece will free when get to the end of the func
            if (fightInfo->getWinner() == 2) {
                piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(piecePos->getPiece()), 2, Piece::getEnumTypeRep(piecePos->getJokerRep()));
                gameBoard.board[pos.getY()][pos.getX()] = std::move(piecePtr);
            }
        }
        return std::move(fightInfo);
    } else { // the cell is empty
        piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(piecePos->getPiece()), player, Piece::getEnumTypeRep(piecePos->getJokerRep()));
        gameBoard.board[pos.getY()][pos.getX()] = std::move(piecePtr);
    }
    return nullptr;
}

// pieceMOve is 1 based
unique_ptr<MyFightInfo> GameManager::makeMove(unique_ptr<Move> &pieceMove, int player) { //for moves case only
    unique_ptr<MyFightInfo> fightInfo = nullptr;
    unique_ptr<Piece> releasePiece1, releasePiece2, piecePtr;
    unique_ptr<PiecePosition> defenderPtr, attackingPtr;

    if (pieceMove.get() == nullptr) {
        cout << "cannot set piece because the piece was nullptr" << endl;
        return nullptr;
    }
    // translate the move to zero based points
    MyPoint pFrom(pieceMove->getFrom().getX() - 1, pieceMove->getFrom().getY() - 1);
    MyPoint pTo(pieceMove->getTo().getX() - 1, pieceMove->getTo().getY() - 1);
    // there is a fight
    if (gameBoard.board[pTo.getY()][pTo.getX()].get() != nullptr) {
        Piece::RPSPiecesTypes defenderPieceType = gameBoard.board[pTo.getY()][pTo.getX()]->type;
        Piece::RPSPiecesTypes attackingPieceType = gameBoard.board[pFrom.getY()][pFrom.getX()]->type;
        Piece::RPSJokerTypes defenderJokerPieceType, attackingJokerPieceType;
        MyPoint FightingPoint(pTo.getX() + 1, pTo.getY() + 1);

        if (attackingPieceType == Piece::Joker) { // create the attack piece to check the fight result
            attackingJokerPieceType = Piece::fromTypeRepToJRep(((JokerPiece *)gameBoard.board[pFrom.getY()][pFrom.getX()].get())->getJokerPiece());
            MyPiecePosition attackingPiecePos(attackingPieceType, FightingPoint, attackingJokerPieceType);
            attackingPtr = std::make_unique<MyPiecePosition>(attackingPiecePos);
        } else {
            MyPiecePosition attackingPiecePos(attackingPieceType, FightingPoint, Piece::JNotAJoker);
            attackingPtr = std::make_unique<MyPiecePosition>(attackingPiecePos);
        }

        if (defenderPieceType == Piece::Joker) { // create the defend piece to check the fight result
            defenderJokerPieceType = Piece::fromTypeRepToJRep(((JokerPiece *)gameBoard.board[pTo.getY()][pTo.getX()].get())->getJokerPiece());
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

        if (fightInfo->getWinner() == 0) { // handle the fight resule
            releasePiece1 = std::move(gameBoard.board[pTo.getY()][pTo.getX()]);
            releasePiece2 = std::move(gameBoard.board[pFrom.getY()][pFrom.getX()]);
        } else if (fightInfo->getWinner() == player) {
            releasePiece1 = std::move(gameBoard.board[pTo.getY()][pTo.getX()]);
            gameBoard.board[pTo.getY()][pTo.getX()] = std::move(gameBoard.board[pFrom.getY()][pFrom.getX()]);
        } else {
            releasePiece1 = std::move(gameBoard.board[pFrom.getY()][pFrom.getX()]);
        }
        return std::move(fightInfo);

    } else {
        gameBoard.board[pTo.getY()][pTo.getX()] = std::move(gameBoard.board[pFrom.getY()][pFrom.getX()]);
        unique_ptr<Piece> attackingPieceType = move(gameBoard.board[pFrom.getY()][pFrom.getX()]);
    }
    return nullptr;
}

GameManager::Turns GameManager::changeTurn(GameManager::Turns turn) {
    if (turn == FIRST_PLAYER_TURN) {
        return SECOND_PLAYER_TURN;
    } else {
        return FIRST_PLAYER_TURN;
    }
}

bool GameManager::checkLegalPositioningVec(const std::vector<unique_ptr<PiecePosition>> &vec, int &errorLineCounter) {
    int tempBoard[RPS::NRows][RPS::MCols] = {0};
    RPS rps;
    rps.initializePiecesArsenal();
    for (const unique_ptr<PiecePosition> &piecePos: vec) {
        errorLineCounter++;
        // transfer to zero based
        MyPoint pos(piecePos->getPosition().getX() - 1, piecePos->getPosition().getY() - 1);
        if (!RPS::isPointInBounds(pos)) {
            std::cout << "ERROR: Piece set outside the board" << std::endl;
            return false;
        }
        if (Piece::getEnumTypeRep(piecePos->getPiece()) == Piece::Undefined) {
            std::cout << "ERROR: Undefined piece type" << piecePos->getPiece() << std::endl;
            return false;
        }
        if (tempBoard[pos.getY()][pos.getX()] == 1) {
            std::cout << "ERROR: " << "(" << pos.getX() + 1 << ", " << pos.getY() + 1 <<  ") already occupied by other piece of the same player" << std::endl;
            return false;
        } else {
            Piece::RPSPiecesTypes pieceType = PieceFactory::charToPieceType(piecePos->getPiece());
            if (rps.playerPiecesArsenal[pieceType] == 0) {
                std::cout << "ERROR: too many pieces of the same type, type enum:" << pieceType << std::endl;
                return false;
            }
            rps.playerPiecesArsenal[pieceType]--;
            tempBoard[pos.getY()][pos.getX()] = 1;
            if (piecePos->getPiece() == Piece::Joker) {
                if (piecePos->getPiece() == Piece::Joker || piecePos->getPiece() == Piece::Undefined || piecePos->getPiece() == Piece::Flag) {
                    std::cout << "ERROR: joker piece type is wrong" << std::endl;
                    return false;
                }
            }
        }
    }

    if (rps.playerPiecesArsenal[Piece::Flag] > 0) {
        std::cout << "ERROR: Not all Flags placed" << std::endl;
        return false;
    }
    return true;
}

void GameManager::checkAndSetBoolFlags(Piece * const currentPiece, bool &playerHaveFlag, bool &playerHaveMovingPieces){
    if (currentPiece->type == Piece::Flag) {
        playerHaveFlag = true;
    } else if (currentPiece->type == Piece::Rock || currentPiece->type == Piece::Scissors || currentPiece->type == Piece::Paper) {
        playerHaveMovingPieces = true;
    } else if (currentPiece->type == Piece::Joker && ((JokerPiece *)currentPiece)->getJokerPiece() != Piece::Bomb) {
        playerHaveMovingPieces = true;
    }
}

void GameManager::checkMovablePieces(bool &player1HaveFlag, bool &player2HaveFlag, bool &player1HaveMovingPieces, bool &player2HaveMovingPieces) {
    for (int i = 0; i < RPS::NRows; i++) {
        for (int j = 0; j < RPS::MCols; j++) {
            Piece * const currentPiece = this->gameBoard.board[i][j].get();
            if (currentPiece != nullptr) {
                if (currentPiece->getPlayerNumber() == 1) {
                    checkAndSetBoolFlags(currentPiece, player1HaveFlag, player1HaveMovingPieces);
                } else {
                    checkAndSetBoolFlags(currentPiece, player2HaveFlag, player2HaveMovingPieces);
                }
            }
        }
    }
}

EndOfGameHandler GameManager::checkWinner(EndOfGameHandler& endOfGameHandler, int currentPlayer) {
    if (endOfGameHandler.getEndOfGameReason() == EndOfGameHandler::Tie100MovesNoFight) {
        endOfGameHandler.setGameState(EndOfGameHandler::Tie);
        return endOfGameHandler;
    }
    bool player1HaveFlag = false, player2HaveFlag = false ,player1HaveMovingPieces = false, player2HaveMovingPieces = false;
    checkMovablePieces(player1HaveFlag, player2HaveFlag, player1HaveMovingPieces, player2HaveMovingPieces);

    if ((!player1HaveFlag) || (!player2HaveFlag)) {
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::LooserAllFlagsEaten);
        if (player1HaveFlag) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player1Win);
        } else if (player2HaveFlag) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player2Win);
        } else {
            endOfGameHandler.setEndOfGameReason(EndOfGameHandler::TieAllFlagsEaten);
            endOfGameHandler.setGameState(EndOfGameHandler::Tie);
        }

    } else if ((!player1HaveMovingPieces && currentPlayer == 1) || (!player2HaveMovingPieces && currentPlayer == 2)) {
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::AllMovingPiecesEaten);
        if (player1HaveMovingPieces) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player1Win);
        } else if (player2HaveMovingPieces) {
            endOfGameHandler.setGameState(EndOfGameHandler::Player2Win);
        } else {
            endOfGameHandler.setGameState(EndOfGameHandler::Tie);
            endOfGameHandler.setEndOfGameReason(EndOfGameHandler::TieAllMovingPiecesEaten);
        }
    }
    return endOfGameHandler;
}

int GameManager::playerNum(GameManager::Turns const &currentTurn) {
    if (currentTurn == FIRST_PLAYER_TURN) {
        return 1;
    } else {
        return 2;
    }
}

bool GameManager::checkJokerChangeAndSet(const JokerChange &jokerChange, int player) {

    if (!(RPS::isPointInBounds(jokerChange.getJokerChangePosition()))) {
        cout << "ERROR: Joker suit change index is out of bound" << endl;
        return false;
    }

    if (gameBoard.board[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()]->getPlayerNumber() != player) {
        cout << "ERROR: not current player piece" << endl;
        return false;
    }

    if (gameBoard.board[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()].get() == nullptr) {
        cout << "ERROR: no joker in the given position" << endl;
        return false;
    }

    if (gameBoard.board[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()]->type != Piece::Joker) {
        cout << "ERROR: Piece in the current cell (" << jokerChange.getJokerChangePosition().getY() << ", " << jokerChange.getJokerChangePosition().getX() << ") is not a Joker type" << endl;
        return false;
    }

    Piece::RPSPiecesTypes jokerPiece = PieceFactory::charToPieceType(jokerChange.getJokerNewRep());

    if (jokerPiece != Piece::Joker && jokerPiece != Piece::Flag && jokerPiece != Piece::Undefined) {
        ((JokerPiece *)gameBoard.board[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()].get())->setJokerPiece(jokerPiece);
    }
    else {
        ((JokerPiece *)gameBoard.board[jokerChange.getJokerChangePosition().getY()][jokerChange.getJokerChangePosition().getX()].get())->setJokerPiece(Piece::Undefined);
        cout << "ERROR: unsupported joker type" << endl;
        return false;
    }
    return true;
}

bool GameManager::handleErrorInAMove(GameManager::Turns &currentTurn, EndOfGameHandler& endOfGameHandler, unique_ptr<Move> &movePtr, int fileLinePlayer[2]){
    if (movePtr.get() == nullptr) {
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadMoveFile);
        endOfGameHandler.setWinner(currentTurn, fileLinePlayer[0], fileLinePlayer[1]);
        cout << "ERROR: there was no move" << endl;
        return false;
    }
    //cout << "player " << playerNum(currentTurn) << " move from (" <<  movePtr->getFrom().getX() << ", " << movePtr->getFrom().getY() << ") to (" <<  movePtr->getTo().getX() << ", " << movePtr->getTo().getY() << ")" << endl;
    const Move &move = *(movePtr.get());
    MyPoint pFrom(move.getFrom().getX() - 1, move.getFrom().getY() - 1);
    MyPoint pTo(move.getTo().getX() - 1, move.getTo().getY() - 1);
    MyMove zeroBasedMove(pFrom, pTo);
    if (!RPS::checkIfMoveIsLegal(this->gameBoard.board, zeroBasedMove, playerNum(currentTurn))) { // check if the move is illegal
        // TODO: ERROR: in making move
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadMoveFile);
        endOfGameHandler.setWinner(currentTurn, fileLinePlayer[0], fileLinePlayer[1]);
        cout << "ERROR: move is illegal" << endl;
        return false;
    }
    return true;
}

bool GameManager::handleATurn(GameManager::Turns &currentTurn, EndOfGameHandler& endOfGameHandler, int fileLinePlayer[2], int &numOfMovesWithoutAFight) {
    numOfMovesWithoutAFight++;
    unique_ptr<Move> movePtr = playerAlgorithms[currentTurn]->getMove();
    if(!handleErrorInAMove(currentTurn, endOfGameHandler, movePtr, fileLinePlayer)){
        return false;
    }
    const Move &move = *(movePtr.get());
    unique_ptr<FightInfo> fightPtr = makeMove(movePtr, playerNum(currentTurn)); // make the move and get the fight result
    const FightInfo &fight = *(fightPtr.get());
    // if there was a fight
    if (fightPtr.get() != nullptr) {
        numOfMovesWithoutAFight = 0;
        playerAlgorithms[currentTurn]->notifyFightResult(fight);
    }
    if (checkWinner(endOfGameHandler, playerNum(changeTurn(currentTurn))).getGameState() != EndOfGameHandler::GameNotOver) {
        return false;
    }
    unique_ptr<JokerChange> jokerChangePtr = playerAlgorithms[currentTurn]->getJokerChange(); // handle joker change of representation
    if (jokerChangePtr.get() != nullptr) {
        const JokerChange &jokerChange = *(jokerChangePtr.get());
        MyPoint jokerPos(jokerChange.getJokerChangePosition().getX() - 1, jokerChange.getJokerChangePosition().getY() - 1);
        MyJokerChange jokerChangeZeroBased(jokerPos, Piece::fromTypeRepToJRep(Piece::getEnumTypeRep(jokerChange.getJokerNewRep())));
        if (!checkJokerChangeAndSet(jokerChangeZeroBased, playerNum(currentTurn))) {
            // TODO: ERROR: in changing joker
            cout << "ERROR: in changing joker" << endl;
            endOfGameHandler.setEndOfGameReason(EndOfGameHandler::BadMoveFile);
            endOfGameHandler.setWinner(currentTurn, fileLinePlayer[0], fileLinePlayer[1]);
            return false;
        }
    }
    playerAlgorithms[changeTurn(currentTurn)]->notifyOnOpponentMove(move);
    if (fightPtr.get() != nullptr) {
        playerAlgorithms[changeTurn(currentTurn)]->notifyFightResult(fight);
    }
    currentTurn = changeTurn(currentTurn); // change turns
    if (numOfMovesWithoutAFight >= 100) { // check the number of turns without a fight
        endOfGameHandler.setEndOfGameReason(EndOfGameHandler::Tie100MovesNoFight);
        return false;
    }
    return true;
}

void GameManager::createOutFile(EndOfGameHandler &endOfGameHandler, bool *isBadInputFile, int *ErrorLine) {
    ofstream fout(GameManager::outputFile);
    if ((isBadInputFile[0] || isBadInputFile[1])) {
        if (!isBadInputFile[0]) {
            fout << "Winner: " << 1 << endl;
        } else if (!isBadInputFile[1]) {
            fout << "Winner: " << 2 << endl;
        } else {
            fout << "Winner: " << 0 << endl;
        }
    } else if (endOfGameHandler.getGameState() == EndOfGameHandler::GameNotOver) {
        fout << "Winner: " << 0 << endl;
    } else {
        fout << "Winner: " << endOfGameHandler.getGameState() << endl;
    }
    fout << "Reason: ";
    if (isBadInputFile[0] && isBadInputFile[1]) {
        fout << "Bad Positioning input file for both players - player 1: line ";
        fout << ErrorLine[0] << ", player 2: line " << ErrorLine[1] << endl;
    } else if (isBadInputFile[0]) {
        fout << "Bad Positioning input file for player 1 - line " << ErrorLine[0] << endl;
    } else if (isBadInputFile[1]) {
        fout << "Bad Positioning input file for player 2 - line " << ErrorLine[1] << endl;
    } else {
        fout << endOfGameHandler.toString() << endl;
    }
    // empty line
    fout << endl;
    for (int i = 0; i < RPS::NRows; i++) {
        for (int j = 0; j < RPS::MCols; j++) {
            if (gameBoard.board[i][j].get() == nullptr) {
                fout << " ";
            } else {
                fout << gameBoard.board[i][j]->toString();
            }
        }
        fout << endl;
    }
    fout.close();
}


bool GameManager::checkAndSetInitPiecePos(int errorLine[2], bool isBadInputVec[2], std::vector<unique_ptr<FightInfo>> &fightInfoVec){
    unique_ptr<MyFightInfo> fightInfo;
    std::vector<unique_ptr<PiecePosition>> vectorToFill_1;
    std::vector<unique_ptr<PiecePosition>> vectorToFill_2;
    playerAlgorithms[0]->getInitialPositions(1, vectorToFill_1);
    playerAlgorithms[1]->getInitialPositions(2, vectorToFill_2);
    isBadInputVec[0] = !(checkLegalPositioningVec(vectorToFill_1, errorLine[0]));
    isBadInputVec[1] = !(checkLegalPositioningVec(vectorToFill_2, errorLine[1]));
    if(!isBadInputVec[0] && !isBadInputVec[1]){
        for (unique_ptr<PiecePosition> &piecePos1: vectorToFill_1) { // get players vectors of pieces positions
            fightInfo = setPiece(piecePos1, 1);
            if (fightInfo.get() != nullptr) {
                fightInfoVec.push_back(std::move(fightInfo)); // fight if the current cell is occupied
            }
        }

        for (unique_ptr<PiecePosition> &piecePos2: vectorToFill_2) {
            fightInfo = setPiece(piecePos2, 2);
            if (fightInfo.get() != nullptr) {
                fightInfoVec.push_back(std::move(fightInfo));
            }
        }
        return true;
    } else if (isBadInputVec[0] && isBadInputVec[1]) {
        cout << "both players lose because unsupported rps.board format" << endl;
    } else if (isBadInputVec[0]) {
        cout << "player1 lose because unsupported rps.board format" << endl;
    } else if (isBadInputVec[1]) {
        cout << "player2 lose because unsupported rps.board format" << endl;
    }
    return false;
}


int GameManager::startGame() {
    bool isBadInputVec[2] = {false, false};
    int errorLine[2] = {0, 0};
    int numOfMovesWithoutAFight = 0;
    Turns currentTurn = FIRST_PLAYER_TURN;
    EndOfGameHandler endOfGameHandler;
    unique_ptr<MyFightInfo> fightInfo;
    std::vector<unique_ptr<FightInfo>> fightInfoVec;
    if(checkAndSetInitPiecePos(errorLine, isBadInputVec, fightInfoVec)){
        this->playerAlgorithms[0]->notifyOnInitialBoard(this->gameBoard, fightInfoVec); // notify results to the players
        this->playerAlgorithms[1]->notifyOnInitialBoard(this->gameBoard, fightInfoVec);
        int fileLinePlayer[2] = {0, 0};
        while ((checkWinner(endOfGameHandler, playerNum(currentTurn))).getGameState() == EndOfGameHandler::GameNotOver) { // make moves until the game is over
//            printBoard();
            fileLinePlayer[currentTurn]++;
            if (!handleATurn(currentTurn, endOfGameHandler, fileLinePlayer, numOfMovesWithoutAFight)) {
                //TODO: handle error
                break;
            }
        }
//        printBoard();
        checkWinner(endOfGameHandler, playerNum(currentTurn));
    }

    GameManager::createOutFile(endOfGameHandler, isBadInputVec, errorLine);
    return static_cast<int>(endOfGameHandler.getGameState());
}
