#include <iostream>

class Piece {
  private:
    int playerNumber;
  public:
		Piece(int playerNumber);
		int getPlayerNumber();
		virtual void toString();

};