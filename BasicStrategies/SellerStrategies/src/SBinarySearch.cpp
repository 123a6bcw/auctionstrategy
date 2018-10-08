#include "../include/SBinarySearch.h"

template <typename T>
T getMiddle(T a, T b) {
    return a + (b - a) / 2;
}

int SBinarySearch :: setPrice() {
    pmove lastMove = previousMoves.back();
    int middle = getMiddle(minValue, maxValie);
    if (lastMove.wasSold()) {
        minValue = middle - 1;
    } else {
        maxValue = middle;
    }
    
    middle = getMiddle(minValue, maxValue);
    return middle;
}

void BSimple::randomParametersChange() {
    
};
