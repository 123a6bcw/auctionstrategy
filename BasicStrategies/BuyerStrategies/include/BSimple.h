#pragma once

/*
 * simplest strategy for buyer. Accepts deal if his gain isn't negative.
 */

#include "../BuyerStrategyAbstract.h"

class BSimple : public BuyerStrategyAbstract {
public:
     BSimple(Player* p, size_t _startMove, size_t _endMove, int _profit) : BuyerStrategyAbstract(p, _startMove, _endMove, _profit) {};
     bool acceptDeal(int) override;
     void randomParametersChange() override;
     void reset() override;
     StrategyAbstract* copy(Player*) const override;
     ~BSimple() override;
     std::string getName() override;
     std::string getDescription() override;
private:
     explicit BSimple(const BSimple*);
};
