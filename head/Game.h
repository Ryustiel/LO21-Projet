#pragma once
#include <string>
#include <iostream>
#include "Card.h"
#include "../exception/ShottenTottenException.h"
#include "Version.h"

class Controller;

using namespace std;

class Game {
private:
	Card** cards;
	unsigned int card_count;
public:
	Game(const Version& v);
	virtual ~Game();
	unsigned int getCardCount() const { return card_count; }
	const Card& getCard(unsigned int i) const;
};