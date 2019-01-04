#include "../include/PSimple.h"

void PSimple::operator () (size_t numberOfChildrens, std::vector<Player*>* players) {
    std::vector<Player*> newChilds = Player::findBestPlayers(numberOfChildrens, players);
    for (auto x : newChilds) {
        players -> push_back(x -> copy());
    }
}