#include "Piece.h"

Piece::Piece(int player) : type(Undefined), playerNumber(player), canMove(true) {
}

int Piece::getPlayerNumber() {
    return this->playerNumber;
}

int Piece::getCanMove()
{
	return this->canMove;
}

void Piece::setCanMove(bool isMovable)
{
	this->canMove = isMovable;
}

std::string Piece::toString()
{
    return "base class";
}

Piece::PiecesPower Piece::isStrongerThan(const Piece& rival) {
    return this->strongerThan[rival.type];
}

char Piece::getCharTypeRep(Piece::RPSPiecesTypes type) {
    switch(type){
        case Piece::Rock:
            return 'R';
        case Piece::Paper:
            return 'P';
        case Piece::Scissors:
            return 'S';
        case Piece::Bomb:
            return 'B';
        case Piece::Joker:
            return 'J';
        case Piece::Flag:
            return 'F';
        default:
        std::cout << "unsupported piece type" << std::endl;
            return '#';

    }
}
Piece::~Piece() {
}
