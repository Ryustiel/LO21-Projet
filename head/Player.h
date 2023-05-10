#pragma once
#include "../exception/ShottenTottenException.h"
#include "Hand.h"

class Player {
private:
    std::string name;
    unsigned int id;
    unsigned int score = 0;
    Hand* hand = nullptr;
    friend class Controller;
public:
    const string& getName() const { return name; }
    unsigned int getId() const { return id; }
    unsigned int getScore() const { return score; }
    const Hand* getHand() const { return hand; }
    void setHand(const Card* c[6]) {
        if (hand == nullptr) hand = new Hand(c);
    }
    void setHand(const Card** c, size_t n) {
        if (hand == nullptr) hand = new Hand(c, n);
    }
protected :
    Player(const string& n, bool idPlayer)
        : name(n), id(idPlayer) {}
    ~Player() {
        delete hand;
    }
};

class PlayerAIRandom : public Player {
private:
    //
public:
    PlayerAIRandom(const string& n, bool idPlayer) : Player(n, idPlayer) {}
};
