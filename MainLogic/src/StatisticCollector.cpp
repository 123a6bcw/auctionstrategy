#include <thread>
#include "../include/StatisticCollector.h"
#include <map>
#include <set>
#include <iomanip>

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

StatisticCounter::StatisticCounter(std::string s, size_t ptrNumber, std::vector<std::vector<std::vector<pmove>>>* moves, size_t movesInGame) :
    ptrNumber(ptrNumber),
    moves(moves),
    parts(std::vector<std::vector<std::vector<std::vector<pmove>>*>>(ptrNumber, std::vector<std::vector<std::vector<pmove>>*>(0,
                                                                                                                    nullptr))),
    movesInGame(movesInGame)
    {
    out = std::fstream();
    out.open("../logs/" + s, std::fstream::out);
    if (!out.is_open()) {
        throw std::runtime_error("can't open log file");
    }

    sellersInThread = moves->size() / ptrNumber;
    createPartition();
}

/*
 * from vector<vector<vector<pmove>>> moves creates new vector with size equal to number of threads. Each element is vector
 * with pointers to vector<vector<pmove>> aka moves[s] for s in range of this part.
 * That way we can create threads so they wouldn't had to access "moves" --- otherwise, several threads would access "moves" and, therefore, won't work in parallel
 */
void StatisticCounter::createPartition() {
    size_t startSeller = 0;
    for (size_t currentPart = 0; currentPart < ptrNumber; currentPart++) {
        size_t endSeller = startSeller + sellersInThread;
        if (currentPart + 1 == ptrNumber) {
            endSeller = moves->size();
        }

        for (size_t seller = startSeller; seller < endSeller; seller++) {
            parts[currentPart].push_back(&(*moves)[seller]);
        }

        startSeller += sellersInThread;
    }
}


/*
 * initialisating statistic for new genetic cycle and clearing the old one
 */
void StatisticCounter::newStep(size_t i) {
    out << "CS " << i << "\n"; // CS means Current Cycle
    clean();
}

/*
 * clear all statistic from previous step of cycle
 */
void StatisticCounter::clean() {
    wasSold = 0;
}

/*
 * Collecting all statistic from given part of moves and store result in fields of this class
 */
void StatisticCounter::partedGather(const std::vector<std::vector<std::vector<pmove>>*>& partedMoves) {
    int newSold = 0;

    for (size_t seller = 0; seller < partedMoves.size(); seller++) {
        for (size_t buyer = 0; buyer < partedMoves[seller]->size(); buyer++) {
            for (auto &x : (*partedMoves[seller])[buyer]) {
                newSold += x.wasSold();
            }
        }
    }

    statsMutex.lock();
    wasSold += newSold;
    statsMutex.unlock();

}

/*
 * Gathering statistic from moves vector (for example, amount of accepted deals) using threads and prints it to output file
 */
void StatisticCounter::gatherFromMoves() {
    threads.clear();
    for (size_t currentPart = 0; currentPart < ptrNumber; currentPart++) {
        threads.emplace_back(std::thread(&StatisticCounter::partedGather, this, parts[currentPart]));
    }

    for (auto& t : threads) {
        t.join();
    }

    out << "WS " << wasSold << "\n"; // WS = Was Sold
}

StatisticCounter::~StatisticCounter() {
    out.close();
}


/*
 * prints s1 if (type == SELLER) and s2 otherwise
 */
void StatisticCounter::switchedPrint(typeOfPlayer type, std::string s1, std::string s2) {
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
void StatisticCounter::gather(std::vector<Player*>* players, typeOfPlayer type) {
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
void StatisticCounter::gatherGain(std::vector<Player*>* players, typeOfPlayer type) {
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