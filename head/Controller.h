#pragma once
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"


class Controller{
private:
	static Controller* instance;
  Deck* clan_deck;
  Deck* tactical_deck;
  Board* board;
  Hand* hand_j1;
  Hand* hand_j2;
public:
	static Controller& getInstance();
  Deck& getClanDeck();
  Deck& getTacticalDeck();
  Board& getBoard();
  Hand& getHand1();
  Hand& getHand2();
	void freeInstance();
};

