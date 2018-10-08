#pragma once

#include "../include/BSimple.h"

bool BSimple::acceptDeal(int price) {
    return price > profit;
}

void BSimple::randomParametersChange() {
};
