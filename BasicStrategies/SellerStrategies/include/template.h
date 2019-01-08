#pragma once

/*
* Template for creating new seller strategy. Instruction inside SellerStrateies/src/template.cpp
*/

#include "../SellerStrategyAbstract.h"

#define NAMEOFSTRATEGY ???

class NAMEOFSTRATEGY : public SellerStrategyAbstract {
public:
    NAMEOFSTRATEGY(Player*, size_t, size_t); // declaration may change!
    int setPrice() override; // declaration immutable
    void reset() override; // declaration immutable
    void randomParametersChange() override; // declaration immutable
    ~NAMEOFSTRATEGY() override; // declaration immutable
    std::string getName() override; // declaration immutable
    std::string getDescription() override; // declaration immutable
    StrategyAbstract* copy(Player*) const override; // declaration immutable
private:
    explicit NAMEOFSTRATEGY(const NAMEOFSTRATEGY*); // declaration immutable
};

#undef NAMEOFSTRATEGY
