#include "MyJokerChange.h"

const Point& MyJokerChange::getJokerChangePosition() const {
    return this->position;
}

char MyJokerChange::getJokerNewRep() const {
    return Piece::fromJRepToChar(this->newJokerRep);
}

bool MyJokerChange::getIsInitialized() const {
    return this->isInitialized;
}

void MyJokerChange::setInitializedTrue() {
    this->isInitialized = true;
}

void MyJokerChange::setPosition(MyPoint &position_) {
    this->position.setX(position_.getX());
    this->position.setY(position_.getY());
}

void MyJokerChange::setNewJokerRep(Piece::RPSJokerTypes newRep) {
    this->newJokerRep = newRep;
}
bool MyJokerChange::init(MyPoint &position, Piece::RPSJokerTypes newRep) {
    if (newRep == Piece::JNotAJoker) {
        return false;
    }
    this->setPosition(position);
    this->setNewJokerRep(newRep);
    this->setInitializedTrue();
    return true;
}

void MyJokerChange::setInitialized(bool init) {
    this->isInitialized = init;
}