#pragma once
#include "Card.h"
#include "Deck.h"
#include "../exception/ShottenTottenException.h"
#include <iostream>

class HandException : public ShottenTottenException {
	ShottenTottenException::ShottenTottenException;
};

class HandIterator {
public:
	HandIterator(const Card** cards, size_t size) : cards(cards), size(size), i(0) {}
	bool operator!=(const HandIterator& other) const { return i != other.i; }
	const Card& operator*() const { return *cards[i]; }
	HandIterator& operator++() { ++i; return *this; }
private:
	const Card** cards;
	size_t size;
	size_t i;
};

class Hand{
private:
	const Card** cards;
	size_t size;
	size_t max_size;
public:
	Hand() : size(0), max_size(6) {
		const Card** c = {};
		cards = c;
	}
	Hand(const Card* c[6]) : cards(c), size(6), max_size(6) {}
	Hand(const Card** c, size_t n) : cards(c), size(n), max_size(6) {} // s'assurer que n <= 6
	void drawCards(Deck* d, int ncards) {
		const Card** c = new const Card* [ncards];
		for (int i = 0; i < ncards; i++) {
			c[i] = &(d->draw());
			std::cout << "\nDREW CARD : " << c[i]->getName();
		}
		cards = c;
	}
	void add(const Card& c);
	void remove(unsigned int i);
	void play(const Card& c); 

	HandIterator begin() const { return HandIterator(cards, size); }
	HandIterator end() const { return HandIterator(cards + size, size); }
};

