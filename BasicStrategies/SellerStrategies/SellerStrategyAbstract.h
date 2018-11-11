#pragma once

/*
 * abstract class for strategy of seller. Each derived class should just implement virtual function setPrice() --- propose a deal to Buyer.
 */

#include "../generalStates.h"
#include "../StrategyAbstract.h"

class SellerStrategyAbstract : public StrategyAbstract {
public:
    SellerStrategyAbstract(Player* p, size_t _startMove, size_t _endMove) : StrategyAbstract(p, _startMove, _endMove) {};
    virtual int setPrice() = 0;
protected:
    explicit SellerStrategyAbstract(const SellerStrategyAbstract* ssa) : StrategyAbstract(ssa) {};
};
