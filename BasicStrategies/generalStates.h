#pragma once

template <typename T>
inline T getMiddle(T a, T b) {
    return a + (b - a) / 2;
}

class pmove {
private:
    int price;
    bool sold;
public:
    pmove (int, bool);
    int wasSold() const;
    int getPrice() const;
};
