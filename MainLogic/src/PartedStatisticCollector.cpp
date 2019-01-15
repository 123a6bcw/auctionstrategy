//
// Created by mistafrosty on 15.01.19.
//

#include "../include/PartedStatisticCollector.h"

/*
 * from vector<vector<vector<pmove>>> moves creates new vector with size equal to number of threads. Each element is vector
 * with pointers to vector<vector<pmove>> aka moves[s] for s in range of this part.
 * That way we can create threads so they wouldn't had to access "moves" --- otherwise, several threads would access "moves" and, therefore, won't work in parallel
 */
PartedStatisticCollector::PartedStatisticCollector(size_t ptrNumber, std::vector<std::vector<std::vector<pmove>>>* moves, std::mutex* statsMutex):
statsMutex(statsMutex),
ptrNumber(ptrNumber),
parts(std::vector<std::vector<std::vector<std::vector<pmove>>*>>(ptrNumber, std::vector<std::vector<std::vector<pmove>>*>(0, nullptr))),
moves(moves)
{
    sellersInThread = moves->size() / ptrNumber;
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
 * Collecting all statistic from given part of moves and store result in fields of this class
 */
void PartedStatisticCollector::partedGather(const std::vector<std::vector<std::vector<pmove>>*>& partedMoves) {
    int newSold = 0;

    for (size_t seller = 0; seller < partedMoves.size(); seller++) {
        for (size_t buyer = 0; buyer < partedMoves[seller]->size(); buyer++) {
            for (auto &x : (*partedMoves[seller])[buyer]) {
                newSold += x.wasSold();
            }
        }
    }

    statsMutex->lock();
    wasSold += newSold;
    statsMutex->unlock();

}

void PartedStatisticCollector::clean() {
    wasSold = 0;
}