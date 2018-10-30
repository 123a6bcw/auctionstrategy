#pragma once

#include "../BuyerStrategyAbstract.h"

class PSimple : PairingAbstract {
public:
     PSimple(int noc, vector<Buyer>& buyers) : PairingAbstract(noc, buyers) {};
     void makeChildrens();
}
