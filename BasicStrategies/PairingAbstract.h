#pragma once

namespace Pairing {

void PairingAbstract {
public:
    PairingAbstract(int a, vector<Player>& pl) : numberOfChildrens(a), players(pl) {};
    virtual void makeChildrens() = deleted;
private:
    int numberOfChildrens;
    vector<Player>& players;    
}

}
