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
    
    void gather(const Buyer*); // for example, gather info of what strategies player use
    void gather(const Seller*);
    void gather(const std::vector<pmove>&); // for example, amount of accepted deals
private:
    std::fstream out; //file there info is being writing to
};
