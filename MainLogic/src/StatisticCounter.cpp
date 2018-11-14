#include "../include/StatisticCounter.h"

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

StatisticCounter::StatisticCounter(std::string s) {
    out = std::fstream();
    out.open(s, std::fstream::out);
    if (!out.is_open()) {
        throw std::runtime_error("can't open log file");
    }
}

/*
 * for example, gather info of what strategies player use
*/
void StatisticCounter::gather(size_t number, const Buyer* buyer) {
    //TODO
}

void StatisticCounter::gather(size_t number, const Seller* seller) {
    //TODO
}

void StatisticCounter::newStep(size_t i) {
    out << "\n";
    out << "Cycle step: " << i << "\n\n";
}

/*
 * for example, amount of accepted deals
 */
void StatisticCounter::gather(size_t seller, size_t buyer, const std::vector<pmove>& moves) {
    int totalCount = 0;
    
    for (auto x : moves) {
        totalCount += x.wasSold();
    }

    out << "Game between seller " << seller << " and buyer " << buyer << "\n";
    out << "Amount of accepted deal: " << totalCount << " out of " << moves.size() << "\n\n";
}
