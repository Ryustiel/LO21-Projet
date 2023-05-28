#pragma once
#include <iostream>
#include "../exception/ShottenTottenException.h"
#include "Hand.h"
#include "Board.h"

class Player {
private:
    std::string name;
    Side side;
    unsigned int score = 0;
    Hand* hand = nullptr;

    friend class Controller;

public:
    const string& getName() const { return name; }
    unsigned int getScore() const { return score; }
    Hand* getHand() const { return hand; }

    virtual unsigned int selectCard() const {
        unsigned int card_nb = 0;
        cin >> card_nb;
        return card_nb;
    }

    virtual unsigned int selectStone() const {
        unsigned int stone_nb = 0;
        cin >> stone_nb;
        return stone_nb;
    }

    // s'utilise avec getScore pour gérer le score de victoire de manches du joueur
    void updateScore() { score++; }

    // initialisation du joueur pour la partie
    void initForNewGame() { 
        std::cout << "\nPlayer::initForNewGame()";
        score = 0;
    }
    // initRound lancée à chaque début de Manche
    void initForNewRound(const Card** c, const size_t size) {
        std::cout << "\nPlayer::initForNewRound()";
        std::cout << "\nHand initialised with " << size << " cards.";
        hand = new Hand(c, size);
        // set pick to None / -1
    }
    
protected :
    Player(const string& n, Side s)
        : name(n), side(s){
    }
    virtual ~Player() {
        delete hand;
    }
};

class PlayerAIRandom : public Player {
private:
    //
public:
    PlayerAIRandom(const string& n, Side s) : Player(n, s) {}
    virtual unsigned int selectCard() const;
    virtual unsigned int selectStone() const;
};
