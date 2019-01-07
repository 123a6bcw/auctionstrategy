#pragma once

/*
 * player who accepts (or refuses) proposed deal.
 */

#include "./Player.h"
#include "../../BasicStrategies/BuyerStrategies/AllBuyerStrategies.h"

class Buyer : public Player {
public:
    Buyer() = delete;
    Buyer(size_t, int, RandomNumberGenerator*, StrategiesController*);
    bool acceptDeal(int price); //main function. Just throws this request to his current strategy and increment current move
    void addGain(int) override; // adds to his gain
    Player* copy() const override;
    ~Buyer() override;
private:
    explicit Buyer(const Buyer*);
    const int profit;
};