#pragma once

namespace Player {

#include "./StrategyAbstract.h"

class Player {
public:
     Player();
     StrategyAbstract& getCurrentStrategy();
protected:
    int currentMove;
    int currentStrategy;
    int totalProfit;
    vector<StrategyAbstract> strategies;
    
    void shiftMove();
}

}
