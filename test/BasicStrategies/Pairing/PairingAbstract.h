#pragma once

/*
 * abstract functor that creates childs in population. Derived functors should realise operator () with some specific strategy for pairing.
 */

#include <vector>
#include "../../Player/include/Buyer.h"

class PairingAbstract {
public:
    virtual void operator () (size_t, std::vector<Player*>*) = 0;
    virtual ~PairingAbstract() = default;
};
