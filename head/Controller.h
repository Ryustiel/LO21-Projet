#pragma once
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"




class Controller{
private:
	static Controller* instance;
public:
	static Controller& getInstance();
	void freeInstance();
};

