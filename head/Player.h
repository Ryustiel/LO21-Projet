#pragma once
#include <iostream>
#include "../exception/ShottenTottenException.h"
#include "Hand.h"

class Player {
private:
    std::string name;
    unsigned int score = 0;
    Hand* hand = nullptr;

    friend class Controller;

public:
    const string& getName() const { return name; }
    unsigned int getScore() const { return score; }
    const Hand* getHand() const { return hand; }
    void setHand(const Card* c[6]) {
        if (hand == nullptr) hand = new Hand(c);
    }

    void setHand(const Card** c, size_t n) {
        if (hand == nullptr) hand = new Hand(c, n);
    }

    // s'utilise avec getScore pour gérer le score de victoire de manches du joueur
    void updateScore() { score++; }

    // initialisation du joueur pour la partie
    void initForNewGame() { 
        std::cout << "\nPlayer::initForNewGame()";
        score = 0;
    }
    // initRound lancée à chaque début de Manche
    void initForNewRound() { 
        std::cout << "\nPlayer::initForNewRound()";
        // hand = new Hand(cards);
        // set pick to None / -1
    }

    void claimStone();
    
protected :
    Player(const string& n)
        : name(n) {}
    virtual ~Player() {
        delete hand;
    }
};

class PlayerAIRandom : public Player {
private:
    //
public:
    PlayerAIRandom(const string& n) : Player(n) {}
};
