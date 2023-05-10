#pragma once
#include "../exception/ShottenTottenException.h"
#include "Hand.h"

class Player {
    std::string name;
    unsigned int id;
    bool isAI;  //0 = non, 1 = oui
    unsigned int score = 0;
    Hand* hand = nullptr;
public:
    Player(const string& n, bool idPlayer, bool AI = 0)
        : name(n), id(idPlayer), isAI(AI) {}
    ~Player(); //suppr. main*
    const string& getName() const { return name; }
    unsigned int getId() const { return id; }
    bool getIsAI() const { return isAI; }
    unsigned int getScore() const { return score; }

};