#pragma once

namespace Buyer {

#include "../BuyerStrategies/AllBuyerStrategies.h"
#include "./Player.h"

class Buyer:Player {
public:
    Buyer();
    bool acceptDeal(int price);
    void addProfit();
private:
    int profit;
};

}
