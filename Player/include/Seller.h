#pragma once

#include "../../BasicStrategies/SellerStrategies/AllSellerStrategies.h"
#include "./Player.h"

class Seller : public Player {
public:
    Seller() = delete;
    explicit Seller(size_t);
    int setPrice();
    void addProfit(int) override;
};