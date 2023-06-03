#pragma once
#include "Card.h"
#include "../exception/ShottenTottenException.h"

class Controller;

class HandException : public ShottenTottenException {
	ShottenTottenException::ShottenTottenException;
};

class Hand{
private:
	const Card** cards;
	size_t size;
	size_t max_size;

	class HandIterator {
	private:
		const Card** cards;
		size_t indice;
	public:
		HandIterator(const Card** cards, size_t i) : cards(cards), indice(i) {};
		const Card* operator*() { return cards[indice]; }
		bool operator==(const HandIterator& other) const { return other.indice == indice; }
		bool operator!=(const HandIterator& other) const { return other.indice != indice; }

		HandIterator& operator++() {
			++indice; 
			return *this;
		}
	};

public:
	Hand(const Card** c, size_t n) : cards(c), size(n), max_size(n) {}
	void add(const Card& c);
	void withdraw(const Card& c);
	void play(const Card& c); 
	size_t getSize() const { return size; }
	size_t getMaxSize() const { return max_size; }
	const Card* getCard(size_t i) const {
		if (i < 0 || i >= size) throw ShottenTottenException("get Card : incorrect card number i");
		return cards[i];
	}

	HandIterator begin() { return HandIterator(cards, 0); };
	HandIterator end() { return HandIterator(cards, size); }
};

