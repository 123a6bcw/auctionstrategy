#include <thread>
#include "../include/StatisticCounter.h"

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

StatisticCounter::StatisticCounter(std::string s, size_t _ptrNumber, std::vector<std::vector<std::vector<pmove>>>* _moves) : ptrNumber(_ptrNumber), moves(_moves),
  parts(std::vector<std::vector<std::vector<std::vector<pmove>>*>>(ptrNumber, std::vector<std::vector<std::vector<pmove>>*>(0,
                                                                                                                    nullptr))) {
    out = std::fstream();
    out.open("../logs/" + s, std::fstream::out);
    if (!out.is_open()) {
        throw std::runtime_error("can't open log file");
    }

    sellersInThread = moves->size() / ptrNumber;
    createPartition();
}

void StatisticCounter::createPartition() {
    size_t currentPart = 0;
    for (size_t startSeller = 0; startSeller < moves->size(); startSeller += sellersInThread) {
        for (size_t seller = startSeller; seller < std::min(startSeller + sellersInThread, moves->size()); seller++) {
            parts[currentPart].push_back(&(*moves)[seller]);
        }

        currentPart++;
    }
}

/*
 * for example, gather info of what strategies player use
*/
void StatisticCounter::gather(size_t number, const Buyer* buyer) {
    // TODO
}

void StatisticCounter::gather(size_t number, const Seller* seller) {
    // TODO
}

void StatisticCounter::newStep(size_t i) {
    out << "CS " << i << "\n"; // CS means Current Cycle
    clean();
}

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

void StatisticCounter::clean() {
    wasSold = 0;
}

/*
 * for example, amount of accepted deals
 */
void StatisticCounter::gatherFromMoves() {
    std::vector<std::thread> threads(0);
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
