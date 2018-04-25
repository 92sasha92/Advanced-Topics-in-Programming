//
// Created by sasha on 4/25/2018.
//

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

//std::ostream &operator<<(std::ostream &os, const MyPoint& p){
//    return os << "(" << p.getX() << ", "<< p.getY() << ")" << std::endl;
//}