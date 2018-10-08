#pragma once

class pmove {
private:
    int price;
    bool sold;
    pmove (int, bool);
public:
    int wasSold() const;
    int getPrice() const;
};
