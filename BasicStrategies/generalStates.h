#pragma once

#include <random>
#include <algorithm>
#include <vector>

/*
 * here will be defined often using functions for strategies (and classes).
 */


/*
 * get middle value between a and b
 */
template <typename T>
inline T getMiddle(T a, T b) {
    return a + (b - a) / 2;
}

/*
 * class for storing moves in game
 */

class pmove {
private:
    int price;
    bool sold;
public:
    pmove() : price(0), sold(false) {};
    pmove(int pri, bool was) : price(pri), sold(was) {};
    inline bool wasSold() const {
        return sold;
    }

    inline int getPrice() const {
        return price;
    }
};

class RandomNumberGenerator {
private:
    std::random_device rng;
    std::mt19937 urng;
    std::uniform_int_distribution<int> dist;
public:
    RandomNumberGenerator() = delete;
    explicit RandomNumberGenerator(size_t);
    inline int getRandomInt() {
        return dist(urng);
    }

    /*
     * gets int in range [minValue, maxValue] inclusive
     */
    inline size_t getRandomNumber(size_t minValue, size_t maxValue) {
        return minValue + static_cast<size_t>(dist(urng)) % (maxValue - minValue + 1);
    }

    template <typename T>
    inline T getRandomNumber(T minValue, T maxValue) {
        return minValue + dist(urng) % (maxValue - minValue + 1);
    }
    void shuffle(std::vector<int>&);
};