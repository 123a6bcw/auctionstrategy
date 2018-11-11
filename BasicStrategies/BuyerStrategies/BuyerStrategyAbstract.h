#pragma once

#include "../generalStates.h"
#include "../StrategyAbstract.h"

class BuyerStrategyAbstract: public StrategyAbstract {
public:
    BuyerStrategyAbstract(Player* p, size_t _startMove, size_t _endMove, int _profit) : StrategyAbstract(p, _startMove, _endMove), profit(_profit) {};
    virtual bool acceptDeal(int) = 0;
protected:
    const int profit;
};
