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

Piece::RPSPiecesTypes Piece::getEnumTypeRep(char type) {
    switch(type){
        case 'R':
            return Piece::Rock;
        case 'P':
            return Piece::Paper;
        case 'S':
            return Piece::Scissors;
        case 'B':
            return Piece::Bomb;
        case 'J':
            return Piece::Joker;
        case 'F':
            return Piece::Flag;
        default:
//            std::cout << "unsupported piece type" << std::endl;
            return Piece::Undefined;

    }
}

Piece::~Piece() {
}

char Piece::fromJRepToChar(Piece::RPSJokerTypes jokerRep) {
    switch(jokerRep){
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
