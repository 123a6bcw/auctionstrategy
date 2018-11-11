#pragma once

#include "../generalStates.h"
#include "../StrategyAbstract.h"

class SellerStrategyAbstract : public StrategyAbstract {
public:
    SellerStrategyAbstract(Player* p, size_t _startMove, size_t _endMove) : StrategyAbstract(p, _startMove, _endMove) {};
    virtual int setPrice() = 0;
};
