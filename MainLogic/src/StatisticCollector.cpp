#include <thread>
#include "../include/StatisticCollector.h"
#include <map>
#include <set>
#include <iomanip>

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

StatisticCollector::StatisticCollector(std::string s, size_t ptrNumber, std::vector<std::vector<std::vector<pmove>>>* moves, size_t movesInGame) :
    partedStatisticCollector(ptrNumber, moves, &statsMutex),
    ptrNumber(ptrNumber),
    movesInGame(movesInGame)
    {
    out = std::fstream();
    out.open("../logs/" + s, std::fstream::out);
    if (!out.is_open()) {
        throw std::runtime_error("can't open log file");
    }
}

/*
 * initialisating statistic for new genetic cycle and clearing the old one
 */
void StatisticCollector::newStep(size_t i) {
    out << "CS " << i << "\n"; // CS means Current Cycle
    clean();
}

/*
 * clear all statistic from previous step of cycle
 */
void StatisticCollector::clean() {
    partedStatisticCollector.clean();
}

/*
 * Gathering statistic from moves vector (for example, amount of accepted deals) using threads and prints it to output file
 */
void StatisticCollector::gatherFromMoves() {
    threads.clear();
    for (size_t currentPart = 0; currentPart < ptrNumber; currentPart++) {
        threads.emplace_back(std::thread(&PartedStatisticCollector::partedGather, &partedStatisticCollector, partedStatisticCollector.parts[currentPart]));
    }

    for (auto& t : threads) {
        t.join();
    }

    out << "WS " << partedStatisticCollector.wasSold << "\n"; // WS = Was Sold
}


/*
 * prints s1 if (type == SELLER) and s2 otherwise
 */
void StatisticCollector::switchedPrint(typeOfPlayer type, std::string s1, std::string s2) {
    switch (type) {
        case SELLER:
            out << s1; //Sellers strategies overall
            break;
        case BUYER:
            out << s2; //Buyers strategies overall
            break;
        default:
            break;
    }
}


/*
 * collects statistic from vector of players. For instance, information about strategy usage
 */
void StatisticCollector::gather(std::vector<Player*>* players, typeOfPlayer type) {
    std::map<std::string, size_t> countMovesStrategies; // for each strategy (name) count total moves all players use it
    std::map<std::string, std::set<Player*>> countPlayersStrategies; //get set of players who plays using this strategy.
    for (const auto& s : (*players)) {
        for (const auto& str : *s->getStrategies()) {
            countMovesStrategies[str->getName()] += str->getMovesLength();
            countPlayersStrategies[str->getName()].insert(s);
        }
    }

    switchedPrint(type, "SSO", "BSO"); //seller strategies overall and buyer strategies overall

    for (const auto& x : countMovesStrategies) {
        out << " " << x.first << " " << x.second; // strategy name and usage length
    }
    out << "\n";

    switchedPrint(type, "SSP", "BSP"); //seller strategies players and buyer strategies players
    for (const auto& x : countPlayersStrategies) {
        out << " " << x.first << " " << x.second.size(); // strategy's name and players set size
    }
    out << "\n";
}

/*
 * Collects overall gain of players.
 */
void StatisticCollector::gatherGain(std::vector<Player*>* players, typeOfPlayer type) {
    switchedPrint(type, "SOG", "BOG"); //sellers (buyers) overall gain

    long long result = 0;
    for (const auto& x : (*players)) {
        result += x->getTotalGain();
    }
    out << " " << result << "\n";

    switchedPrint(type, "SAG", "BAG"); //sellers(buyers) average gain
    out << " " << std::setprecision(3) << std::fixed << (static_cast<double>(result)) / players->size() << "\n";

    switchedPrint(type, "SAGPG", "BAGPG"); //sellers(buyers) average gain per game
    out << " " << std::setprecision(3) << std::fixed << ((static_cast<double>(result)) / players->size()) / movesInGame << "\n";
}

StatisticCollector::~StatisticCollector() {
    out.close();
}