#pragma once

//TODO comment
//TODO unused includes

#include <thread>
#include <mutex>
#include "../../Player/include/Buyer.h"
#include "../../Player/include/Seller.h"
#include "../../BasicStrategies/StrategiesController.h"

class PartedStatisticCollector {
public:
    explicit PartedStatisticCollector(size_t, std::vector<std::vector<std::vector<pmove>>>*, std::mutex*);
    std::mutex* statsMutex;
    size_t ptrNumber; // number of threads
    std::vector<std::vector<std::vector<std::vector<pmove>>*>> parts; // partition of sellers. See realisation
    size_t sellersInThread; // partition. See realisation.
    std::vector<std::vector<std::vector<pmove>>>* moves; // pointer to moves from class GeneticCycle

    void partedGather(const std::vector<std::vector<std::vector<pmove>>*>&);
    void clean();
    int wasSold; // number of accepted deals
};