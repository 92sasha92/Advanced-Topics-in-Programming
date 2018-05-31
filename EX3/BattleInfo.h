#pragma once

#include "BattleInfo.h"
#include <string>

class BattleInfo {
  private:
    std::string id1, id2;
    bool isAlgo1BattleCount, isAlgo2BattleCount;

  public:
    BattleInfo(std::string id1_, std::string id2_, bool isAlgo1BattleCount_, bool isAlgo2BattleCount_) : id1(id1_), id2(id2_), isAlgo1BattleCount(isAlgo1BattleCount_), isAlgo2BattleCount(isAlgo2BattleCount_) {}
    std::string getId1();
    std::string getId2();
    bool getIsAlgo1BattleCount();
    bool getIsAlgo2BattleCount();
};



