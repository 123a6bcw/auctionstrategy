#include "../include/GeneticCycle.h"
#include "../../BasicStrategies/StrategiesController.h"

/*
 * Main class of the project. There is sellers and buyers, each have genome - set of strategies (with parameters) implemented in BasicStrategies,
 * Runs cycle, on each step all players play with each other, then worst players replaces with childs creating via pairing class. All info are saving into log file via class StatisticCounter.
 * gets amount of players in cycle, amount of step in cycle, amount of steps in each playing game, how many players will die on each step of the cycle, two special function for creating
 * childs in population, and string --- name of log file.
*/

GeneticCycle :: GeneticCycle(size_t numberOfSellers, size_t numberOfBuyers, size_t _totalSteps, size_t _movesInGame, size_t _howMuchToKill,
        size_t numberOfBuyerPairing, size_t numberOfSellerPairing, std::string of, size_t _ptrNumber) :
    totalSteps(_totalSteps), movesInGame(_movesInGame), howMuchToKill(_howMuchToKill), randomNumberGenerator(67), ptrNumber(_ptrNumber),
    moves(std::vector<std::vector<std::vector<pmove>>>(numberOfSellers, std::vector<std::vector<pmove>>(numberOfBuyers, std::vector<pmove>(0)))),
    stats(std::move(of), _ptrNumber, &moves, _movesInGame), controller(StrategiesController(&randomNumberGenerator)) {
        pairSellers = controller . createPairing(numberOfSellerPairing, SELLER);
        pairBuyers  = controller . createPairing(numberOfBuyerPairing, BUYER);

        sellers = std::vector<Player*>(0);
        for (size_t i = 0; i < numberOfSellers; i++) {
            sellers.push_back(new Seller(_movesInGame, &randomNumberGenerator, &controller));
        }

        buyers = std::vector<Player*>(0);
        for (size_t i = 0; i < numberOfBuyers; i++) {
            buyers.push_back(new Buyer(_movesInGame, randomNumberGenerator . getRandomInt() % 1000, &randomNumberGenerator, &controller));
              //TODO random parameter is buyer's inside profit. Is this OK to just make it random?
        }

        if (numberOfBuyers < ptrNumber || numberOfSellers < ptrNumber) {
            throw(std::runtime_error("Genetic Cycle: number of buyers or sellers should be at least 10"));
        }

        createPartition(numberOfSellers, ptrNumber, &sellersParts);
        createPartition(numberOfBuyers, ptrNumber, &buyersParts);
}

/*
 * Creates partition: split players with number from 1 to "numberOfPlayers" into "partsNumber" equal (possibly except the last one) parts,
 * store in vector "parts" beginning and ending of each part: players in range [start, end) -> pair(start, end).
 */
void GeneticCycle::createPartition(size_t numberOfPlayers, size_t partsNumber, std::vector<std::pair<size_t, size_t>>* parts) const {
    size_t playersInPart = numberOfPlayers / partsNumber;
    size_t startPlayer = 0;
    for (size_t i = 0; i < partsNumber; i++) {
        size_t endPlayer = startPlayer + playersInPart;
        if (i + 1 == partsNumber) {
            endPlayer = numberOfPlayers; // last part can be larger if (numberOfPlayers `mod` partsNumber != 0)
        }

        parts->push_back({startPlayer, endPlayer});
        startPlayer += playersInPart;
    }
}

/*
 * clears amount of money each player won on the step of the cycle
 */
void GeneticCycle::clearProfit(std::vector<Player*>& players) const {
    for (auto& x : players) {
        x -> clearGain();
    }
}

/*
 * destroying players with the worst result on each step of the cycle
 */
void GeneticCycle::destroyWorstPlayers(std::vector<Player *> &players) {
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

/*
 * each player in given parts plays with each other. That way we can parallel this process
 */
void GeneticCycle::runPartedCycle(size_t sellerPart, size_t buyerPart) {
    AuctionGame game;

    for (size_t s = sellersParts[sellerPart].first; s < sellersParts[sellerPart].second; s++) {
        for (size_t b = buyersParts[buyerPart].first; b < buyersParts[buyerPart].second; b++) {
            game(sellers[s], buyers[b], movesInGame, &moves[s][b]);
        }
    }
}

/*
 * main cycle
 */
void GeneticCycle :: runCycle() {
    for (size_t currentStep = 0; currentStep < totalSteps; currentStep++) {
        clearProfit(sellers); //clear amount of money they won on previous step
        clearProfit(buyers);

        stats.newStep(currentStep);
        stats.gather(sellers, SELLER); //collects some sort of statistic
        stats.gather(buyers, BUYER);

        std::vector<std::thread> threads(0);
        for (size_t shift = 0; shift < ptrNumber; shift++) {
            /*
             * for given shift for each x, sellers in part x plays with buyers in part (x + shift) % numberOfParts
             * That way everyone plays with everyone, but for given shift, all players in parts are disjoint, so we can
             * use threads to parallel this process
             */

            threads.clear();
            for (size_t sellerPart = 0; sellerPart < sellersParts.size(); sellerPart++) {
                size_t buyerPart = (sellerPart + shift) % buyersParts.size();
                threads.emplace_back(std::thread(&GeneticCycle::runPartedCycle, this, sellerPart, buyerPart));
            }

            for (auto& t : threads) {
                t.join();
            }
        }

        stats.gatherFromMoves();
        stats.gatherGain(sellers, SELLER);
        stats.gatherGain(buyers, BUYER);

        destroyWorstPlayers(sellers);
        destroyWorstPlayers(buyers);
        (*pairSellers)(howMuchToKill, &sellers);
        (*pairBuyers)(howMuchToKill, &buyers); //appends child in quantity of how much was just killed
    }
}

GeneticCycle::~GeneticCycle() {
    for (auto& x : buyers) {
        delete x;
    }

    for (auto& y : sellers) {
        delete y;
    }

    delete pairBuyers;
    delete pairSellers;
}
