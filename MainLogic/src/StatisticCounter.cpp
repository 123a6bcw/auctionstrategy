#include "../include/StatisticCounter.h"

/*
 * class for gathering statistic of game. Writes it into log file with given name
 */

StatisticCounter::StatisticCounter(std::string s) {
    out = std::fstream();
    out.open(s, std::fstream::in);
}

/*
 * for example, gather info of what strategies player use
*/
void StatisticCounter::gather(const Buyer* buyer) {
    //TODO
}

void StatisticCounter::gather(const Seller* seller) {
    //TODO
}

/*
 * for example, amount of accepted deals
 */
void StatisticCounter::gather(const std::vector<pmove>& moves) {
    int totalCount = 0;
    
    for (auto x : moves) {
        totalCount += x.wasSold();
    }
    
    out << "Количество успешных сделок: " << totalCount << " из " << moves.size() << "\n";
}
