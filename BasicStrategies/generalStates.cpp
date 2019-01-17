#include "./generalStates.h"

bool operator == (const pmove& a, const pmove& b) {
    return a.getPrice() == b.getPrice() && a.wasSold() == b.wasSold();
}

RandomNumberGenerator::RandomNumberGenerator(size_t seed) {
    urng = std::mt19937(rng());
    urng.seed(seed);
    dist = std::uniform_int_distribution<int>(0, std::numeric_limits<int>::max());
}

void RandomNumberGenerator::shuffle(std::vector<int>& v) {
    std::shuffle(v.begin(), v.end(), urng);
}