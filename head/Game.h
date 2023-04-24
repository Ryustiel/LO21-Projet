#pragma once
#include "Card.h"

class Game{
private:
	static Game* instance;
	Clan* clanCards[clanCardsNumber];
	Tactical* tacticalCards[tacticalCardsNumber];
public:
	Game();
	Game(const Game& j) = delete;
	Game& operator= (const Game& j) = delete;
	static Game& getInstance();
	static void freeInstance();
};


