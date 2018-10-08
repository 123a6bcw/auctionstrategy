#pragma once

#include "./StrategyAbstract.h"

class Player {
public:
     Player();
     StrategyAbstract& getCurrentStrategy();
protected:
    int currentMove;
    int currentStrategy;
    vector<StrategyAbstract> strategies;
    
    void shiftMove();
}
