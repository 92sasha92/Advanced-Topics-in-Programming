#include "GameManager.h"


GameManager::GameManager(PlayerAlgorithm &player1Algoritm_, PlayerAlgorithm &player2Algoritm_): player1Algoritm(player1Algoritm_), player2Algoritm(player2Algoritm_), gameBoard() {
    startGame();
}

void GameManager::printBoard() {
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;

    for (int i = 0; i < RPS::Nrows; i++) {
        cout << "----------------------------------------" << endl;
        for (int j = 0; j < RPS::Mcols; j++) {
            if (this->gameBoard.board[i][j].get() != nullptr) {
                cout << this->gameBoard.board[i][j]->toString() << " |";
            } else {
                cout << "   |";
            }
        }
        cout << endl;
    }
}

unique_ptr<MyFightInfo> GameManager::fight(unique_ptr<PiecePosition> &player1PiecePos, unique_ptr<PiecePosition> &player2PiecePos) {
    std::unique_ptr<MyFightInfo> fightInfo = nullptr;
    unique_ptr<Piece> piece1 , piece2;

    if (player1PiecePos->getPosition().getY() != player2PiecePos->getPosition().getY() || player1PiecePos->getPosition().getX() != player2PiecePos->getPosition().getX()) {
        cout << "ERROR: The pieces are not in the same cell" << endl;
        return nullptr;
    }
    MyPoint point(player1PiecePos->getPosition().getX(), player1PiecePos->getPosition().getY());

    if (Piece::getEnumTypeRep(player1PiecePos->getPiece()) == Piece::Joker) {
        piece1 = PieceFactory::createPiece(Piece::getEnumTypeRep(player1PiecePos->getJokerRep()), 0);
    } else {
        piece1 = PieceFactory::createPiece(Piece::getEnumTypeRep(player1PiecePos->getPiece()) ,0);
    }

    if (Piece::getEnumTypeRep(player2PiecePos->getPiece()) == Piece::Joker) {
        piece2 = PieceFactory::createPiece(Piece::getEnumTypeRep(player2PiecePos->getJokerRep()), 1);
    } else {
        piece2 = PieceFactory::createPiece(Piece::getEnumTypeRep(player2PiecePos->getPiece()) ,1);
    }

    Piece::PiecesPower winner = piece1->isStrongerThan(*(piece2.get()));
    switch (winner){
        case Piece::Stronger:{
            cout << "player1 win in cell (" << point.getX() + 1 << "," << point.getY() + 1 << ")"  << endl;
            return std::make_unique<MyFightInfo>(point, piece1->type, piece2->type, 1);
        }
        case Piece::Weaker:{
            cout << "player2 win in cell (" << point.getX() + 1 << "," << point.getY() + 1 << ")"  << endl;
            return std::make_unique<MyFightInfo>(point, piece1->type, piece2->type, 2);
        }
        case Piece::Equal:{
            cout << "tie cell (" << point.getX() + 1 << "," << point.getY() + 1 << ")"  << endl;
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

    if (gameBoard.board[piecePos->getPosition().getY()][piecePos->getPosition().getX()].get() != nullptr) {
        // TODO: set "player1PiecePos" to be player 1 piece
        Piece::RPSPiecesTypes type = gameBoard.board[piecePos->getPosition().getY()][piecePos->getPosition().getX()]->type;
        MyPoint point(piecePos->getPosition().getX(), piecePos->getPosition().getY());

        if (gameBoard.board[piecePos->getPosition().getY()][piecePos->getPosition().getX()]->type == Piece::Joker) {
            MyPiecePosition player1PiecePos(type, point,Piece::fromTypeRepToJRep(((JokerPiece *)gameBoard.board[piecePos->getPosition().getY()][piecePos->getPosition().getX()].get())->getJokerPiece()));
            unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(player1PiecePos);
            fightInfo = fight(ptr, piecePos);
        } else {
            MyPiecePosition player1PiecePos(type, point, Piece::JNotAJoker);
            unique_ptr<PiecePosition> ptr = std::make_unique<MyPiecePosition>(player1PiecePos);
            fightInfo = fight(ptr, piecePos);
        }

        if (fightInfo->getWinner() == 0 || fightInfo->getWinner() == 2){ // if player1 wins we are not set the piece of player2 on board
            releasePiece = std::move(gameBoard.board[piecePos->getPosition().getY()][piecePos->getPosition().getX()]); // piece will free when get to the end of the func
            if (fightInfo->getWinner() == 2) {
                piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(piecePos->getPiece()), 2, Piece::getEnumTypeRep(piecePos->getJokerRep()));
                gameBoard.board[piecePos->getPosition().getY()][piecePos->getPosition().getX()] = std::move(piecePtr);
            }
        }
        return std::move(fightInfo);
    } else {
        piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(piecePos->getPiece()), player, Piece::getEnumTypeRep(piecePos->getJokerRep()));
        gameBoard.board[piecePos->getPosition().getY()][piecePos->getPosition().getX()] = std::move(piecePtr);
    }
    return nullptr;
}

unique_ptr<MyFightInfo> GameManager::setPiece(unique_ptr<Move> &pieceMove, int player) { //for moves case only
    unique_ptr<MyFightInfo> fightInfo = nullptr;
    unique_ptr<Piece> releasePiece1, releasePiece2, piecePtr;
    unique_ptr<PiecePosition> defenderPtr, attackingPtr;

    if (pieceMove.get() == nullptr) {
        cout << "cannot set piece because piece was nullptr" << endl;
        return nullptr;
    }

    if (gameBoard.board[pieceMove->getTo().getY()][pieceMove->getTo().getX()].get() != nullptr) {
        Piece::RPSPiecesTypes defenderPieceType = gameBoard.board[pieceMove->getTo().getY()][pieceMove->getTo().getX()]->type;
        Piece::RPSPiecesTypes attackingPieceType = gameBoard.board[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]->type;
        Piece::RPSJokerTypes defenderJokerPieceType, attackingJokerPieceType;
        MyPoint FightingPoint(pieceMove->getTo().getY(), pieceMove->getTo().getX());

        if (attackingPieceType == Piece::Joker) {
            attackingJokerPieceType = Piece::fromTypeRepToJRep(((JokerPiece *)gameBoard.board[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()].get())->getJokerPiece());
            MyPiecePosition attackingPiecePos(attackingPieceType, FightingPoint, attackingJokerPieceType);
            attackingPtr = std::make_unique<MyPiecePosition>(attackingPiecePos);
        } else {
            MyPiecePosition attackingPiecePos(attackingPieceType, FightingPoint, Piece::JNotAJoker);
            attackingPtr = std::make_unique<MyPiecePosition>(attackingPiecePos);
        }

        if (defenderPieceType == Piece::Joker) {
            defenderJokerPieceType = Piece::fromTypeRepToJRep(((JokerPiece *)gameBoard.board[pieceMove->getTo().getY()][pieceMove->getTo().getX()].get())->getJokerPiece());
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
            releasePiece1 = std::move(gameBoard.board[pieceMove->getTo().getY()][pieceMove->getTo().getX()]);
            releasePiece2 = std::move(gameBoard.board[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]);
        } else if (fightInfo->getWinner() == player) {
            releasePiece1 = std::move(gameBoard.board[pieceMove->getTo().getY()][pieceMove->getTo().getX()]);
            gameBoard.board[pieceMove->getTo().getY()][pieceMove->getTo().getX()] = std::move(gameBoard.board[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]);
        } else {
            releasePiece1 = std::move(gameBoard.board[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]);
        }
        return std::move(fightInfo);

    } else {
        char type = gameBoard.board[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()]->type;
        if (type == Piece::Joker) {
            char jokerType = ((JokerPiece *)gameBoard.board[pieceMove->getFrom().getY()][pieceMove->getFrom().getX()].get())->getJokerPiece();
            piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(type), player, Piece::getEnumTypeRep(jokerType));
        } else {
            piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(type), player);
        }
        gameBoard.board[pieceMove->getTo().getY()][pieceMove->getTo().getX()] = std::move(piecePtr);
    }
    return nullptr;
}

void GameManager::startGame(){
    unique_ptr<MyFightInfo> fightInfo;
    std::vector<unique_ptr<MyFightInfo>> fightInfoVec;
    std::vector<unique_ptr<PiecePosition>> vectorToFill_1;
    std::vector<unique_ptr<PiecePosition>> vectorToFill_2;
    player1Algoritm.getInitialPositions(1, vectorToFill_1);
    player2Algoritm.getInitialPositions(2, vectorToFill_2);

    for (unique_ptr<PiecePosition> &piecePos1: vectorToFill_1) {
        fightInfo = setPiece(piecePos1, 1);
        if (fightInfo.get() != nullptr) {
            fightInfoVec.push_back(std::move(fightInfo));
        }
    }

    for (unique_ptr<PiecePosition> &piecePos2: vectorToFill_2) {
        fightInfo = setPiece(piecePos2, 2);
        if (fightInfo.get() != nullptr) {
            fightInfoVec.push_back(std::move(fightInfo));
        }
    }
//    this->player1Algoritm.

    printBoard();

    /* TODO:
     *
     * notice that we change the player indexes from (0,1) to (1,2) {take place at parser line 122}
     * need to find the reason to the weird prints
     * check the SetPiece() for unique_ptr<Move> type (that will be done by writes the next instruction ->)
     * create a game move while loop int the StartGame()
     * handle and use all notify functions
     * create function to handle changeJokerSuit
     * remove all release() functions
     * create the AutoPlayer algorithm
     * check leak of memory
     * create new tests
     * fix print function (upper case)
     * SMILE!!!
     *
     * */
}
