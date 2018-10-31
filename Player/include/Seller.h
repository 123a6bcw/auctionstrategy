#pragma once

namespace Seller {

#include "../SellerStrategies/AllSellerStrategies.h"
#include "./Player.h"

class Seller:Player {
public:
    int setPrice();
    void addProfit(int);
}

}
