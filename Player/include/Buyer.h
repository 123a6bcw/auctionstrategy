#pragma once

#include "../../BasicStrategies/BuyerStrategies/AllBuyerStrategies.h"
#include "./Player.h"

class Buyer : public Player {
public:
    Buyer() = delete;
    Buyer(size_t, int);
    bool acceptDeal(int price);
    void addProfit(int) override;
private:
    int profit;
};