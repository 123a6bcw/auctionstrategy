#include "./generalStates.h"

pmove::pmove (int pri, bool was) : price(pri), sold(was) {}

int pmove::wasSold() const {
    return sold;
}

int pmove::getPrice() const {
    return price;
}
