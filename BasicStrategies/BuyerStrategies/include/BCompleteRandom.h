#pragma once

/*
 * Here's template for creating buyer's strategies. Define NAMEOFSTRATEGY
 */

#include "../BuyerStrategyAbstract.h"

#define NAMEOFSTRATEGY BCompleteRandom

class NAMEOFSTRATEGY : public BuyerStrategyAbstract {
public:
     NAMEOFSTRATEGY(Player*, size_t, size_t, int); // Declaration may change!
     void reset() override; // declaration immutable
     bool acceptDeal(int) override; // declaration immutable
     std::string getDescription() override; // declaration immutable
     void randomParametersChange() override; // declaration immutable
     ~NAMEOFSTRATEGY() override; // declaration immutable
     std::string getName() override; // declaration immutable
    StrategyAbstract* copy(Player*) const override; // declaration immutable
private:
     explicit NAMEOFSTRATEGY(const NAMEOFSTRATEGY*); // declaration immutable
};

#undef NAMEOFSTRATEGY
