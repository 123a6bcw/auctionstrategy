#pragma once

/*
 * abstract class for Buyer's strategies. Each derived class should just implement virtual function acceptDeal() (aside of function demanding from AbstractStrategy)
 */

#include "../StrategyAbstract.h"
#include "../generalStates.h"

class BuyerStrategyAbstract: public StrategyAbstract {
public:
    BuyerStrategyAbstract(Player* player, size_t startMove, size_t endMove, int profit) : StrategyAbstract(player, startMove, endMove), profit(profit) {};
    virtual bool acceptDeal(int) = 0; // either accepts or refuse deal proposed by seller
protected:
    const int profit; //How much money buyer gain from buying product
    explicit BuyerStrategyAbstract(const BuyerStrategyAbstract* bsa) : StrategyAbstract(bsa), profit(bsa -> profit) {};
};
