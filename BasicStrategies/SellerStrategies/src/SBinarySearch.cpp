#include "../include/SBinarySearch.h"

/*
Binary search on buyer profit. Assumes that buyer's profit is between minValue and maxValue. Proposes deal with the average value and change minValue and maxValue accordingly to the result of the deal.
*/

int SBinarySearch :: setPrice() {
    int middle = getMiddle(minValue, maxValue);

    if (owner -> getCurrentMove() > startMove) {
        pmove lastMove = owner -> getPreviousMoves() -> back();
        if (lastMove.wasSold()) {
            minValue = middle - 1;
        } else {
            maxValue = middle;
        }
    }    

    return middle;
}

void SBinarySearch::randomParametersChange() {
    //undefined
}
