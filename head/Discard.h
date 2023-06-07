#pragma once
#include "Card.h"
#include "..\exception\ShottenTottenException.h"

class DiscardException : public ShottenTottenException {
	using ShottenTottenException::ShottenTottenException;
};


class Discard{
private:
	const Card** cards;
	size_t size;
	size_t max_size;

	class DiscardIterator {
	private:
		const Card** cards;
		size_t indice;
	public:
		DiscardIterator(const Card** cards, size_t i) : cards(cards), indice(i) {};
		const Card* operator*() { return cards[indice]; }
		bool operator==(const DiscardIterator& other) const { return other.indice == indice; }
		bool operator!=(const DiscardIterator& other) const { return other.indice != indice; }

		DiscardIterator& operator++() {
			++indice;
			return *this;
		}
	};
public:
	Discard(): cards(nullptr),size(0),max_size(0) {}
	~Discard();
	void addCard(const Card& c);
	void withdrawCard(const Card& c);
	size_t getSize() const { return size; }
	size_t getMaxSize() const { return max_size; }
	const Card** getCards() const { return cards; }

	DiscardIterator begin() { return DiscardIterator(cards, 0); }
	DiscardIterator end() { return DiscardIterator(nullptr, size); }
};