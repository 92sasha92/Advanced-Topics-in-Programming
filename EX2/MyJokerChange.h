#pragma once

#include "JokerChange.h"
#include "MyPoint.h"
#include "Piece.h"

class MyJokerChange: public JokerChange{
private:
    MyPoint position;
    Piece::RPSJokerTypes newJokerRep;

public:
    MyJokerChange(MyPoint& position_, Piece::RPSJokerTypes jokerRep_): position(position_), newJokerRep(jokerRep_){};
    const Point& getJokerChangePosition() const override;
    char getJokerNewRep() const override; // R, P, S or B (but NOT J and NOT F)
};



