#include "../include/GeneticCycle.h"

/*
 * Main class of the project. There is sellers and buyers, each have genome - set of strategies (with parameters) implemented in BasicStrategies,
 * Runs cycle, on each step all players play with each other, then worst players replaces with childs creating via pairing class. All info are saving into log file via class StatisticCounter.
 * gets amount of players in cycle, amount of step in cycle, amount of steps in each playing game, how many players will die on each step of the cycle, two special function for creating
 * childs in population, and string --- name of log file.
*/

GeneticCycle :: GeneticCycle(size_t numberOfSellers, size_t numberOfBuyers, size_t _totalSteps, size_t _movesInGame, size_t _howMuchToKill, class PairingAbstract& pb, PairingAbstract& ps, std::string of) :
    totalSteps(_totalSteps), movesInGame(_movesInGame), howMuchToKill(_howMuchToKill) , pairBuyers(pb), pairSellers(ps), game(AuctionGame()), stats(StatisticCounter(std::move(of))) {
        sellers = std::vector<Player*>(numberOfSellers, new Seller(movesInGame));

        /*
         * TODO last parameter in Buyer is his inside profit. It's bad working version, SHOULD be changed later.
         */
        buyers = std::vector<Player*>(numberOfBuyers, new Buyer(movesInGame, rand() % 1000));
}

/*
 * clears amount of money each player won on the step of the cycle
 */
void GeneticCycle::clearProfit(std::vector<Player*>& players) {
    for (auto x : players) {
        x -> clearProfit();
    }
}

/*
 * destroying players with the worst result on each step of the cycle
 */
void GeneticCycle::destroyWorstPlayers(std::vector<Player*>& players) {
    if (howMuchToKill + 1 >= players.size()) {
        throw std::runtime_error("You asked to kill too many players - should be no more than amount of players - 1");
    }

    sort(players.begin(), players.end(), Player::byProfit()); //sorted by amount of money they won. Descending
    players.resize(players.size() - howMuchToKill);

    //TODO handle memory leak
}

/*
 * main cycle
 */
void GeneticCycle :: runCycle() {
    for (size_t t = 1; t <= totalSteps; t++) {
        clearProfit(buyers); //clear amount of money they won
        clearProfit(sellers);

        for (auto x : buyers) {
            stats.gather(dynamic_cast<Buyer*>(x));
            //There is base class Player with derived classes Buyer and Seller, vector buyers stores Player*, but in fact they all are class Buyer, so we can (have to) use dynamic_cast<>
            //here stats gathering info about which strategies each player uses.
        }

        for (auto y : sellers) {
            stats.gather(dynamic_cast<Seller*>(y));
        }

        for (auto x : buyers) {
            for (auto y : sellers) {
                // game is functor that plays game between two players and return vector of moves in this game --- pair of int price sets by Seller and bool that shows if deal was accepted
                // (also count how much money each player got)
                // then statistic are gathering.
               const std::vector<pmove> moves = game(dynamic_cast<Buyer*>(x), dynamic_cast<Seller*>(y), movesInGame);
               stats.gather(moves);
            }
        }

        destroyWorstPlayers(buyers);
        destroyWorstPlayers(sellers);

        pairBuyers(howMuchToKill, buyers); //appends child in quantity of how much was just killed
        pairSellers(howMuchToKill, sellers);
    }
}
