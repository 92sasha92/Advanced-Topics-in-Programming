#include "MyPiecePosition.h"


const Point& MyPiecePosition::getPosition() const{
    return this->position;
}

char MyPiecePosition::getPiece() const {
    return Piece::getCharTypeRep(this->type);
}

char MyPiecePosition::getJokerRep() const {
    switch(this->jokerRep){
        case Piece::JRock:
            return Piece::getCharTypeRep(Piece::Rock);
        case Piece::JPaper:
            return Piece::getCharTypeRep(Piece::Paper);
        case Piece::JScissors:
            return Piece::getCharTypeRep(Piece::Scissors);
        case Piece::JBomb:
            return Piece::getCharTypeRep(Piece::Bomb);
        default:
            return '#';
    }
}
