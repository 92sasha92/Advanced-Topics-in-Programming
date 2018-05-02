#pragma once

#include "JokerChange.h"
#include "MyPoint.h"
#include "Piece.h"

class MyJokerChange: public JokerChange{
private:
    MyPoint position;
    Piece::RPSJokerTypes newJokerRep;
    bool isInitialized;
public:
    MyJokerChange(): position(-1, -1), newJokerRep(Piece::JNotAJoker), isInitialized(false){};
    MyJokerChange(MyPoint& position_, Piece::RPSJokerTypes jokerRep_): position(position_), newJokerRep(jokerRep_), isInitialized(true){};
    const Point& getJokerChangePosition() const override;
    char getJokerNewRep() const override; // R, P, S or B (but NOT J and NOT F)
    bool getIsInitialized() const;
    void setInitializedTrue();
    void setPosition(MyPoint &position_);
    void setNewJokerRep(Piece::RPSJokerTypes newRep);
    bool init(MyPoint &position, Piece::RPSJokerTypes newJokerRep);
};



