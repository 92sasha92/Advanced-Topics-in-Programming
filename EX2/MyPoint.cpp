#include "MyPoint.h"

int MyPoint::getX() const{
    return this->x;
}

int MyPoint::getY() const{
    return this->y;
}

void MyPoint::setX(int x) {
    this->x = x;
}

void MyPoint::setY(int y) {
    this->y = y;
}

void MyPoint::setPoint(int x, int y) {
    setX(x);
    setY(y);
}

std::ostream &operator<<(std::ostream &os, const MyPoint& p){
    return os << "(" << p.getX() << ", "<< p.getY() << ")";
}