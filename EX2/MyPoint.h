#pragma once

#include "Point.h"
#include <iostream>

class MyPoint: public Point{
private:
    int x;
    int y;
public:
    MyPoint(int x_, int y_): x(x_), y(y_){};
    virtual int getX() const override;
    virtual int getY() const override;
    void setX(int x);
    void setY(int y);
    //friend std::ostream &operator<<(std::ostream &os, const MyPoint& p);
};



