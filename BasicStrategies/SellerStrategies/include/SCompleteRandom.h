#pragma once

/*
* Template for creating new seller strategy. Instruction inside SellerStrateies/src/template.cpp
*/

#define NAMEOFSTRATEGY SCompleteRandom

#include "../SellerStrategyAbstract.h"

class NAMEOFSTRATEGY : public SellerStrategyAbstract {
public:
    NAMEOFSTRATEGY(Player*, size_t, size_t, int, int); // declaration may change!
    void reset() override; // declaration immutable
    int setPrice() override; // declaration immutable
    std::string getDescription() override; // declaration immutable
    void randomParametersChange() override; // declaration immutable
    ~NAMEOFSTRATEGY() override; // declaration immutable
    std::string getName() override; // declaration immutable
    StrategyAbstract* copy(Player*) const override; // declaration immutable
private:
    explicit NAMEOFSTRATEGY(const NAMEOFSTRATEGY*); // declaration immutable
    int minValue;
    int maxValue;
};

#undef NAMEOFSTRATEGY
