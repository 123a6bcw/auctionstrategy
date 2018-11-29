#include "../include/StatisticCounter.h"

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

StatisticCounter::StatisticCounter(std::string s) {
    out = std::fstream();
    out.open("../logs/" + s, std::fstream::out);
    if (!out.is_open()) {
        throw std::runtime_error("can't open log file");
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
    out << "CS " << i << "\n";
    std::cout << i << "\n";
}

/*
 * for example, amount of accepted deals
 */
void StatisticCounter::gather(size_t seller, size_t buyer, const std::vector<pmove>* moves) {
    int totalCount = 0;
    
    for (auto x : *moves) {
        totalCount += x.wasSold();
    }

    out << "SB " << seller << " " << buyer << "\n";
    out << "ACD " << totalCount << " " << moves -> size() << "\n";
}

StatisticCounter::~StatisticCounter() {
    out.close();
}
