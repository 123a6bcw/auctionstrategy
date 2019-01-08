#pragma once

/*
* Template for creating pairing function. Instruction inside template.cpp
*/

#include "../PairingAbstract.h"

#define NAMEOFPAIRING PSmt

class NAMEOFPAIRING : public PairingAbstract {
public:
    void operator () (size_t, std::vector<Player*>*) override;
    ~NAMEOFPAIRING() override;
};

#undef NAMEOFPAIRING
