#pragma once
#include "Move.h"
#include "MyPoint.h"
class MyMove: public Move {
private:
    MyPoint fPoint;
    MyPoint toPoint;
    bool isInitialized;
public:
    MyMove(): fPoint(-1, -1), toPoint(-1, -1), isInitialized(false){};
    MyMove(MyPoint &fPoint_, MyPoint &toPoint_): fPoint(fPoint_), toPoint(toPoint_), isInitialized(true){};
    const Point& getFrom() const override;
    const Point& getTo() const override;
    bool getIsInitialized() const;
    void setFrom(MyPoint &newFPoint);
    void setTo(MyPoint &newToPoint);
    void setInitializedTrue();
    void init(MyPoint &newFPoint, MyPoint &newToPoint);
};

