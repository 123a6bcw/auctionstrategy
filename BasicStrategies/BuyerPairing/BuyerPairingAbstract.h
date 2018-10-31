#pragma once

#include "../PairingAbstract.h"

class BuyerPairingAbstract: PairingAbstract {
public:
    BuyerPairingAbstract(int a, vector<Player>& pl) : PairingAbstract(a, pl) {};
    virtual void makeChildrens() = delete;
};
