#pragma once
#include <iostream>
#include "../exception/ShottenTottenException.h"
#include "Hand.h"
#include "Board.h"

#include "../head/Utility.h"

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

    // s'utilise avec getScore pour gérer le score de victoire de manches du joueur
    void updateScore() { score++; }

    // initialisation du joueur pour la partie
    void initForNewGame() { 
        std::cout << "Player::initForNewGame()"<<endl;
        score = 0;
    }
    // initRound lancée à chaque début de Manche
    void initForNewRound(const Card** c, const size_t size) {
        std::cout << "Player::initForNewRound()" << endl;
        std::cout << "Hand initialised with " << size << " cards." << endl;
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
    int selectCard(bool* pickable) const;
    unsigned int selectStone(bool * pickable) const;
    unsigned int selectStoneForCombatMode(bool* pickable) const;
    unsigned int selectStoneForClaim(bool* pickable) const;
    void selectStoneAndCard(Side s, int& cardNb, int& stoneNb, bool* pickableStone) const;
    unsigned int selectDeck() const;
    bool WantClaimStone() const;
    int selectCardOnStone(Side s, unsigned int stone_nb) const;
    bool booleanChoice() const {
        return rand() % 2;
    }
};
