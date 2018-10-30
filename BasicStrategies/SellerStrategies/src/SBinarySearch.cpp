#include "../include/SBinarySearch.h"

/*
Binary search on buyer profit. Assumes that buyer's profit is between minValue and maxValue. Proposes deal with the average value and change minValue and maxValue accordingly to the result of the deal.
*/

SBinarySearch(int _endMove, vector&<pmove> prevMoves): SellerStrategyAbstract(_endMove, prevMoves);

int SBinarySearch :: setPrice() {
    if (currentMove > startMove) {
        pmove lastMove = previousMoves.back();
        int middle = getMiddle(minValue, maxValie);
        if (lastMove.wasSold()) {
            minValue = middle - 1;
        } else {
            maxValue = middle;
        }
    }    
    middle = getMiddle(minValue, maxValue);
    return middle;
}

void BSimple::randomParametersChange() {
};
