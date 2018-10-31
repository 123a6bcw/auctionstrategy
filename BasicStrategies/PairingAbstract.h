#pragma once

namespace Pairing {

void PairingAbstract {
public:
    virtual void operator () (int numberOfChildrens, vector<Player>& players) = delete; 
}

}
