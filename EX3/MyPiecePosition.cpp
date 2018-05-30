#include "MyPiecePosition.h"


const Point& MyPiecePosition::getPosition() const{
    return this->position;
}

char MyPiecePosition::getPiece() const {
    return Piece::getCharTypeRep(this->type);
}

char MyPiecePosition::getJokerRep() const {
    return Piece::fromJRepToChar(this->jokerRep);
}
