#pragma once
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"
#include "Board.h"
#include "Hand.h"



class Controller{
private:
	static Controller* instance;
	Deck* clan_deck;
	Deck* tactical_deck;
	Board* board;
	Hand* hand_j1;
	Hand* hand_j2;
public:
	Deck& getClanDeck();
	Deck& getTacticalDeck();
	Board& getBoard();
	Hand& getHand1();
	Hand& getHand2();
	Controller() = default;
	~Controller() = default;
	struct Handler {
		Controller* instance = nullptr;
		~Handler() { delete instance; }
	};
	static Handler handler;
	Controller(const Controller& j) = delete;
	Controller& operator=(const Controller& j) = delete;
	static const Controller& getInstance();
	void freeInstance();
};

