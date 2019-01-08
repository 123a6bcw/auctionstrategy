#pragma once

/*
 * Here's template for creating buyer's strategies. Define NAMEOFSTRATEGY
 */

#include "../BuyerStrategyAbstract.h"

#define NAMEOFSTRATEGY BIncreaseProfit
class NAMEOFSTRATEGY : public BuyerStrategyAbstract {
public:
     NAMEOFSTRATEGY(Player* p, size_t _startMove, size_t _endMove, int _profit, int, size_t); // Declaration may change!
     bool acceptDeal(int) override; // declaration immutable
     void randomParametersChange() override; // declaration immutable
     void reset() override; // declaration immutable
     StrategyAbstract* copy(Player*) const override; // declaration immutable
     ~NAMEOFSTRATEGY() override; // declaration immutable
     std::string getName() override; // declaration immutable
     std::string getDescription() override; // declaration immutable
private:
     explicit NAMEOFSTRATEGY(const NAMEOFSTRATEGY*); // declaration immutable
     int falseProfit;
     size_t pretendMovesLength;
     size_t pretendMovesLeft;
};

#undef NAMEOFSTRATEGY
