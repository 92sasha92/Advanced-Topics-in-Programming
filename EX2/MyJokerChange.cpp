#include "MyJokerChange.h"

const Point& MyJokerChange::getJokerChangePosition() const {
    return this->position;
}

char MyJokerChange::getJokerNewRep() const {
    return Piece::fromJRepToChar(this->newJokerRep);
}
