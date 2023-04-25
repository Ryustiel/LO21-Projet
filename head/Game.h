#pragma once
#include <string>
#include <iostream>
#include "Card.h"

using namespace std;

class Game {
private:
	const Card** cards;
	unsigned int card_count;
public:
	Game(const string& version);
	~Game();
	unsigned int getCardCount() const { return card_count; }
	const Card& getCard(unsigned int i) const;
};