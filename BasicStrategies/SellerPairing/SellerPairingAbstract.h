#pragma once

#include "../PairingAbstract.h"

class SellerPairingAbstract: PairingAbstract {
public:
    SellerPairingAbstract(int a, vector<Player>& pl) : PairingAbstract(a, pl) {};
    virtual void makeChildrens() = delete;
};
