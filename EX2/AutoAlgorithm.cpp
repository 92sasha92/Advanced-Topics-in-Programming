#include "AutoAlgorithm.h"

AutoAlgorithm::AutoAlgorithm(): player(0), opponent(0), opponentNumOfFlags(RPS::F), isOpponentAttacked(false), lastMove(), selfGameBoard(){}

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
                if (this->selfGameBoard.board[row][col] == nullptr) {
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
                    selfGameBoard.board[row][col] = std::move(piecePtr);
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
            trash.push_back(std::move(selfGameBoard.board[fightInfo->getPosition().getY()][fightInfo->getPosition().getX()]));
            if (fightInfo->getWinner() == opponent) { // not a tie
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo->getPiece(opponent)), opponent);
                selfGameBoard.board[fightInfo->getPosition().getY()][fightInfo->getPosition().getX()] = std::move(piecePtr);
            }
        }
    }

    for (int i = 0; i < RPS::Nrows; i++) {
        for (int j = 0; j < RPS::Mcols; j++) {
            p.setX(j);
            p.setY(i);
            if (b.getPlayer(p) == opponent) {
                unique_ptr<Piece> piecePtr = std::make_unique<Piece>(opponent);
                selfGameBoard.board[i][j] = std::move(piecePtr);
            }
        }
    }
}

void AutoAlgorithm::notifyOnOpponentMove(const Move& move) { // TODO: check that move is legal
    if (this->selfGameBoard.board[move.getTo().getY()][move.getTo().getY()].get() != nullptr) {
        MyPoint pFrom(move.getFrom().getY(), move.getFrom().getX());
        MyPoint pTo(move.getTo().getY(), move.getTo().getX());
        lastMove.init(pFrom, pTo);
        isOpponentAttacked = true;
        return;
    }

    this->selfGameBoard.board[move.getTo().getY()][move.getTo().getY()] = std::move(this->selfGameBoard.board[move.getFrom().getY()][move.getFrom().getY()]);
    isOpponentAttacked = false;
}

void AutoAlgorithm::notifyFightResult(const FightInfo& fightInfo) {
    vector<unique_ptr<Piece>> trash;
    Piece::RPSPiecesTypes opponentType;

    if (fightInfo.getWinner() == TIE) {
        trash.push_back(std::move(selfGameBoard.board[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));
        trash.push_back(std::move(selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()]));

    } else if (isOpponentAttacked) { // player defend
        if (fightInfo.getWinner() == player) {
            trash.push_back(std::move(selfGameBoard.board[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));
        } else {
            opponentType = selfGameBoard.board[lastMove.getFrom().getY()][lastMove.getFrom().getX()]->type;
            trash.push_back(std::move(selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()]));

            if (opponentType == Piece::Undefined) {
                trash.push_back(std::move(selfGameBoard.board[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo.getPiece(opponent)), opponent);
                selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr);

            } else if ((opponentType != Piece::Joker) && (opponentType != Piece::getEnumTypeRep(fightInfo.getPiece(opponent)))){
                trash.push_back(std::move(selfGameBoard.board[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::Joker, opponent);
                selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr);

            } else {
                selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(selfGameBoard.board[lastMove.getFrom().getY()][lastMove.getFrom().getX()]);
            }
        }
    } else { // player attack
        if (fightInfo.getWinner() == opponent) {
            opponentType = selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()]->type;
            trash.push_back(std::move(selfGameBoard.board[lastMove.getFrom().getY()][lastMove.getFrom().getX()]));

            if (opponentType == Piece::Undefined) {
                trash.push_back(std::move(selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::getEnumTypeRep(fightInfo.getPiece(opponent)), opponent);
                selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr);

            } else if ((opponentType != Piece::Joker) && (opponentType != Piece::getEnumTypeRep(fightInfo.getPiece(opponent)))) {
                trash.push_back(std::move(selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()]));
                unique_ptr<Piece> piecePtr = PieceFactory::createPiece(Piece::Joker, opponent);
                selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(piecePtr);
            }
        } else {
            trash.push_back(std::move(selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()]));
            selfGameBoard.board[lastMove.getTo().getY()][lastMove.getTo().getX()] = std::move(selfGameBoard.board[lastMove.getFrom().getY()][lastMove.getFrom().getX()]);
        }
    }
}

unique_ptr<Move> AutoAlgorithm::getMove() {

    //TODO: lastMove = // update the move i do
    isOpponentAttacked = false;
    return nullptr;
}

unique_ptr<JokerChange> AutoAlgorithm::getJokerChange() {
    // TODO: change the joker that is the most threat to winner piece
    return nullptr;
}
