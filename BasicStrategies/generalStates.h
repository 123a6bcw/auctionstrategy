#pragma once

template <typename T>
T getMiddle(T a, T b) {
    return a + (b - a) / 2;
}

class pmove {
private:
    int price;
    bool sold;
    pmove (int, bool);
public:
    int wasSold() const;
    int getPrice() const;
};
