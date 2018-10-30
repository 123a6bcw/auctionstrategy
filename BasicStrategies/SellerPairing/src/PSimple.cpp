#pragma once

#include "../include/PSimple.h"

void PSimple::makeChildrens() {
    vector<Seller> newChilds = findBestPlayers(players, numberOfChildrens);
    for (auto x : newChilds) {
        sellers.push_back(std::move(x));
    }
}
