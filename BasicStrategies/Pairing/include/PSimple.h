#pragma once

#include "../PairingAbstract.h"

class PSimple : public PairingAbstract {
public:
    void operator () (size_t, std::vector<Player*>&) override;
};