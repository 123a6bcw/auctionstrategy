#pragma once

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
 * class for storing
 */

class pmove {
private:
    int price;
    bool sold;
public:
    pmove() = delete;
    pmove(int pri, bool was) : price(pri), sold(was) {};
    int wasSold() const {
        return sold;
    }

    int getPrice() const {
        return price;
    }
};