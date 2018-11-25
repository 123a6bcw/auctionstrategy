#pragma once

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

#include <cstring>
#include <fstream>
#include "../../Player/include/Buyer.h"
#include "../../Player/include/Seller.h"

class StatisticCounter {
public:
    explicit StatisticCounter(std::string);
    
    void gather(size_t, const Seller*); // for example, gather info of what strategies player use
    void gather(size_t, const Buyer*);
    void newStep(size_t);
    void gather(size_t, size_t, const std::vector<pmove>*); // for example, amount of accepted deals
    ~StatisticCounter();
private:
    std::fstream out; //file there info is being writing to
    std::fstream status;
};
