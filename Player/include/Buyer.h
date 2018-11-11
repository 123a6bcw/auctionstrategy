#pragma once

/*
 * player who accepts (or refuses) proposed deal.
 */

#include "../../BasicStrategies/BuyerStrategies/AllBuyerStrategies.h"
#include "./Player.h"

class Buyer : public Player {
public:
    Buyer() = delete;
    Buyer(size_t, int); //moves in one game and his inside profit
    bool acceptDeal(int price); //main function. Just throws this request to his current strategy and increment current move
    void addGain(int) override; // adds to his gain
    Player* copy() const override;
private:
    const int profit;
    explicit Buyer(const Buyer*);
};