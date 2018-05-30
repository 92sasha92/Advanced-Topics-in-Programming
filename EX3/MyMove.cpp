#include "MyMove.h"

const Point& MyMove::getFrom() const {
    return this->fPoint;
}

const Point& MyMove::getTo() const {
    return this->toPoint;
}

bool MyMove::getIsInitialized() const {
    return this->isInitialized;
}

void MyMove::setFrom(MyPoint &newFPoint) {
    this->fPoint.setX(newFPoint.getX());
    this->fPoint.setY(newFPoint.getY());
}

void MyMove::setTo(MyPoint &newToPoint) {
    this->toPoint.setX(newToPoint.getX());
    this->toPoint.setY(newToPoint.getY());
}

void MyMove::setInitializedTrue() {
    this->isInitialized = true;
}

void MyMove::init(MyPoint &newFPoint, MyPoint &newToPoint) {
    this->setFrom(newFPoint);
    this->setTo(newToPoint);
    this->setInitializedTrue();
}
