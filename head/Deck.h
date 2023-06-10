#pragma once
#include <string>
#include <iostream>
#include "Card.h"
#include "Game.h"
#include "../exception/ShottenTottenException.h"

using namespace std;

#include "Utility.h"

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
	const Card* getCard(unsigned int i) {
		if (i < 0 || i > card_count) throw ShottenTottenException("getCard : inadequate card number i");
		return cards[i];
	}

	bool isEmpty() const { return card_count == 0; }
	const Card& draw();
	void addCard(const Card& c);
	//permet de remplir un tableau et retourne combien de carte il a reussi à donner (si il y en a pas assez il en donne moins)
	const size_t drawMultiple(const Card** cards, const size_t number);
};