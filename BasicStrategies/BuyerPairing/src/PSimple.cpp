#pragma once

#include "../include/PSimple.h"

void PSimple::makeChildrens() {
    vector<Buyer> newChilds = findBestPlayers(players, numberOfChildrens);
    for (auto x : newChilds) {
        buyers.push_back(std::move(x));
    }
}
