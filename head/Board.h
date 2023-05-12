#pragma once
#include <iostream>

class Board {
private:
    bool won = false;
public:
    void setWon() { won = true; }
    bool isWon() { return won; }
    void init() { std::cout << "\nInitializing board"; won = false;}
};