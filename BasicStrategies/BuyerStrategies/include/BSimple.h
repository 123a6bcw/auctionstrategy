#pragma once

/*
 * simplest strategy for buyer. Accepts deal if his gain isn't negative.
 */

#include "../BuyerStrategyAbstract.h"

class BSimple : public BuyerStrategyAbstract {
public:
     BSimple(Player* player, size_t startMove, size_t endMove, int profit) : BuyerStrategyAbstract(player, startMove, endMove, profit) {};
     void reset() override;
     bool acceptDeal(int) override;
     void randomParametersChange() override;
     std::string getDescription() override;
    StrategyAbstract* copy(Player*) const override;
    std::string getName() override;
    ~BSimple() override;
private:
     explicit BSimple(const BSimple*);
};
