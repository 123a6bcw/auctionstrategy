//
// Created by mistafrosty on 15.01.19.
//

#include "../include/PlayersHandler.h"

PlayersHandler::PlayersHandler(size_t seed, size_t movesInGame, size_t howMuchToKill, size_t scenarioNumber,
        size_t numberOfSellerPairing, size_t numberOfBuyerPairing, size_t numberOfSellers, size_t numberOfBuyers):
    randomNumberGenerator(seed),
    controller(StrategiesController(&randomNumberGenerator)),
    movesInGame(movesInGame),
    howMuchToKill(howMuchToKill),
    scenarioNumber(scenarioNumber),
    buyers(std::vector<Player*>(0)),
    sellers(std::vector<Player*>(0)),
    pairSellers(controller.createPairing(numberOfSellerPairing, SELLER)),
    pairBuyers(controller.createPairing(numberOfBuyerPairing, BUYER))
    {
    switch (scenarioNumber) {
        case 0:
            throw std::runtime_error("Wrong scenario number");
            break;
        case 1:
            createStandartScenario(numberOfSellers, numberOfBuyers);
            break;
        default:
            throw std::runtime_error("Wrong scenario number");
            break;
    }
}

/*
 * TODO: comment
 */
void PlayersHandler::clearProfit() {
    clearProfit(sellers);
    clearProfit(buyers);
}

/*
 * clears amount of money each player won on the step of the cycle
 */
void PlayersHandler::clearProfit(std::vector<Player*>& players) {
    for (auto& x : players) {
        x -> clearGain();
    }
}

/*
 * destroying players with the worst result on each step of the cycle
 */
void PlayersHandler::destroyWorstPlayers(std::vector<Player *> &players) {
    if (howMuchToKill + 1 >= players.size()) {
        throw std::runtime_error("You asked to kill too many players - should be no more than amount of players - 1");
    }

    sort(players.begin(), players.end(), Player::byGain()); //sorted by amount of money they won. Ascending
    reverse(players.begin(), players.end());
    for (size_t i = players.size() - howMuchToKill; i < players.size(); i++) {
        delete players[i];
    }
    players.resize(players.size() - howMuchToKill);
}

PlayersHandler::~PlayersHandler() {
    for (auto& x : buyers) {
        delete x;
    }

    for (auto& y : sellers) {
        delete y;
    }

    delete pairBuyers;
    delete pairSellers;
}

void PlayersHandler::createStandartScenario(size_t numberOfSellers, size_t numberOfBuyers) {
    sellers = std::vector<Player*>(0);
    for (size_t i = 0; i < numberOfSellers; i++) {
    sellers.push_back(new Seller(movesInGame, &randomNumberGenerator, &controller));
    }

    buyers = std::vector<Player*>(0);
    for (size_t i = 0; i < numberOfBuyers; i++) {
    buyers.push_back(new Buyer(movesInGame, randomNumberGenerator . getRandomInt() % 1000, &randomNumberGenerator, &controller));
    //TODO random parameter is buyer's inside profit. Is this OK to just make it random?
    }
}

void PlayersHandler::pairPlayers() {
    destroyWorstPlayers(sellers);
    destroyWorstPlayers(buyers);
    (*pairSellers)(howMuchToKill, &sellers);
    (*pairBuyers)(howMuchToKill, &buyers); //appends child in quantity of how much was just killed
}