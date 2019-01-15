#pragma once

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

#include <cstring>
#include <iostream>
#include <fstream>
#include <mutex>
#include "PartedStatisticCollector.h"
#include "../../Player/include/Buyer.h"
#include "../../Player/include/Seller.h"
#include "../../BasicStrategies/StrategiesController.h"

class StatisticCollector {
public:
    std::mutex statsMutex; // mutex for threads cause they access private fields of this class
    PartedStatisticCollector partedStatisticCollector;

    explicit StatisticCollector(std::string, size_t, std::vector<std::vector<std::vector<pmove>>>*, size_t);
    void newStep(size_t); //initialisating statistic of new genetic cycle
    void gatherFromMoves(); // for example, amount of accepted deals
    void switchedPrint(typeOfPlayer, std::string, std::string); //TODO comment
    void gather(std::vector<Player*>*, typeOfPlayer); // for example, gather info of what strategies player use
    void gatherGain(std::vector<Player*>*, typeOfPlayer);
    ~StatisticCollector();
private:
    void clean();

    std::vector<std::thread> threads; //TODO comment
    size_t ptrNumber; // number of threads
    std::fstream out; //file there info is being writing to
    size_t movesInGame;
};
