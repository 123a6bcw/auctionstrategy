#pragma once

/*
 * Simple strategy for pairing. Just creates copies of most successfull players
 */

#include "../PairingAbstract.h"

class PSimple : public PairingAbstract {
public:
    void operator () (size_t, std::vector<Player*>*) override;
    ~PSimple() override = default;
};