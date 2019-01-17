#pragma once

/*
 * Player who sets price and proposes deal to buyer
 */

#include "../../BasicStrategies/SellerStrategies/AllSellerStrategies.h"
#include "./Player.h"

class Seller : public Player {
public:
    Seller() = delete;
    explicit Seller(size_t, RandomNumberGenerator*, StrategiesController*);
    explicit Seller(size_t, RandomNumberGenerator*, StrategiesController*, std::vector<StrategyAbstract*>*);
    int setPrice(); //proposes deal to buyer
    void addGain(int) override; // adds how much money he gain
    Player* copy() const override;
    ~Seller() override;
private:
    explicit Seller(const Seller*);
};