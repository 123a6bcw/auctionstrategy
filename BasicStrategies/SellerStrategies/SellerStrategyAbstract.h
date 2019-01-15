#pragma once

/*
 * abstract class for strategy of seller. Each derived class should just implement virtual function setPrice() --- propose a deal to Buyer.
 */

#include "../StrategyAbstract.h"
#include "../generalStates.h"

class SellerStrategyAbstract : public StrategyAbstract {
public:
    SellerStrategyAbstract(Player* player, size_t startMove, size_t endMove) : StrategyAbstract(player, startMove, endMove) {};
    virtual int setPrice() = 0;
protected:
    explicit SellerStrategyAbstract(const SellerStrategyAbstract* sellerStrategyAbstract) : StrategyAbstract(sellerStrategyAbstract) {};
};
