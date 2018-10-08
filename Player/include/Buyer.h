#pragma once

#include "../BuyerStrategies/AllBuyerStrategies.h"
#include "./Player.h"

class Buyer:Player {
public:
    Buyer();
    bool acceptDeal(int price);
private:
    int profit;
};
