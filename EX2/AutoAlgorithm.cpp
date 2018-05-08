#include "AutoAlgorithm.h"

AutoAlgorithm::AutoAlgorithm(): player(0), opponent(0), opponentNumOfFlags(RPS::F), selfGameBoard(){}

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

void AutoAlgorithm::notifyOnOpponentMove(const Move& move) {

}

void AutoAlgorithm::notifyFightResult(const FightInfo& fightInfo) {

}

unique_ptr<Move> AutoAlgorithm::getMove() {
    return nullptr;
}

unique_ptr<JokerChange> AutoAlgorithm::getJokerChange() {
    return nullptr;
}
