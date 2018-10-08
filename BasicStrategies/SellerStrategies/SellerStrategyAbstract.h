#pragma once

#include "../include/generalStates.h"
#include "../include/StrategyAbstract.h"

class SellerStrategyAbstract: StrategyAbstract {
public:
    virtual int setPrice() = delete;
};
