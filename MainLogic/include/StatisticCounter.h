#pragma once

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

#include <cstring>
#include <iostream>
#include <fstream>
#include <mutex>
#include "../../Player/include/Buyer.h"
#include "../../Player/include/Seller.h"

class StatisticCounter {
public:
    explicit StatisticCounter(std::string, size_t, std::vector<std::vector<std::vector<pmove>>>*);
    
    void gather(size_t, const Seller*); // for example, gather info of what strategies player use
    void gather(size_t, const Buyer*);
    void newStep(size_t);
    void gatherFromMoves(); // for example, amount of accepted deals
    void partedGather(const std::vector<std::vector<std::vector<pmove>>*>&);
    ~StatisticCounter();
    void createPartition();
    void clean();
private:
    size_t ptrNumber;
    std::fstream out; //file there info is being writing to
    std::mutex statsMutex;
    std::vector<std::vector<std::vector<pmove>>>* moves;
    std::vector<std::vector<std::vector<std::vector<pmove>>*>> parts;
    size_t sellersInThread;
    int wasSold;
};
