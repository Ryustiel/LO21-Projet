#include "..\head\Discard.h"

Discard::~Discard() {
	delete[] cards;
}

void Discard::addCard(const Card& c) {
	if (size == max_size) {
		const Card** newTab = new const Card * [++max_size];
		for (size_t i = 0; i < size; ++i) {
			newTab[i] = cards[i];
		}
		delete[] cards;
		cards = newTab;
	}
	cards[size++] = &c;
	cout << "check";
}

void Discard::withdrawCard(const Card& c) {
	for (size_t i = 0; i < size; ++i) {
		if (cards[i] == &c) {
			for (size_t j = i; i < size-1; ++i) {
				cards[i] = cards[i + 1];
			}
			--size;
			return;
		}
	}
	throw DiscardException("Discard withdrawCard error : this cards isn't in the discard !");
}