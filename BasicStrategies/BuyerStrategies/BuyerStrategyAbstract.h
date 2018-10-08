#pragma once

#include "../include/generalStates.h"
#include "../include/StrategyAbstract.h"

class BuyerStrategyAbstract: StrategyAbstract {
public:
    BuyerStrategyAbstract(int _profit, int _endMoves, vector&<pmove> prevMoves) : profit(_profit), StrategyAbstract(_endMove, prevMoves){};
    virtual bool acceptDeal(int) = delete;
protected:
    const int profit;
};
