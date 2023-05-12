#pragma once
#include <string>
#include <iostream>
#include "Card.h"
#include "Game.h"
#include "../exception/ShottenTottenException.h"

using namespace std;

class Deck {
private :
	const Card** cards;
	unsigned int card_count;
	unsigned int max_card_count;

public :
	explicit Deck(const Game& g);
	~Deck();
	Deck(const Deck& p) = delete;
	Deck& operator=(const Deck& p) = delete;
	unsigned int getCardCount() const { return card_count; }
	unsigned int getMaxCardCount() const { return max_card_count; }
	bool isEmpty() const { return card_count == 0; }
	const Card& draw();
};