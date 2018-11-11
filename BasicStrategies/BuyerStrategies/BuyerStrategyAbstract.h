#pragma once

/*
 * abstract class for Buyer's strategies. Each derived class should just implement virtual function acceptDeal() (aside of function demanding from AbstractStrategy)
 */

#include "../generalStates.h"
#include "../StrategyAbstract.h"

class BuyerStrategyAbstract: public StrategyAbstract {
public:
    BuyerStrategyAbstract(Player* p, size_t _startMove, size_t _endMove, int _profit) : StrategyAbstract(p, _startMove, _endMove), profit(_profit) {};
    virtual bool acceptDeal(int) = 0; // either accepts or refuse deal proposed by seller
protected:
    const int profit; //How much money buyer gain from buying product
    explicit BuyerStrategyAbstract(const BuyerStrategyAbstract* bsa) : StrategyAbstract(bsa), profit(bsa -> profit) {};
};
