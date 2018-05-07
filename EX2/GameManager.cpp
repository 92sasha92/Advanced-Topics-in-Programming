#include "GameManager.h"


GameManager::GameManager(PlayerAlgorithm &player1Algoritm_, PlayerAlgorithm &player2Algoritm_): player1Algoritm(player1Algoritm_), player2Algoritm(player2Algoritm_), gameBoard() {
    startGame();
}

unique_ptr<MyFightInfo> GameManager::fight(unique_ptr<PiecePosition> player1PiecePos, unique_ptr<PiecePosition> player2PiecePos) {
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

void GameManager::startGame(){
    std::vector<unique_ptr<PiecePosition>> vectorToFill_1;
    std::vector<unique_ptr<PiecePosition>> vectorToFill_2;
    player1Algoritm.getInitialPositions(1, vectorToFill_1);
    player2Algoritm.getInitialPositions(2, vectorToFill_2);
}
