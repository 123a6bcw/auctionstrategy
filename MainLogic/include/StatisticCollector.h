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
#include "../../BasicStrategies/StrategiesController.h"

class StatisticCounter {
public:
    explicit StatisticCounter(std::string, size_t, std::vector<std::vector<std::vector<pmove>>>*, size_t);
    void gather(std::vector<Player*>, typeOfPlayer); // for example, gather info of what strategies player use
    void newStep(size_t); //initialisating statistic of new genetic cycle
    void gatherFromMoves(); // for example, amount of accepted deals
    void gatherGain(std::vector<Player*>, typeOfPlayer);
    void switchedPrint(typeOfPlayer, std::string, std::string);
    ~StatisticCounter();
private:
    void partedGather(const std::vector<std::vector<std::vector<pmove>>*>&);
    void createPartition();
    void clean();

    size_t ptrNumber; // number of threads
    std::fstream out; //file there info is being writing to
    std::mutex statsMutex; // mutex for threads cause they access private fields of this class
    std::vector<std::vector<std::vector<pmove>>>* moves; // pointer to moves from class GeneticCycle
    std::vector<std::vector<std::vector<std::vector<pmove>>*>> parts; // partition of sellers. See realisation
    size_t sellersInThread; // partition. See realisation.
    int wasSold; // number of accepted deals
    size_t movesInGame;
};
