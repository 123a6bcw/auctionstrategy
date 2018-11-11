#pragma once

#include "../BuyerStrategyAbstract.h"

class BSimple : public BuyerStrategyAbstract {
public:
     BSimple(Player* p, size_t _startMove, size_t _endMove, int _profit) : BuyerStrategyAbstract(p, _startMove, _endMove, _profit) {};
     bool acceptDeal(int) override;
     void randomParametersChange() override;
};
