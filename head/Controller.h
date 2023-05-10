#pragma once
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"




class Controller{
private:
	Controller();
	~Controller();
	struct Handler {
		Controller* instance = nullptr;
		~Handler() { delete instance; }
	};
	static Handler handler;
	Controller(const Controller& j) = delete;
	Controller& operator=(const Controller& j) = delete;
public:
	static const Controller& getInstance();
	void freeInstance();
};

