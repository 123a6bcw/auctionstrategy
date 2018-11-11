#pragma once

#include <vector>
#include "../../Player/include/Buyer.h"

class PairingAbstract {
public:
    virtual void operator () (size_t, std::vector<Player*>&) = 0;
};
