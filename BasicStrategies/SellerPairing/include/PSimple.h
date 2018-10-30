#pragma once

#include "../BuyerStrategyAbstract.h"

class PSimple : PairingAbstract {
public:
     PSimple(int noc, vector<Seller>& sellers) : PairingAbstract(noc, sellers) {};
     void makeChildrens();
}
