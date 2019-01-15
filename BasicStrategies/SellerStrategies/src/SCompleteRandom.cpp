#include "../include/SCompleteRandom.h"
#include <iostream>
#include "../../../Player/include/Player.h"

#ifndef TOSTRING
#define STR(x) #x
#define TOSTRING(x) STR(x)
#endif

#define NAMEOFSTRATEGY SCompleteRandom

/*
* Constructor.
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(Player* player, size_t startMove, size_t endMove, int minValue, int maxValue):
SellerStrategyAbstract(player, startMove, endMove),
  minValue(minValue), maxValue(maxValue) {}

/*
* Copying;
*/
NAMEOFSTRATEGY::NAMEOFSTRATEGY(const NAMEOFSTRATEGY* anotherStrategy):
SellerStrategyAbstract(anotherStrategy),
minValue(anotherStrategy->minValue),
maxValue(anotherStrategy->maxValue)
{}

/*
* Set changing fields during playing one game to it's default values
* No parameteres need to reset
 */
void NAMEOFSTRATEGY::reset() {
}

/*
* Propose a deal to buyer.
*/
int NAMEOFSTRATEGY::setPrice() {
    return owner->randomNumberGenerator->getRandomNumber(minValue, maxValue);
}

/*
* Short description what does this strategy doing.
*/
std::string NAMEOFSTRATEGY::getDescription() {
    return "Propose absolutely random deal in given range";
}

/*
* Not quite sure yet that this function supposed to be doing. Something like slightly changing the parameters for genetic diversity.
* TODO: implement?
*/
void NAMEOFSTRATEGY::randomParametersChange() {
}

/*
* Descructor. Implement if neccessary
*/
NAMEOFSTRATEGY::~NAMEOFSTRATEGY() = default;

/*
* DON"T CHANGE
* Copying with changing owner
*/
StrategyAbstract* NAMEOFSTRATEGY::copy(Player* player) const {
    return (new NAMEOFSTRATEGY(this))->changeOwner(player);
}

/*
* DON"T CHANGE
* Returns the name of this class
*/
std::string NAMEOFSTRATEGY::getName() {
    return TOSTRING(NAMEOFSTRATEGY);
}

#undef NAMEOFSTRATEGY
