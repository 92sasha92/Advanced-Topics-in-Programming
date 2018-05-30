#include "MyFightInfo.h"


MyFightInfo::MyFightInfo(MyPoint &point_, Piece::RPSPiecesTypes piece_1, Piece::RPSPiecesTypes piece_2, int winner_): point(point_), piece1(piece_1), piece2(piece_2), winner(winner_) {}

const Point& MyFightInfo::getPosition() const{
    return point;
}

char MyFightInfo::getPiece(int player) const{
    if (player == 1) {
        return Piece::getCharTypeRep(piece1);
    } else if (player == 2) {
        return Piece::getCharTypeRep(piece2);
    }
    std::cout << "unsupported player number" << std::endl;
    return '#';
}

int MyFightInfo::getWinner() const {
    return winner;
}

void MyFightInfo::setWinner(int winner_) {
    winner = winner_;
}